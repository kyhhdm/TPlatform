/**
 * @file WorkerServiceImpl.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/WorkerServiceImpl.hpp"
#include "master/MasterException.hpp"
#include "master/MasterConfig.hpp"

using namespace mapreduce;
using namespace std;

MasterCommands WorkerServiceImpl::sendHeartbeat(const Address& worker, const Heartbeat& heartbeat, const Ice::Current&)
{
    m_db->m_workers.renewHeartbeat(worker, heartbeat);
    log4cplus::NDCContextCreator ndc("sendHeartbeat()");
    MasterCommands mcs;
    MasterCommand mc;
    mc.command = McDoNothing;

    if (m_db->m_workers.isSafeMode()){
        // Are we in safe mode?
        mc.command = McDoNothing;
        mcs.push_back(mc);
    }
    else{
        // find proper job first
        //int32_t jobid = m_db->m_workers.getPriorJob(worker);
        // find ready task
        
        //check jobid
        
        //no check with jobid
        /*
        try{
            task = m_db->m_tasks.getReadyTask(worker, jobid, false);
        }catch(Ice::Exception &ex){
            LOG4CPLUS_ERROR(m_logger, "Catch Exception " << ex );
        }
        */
        
        //check with jobid
        Tasks tasks;
        try{
           tasks = m_db->m_tasks.getReadyTasks(worker, -1, false);
        }catch(Ice::Exception &ex){
            LOG4CPLUS_ERROR(m_logger, "Catch Exception " << ex );
        }
//         if(task.first == -1){
//             //no check: the worker has no task of jobid, find other task
//             try{
//                 task = m_db->m_tasks.getReadyTask(worker, jobid, false);
//             }catch(Ice::Exception &ex){
//                 LOG4CPLUS_ERROR(m_logger, "Catch Exception " << ex );
//             }
//         }
        //check over
        if (tasks.empty()){
            mc.command = McDoNothing;
            mcs.push_back(mc);        
        }
        for (int taskIdx = 0; taskIdx < tasks.size(); taskIdx++){
            Task task = tasks[taskIdx];
            if (task.second.type == TT_CLEAN){
                // TT_CLEAN
                mc.command = McDoClean;
                mc.taskId = task.first;
                mc.jobId = task.second.jobId;

//                 task.second.status = TS_INPROGRESS;
//                 m_db->m_tasks.setTask(task.first, task.second);
                LOG4CPLUS_INFO(m_logger, "Assign clean task " << task << " to worker " << worker );
            }
            else if (task.second.type == TT_MAP){
//                 task.second.status = TS_INPROGRESS;
//                 m_db->m_tasks.setTask(task.first, task.second);
                mc.command = McDoMap;
                mc.taskId = task.first;
                mc.jobId = task.second.jobId;
                Job job = m_db->m_jobs.getJob(task.second.jobId);
                if (job.second.status == JS_IDLE){
                    m_db->m_jobs.setJobStatus(task.second.jobId, JS_INPROGRESS);
                }
                mc.soFile = job.second.jobSpec.soFile;

                mc.mapperClass = job.second.jobSpec.mapperClass;
                mc.mapperInKeyClass = job.second.jobSpec.mapperInKeyClass;
                mc.mapperInValueClass = job.second.jobSpec.mapperInValueClass;
                mc.mapperOutKeyClass = job.second.jobSpec.mapperOutKeyClass;
                mc.mapperOutValueClass = job.second.jobSpec.mapperOutValueClass;
                mc.mapperRecordReaderClass = job.second.jobSpec.mapperRecordReaderClass;
                mc.reducerClass = job.second.jobSpec.reducerClass;
                mc.reducerOutKeyClass = job.second.jobSpec.reducerOutKeyClass;
                mc.reducerOutValueClass = job.second.jobSpec.reducerOutValueClass;
                mc.reducerRecordWriterClass = job.second.jobSpec.reducerRecordWriterClass;

                int32_t chunkIdx = task.second.chunkIdx;
                mc.chunkID = job.second.lchks[chunkIdx].chkId;
                mc.chunkSize = job.second.lchks[chunkIdx].chkSize;
                mc.reduceTaskNum = job.second.jobSpec.reduceTaskNum;
                mc.doLocalCombine = job.second.jobSpec.doLocalCombine;
                // select the chunk location
                bool bLocalWork = false;
                for (int i = 0; i < job.second.lchks[chunkIdx].locations.size(); i++){
                    if (job.second.lchks[chunkIdx].locations[i].name == worker.name){
                        bLocalWork = true;
                        mc.chunkLocation.name = job.second.lchks[chunkIdx].locations[i].name;
                        mc.chunkLocation.port = job.second.lchks[chunkIdx].locations[i].port;
                        break;
                    }
                }
                if (!bLocalWork){
                    mc.chunkLocation.name = job.second.lchks[chunkIdx].locations[0].name;
                    mc.chunkLocation.port = job.second.lchks[chunkIdx].locations[0].port;
                }
//                 task.second.worker = worker;
//                 m_db->m_tasks.setTask(task.first, task.second);
                LOG4CPLUS_DEBUG(m_logger, "assign map task, reducerno: " << mc.reduceTaskNum);
                LOG4CPLUS_INFO(m_logger, "Assign map task " << task << " to worker " << worker );
            }
            else if (task.second.type == TT_TRANS){
//                 task.second.status = TS_INPROGRESS;
//                 m_db->m_tasks.setTask(task.first, task.second);
                    
                mc.command = McDoTrans;
                mc.taskId = task.first;
                mc.jobId = task.second.jobId;
                mc.transMapTaskId = task.second.mapTaskId;
                Task mapTask = m_db->m_tasks.getTask(task.second.mapTaskId);
                mc.transMapWorker = mapTask.second.worker;
                Task reduceTask = m_db->m_tasks.getTask(task.second.reduceTaskId);
                mc.partition = reduceTask.second.partition;
                LOG4CPLUS_INFO(m_logger, "Assign trans task " << task << " to worker " << worker );
            }
            else if (task.second.type == TT_REDUCE){
//                 task.second.status = TS_INPROGRESS;
//                 m_db->m_tasks.setTask(task.first, task.second);
                    
                mc.command = McDoReduce;
                mc.taskId = task.first;
                mc.jobId = task.second.jobId;
                mc.partition = task.second.partition;
                Job job = m_db->m_jobs.getJob(task.second.jobId);
                mc.soFile = job.second.jobSpec.soFile;
                mc.outputFile = job.second.jobSpec.outputFile;
                mc.outputReplication = job.second.jobSpec.outputReplication;

                mc.mapperClass = job.second.jobSpec.mapperClass;
                mc.mapperInKeyClass = job.second.jobSpec.mapperInKeyClass;
                mc.mapperInValueClass = job.second.jobSpec.mapperInValueClass;
                mc.mapperRecordReaderClass = job.second.jobSpec.mapperRecordReaderClass;
                mc.reducerClass = job.second.jobSpec.reducerClass;
                mc.mapperOutKeyClass = job.second.jobSpec.mapperOutKeyClass;
                mc.mapperOutValueClass = job.second.jobSpec.mapperOutValueClass;
                mc.reducerOutKeyClass = job.second.jobSpec.reducerOutKeyClass;
                mc.reducerOutValueClass = job.second.jobSpec.reducerOutValueClass;
                mc.reducerRecordWriterClass = job.second.jobSpec.reducerRecordWriterClass;

                mc.doGroupBySort = job.second.jobSpec.doGroupBySort;
                LOG4CPLUS_INFO(m_logger, "Assign reduce task " << task << " to worker " << worker );
            }
            mcs.push_back(mc);
        } // end for each ready task
    } // end if safemode
    return mcs;
}

void WorkerServiceImpl::completeTask(const Address& worker, int32_t taskID, const Ice::Current&)
{
    log4cplus::NDCContextCreator ndc("completeTask()");
    Task task = m_db->m_tasks.getTask(taskID);
    LOG4CPLUS_INFO(m_logger, worker << " completed " << task );
    // If a reduce task is abandon, its corresponding trans tasks will be removed (@see WorkerServiceImpl::abandonTask).
    // In this situation, all the removed IN_PROGRESS trans tasks will not be found when completed or abandoned. 
    if (task.first == -1) {
        LOG4CPLUS_WARN(m_logger, "No task found for taskId " << taskID);
        return;
    }
    // for the invocation is at-least-once
    if (task.second.status != TS_INPROGRESS){
        LOG4CPLUS_WARN(m_logger, "The task is not INPROGRESS " << taskID);
        return;
    }

    // set task as completed
    task.second.status = TS_COMPLETED;
    m_db->m_tasks.setTask(task.first, task.second);
    
    if (task.second.type == TT_MAP){ // TT_MAP
        m_db->m_statistics.doneMap();
        m_db->m_workers.increaseDoneTasks(task.second.worker, TT_MAP);
    }
    else if (task.second.type == TT_TRANS){ // TT_TRANS
        m_db->m_statistics.doneTrans();
        Task reduceTask = m_db->m_tasks.getTask(task.second.reduceTaskId);
        if (reduceTask.first == -1){
            LOG4CPLUS_ERROR(m_logger, "No reduce task for trans task " << task);
        }
        else{
            m_db->m_workers.increaseDoneTasks(reduceTask.second.worker, TT_TRANS);
        }
    }
    else if (task.second.type == TT_REDUCE){                       // TT_REDUCE
        m_db->m_statistics.doneReduce();
        m_db->m_workers.increaseDoneTasks(task.second.worker, TT_REDUCE);

        if (m_db->m_tasks.isAllTasksCompleted(task.second.jobId, TT_REDUCE)){
            // job completed!
            Job job = m_db->m_jobs.getJob(task.second.jobId);
            // concat output files
            if (job.second.jobSpec.doConcatOutputs){
                vector<string> outputFiles;
                for (int i = 0; i < job.second.jobSpec.reduceTaskNum; i++){
                    stringstream ss;
                    ss << i;
                    outputFiles.push_back(job.second.jobSpec.outputFile + "/" + ss.str());
                }
                
                string dstFile = job.second.jobSpec.outputFile + "/result";
                bool ret = m_db->m_tfsFile.concatFiles(outputFiles, dstFile);
                LOG4CPLUS_INFO(m_logger, "Concat output files " << (ret?"OK":"ERROR"));
            }

            // release resources, add clean task
            Addresses workers = m_db->m_workers.getAllWorkers();
            for (int i = 0; i < workers.size(); i++){
                m_db->m_tasks.addCleanTask(task.second.jobId, workers[i]);
            }

            m_db->m_jobs.setJobStatus(task.second.jobId, JS_COMPLETED);
            m_db->m_statistics.doneJob();
            
            //@ADD by Chen Rishan
            //erase job from schedule lists on workers
            //m_db->m_workers.removeScheduledJob(task.second.jobId);
            LOG4CPLUS_INFO(m_logger, "Complete job " << job );
        }
    }else{
        // TT_CLEAN
        Job job = m_db->m_jobs.getJob(task.second.jobId);
        if ((job.second.status == JS_COMPLETED || job.second.status == JS_CANCELLED)
            && m_db->m_tasks.isAllTasksCompleted(task.second.jobId, TT_CLEAN)){
            m_db->m_tasks.removeTasks(task.second.jobId);
	    // Do not remove job information from the system
            //m_db->m_jobs.remove(task.second.jobId);
        }
    }
}

void WorkerServiceImpl::abandonTask(const Address& worker, int32_t taskId, const Ice::Current&)
{
    log4cplus::NDCContextCreator ndc("abandonTask()");
    Task task = m_db->m_tasks.getTask(taskId);
    LOG4CPLUS_INFO(m_logger, worker << " abandon task " << task );
    // If a reduce task is abandon, its corresponding trans tasks will be removed (@see WorkerServiceImpl::abandonTask).
    // In this situation, all the removed IN_PROGRESS trans tasks will not be found when completed or abandoned. 
    if (task.first == -1) {
        LOG4CPLUS_WARN(m_logger, "No task found for taskId " << taskId);
        return;
    }
    // for the invocation is at-least-once
    if (task.second.status != TS_INPROGRESS){
        LOG4CPLUS_WARN(m_logger, "The task is not INPROGRESS " << taskId);
        return;
    }
    
    if (task.second.type == TT_TRANS){
        task.second.abandonCount++;
        task.second.status = TS_IDLE;
        m_db->m_tasks.setTask(task.first, task.second);
        LOG4CPLUS_INFO(m_logger, "Re-assign trans task" << task.first);
        return;
    }
    
    try{

        if (task.second.abandonCount >= MasterConfig::TaskMaxAbandonCount){
            // cancel the job
            LOG4CPLUS_INFO(m_logger, "Cancel job " << task.second.jobId << " for " << task << " cannot be completed");
            m_db->cancelJob(task.second.jobId);
        }
        else{
            // reschedule the map/reducetask

            switch (task.second.type){
            case TT_MAP:
            {
                // select another worker and assign it to the task
                int32_t chunkIdx = task.second.chunkIdx;
                Job job = m_db->m_jobs.getJob(task.second.jobId);
                Address address;
                Addresses candidates;
                for (int j = 0; j < job.second.lchks[chunkIdx].locations.size(); j++){
                    address.name = job.second.lchks[chunkIdx].locations[j].name;
                    address.port = job.second.lchks[chunkIdx].locations[j].port;
                    candidates.push_back(address);
                }
                Address worker = m_db->m_workers.selectWorker(candidates);
                task.second.worker = worker;
                task.second.abandonCount++;
                task.second.status = TS_IDLE;
                m_db->m_tasks.setTask(task.first, task.second);
                LOG4CPLUS_INFO(m_logger, "Re-assign map task" << task.first << " to " << task.second.worker);
                break;
            }
            case TT_REDUCE:
            {
                Addresses candidates;
                Address worker = m_db->m_workers.selectWorker(candidates);
                task.second.worker = worker;
                task.second.abandonCount++;
                task.second.status = TS_IDLE;
                m_db->m_tasks.setTask(task.first, task.second);
                LOG4CPLUS_INFO(m_logger, "Re-assign reduce task" << task.first << " to " << task.second.worker);

                // re-assign the trans tasks releted to this reduce task
                Tasks transTasks = m_db->m_tasks.getTransTasksForReduce(task.second.jobId, task.first);
                for(int i = 0; i < transTasks.size(); i++){
                    transTasks[i].second.worker = worker;
                    transTasks[i].second.abandonCount = 0;
                    transTasks[i].second.status = TS_IDLE;
                    m_db->m_tasks.setTask(transTasks[i].first, transTasks[i].second);
                    LOG4CPLUS_INFO(m_logger, "Re-assign trans task" << transTasks[i].first << " to " << transTasks[i].second.worker);
                }
                break;
            }
            default:
                LOG4CPLUS_ERROR(m_logger, "Wrong task type to be abandoned " << task);
                break;
            }

        }
    
    }catch (SafeModeException &ex){
	// cancel the job
        LOG4CPLUS_WARN(m_logger, "Catch Exception " << ex.what());
        LOG4CPLUS_INFO(m_logger, "Cancel job " << task.second.jobId << " for SafeModeException");
        m_db->cancelJob(task.second.jobId);
    }
    
}

