/** 
 * @file MasterDaemon.hpp
 * A daemon thread.
 * 
 * @author Zhifeng YANG
 * @date 2007-12-18
 */
#ifndef _MASTERDAEMON_HPP
#define _MASTERDAEMON_HPP 1

#include <IceUtil/Thread.h>
#include "master/MasterDB.hpp"
#include "util/Logger.hpp"

namespace mapreduce
{    
    class MasterDaemon: public IceUtil::Thread
    {
        /// the daemon wakes up every m_sleepSeconds seconds 
        int32_t m_sleepSeconds;
        /// pointer to master db
        MasterDB* m_db;
        /// logger
        Logger m_logger;

        /** 
         * reschedule the task after the worker fails
         * 
         * @param failedWorker
         */
        void rescheduleWorkerFails(const Address& failedWorker);
    public:
        MasterDaemon(int32_t sleepSeconds);
        /**
         * thread main function that awakes periodly. 
         * 
         */
        void run();
        /** 
         * whether the system is idel
         * 
         * 
         * @return 
         */
        bool isSystemIdel();
    };

    inline MasterDaemon::MasterDaemon(int32_t sleepSeconds)
        :m_sleepSeconds(sleepSeconds), m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }
    
}


#endif /* _MASTERDAEMON_HPP */
