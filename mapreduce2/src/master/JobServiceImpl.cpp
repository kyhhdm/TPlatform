/**
 * @file JobServiceImpl.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/JobServiceImpl.hpp"
#include "master/MasterConfig.hpp"
#include "master/MasterException.hpp"
#include "master/WorkerManager.hpp"
#include <IceUtil/Mutex.h>
#include <IceUtil/Monitor.h>
#include <vector>
using namespace std;
using namespace mapreduce;
using namespace tfs::api;
using namespace tfs::mapred;

int32_t JobServiceImpl::create(const MapReduceJob& job, const Ice::Current&)
{
    if (m_db->m_workers.isSafeMode()){
        ///@todo throw SafeModeException
        LOG4CPLUS_DEBUG(m_logger, "JobServiceImpl::create() We are in safe mode");
        return -1;
    }
    // we do not assign task when in safe mode
    WorkerManager::ToggleSafeMode safeMode(m_db->m_workers);

    // get chunks info of the input file(s)
    LocatedChunks allLocatedChunks;
    try{
        vector<string> names;
        
        FilesInfo files;
        
        FileInfo fileinfo = m_db->m_tfs.getFileInfo(job.inputFile);
        if (fileinfo.flag & FileModeTypeDir){
            // the input is a dir
            files = m_db->m_tfs.listDirectory(job.inputFile);
            string dir = job.inputFile;
            
            if (dir[dir.size() - 1] != '/')
            {
                dir += '/';
            }
            for (int i = 0; i < files.size(); i++){
                names.push_back(dir + files[i].name);
            }
        }
        else{
            // the input is a file
            names.push_back(job.inputFile);
        }
        
        for (int i = 0; i < names.size(); i++){
            // for each file in the dir
            LocatedChunks lchks = m_db->m_tfsFile.getChunksInfo(names[i]);
            allLocatedChunks.insert(allLocatedChunks.begin(), lchks.begin(), lchks.end());
            LOG4CPLUS_DEBUG(m_logger, "Input file " << i+1 << " " << names[i] << " has " << lchks.size() << " chunks");
        }
        
        LOG4CPLUS_DEBUG(m_logger, "Input file(s) " << job.inputFile << " totally has " << allLocatedChunks.size() << " chunks");

        if (allLocatedChunks.empty()){
            LOG4CPLUS_WARN(m_logger, "JobServiceImpl::create() TFS file or dir" << job.inputFile << " doesn't exist or has no chunks");
            return -1;
        }
        
    }catch(std::exception &ex){
        LOG4CPLUS_WARN(m_logger, "JobServiceImpl::create() catch " << ex.what());
        return -1;
    }
    catch(...){
        LOG4CPLUS_WARN(m_logger, "JobServiceImpl::create(): Unknown tfs exception!!!");
        return -1;
    }    
    
    // create output dir if necessary
    try{
        if (!m_db->m_tfs.existDirectory(job.outputFile)){
            m_db->m_tfs.createDirectory(job.outputFile);
        }
    }
    catch(std::exception &ex){
        LOG4CPLUS_WARN(m_logger, "JobServiceImpl::create() catch " << ex.what());
        return -1;
    }

    MapReduceJob jobSpec(job);
    // we assign each chunk a map task
    jobSpec.mapTaskNum = allLocatedChunks.size();
    // the number of reduce tasks is less than the number of workers or too large
    if (jobSpec.reduceTaskNum < MasterConfig::MinReduceTaskNumPerJob){
        jobSpec.reduceTaskNum = MasterConfig::MinReduceTaskNumPerJob;
    }
    else if (jobSpec.reduceTaskNum > MasterConfig::MaxReduceTaskNumPerJob){
        jobSpec.reduceTaskNum = MasterConfig::MaxReduceTaskNumPerJob;
    }
    int32_t jobId = m_db->m_jobs.add(jobSpec, allLocatedChunks);
    LOG4CPLUS_INFO(m_logger, "Create job for " << jobSpec);
    
    // add map tasks
    vector<int32_t> mapTaskIds;
    try{
    for (int i = 0; i < allLocatedChunks.size(); i++){
        Address address;
        Addresses candidates;
        for (int j = 0; j < allLocatedChunks[i].locations.size(); j++){
            address.name = allLocatedChunks[i].locations[j].name;
            address.port = allLocatedChunks[i].locations[j].port;
            candidates.push_back(address);
        }
        Address worker = m_db->m_workers.selectWorker(candidates);
        int32_t taskId = m_db->m_tasks.addMapTask(jobId, i, worker);
        mapTaskIds.push_back(taskId);
    }
    }catch (SafeModeException &ex){
        LOG4CPLUS_WARN(m_logger, "JobServiceImpl::create() catch " << ex.what());
        m_db->cancelJob(jobId);
        return -1;
    }

    // add reduce tasks
    Addresses workers = m_db->m_workers.getAllWorkers();
    for (int i = 0; i < jobSpec.reduceTaskNum; i++){
        LOG4CPLUS_DEBUG(m_logger, " reduceTask worker " << workers[i%workers.size()] << " "<< i << " "<< workers.size() );
        int32_t reduceTaskId = m_db->m_tasks.addReduceTask(jobId, i, workers[i%workers.size()]);
        // add trans tasks
        for (int j = 0; j < mapTaskIds.size(); j++){
            m_db->m_tasks.addTransTask(jobId, mapTaskIds[j], reduceTaskId);
        }
    }
    
    // @add by Chen Rishan
    // add job schedule infomation in workermanager
    
//     Tasks tasks = m_db->m_tasks.getAllTasks(jobId);
//     Job waitingJob = m_db->m_jobs.getJob(jobId);
//     JobPriority jobPrio = waitingJob.second.jobInitPriority;
//     m_db->m_workers.setJobPriority(tasks, jobPrio);
    
    LOG4CPLUS_INFO(m_logger, "Created job " << jobId);
    return jobId;
}

// int32_t JobServiceImpl::wait(int32_t jobId, const Ice::Current&)
// {
//     Job job = m_db->m_jobs.getJob(jobId);
//     if (job.first == -1){
//         LOG4CPLUS_WARN(m_logger, "JobServiceImpl::wait() job doesnot exist: " << jobId);
//         return -1;
//     }
//     if (job.second.bDetached){
//         LOG4CPLUS_WARN(m_logger, "JobServiceImpl::wait() job has been detached: " << jobId);
//         return -1;
//     }
//     LOG4CPLUS_DEBUG(m_logger, "JobServiceImpl::wait() Waiting job " << jobId);
//     // wait if the job is not completed
//     // !!! The current thread will be suspended. The Ice should be configured as ThreadPerConnection concurrent model
//     // or set Ice.ThreadPool.Server.SizeMax to a proper value greater than one (which is the default value). 
//     // See section 32.9 in Ice-3.2 manual for details explanations. 
//     // For the moment, I choose to use ThreadPerConnection model. @see MasterMain.cpp 
//     IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*(job.second.pMonitor));
//     while (job.second.status != JS_COMPLETED && job.second.status != JS_CANCELLED){
//         job.second.pMonitor->wait();
//         job = m_db->m_jobs.getJob(jobId);
//     }
//     LOG4CPLUS_DEBUG(m_logger, "JobServiceImpl::wait() The waiting thread wakes up");
//     // release resources
//     Addresses workers = m_db->m_workers.getAllWorkers();
//     for (int i = 0; i < workers.size(); i++){
//         m_db->m_tasks.addCleanTask(jobId, workers[i]);
//     }
//     LOG4CPLUS_DEBUG(m_logger, "JobServiceImpl::wait() Stop waiting job " << jobId);
//     if (job.second.status == JS_COMPLETED){
//         return 0;
//     }
//     else {
//         return 1;
//     }
// }

JobDetail JobServiceImpl::getJobDetail(int32_t jobId, const ::Ice::Current&)
{
    Job job = m_db->m_jobs.getJob(jobId);
    JobDetail detail;
    detail.id = -1;
    if (job.first == -1){
        LOG4CPLUS_WARN(m_logger, "JobServiceImpl::getJobDetail() job doesnot exist: " << jobId);
        return detail;
    }   

    LOG4CPLUS_TRACE(m_logger, "getJobDetail " << job);
    detail.id = job.first;
    detail.createTime = job.second.createTime;
    detail.finishTime = job.second.finishTime;
    detail.detached = job.second.bDetached;
    detail.jobSpec = job.second.jobSpec;
    detail.status = job.second.status;
    return detail;
}

// void JobServiceImpl::detach(int32_t jobId, const Ice::Current&)
// {
//     Job job = m_db->m_jobs.getJob(jobId);
//     if (job.first == -1){
//         LOG4CPLUS_WARN(m_logger, "JobServiceImpl::detach() job doesnot exist: " << jobId);
//         return;
//     }
//     LOG4CPLUS_DEBUG(m_logger, "Detach job " << jobId);
//     m_db->m_jobs.setJobDetached(jobId);
// }

int JobServiceImpl::kill(int32_t jobId, const Ice::Current&)
{
    LOG4CPLUS_DEBUG(m_logger, "Kill job " << jobId);
    return m_db->cancelJob(jobId);
}

