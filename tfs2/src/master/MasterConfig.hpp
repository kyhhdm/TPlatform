/** 
 * @file MasterConfig.hpp
 * configuration of master.
 * 
 * @author Zhifeng YANG
 * @date 2007-08-09
 */
#ifndef _MASTERCONFIG_HPP
#define _MASTERCONFIG_HPP 1
#include "common/Types.hpp"
#include "util/Logger.hpp"

namespace tfs{
    class MasterConfig
    {
    public:
        static Short MaxReplication;
        static Short DefaultReplication;
        static Long MinMaxChunkSize;
        static Long MaxMaxChunkSize;
        static Long DefaultMaxChunkSize;
        static std::string LogFilename;
        static int32_t ServicePort;
        static int32_t ClientMonitorSleepSeconds;
        static int32_t ClientExpiredSeconds;
        static int32_t ChunkServerMonitorSleepSeconds;
        static int32_t ChunkServerExpiredSeconds;
        static int32_t MasterDaemonSleepHours;
        
        static std::string JournalFilePathName;
        static Short DefaultFileModeMask;
        /// @see <log4cplus/loglevel.h> for LogLevel values
        static LogLevel RuntimeLogLevel;

        /** 
         * load config from config file
         * 
         * @param szConfigFile 
         * 
         * @return 
         */
        static bool load(const char* szConfigFile);
    };
}


#endif /* _MASTERCONFIG_HPP */
