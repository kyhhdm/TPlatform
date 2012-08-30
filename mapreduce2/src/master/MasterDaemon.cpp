/**
 * @file MasterDaemon.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-18
 */

#include "master/MasterDaemon.hpp"
#include "master/MasterException.hpp"
using namespace mapreduce;

bool MasterDaemon::isSystemIdel()
{
    return true;
}

void MasterDaemon::run()
{
    log4cplus::NDCContextCreator ndc("MasterDaemon::run()");
    while(true){
        IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(m_sleepSeconds));
        if (this->isSystemIdel()){
            // remove expired workers and re-assign tasks
            Addresses expiredWorkers = m_db->m_workers.removeExpired();
            if (!expiredWorkers.empty()){
                LOG4CPLUS_INFO(m_logger, "Remove expired workers " << expiredWorkers);
            }
            Task task;
            try{
                for (int i = 0; i < expiredWorkers.size(); i++){
                    this->rescheduleWorkerFails(expiredWorkers[i]);
                }
            }catch (SafeModeException &ex){
                LOG4CPLUS_WARN(m_logger, "Catch exception " << ex.what());
                LOG4CPLUS_INFO(m_logger, "Cancel job " << task.second.jobId << " for SafeModeException");
                m_db->cancelJob(task.second.jobId);
            }
            /// @todo check orphan tasks who have assigned to workers not available any more
            // re-balance tasks according to the current workloads of workers
            // m_db->m_tasks.rebalance(m_db->m_workers.getFreeWorkers());
        }        
    }
}

void MasterDaemon::rescheduleWorkerFails(const Address& failedWorker)
{
    Tasks tasks = m_db->m_tasks.getAllTasks(failedWorker);
    Tasks reduceTasks;
    Tasks mapTasks;
    for (int i = 0; i < tasks.size(); i++){
	switch (tasks[i].second.type){
	case TT_MAP:
	{
	    mapTasks.push_back(tasks[i]);
	    break;
	}
	case TT_REDUCE:
	{
	    reduceTasks.push_back(tasks[i]);
	    break;
	}
	default:
	    break;
	}
    }    
    // we ought to re-assign reduce tasks first
    for (int i = 0; i < reduceTasks.size(); i++){
	Task task = reduceTasks[i];
	
        switch (task.second.status){
        case TS_IDLE:
        case TS_INPROGRESS:
        {
            Addresses candidates;
            Address worker = m_db->m_workers.selectWorker(candidates);
            task.second.worker = worker;
            task.second.status = TS_IDLE;
            m_db->m_tasks.setTask(task.first, task.second);
            LOG4CPLUS_INFO(m_logger, "Re-assign reduce task" << task.first << " to " << task.second.worker);

            // re-assign the trans tasks releted to this reduce task
            Tasks transTasks = m_db->m_tasks.getTransTasksForReduce(task.second.jobId, task.first);
            for(int i = 0; i < transTasks.size(); i++){
                transTasks[i].second.abandonCount = 0;
                transTasks[i].second.status = TS_IDLE;
                m_db->m_tasks.setTask(transTasks[i].first, transTasks[i].second);
            }

            break;
        }
        case TS_COMPLETED:
        {
            break;
        }
        default:
            break;
        } 

    } // endfor

    // then re-assign map tasks
    for (int i = 0; i < mapTasks.size(); i++){
	Task task = mapTasks[i];
        switch (task.second.status){
        case TS_IDLE:
        case TS_INPROGRESS:
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
            task.second.status = TS_IDLE;
            m_db->m_tasks.setTask(task.first, task.second);
            LOG4CPLUS_INFO(m_logger, "Re-assign IDLE/INPR map task" << task.first << " to " << task.second.worker);

            break;
        }
        case TS_COMPLETED:
        {
	    // If a worker fails, it is possible that some INPR reduce task need to be re-do. We re-assign
	    // the reduce tasks first to make the related trans tasks IDLE. So the related map tasks will
	    // have some in-completed trans task, which will be re-assigned

            Tasks transTasks = m_db->m_tasks.getTransTasksForMap(task.second.jobId, task.first);
            bool bReassign = false;
	    
            for (int j = 0; j < transTasks.size(); j++){
                if (transTasks[j].second.status != TS_COMPLETED){ 
                    // re-assign if there is any in-completed trans task
		    bReassign = true;
		    break;
		}
	    }

	    if (bReassign){
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
		task.second.status = TS_IDLE;
		m_db->m_tasks.setTask(task.first, task.second);
		LOG4CPLUS_INFO(m_logger, "Re-assign COMP map task" << task.first << " to " << task.second.worker);
		
		// re-assign the trans tasks releted to this map task, whose related reduce task is IDLE
		for (int j = 0; j < transTasks.size(); j++){
		    Task reduceTask = m_db->m_tasks.getTask(transTasks[j].second.reduceTaskId);
		    if (reduceTask.first == -1){
			LOG4CPLUS_WARN(m_logger, "MasterDaemon: No reduce task found for trans " << transTasks[j].first);
			continue;
		    }
		    if (reduceTask.second.status == TS_IDLE){
			transTasks[j].second.abandonCount = 0;
			transTasks[j].second.status = TS_IDLE;
			m_db->m_tasks.setTask(transTasks[j].first, transTasks[j].second);
			LOG4CPLUS_INFO(m_logger, "Re-assign trans task" << transTasks[j].first);
		    }
		}
	    } // endif

            break;
        }
        default:
            break;
        }
    } // endfor
}
