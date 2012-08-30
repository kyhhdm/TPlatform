/* 
 * @(#)ClientServiceImpl.hpp
 * AUTHOR: YangZhifeng
 * CREATE DATE: 22  5月 2007
 * DESCRIPTION: 
 */
/** @file ClientServiceImpl.hpp
 * the implementation of virtual class ClientService.
 * @author YangZhifeng
 * @date 22  5月 2007
 */
#ifndef _CLIENTSERVICEIMPL_HPP
#define _CLIENTSERVICEIMPL_HPP 1
#include "ClientService.h"
#include "master/MasterDB.hpp"
#include "common/IceGenerated.hpp"
#include "util/Logger.hpp"

namespace tfs
{
    class ClientServiceImpl:public ::tfs::slice::ClientService
    {
    public:
        // constructor
        ClientServiceImpl();

        // interface
        void open(const Address& client, const ::std::string&filename, ::Ice::Int openMode, const ::Ice::Current& );

        void close(const Address& client, const ::std::string&filename, const ::Ice::Current& );

        LocatedChunks getChunksInfo(const Address& client, const ::std::string& filename, const ::Ice::Current& );

        LocatedChunk addChunk(const Address& client, const ::std::string& filename, const ::Ice::Current& );

        void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Current& );

        void abandonAddChunk(const ::tfs::slice::Chunk& chk, const ::Ice::Current& );

        void updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Current&);

        void reportBadChunks(const ::tfs::LocatedChunks& lcks, const ::Ice::Current& ) ;

        void setReplication(const ::std::string& filename, ::Ice::Short replication, const ::Ice::Current& ) ;

        FileInfo getFileInfo(const ::std::string& filename, const ::Ice::Current& ) ;

        void create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize, const ::Ice::Current& ) ;

        void mkdir(const ::std::string& name, const ::Ice::Current& ) ;

        void rename(const ::std::string& src, const ::std::string&dst, const ::Ice::Current& ) ;

        void renamedir(const ::std::string& src, const ::std::string& dst, const ::Ice::Current& );

        void remove(const ::std::string& name, const ::Ice::Current& ) ;

        void rmdir(const ::std::string& name, const ::Ice::Current& );

        //bool exists(const ::std::string& name, const ::Ice::Current& ) ;

        //bool isdir(const ::std::string& name, const ::Ice::Current& ) ;

        FilesInfo lsdir(const ::std::string& dirname, const ::Ice::Current& ) ;

        void concatFiles(const Strings& srcFiles, const std::string &dst, const ::Ice::Current& );

        void reportHeartbeat(const Address& client, const ::Ice::Current& ) ;

    private:
        MasterDB* m_db;
        Logger m_logger;
    };

    inline ClientServiceImpl::ClientServiceImpl()
        :m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }
    
}



#endif /* _CLIENTSERVICEIMPL_HPP */
