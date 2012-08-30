/* 
 * @(#)ClientServiceImpl.cpp
 * AUTHOR: YangZhifeng
 * CREATED DATE: 22  5月 2007
 * DESCRIPTION: 
 */
#include "master/ClientServiceImpl.hpp"
#include "master/MasterConfig.hpp"
#include "common/IceGenerated.hpp"
#include "common/Exception.hpp"
#include <IceUtil/Mutex.h>
#include <cassert>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>
using namespace tfs;
using std::stringstream;
using std::ostream;

void ClientServiceImpl::open(const Address& client, const ::std::string& filename, ::Ice::Int openMode, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_OPEN]++;
    LOG4CPLUS_DEBUG(m_logger, "client " << client.name << ":" << client.port << " open file " << filename << " with openMode " << openMode);
    // register the client
    m_db->m_activeClients.renewHeartbeat(client);
    stringstream ssHolder;
    ssHolder << client.name << ":" << client.port;
    switch(openMode){
    case slice::FileOpenRead:
        m_db->m_dir.obtainLock(filename, ssHolder.str(), tfs::FsDirectory::READLOCK);
        break;
    case slice::FileOpenWrite:
        m_db->m_dir.obtainLock(filename, ssHolder.str(), tfs::FsDirectory::WRITELOCK);
        break;
    case slice::FileOpenAppend:
        m_db->m_dir.obtainLock(filename, ssHolder.str(), tfs::FsDirectory::READLOCK);
        break;
    default:
        LOG4CPLUS_FATAL(m_logger, "unknown openMode " << openMode);
        assert(false);
    }
    
}

void ClientServiceImpl::close(const Address& client, const ::std::string&filename, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_CLOSE]++;
    LOG4CPLUS_DEBUG(m_logger, "client " << client.name << ":" << client.port << " close file " << filename );

    stringstream ssHolder;
    ssHolder << client.name << ":" << client.port;
    m_db->m_dir.releaseLock(filename, ssHolder.str());                 
    // un-register the client if neccesary
    
}

LocatedChunks ClientServiceImpl::getChunksInfo(const Address& client, const ::std::string& filename, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_GET_CHUNKS_INFO]++;
    LOG4CPLUS_DEBUG(m_logger, "client " << client.name << " getChunksInfo of " << filename);
    const Chunks& Chunks = m_db->m_dir.getFileChunks(filename);
    LOG4CPLUS_DEBUG(m_logger, "file " << filename << " consists of " << (Chunks));
    
    return m_db->m_activeChunks.getLocatedChunks(Chunks);
}


LocatedChunk ClientServiceImpl::addChunk(const Address& client, const ::std::string&filename, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_ADD_CHUNK]++;
    LOG4CPLUS_DEBUG(m_logger, "client " << client.name << ":" << client.port << " add chunk for file " << filename );

    LocatedChunk lchk;
    // mdb->namespace->addChunk(filename)
    lchk.chk = m_db->m_dir.newChunk(filename, client.name);
    FileInfo fi = m_db->m_dir.getFileInfo(filename);
    lchk.locations = m_db->m_chunkServers.chooseBestChunkServers(fi.replication);
    
    // mdb->activeClient->addPendingChunk(client, filename, chunk)
    
    return lchk;
}

void ClientServiceImpl::completeWrittenChunk(const slice::LocatedChunk& lchk, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_COMPLETE_WRITTEN_CHUNK]++;
    LOG4CPLUS_DEBUG(m_logger, "complete witten chunk " << lchk.chk.id);

    m_db->m_dir.commitChunk(lchk.chk);
    m_db->m_activeChunks.add(lchk);
    m_db->m_chunkServers.add(lchk);

    
}

void ClientServiceImpl::updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Current&)
{
    m_db->m_statistics.m_operationsCount[OP_UPDATE_CHUNK_INFO]++;
    LOG4CPLUS_DEBUG(m_logger, "update chunk " << lchk.chk.id << " chunk size: " << lchk.chk.size);
    // may throw NoSuchChunk exception
    m_db->m_dir.updateChunk(lchk.chk);
}

void ClientServiceImpl::abandonAddChunk(const Chunk& chk, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_ABANDON_ADD_CHUNK]++;
    LOG4CPLUS_DEBUG(m_logger, "abandon chunk " << chk);
    
    m_db->m_dir.abandonChunk(chk);

    
}


void ClientServiceImpl::reportBadChunks(const LocatedChunks& lchks, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_REPORT_BAD_CHUNKS]++;
    LOG4CPLUS_DEBUG(m_logger, "report bad chunks ");

    // garbage collection
    m_db->m_gc.add(lchks);
    // make them not available to clients
    m_db->m_activeChunks.remove(lchks);
    // remove them from chunkserver manager
    m_db->m_chunkServers.remove(lchks);
    
    
}


void ClientServiceImpl::setReplication(const ::std::string& filename, ::Ice::Short replication, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_SET_REPLICATION]++;
    LOG4CPLUS_DEBUG(m_logger, "file " << filename << "replication set to " << replication);

    // check value
    if (replication < 0 || replication > MasterConfig::MaxReplication){
        LOG4CPLUS_WARN(m_logger, "replication " << replication <<" out of range");
        throw ReplicationOutOfRange("From ClientServiceImpl::setReplication");
    }
    // default value
    if (replication == 0){
        replication = MasterConfig::DefaultReplication;
    }

    // decrease or increase chunk replication
    int16_t oldReplication = m_db->m_dir.setReplication(filename, replication);
    if (oldReplication > replication) {
        // garbage collection
        const Chunks& chks = m_db->m_dir.getFileChunks(filename);
        LocatedChunks lchks = m_db->m_activeChunks.getLocatedChunks(chks);
        for (int i = 0; i < lchks.size(); i++){
            LocatedChunk lchk = lchks[i];
            Addresses chunkServers = m_db->m_chunkServers.chooseWorstChunkServers(lchk.locations, oldReplication - replication);
            lchk.locations = chunkServers;
            m_db->m_gc.add(lchk);
            m_db->m_activeChunks.remove(lchk);
            m_db->m_chunkServers.remove(lchk);
        }
    }
    else if (oldReplication < replication){
        // @todo chunk migration
        //m_chunkMigration.increaseReplication(filename, replication - oldReplication);
    }
    
}


FileInfo ClientServiceImpl::getFileInfo(const ::std::string& filename, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_GET_FILE_INFO]++;
    LOG4CPLUS_DEBUG(m_logger, "get info of file " << filename);
    
    // namespace->getFileInfo
    return m_db->m_dir.getFileInfo(filename);
}


void ClientServiceImpl::create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_CREATE]++;
    LOG4CPLUS_DEBUG(m_logger, "create file " << filename);

    if (chunkSize == 0){
        chunkSize = MasterConfig::DefaultMaxChunkSize;
    }
    if (replication == 0){
        replication = MasterConfig::DefaultReplication;
    }
    

    // check value
    if (replication < 0 || replication > MasterConfig::MaxReplication){
        LOG4CPLUS_WARN(m_logger, "replication " << replication <<" out of range");
        throw ReplicationOutOfRange("From ClientServiceImpl::create");
    }
    if (chunkSize < MasterConfig::MinMaxChunkSize || chunkSize > MasterConfig::MaxMaxChunkSize){
        LOG4CPLUS_WARN(m_logger, "chunkSize " << chunkSize <<" out of range");
        throw ChunkSizeOutOfRange("From ClientServiceImpl::create");
    }
    
    // namespace->createFile
    m_db->m_dir.createFile(filename, chunkSize, replication);
    
    
}


void ClientServiceImpl::mkdir(const ::std::string& name, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_MKDIR]++;
    LOG4CPLUS_DEBUG(m_logger, "create dir " << name);

    m_db->m_dir.createDir(name);
    
}

void ClientServiceImpl::rename(const ::std::string& src, const ::std::string&dst, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_RENAME]++;
    LOG4CPLUS_DEBUG(m_logger, "rename file from " << src << " to " << dst);
    m_db->m_dir.renameFile(src, dst);
    
}


void ClientServiceImpl::remove(const ::std::string& name, const ::Ice::Current& ) 
{
    m_db->m_statistics.m_operationsCount[OP_REMOVE]++;
    LOG4CPLUS_DEBUG(m_logger, "remove file " << name);
    // remove file from namespace
    Chunks chks;
    m_db->m_dir.deleteFile(name, chks);
    // get location of these chunks
    LocatedChunks lchks = m_db->m_activeChunks.getLocatedChunks(chks);

    // garbage collection
    m_db->m_gc.add(lchks);
    // make them not available to clients
    m_db->m_activeChunks.remove(lchks);
    // remove them from chunkserver manager
    m_db->m_chunkServers.remove(lchks);

    
}

void ClientServiceImpl::renamedir(const ::std::string& src, const ::std::string& dst, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_RENAME_DIR]++;
    LOG4CPLUS_DEBUG(m_logger, "rename dir from " << src << " to " << dst);
    m_db->m_dir.renameDir(src, dst);
    
}


void ClientServiceImpl::rmdir(const ::std::string& name, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_RMDIR]++;
    LOG4CPLUS_DEBUG(m_logger, "remove dir " << name);
    Chunks chks;
    
    //pb,deleteDir() changed.0904 only empty dir can be delete now
    //m_db->m_dir.deleteDir(name, chks);
    m_db->m_dir.deleteDir(name);
    
    return;

    // get location of these chunks
    LocatedChunks lchks = m_db->m_activeChunks.getLocatedChunks(chks);

    // garbage collection
    m_db->m_gc.add(lchks);
    // make them not available to clients
    m_db->m_activeChunks.remove(lchks);
    // remove them from chunkserver manager
    m_db->m_chunkServers.remove(lchks);

    
}


// bool ClientServiceImpl::exists(const ::std::string& name, const ::Ice::Current& )
// {
    
//     LOG4CPLUS_DEBUG(m_logger, "test existence of name " << name);
    
//     //#BUGFIX, should not return before getNDC().pop()
//     bool ret = m_db->m_dir.exists(name);
    
//     return ret;
// }


// bool ClientServiceImpl::isdir(const ::std::string& name, const ::Ice::Current& ) 
// {
    
//     LOG4CPLUS_DEBUG(m_logger, "test dir " << name);
    
//     return m_db->m_dir.isDir(name);
// }


FilesInfo ClientServiceImpl::lsdir(const ::std::string& dirname, const ::Ice::Current& )
{
    m_db->m_statistics.m_operationsCount[OP_LSDIR]++;
    LOG4CPLUS_DEBUG(m_logger, "list dir " << dirname);
    FilesInfoPtr fip = m_db->m_dir.readDir(dirname);
    FilesInfo fi(*fip);
    
    return fi;
}

// inline std::ostream& operator<< (std::ostream &os, const Strings& vs){
//   for (Strings::const_iterator it = vs.begin(); it != vs.end(); ++it){
//     os << *it << ":";
//   }
//   return os;
// }
void ClientServiceImpl::concatFiles(const Strings& srcFiles, const std::string &dst, const ::Ice::Current&)
{
    if (srcFiles.size() < 1){
        return;
    }
    
    m_db->m_statistics.m_operationsCount[OP_CONCAT]++;
    LOG4CPLUS_DEBUG(m_logger, "concat files to " << dst);
    
    m_db->m_dir.concatFiles(srcFiles, dst);

}

void ClientServiceImpl::reportHeartbeat(const Address& client, const ::Ice::Current& )
{
    
    //LOG4CPLUS_DEBUG(m_logger, "client " << client.name << ":" << client.port << " report heartbeat");
    // renew the heartbeat
    m_db->m_activeClients.renewHeartbeat(client);
    
}

