/**
 * @file MasterConfig.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/MasterConfig.hpp"
#include "util/Config.hpp"
#include <iostream>
using namespace mapreduce;
using namespace std;

// default config values
string MasterConfig::LogFilename("mapred_master.log");
string MasterConfig::TfsMasterHostname("127.0.0.1");
int32_t MasterConfig::TfsMasterPort = 10000;
int32_t MasterConfig::ServicePort = 20000;
int32_t MasterConfig::WorkerExpiredSeconds = 60;
LogLevel MasterConfig::RuntimeLogLevel = ALL_LOG_LEVEL;
int32_t MasterConfig::MasterDaemonSleepSeconds = 20;
int32_t MasterConfig::MaxReduceTaskNumPerJob = 40;
int32_t MasterConfig::MinReduceTaskNumPerJob = 1;
int32_t MasterConfig::TaskMaxAbandonCount = 5;
int32_t MasterConfig::MaxActiveTaskNumPerWorker = 3;      // we have 4 CPUs per worker
int32_t MasterConfig::MaxActiveTransTaskNumPerWorker = 5; // we have 1 network interface used
int32_t MasterConfig::SafeModeThreshold = 1;

bool MasterConfig::load(const char* szConfigFile)
{
    Config conf;
    if (!conf.load(szConfigFile)){
        return false;
    }
    conf.setSection("master");
    if (conf.exists("log_file")){
        LogFilename = conf.getStringValue("log_file");
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
    if (conf.exists("tfs_master_hostname")){
        TfsMasterHostname = conf.getStringValue("tfs_master_hostname");
    }
    if (conf.exists("tfs_master_port")){
        TfsMasterPort = conf.getIntValue("tfs_master_port");
    }
    if (conf.exists("service_port")){
        ServicePort = conf.getIntValue("service_port");
    }
    if (conf.exists("worker_expired_seconds")){
        WorkerExpiredSeconds = conf.getIntValue("worker_expired_seconds");
    }
    if (conf.exists("master_daemon_sleep_seconds")){
        MasterDaemonSleepSeconds = conf.getIntValue("master_daemon_sleep_seconds");
    }
    if (conf.exists("max_reduce_task_num_per_job")){
        MaxReduceTaskNumPerJob = conf.getIntValue("max_reduce_task_num_per_job");
    }
    if (conf.exists("min_reduce_task_num_per_job")){
        MinReduceTaskNumPerJob = conf.getIntValue("min_reduce_task_num_per_job");
    }
    if (conf.exists("task_max_abandon_count")){
        TaskMaxAbandonCount = conf.getIntValue("task_max_abandon_count");
    }
    if (conf.exists("max_active_task_num_per_worker")){
        MaxActiveTaskNumPerWorker = conf.getIntValue("max_active_task_num_per_worker");
    }
    if (conf.exists("max_active_trans_task_num_per_worker")){
        MaxActiveTransTaskNumPerWorker = conf.getIntValue("max_active_trans_task_num_per_worker");
    }
    if (conf.exists("safe_mode_threshold")){
        SafeModeThreshold = conf.getIntValue("safe_mode_threshold");
    }

    return true;
}

void MasterConfig::print(ostream & os)
{
    os << "log_file=" << LogFilename << " ";
    os << "log_level=" << RuntimeLogLevel << " ";
    os << "tfs_master_hostname=" << TfsMasterHostname << " ";    
    os << "tfs_master_port=" << TfsMasterPort << " ";
    os << "service_port=" << ServicePort << " ";
    os << "worker_expired_seconds=" << WorkerExpiredSeconds << " " ;
    os << "master_daemon_sleep_seconds=" << MasterDaemonSleepSeconds << " ";
    os << "max_reduce_task_num_per_job=" << MaxReduceTaskNumPerJob << " ";
    os << "min_reduce_task_num_per_job=" << MinReduceTaskNumPerJob << " ";
    os << "task_max_abandon_count=" << TaskMaxAbandonCount << " ";
    os << "max_active_task_num_per_worker=" << MaxActiveTaskNumPerWorker << " ";
    os << "max_active_trans_task_num_per_worker=" << MaxActiveTransTaskNumPerWorker << " ";
    os << "safe_mode_threshold=" << SafeModeThreshold << " ";
}
