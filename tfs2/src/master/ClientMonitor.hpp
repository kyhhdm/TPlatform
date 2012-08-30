/** 
 * @file ClientMonitor.hpp
 * This is a thread running periodly to remove expired clients.
 * 
 * @author Zhifeng YANG
 * @date 2007-07-17
 */
#ifndef _CLIENTMONITOR_HPP
#define _CLIENTMONITOR_HPP 1
#include <IceUtil/Thread.h>
#include "master/MasterDB.hpp"

namespace tfs
{    
    class ClientMonitor: public IceUtil::Thread
    {
        /// the monitor wakes up every m_sleepSeconds seconds 
        int32_t m_sleepSeconds;
        /// pointer to master db
        MasterDB* m_db;
        Logger m_logger;
    public:
        ClientMonitor(int32_t sleepSeconds);
        /**
         * thread main function that check heartbeat periodly. 
         * 
         */
        void run();
    };

    inline ClientMonitor::ClientMonitor(int32_t sleepSeconds)
        :m_sleepSeconds(sleepSeconds),m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }
    
}


#endif /* _CLIENTMONITOR_HPP */
