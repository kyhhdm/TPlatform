/** 
 * @file ChunkServerMonitor.hpp
 * This is a thread running periodly to remove expired clients.
 * 
 * @author Zhifeng YANG
 * @date 2007-08-08
 */
#ifndef _CHUNKSERVERMONITOR_HPP
#define _CHUNKSERVERMONITOR_HPP 1

#include <IceUtil/Thread.h>
#include "master/MasterDB.hpp"

namespace tfs
{    
    class ChunkServerMonitor: public IceUtil::Thread
    {
        /// the monitor wakes up every m_sleepSeconds seconds 
        int32_t m_sleepSeconds;
        /// pointer to master db
        MasterDB* m_db;
    public:
        ChunkServerMonitor(int32_t sleepSeconds);
        /**
         * thread main function that check heartbeat periodly. 
         * 
         */
        void run();
    };

    inline ChunkServerMonitor::ChunkServerMonitor(int32_t sleepSeconds)
        :m_sleepSeconds(sleepSeconds)
    {
        m_db = MasterDB::instance();
    }
    
}


#endif /* _CHUNKSERVERMONITOR_HPP */
