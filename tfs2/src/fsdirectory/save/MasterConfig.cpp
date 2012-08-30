/**
 * @file MasterConfig.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-08-09
 */

#include "fsdirectory/MasterConfig.hpp"
#include "util/Config.hpp"
#include <iostream>
using namespace tfs;
using namespace std;


std::string MasterConfig::LogFilename("tfs_master.log");
std::string MasterConfig::JournalFilePathName("tfs_journal/");
int32_t MasterConfig::ServicePort = 10000;
Short MasterConfig::MaxReplication = 5;
Short MasterConfig::DefaultReplication = 3;
Long MasterConfig::DefaultMaxChunkSize = (64*1024*1024); // 64 megabytes
Long MasterConfig::MinMaxChunkSize = (1024*1024); // 1 megabytes
Long MasterConfig::MaxMaxChunkSize = (128*1024*1024); // 128 megabytes
int32_t MasterConfig::ClientMonitorSleepSeconds = 30;
int32_t MasterConfig::ClientExpiredSeconds = 15;
int32_t MasterConfig::ChunkServerMonitorSleepSeconds = 30;
int32_t MasterConfig::ChunkServerExpiredSeconds = 15;
int32_t MasterConfig::MasterDaemonSleepHours=2;
Short MasterConfig::DefaultFileModeMask = 0666;
LogLevel MasterConfig::RuntimeLogLevel = ALL_LOG_LEVEL;

bool MasterConfig::load(const char* szConfigFile)
{
    Config conf;
    if (!conf.load(szConfigFile)){
        return false;
    }
    conf.setSection("master");
    if (conf.exists("log")){
        LogFilename = conf.getStringValue("log");
    }
    if (conf.exists("log_level")){
        std::string logLevel = conf.getStringValue("log_level");
        if (logLevel == "FATAL"){
            RuntimeLogLevel = FATAL_LOG_LEVEL;
        }
        else if (logLevel == "ERROR"){
            RuntimeLogLevel = FATAL_LOG_LEVEL;
        }
        else if (logLevel == "WARN"){
            RuntimeLogLevel = WARN_LOG_LEVEL;
        }
        else if (logLevel == "INFO"){
            RuntimeLogLevel = INFO_LOG_LEVEL;
        }
        else if (logLevel == "DEBUG"){
            RuntimeLogLevel = DEBUG_LOG_LEVEL;
        }
        else if (logLevel == "TRACE"){
            RuntimeLogLevel = TRACE_LOG_LEVEL;
        }
        else {
            cerr << "Warning: unknown log level set in the configuration file, use ALL_LOG_LEVEL" << endl;
        }
        
    }
    if (conf.exists("journal_path")){
        JournalFilePathName = conf.getStringValue("journal_path");
    }
    if (conf.exists("port")){
        ServicePort = conf.getIntValue("port");
    }
    if (conf.exists("max_replication")){
    MaxReplication = conf.getIntValue("max_replication");
    }
    if (conf.exists("default_replication")){
        DefaultReplication = conf.getIntValue("default_replication");
    }
    if (conf.exists("default_max_chunk_size")){
        DefaultMaxChunkSize = conf.getIntValue("default_max_chunk_size");
    }
    if (conf.exists("min_max_chunk_size")){
        MinMaxChunkSize = conf.getIntValue("min_max_chunk_size");
    }
    if (conf.exists("max_max_chunk_size")){
        MaxMaxChunkSize = conf.getIntValue("max_max_chunk_size");
    }
    if (conf.exists("client_monitor_sleep_seconds")){
        ClientMonitorSleepSeconds = conf.getIntValue("client_monitor_sleep_seconds");
    }
    if (conf.exists("client_expired_seconds")){
        ClientExpiredSeconds = conf.getIntValue("client_expired_seconds");
    }
    if (conf.exists("chunkserver_monitor_sleep_seconds")){
        ChunkServerMonitorSleepSeconds = conf.getIntValue("chunkserver_monitor_sleep_seconds");
    }
    if (conf.exists("chunkserver_expired_seconds")){
        ChunkServerExpiredSeconds = conf.getIntValue("chunkserver_expired_seconds");
    }

    return true;
}
