/** 
 * @file MasterDaemon.hpp
 * Daemon woke up periodly to check system consistency and do some job.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-07
 */
#ifndef _MASTERDAEMON_HPP
#define _MASTERDAEMON_HPP 1

#include <IceUtil/Thread.h>
#include "master/MasterDB.hpp"
#include "util/Logger.hpp"

namespace tfs
{    
    class MasterDaemon: public IceUtil::Thread
    {
        /// the daemon wakes up every m_sleepSeconds seconds 
        int32_t m_sleepSeconds;
        /// pointer to master db
        MasterDB* m_db;
        /// logger
        Logger m_logger;

    public:
        MasterDaemon(int32_t sleepHours);
        /**
         * thread main function that check heartbeat periodly. 
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

    inline MasterDaemon::MasterDaemon(int32_t sleepHours)
        :m_sleepSeconds(60*60*sleepHours), m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }
    
}


#endif /* _MASTERDAEMON_HPP */
