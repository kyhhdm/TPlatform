/**
 * @file FsDirectory.cpp
 * Implementation of FileSystem Directory Service Interface.
 * 
 * @author Peng Bo
 * @date 2007-08-26
 */

#include "fsdirectory/FsDirectory.hpp"
#include "fsdirectory/FsDirectoryImpl.hpp"
#include "fsdirectory/FsJournalManager.hpp"
#include "common/Exception.hpp"
#include <deque>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace tfs;


FsDirectory::FsDirectory(FsJournalManager* pFsJournal)
{
    assert(pFsJournal != NULL);

    m_pFsJournal = pFsJournal;

    m_pDirectory = m_pFsJournal->getFsDirectoryInstance();
    
    m_dirty = 0;    
}

FsDirectory::FsDirectory()
{
    m_pDirectory = new FsDirectoryImpl();
    m_pFsJournal = NULL;
    m_dirty = 0;    
}

FsDirectory::~FsDirectory()
{
    if(m_pDirectory) delete m_pDirectory;
}

bool FsDirectory::exists(const std::string &name)
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    return m_pDirectory->exists(name);
}

bool FsDirectory::isDir(const std::string& dirName) const
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    return m_pDirectory->isDir(dirName);
}


void FsDirectory::createFile(const std::string& filename, int maxChunkSize, short replication)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->createFile(filename, maxChunkSize, replication);
    if(m_pFsJournal) m_pFsJournal->logCreateFile(filename, maxChunkSize, replication);

    m_dirty++;    
}

void FsDirectory::renameFile(const std::string& src, const std::string& dst)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);

    m_pDirectory->renameFile(src, dst);

    if(m_pFsJournal) m_pFsJournal->logRenameFile(src, dst);
    m_dirty++;    
}

void FsDirectory::deleteFile(const std::string& filename, Chunks& deletedChunks)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->deleteFile(filename, deletedChunks);

    if(m_pFsJournal) m_pFsJournal->logDeleteFile(filename);
    m_dirty++;    
}

void FsDirectory::concatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->concatFiles(srcFiles, dstFile);

    if(m_pFsJournal) m_pFsJournal->logConcatFiles(srcFiles, dstFile);
    m_dirty++;    
}

void FsDirectory::createDir(const std::string& dirname)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->createDir(dirname);

    if(m_pFsJournal) m_pFsJournal->logCreateDir(dirname);
    m_dirty++;    

}

void FsDirectory::renameDir(const std::string& src, const std::string& dst)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->renameDir(src, dst);

    if(m_pFsJournal) m_pFsJournal->logRenameDir(src, dst);
    m_dirty++;    

}

void FsDirectory::deleteDir(const std::string& dirName)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->deleteDir(dirName);

    if(m_pFsJournal) m_pFsJournal->logDeleteDir(dirName);
    m_dirty++;    

}

FileInfo FsDirectory::getFileInfo(const std::string& filename) const
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    FileInfo info = m_pDirectory->getFileInfo(filename);

    return info;
}

FilesInfoPtr FsDirectory::readDir(const std::string& dirname) const
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    FilesInfoPtr pFileInfo = m_pDirectory->readDir(dirname);
    
    return pFileInfo;
}

const Chunk* FsDirectory::findChunk(const Long chunkId)
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    const Chunk* pChunk = m_pDirectory->findChunk(chunkId);
    return pChunk;
}

bool FsDirectory::updateChunk(const Chunk& chunk)
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    bool ret = m_pDirectory->updateChunk(chunk);

    if(m_pFsJournal) m_pFsJournal->logUpdateChunk(chunk);
    if(ret) m_dirty++;    

    return ret;
}

Chunk FsDirectory::newChunk(const std::string& filename, const std::string& holder)
{
    //#TODO -- Can getFileChunks and xxxChunk operate concurrently?
    // directory has a rwmutex, controling access on it's tree structure. 
    // inode need a mutex, controling access on it's data, especailly chunks data.
    // chunktable, newchunktable, need another mutex ???
    //
    //  NewChunk(){
    //      RWRecMutex::RLock lock(m_dirRwMutex);   //read directory 
    //      Mutex::Lock lock2(m_chunkTableMutex);   //write chunkTable and newchunktable;
    //  }
    //  CommitChunk(){
    //      RWRecMutex::RLock lock(m_dirRwMutex);   //read directory 
    //      Mutex::Lock lock2(m_chunkTableMutex);   //write chunkTable and newchunktable;
    //      RWRecMutex::WLock lock3(m_inodeMutex);  //write inode, associate with filename
    //  }
    //  getFileChunks(){
    //      RWRecMutex::RLock lock(m_dirRwMutex);   //read directory 
    //      RWRecMutex::RLock lock3(m_inodeMutex);  //read inode
    //  }
    //
    //
    // Another question is , concurrent operation may break Journaling sequence,
    // is that ok?
    //
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    Chunk chunk = m_pDirectory->newChunk(filename, holder);

    if(m_pFsJournal) m_pFsJournal->logNewChunk(filename, holder, chunk.id);
    m_dirty++;    
    return chunk;
}

void FsDirectory::commitChunk(const Chunk& chunk)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->commitChunk(chunk);
    if(m_pFsJournal) m_pFsJournal->logCommitChunk(chunk);
    m_dirty++;    

}

void FsDirectory::abandonChunk(const Chunk& chunk)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    m_pDirectory->abandonChunk(chunk);

    if(m_pFsJournal) m_pFsJournal->logAbandonChunk(chunk);
    m_dirty++;    
}
        
//bool updateChunk(const Chunk& chunk)

const Chunks& FsDirectory::getFileChunks(const std::string& filename) const
{
    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);
    const Chunks& chunks = m_pDirectory->getFileChunks(filename);

    return chunks;
}


void FsDirectory::setFileInfo(const std::string& filename, const FileInfo& info)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    //TODO,

    if(m_pFsJournal) m_pFsJournal->logSetFileInfo(filename, info);
    m_dirty++;    
}

Short FsDirectory::setReplication(const std::string& filename, Short replication)
{
    IceUtil::RWRecMutex::WLock lock(m_dirRwMutex);
    Short ret = m_pDirectory->setReplication(filename, replication);
    if(m_pFsJournal) m_pFsJournal->logSetReplication(filename, replication);
    m_dirty++;    
    return ret;
}
        

void FsDirectory::obtainLock(const std::string& filename, const std::string& holder, LockType lockType)
{
    UNUSED(filename);
    UNUSED(holder);
    UNUSED(lockType);

    //TODO,
}

void FsDirectory::releaseLock(const std::string& filename, const std::string& holder)
{
    UNUSED(filename);
    UNUSED(holder);
    
    
    //TODO,
}

        
void FsDirectory::releaseResource(const std::string& holder)
{
    UNUSED(holder);
    //TODO,
}


void FsDirectory::createCheckPoint()
{
    if(m_dirty == 0) return;

    IceUtil::RWRecMutex::RLock lock(m_dirRwMutex);    
    if(m_pFsJournal) m_pFsJournal->createCheckPoint();
    m_dirty = 0;    

}
