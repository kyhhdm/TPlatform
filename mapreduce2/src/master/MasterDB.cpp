/**
 * @file MasterDB.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/MasterDB.hpp"
#include "master/MasterConfig.hpp"
#include <cstdlib>
#include <ctime>
using namespace mapreduce;

MasterDB::MasterDB()
    :m_logger(Logger::getInstance("master")),
     m_workers(MasterConfig::WorkerExpiredSeconds, MasterConfig::SafeModeThreshold), 
     m_tfsFile(MasterConfig::TfsMasterHostname, MasterConfig::TfsMasterPort)
{
    // seed the rand()
    srand(time((time_t*)NULL));
}

MasterDB* MasterDB::instance()
{
    static MasterDB instance;
    return &instance;
}

int32_t MasterDB::cancelJob(int32_t jobId){
    // cancel the job
    Job job = this->m_jobs.getJob(jobId);
    if (job.first == -1){
        LOG4CPLUS_WARN(m_logger, "MasterDB::cancelJob() Job doesnot exist: " << jobId);
        return -1;
    }
    LOG4CPLUS_DEBUG(m_logger, "MasterDB::cancelJob() cancel job " << job);
    if (job.second.status == JS_INPROGRESS){
        // set the job status as abandoned
        this->m_jobs.setJobStatus(jobId, JS_CANCELLED);
        // set all the idle tasks as abandoned to prevent them from being assigned 
        this->m_tasks.setTasksCancelled(jobId);            

	    // release resources, add clean task
	    Addresses workers = this->m_workers.getAllWorkers();
	    for (int i = 0; i < workers.size(); i++){
            this->m_tasks.addCleanTask(jobId, workers[i]);
	    }

    } // endif
    return 0;
}
