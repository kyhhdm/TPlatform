/** 
 * @file MasterConfig.hpp
 * master configurations.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _MASTERCONFIG_HPP
#define _MASTERCONFIG_HPP 1

#include "common/Types.hpp"
#include "util/Logger.hpp"
#include <iostream>

namespace mapreduce{
    class MasterConfig
    {
    public:
        static std::string TfsMasterHostname;
        static int32_t TfsMasterPort;
        
        static std::string LogFilename;
        static int32_t ServicePort;
        
        static int32_t WorkerExpiredSeconds;
        /// @see <log4cplus/loglevel.h> for LogLevel values
        static LogLevel RuntimeLogLevel;

        static int32_t MasterDaemonSleepSeconds;

        static int32_t MaxReduceTaskNumPerJob;
        static int32_t MinReduceTaskNumPerJob;
        /// if a task is abandoned more than TaskMaxAbandonCount times, the whole job will be abandoned
        static int32_t TaskMaxAbandonCount;
        static int32_t MaxActiveTaskNumPerWorker;
        static int32_t MaxActiveTransTaskNumPerWorker;
        static int32_t SafeModeThreshold;

        /** 
         * load config from config file
         * 
         * @param szConfigFile 
         * 
         * @return
         */
        static bool load(const char* szConfigFile);
        /** 
         * print the config parameters into the stream
         * 
         * @param os 
         */
        static void print(std::ostream & os);
    };
}



#endif /* _MASTERCONFIG_HPP */
