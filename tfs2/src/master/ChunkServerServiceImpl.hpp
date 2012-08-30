/** 
 * @file ChunkServerServiceImpl.hpp
 * Implementation of RPC interface ChunkServerService.
 * 
 * @author Zhifeng YANG
 * @date 31  5 2007
 */
#ifndef _CHUNKSERVERSERVICEIMPL_HPP
#define _CHUNKSERVERSERVICEIMPL_HPP 1
#include "ChunkServerService.h"
#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "master/MasterDB.hpp"
#include "util/Logger.hpp"
#include <string>

namespace tfs
{
    class ChunkServerServiceImpl: public tfs::slice::ChunkServerService
    {
    public:
        // constructor
        ChunkServerServiceImpl();

        /// RPC interface, @see ChunkServerService.ice
        void enroll(const Address& chunkServerAddress, const ::Ice::Current& = ::Ice::Current());
        MasterCommand sendHeartbeat(const Address& chunkServerAddress, const Heartbeat& hb, const ::Ice::Current& = ::Ice::Current());
        void chunkReport(const Address& chunkServerAddress, const Chunks& chks, const ::Ice::Current& = ::Ice::Current());
        void completeMigrateChunk(const LocatedChunk& lchk, const ::Ice::Current& = ::Ice::Current());
    private:
        MasterDB* m_db;
        Logger m_logger;
    };

    inline ChunkServerServiceImpl::ChunkServerServiceImpl()
        :m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }

}


#endif /* _CHUNKSERVERSERVICEIMPL_HPP */
