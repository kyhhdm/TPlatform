/**
 * @file TaskManager.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-29
 */
#include "common/Types.hpp"
#include "master/TaskManager.hpp"
#include "master/MasterConfig.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;
using namespace mapreduce;

TaskManager::~TaskManager()
{
    if (!m_id2info.empty()){
        Tasks tasks = this->getAllTasks();
        LOG4CPLUS_WARN(m_logger, "Tasks still alive when shutdown: " << tasks);
    }
}

inline int32_t TaskManager::newId() const
{
    //IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    int32_t id;
    id2info_t::const_iterator it;
    do{
        id = rand();
        it = m_id2info.find(id);
    }while(it != m_id2info.end());
    return id;
}

int32_t TaskManager::addMapTask(int32_t jobId, int32_t chunkIdx, const Address& worker)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    TaskInfo taskInfo;
    taskInfo.type = TT_MAP;
    taskInfo.status = TS_IDLE;
    taskInfo.jobId = jobId;
    taskInfo.chunkIdx = chunkIdx;
    taskInfo.abandonCount = 0;
    taskInfo.worker = worker;

    int32_t taskId = this->newId();
    m_id2info[taskId] = taskInfo;
    LOG4CPLUS_INFO(m_logger, "Add map task " << taskId << " with worker " << worker);
    return taskId;
}

int32_t TaskManager::addTransTask(int32_t jobId, int32_t mapTaskId, int32_t reduceTaskId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    TaskInfo taskInfo;
    taskInfo.type = TT_TRANS;
    taskInfo.status = TS_IDLE;
    taskInfo.jobId = jobId;
    taskInfo.abandonCount = 0;
    taskInfo.mapTaskId = mapTaskId;
    taskInfo.reduceTaskId = reduceTaskId;
    taskInfo.worker.name = "invalid";
    taskInfo.worker.port = 0;

    int32_t taskId = this->newId();
    m_id2info[taskId] = taskInfo;
    LOG4CPLUS_INFO(m_logger, "Add trans task " << taskId);
    return taskId;
}

int32_t TaskManager::addReduceTask(int32_t jobId, int32_t partition, const Address& worker)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    TaskInfo taskInfo;
    taskInfo.type = TT_REDUCE;
    taskInfo.status = TS_IDLE;
    taskInfo.jobId = jobId;
    taskInfo.abandonCount = 0;
    taskInfo.partition = partition;
    taskInfo.worker = worker;
    
    int32_t taskId = this->newId();
    m_id2info[taskId] = taskInfo;
    LOG4CPLUS_INFO(m_logger, "Add reduce task " << taskId);
    return taskId;
}

int32_t TaskManager::addCleanTask(int32_t jobId, const Address& worker)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    TaskInfo taskInfo;
    taskInfo.type = TT_CLEAN;
    taskInfo.status = TS_IDLE;
    taskInfo.jobId = jobId;
    taskInfo.abandonCount = 0;
    taskInfo.worker = worker;

    int32_t taskId = this->newId();
    m_id2info[taskId] = taskInfo;
    LOG4CPLUS_INFO(m_logger, "Add clean task " << taskId);
    return taskId;
}

void TaskManager::setTasksCancelled(int jobId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    id2info_t::iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId
            && it->second.status == TS_IDLE){
            it->second.status = TS_CANCELLED;
            //LOG4CPLUS_DEBUG(m_logger, "Set idle task " << it->first << " as cancelled" );
        }
    }
}

void TaskManager::setTask(int32_t taskId, const TaskInfo &taskInfo)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    id2info_t::iterator it = m_id2info.find(taskId);
    if (it != m_id2info.end()){
        (*it).second = taskInfo;
    } else{
        LOG4CPLUS_WARN(m_logger, "TaskManager::setTask() No task found for taskId " << taskId);
    }
}

Task TaskManager::getReadyTask(const Address& worker, int32_t jobid, bool checkJobId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    
    Task task;
    // no ready tasks for this worker
    task.first = -1;

    id2info_t::iterator it;
    // clean task goes first
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.worker == worker 
            && it->second.type == TT_CLEAN
            && it->second.status == TS_IDLE
            ){//no check
            //LOG4CPLUS_DEBUG(m_logger, "Get ready clean task " << *it);
            // change status immediatly
            it->second.status = TS_INPROGRESS;
            return *it;
        }
    }

    // get worker's workload 
    vector<int32_t> counts(5);
    for (int i = 0; i < 5; i++){
        counts[i] = 0;
    }

    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.status == TS_INPROGRESS){
	    switch(it->second.type){
	    case TT_MAP:
	    {
		    if (it->second.worker == worker){
		        counts[1]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_REDUCE:
	    {
		    if (it->second.worker == worker){
		        counts[2]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_TRANS:
	    {
		    id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
		    if (itReduce != m_id2info.end() && itReduce->second.worker == worker){
		        counts[3]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_CLEAN:
	    {
		    if (it->second.worker == worker){
		        counts[4]++;
                counts[0]++;
		    }
		    break;
	    }
        case TT_NUM:;
	    }//switch
        }//if
    }//for

    // then the map tasks
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.worker == worker 
            && it->second.type == TT_MAP
            && it->second.status == TS_IDLE ){
            if (counts[1] + counts[2] >= MasterConfig::MaxActiveTaskNumPerWorker){
                // Is the worker's CPU too busy?
                continue;
            }
            else{
                //LOG4CPLUS_DEBUG(m_logger, "Get ready map task " << *it);
                
                // change status immediatly
                if(checkJobId && it->second.jobId == jobid){
                    task = *it;
                    it->second.status = TS_INPROGRESS;
                    break;
                }
                if(!checkJobId){
                    task = *it;
                    it->second.status = TS_INPROGRESS;
                    break;
                }

            }
        }
    } // end for

    if (task.first != -1){
        return task;
    }
    else{
        // no map task for this worker
        //if the worker is free and we have some IDLE map task, assign the worker to it
        if (counts[1] + counts[2] < MasterConfig::MaxActiveTaskNumPerWorker){
            for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
                if (it->second.type == TT_MAP
                    && it->second.status == TS_IDLE){
                    if((checkJobId && it->second.jobId == jobid) || !checkJobId){
                        // change status immediatly
                        it->second.status = TS_INPROGRESS;
                        it->second.worker = worker;
                        task = *it;
                        LOG4CPLUS_INFO(m_logger, "getReadyTask() rebalance task " << *it << " to " << worker);
                        break;
                    }
                }
            } // end for
        } // end if 
    } // end else
    if (task.first != -1){
        return task;
    }

    // then the trans or reduce tasks
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.type == TT_TRANS
                 && it->second.status == TS_IDLE
                 ){
            
            if (counts[3] >= MasterConfig::MaxActiveTransTaskNumPerWorker){
                // Is the worker's network too busy?
                //LOG4CPLUS_DEBUG(m_logger, "worker is too busy to do tran task " << it->first << " " << counts[3] );
                continue;
            }
            else{
                //LOG4CPLUS_DEBUG(m_logger, " tran task comes here " << it->first);
                id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
                if (itReduce == m_id2info.end()){
                    LOG4CPLUS_ERROR(m_logger, "TaskManager::getReadyTask() No reduce task for trans task " << *it);
                    //LOG4CPLUS_DEBUG(m_logger, " tran task comes here2 " << it->first);
                    continue;
                }
                if (itReduce->second.worker != worker){
                    //LOG4CPLUS_DEBUG(m_logger, " trans " << it->first << " " << itReduce->first);
                    //LOG4CPLUS_DEBUG(m_logger, " comes here3 " << it->first << " " << itReduce->second.worker << " " << worker);
                    continue;
                }
                id2info_t::const_iterator it2 = m_id2info.find(it->second.mapTaskId);
                if (it2 == m_id2info.end()){
                    LOG4CPLUS_ERROR(m_logger, "TaskManager::getReadyTask() No map task for trans task " << *it);
                    continue;
                }
                if (it2->second.status == TS_COMPLETED){
                    //LOG4CPLUS_DEBUG(m_logger, "Get ready trans task " << *it);
                    //no matter with job schedule: transfer task was executed once after map task done 
                    // change status immediatly
                    it->second.status = TS_INPROGRESS;
                    task = *it;
                    break;
                }
            } // end else
        }
        else if (it->second.worker == worker 
            && it->second.type == TT_REDUCE
            && it->second.status == TS_IDLE
            ){
            if (counts[1] + counts[2] >= MasterConfig::MaxActiveTaskNumPerWorker){
                // Is the worker's CPU too busy?
                continue;
            }
            else{
                int32_t nCompletedTransTasks = 0;
                int32_t nMapTasks = 0;
                id2info_t::const_iterator it2;
                for (it2 = m_id2info.begin(); it2 != m_id2info.end(); ++it2){
                    if (it2->second.jobId == it->second.jobId 
                        && it2->second.type == TT_TRANS 
                        && it2->second.status == TS_COMPLETED
                        && it2->second.reduceTaskId == it->first){
                        nCompletedTransTasks++;
                    }else if (it2->second.type == TT_MAP
                              && it2->second.jobId == it->second.jobId){
                        nMapTasks++;
                    }
                }
                if (nCompletedTransTasks == nMapTasks && nMapTasks != 0){
                    // ready to reduce
                    //LOG4CPLUS_DEBUG(m_logger, "Get ready reduce task " << *it);
                    if(checkJobId && it->second.jobId == jobid){
                        task = *it;
                        it->second.status = TS_INPROGRESS;
                        break;
                    }
                    if(!checkJobId){
                        task = *it;
                        it->second.status = TS_INPROGRESS;
                        break;
                    }
                }
            } // end else
        } // end if REDUCE
    } // end for

    return task;
}

Tasks TaskManager::getReadyTasks(const Address& worker, int32_t jobid, bool checkJobId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    
    Tasks tasks;
    int32_t cleanTaskCount = 0;
    int32_t mapTaskCount = 0;
    int32_t rebalanceMapTaskCount = 0;
    int32_t reduceTaskCount = 0;
    int32_t transTaskCount = 0;

    id2info_t::iterator it;
    // get worker's workload 
    vector<int32_t> counts(5);
    for (int i = 0; i < 5; i++){
        counts[i] = 0;
    }

    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.status == TS_INPROGRESS){
	    switch(it->second.type){
	    case TT_MAP:
	    {
		    if (it->second.worker == worker){
		        counts[1]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_REDUCE:
	    {
		    if (it->second.worker == worker){
		        counts[2]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_TRANS:
	    {
		    id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
		    if (itReduce != m_id2info.end() && itReduce->second.worker == worker){
		        counts[3]++;
                counts[0]++;
		    }
		    break;
	    }
	    case TT_CLEAN:
	    {
		    if (it->second.worker == worker){
		        counts[4]++;
                counts[0]++;
		    }
		    break;
	    }
        case TT_NUM:;
	    }//switch
        }//if
    }//for

    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.worker == worker 
            && it->second.type == TT_CLEAN
            && it->second.status == TS_IDLE
            ){//no check
            //LOG4CPLUS_DEBUG(m_logger, "Get ready clean task " << *it);
            // change status immediatly
            // if there is a clean task, we dont assign other type of task
            it->second.status = TS_INPROGRESS;
            tasks.clear();
            tasks.push_back(*it);
            cleanTaskCount++;
            break;
        } // end if clean task
        else if (it->second.worker == worker 
            && it->second.type == TT_MAP
            && it->second.status == TS_IDLE ){
            if (counts[1] + counts[2] + mapTaskCount + reduceTaskCount >= MasterConfig::MaxActiveTaskNumPerWorker){
                // Is the worker's CPU too busy?
                continue;
            }
            else{
                //LOG4CPLUS_DEBUG(m_logger, "Get ready map task " << *it);
                if((checkJobId && it->second.jobId == jobid) || !checkJobId){
                    // change status immediatly
                    it->second.status = TS_INPROGRESS;
                    tasks.push_back(*it);
                    mapTaskCount++;
                    continue;
                }
            } // end if map task
        }
        else if (it->second.type == TT_TRANS
                 && it->second.status == TS_IDLE){
            
            if (counts[3] + transTaskCount >= MasterConfig::MaxActiveTransTaskNumPerWorker){
                // Is the worker's network too busy?
                //LOG4CPLUS_DEBUG(m_logger, "worker is too busy to do tran task " << it->first << " " << counts[3] );
                continue;
            }
            else{
                //LOG4CPLUS_DEBUG(m_logger, " tran task comes here " << it->first);
                id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
                if (itReduce == m_id2info.end()){
                    LOG4CPLUS_ERROR(m_logger, "TaskManager::getReadyTasks() No reduce task for trans task " << *it);
                    //LOG4CPLUS_DEBUG(m_logger, " tran task comes here2 " << it->first);
                    continue;
                }
                if (itReduce->second.worker != worker){
                    //LOG4CPLUS_DEBUG(m_logger, " trans " << it->first << " " << itReduce->first);
                    //LOG4CPLUS_DEBUG(m_logger, " comes here3 " << it->first << " " << itReduce->second.worker << " " << worker);
                    continue;
                }
                id2info_t::const_iterator it2 = m_id2info.find(it->second.mapTaskId);
                if (it2 == m_id2info.end()){
                    LOG4CPLUS_ERROR(m_logger, "TaskManager::getReadyTasks() No map task for trans task " << *it);
                    continue;
                }
                if (it2->second.status == TS_COMPLETED){
                    //LOG4CPLUS_DEBUG(m_logger, "Get ready trans task " << *it);
                    //no matter with job schedule: transfer task was executed once after map task done 
                    // change status immediatly
                    it->second.status = TS_INPROGRESS;
                    tasks.push_back(*it);
                    transTaskCount++;
                    continue;
                }
            } // end else
        }     // end if TRANS
        else if (it->second.worker == worker 
            && it->second.type == TT_REDUCE
            && it->second.status == TS_IDLE){
            if (counts[1] + counts[2] + mapTaskCount + reduceTaskCount >= MasterConfig::MaxActiveTaskNumPerWorker){
                // Is the worker's CPU too busy?
                continue;
            }
            else{
                int32_t nCompletedTransTasks = 0;
                int32_t nMapTasks = 0;
                id2info_t::const_iterator it2;
                for (it2 = m_id2info.begin(); it2 != m_id2info.end(); ++it2){
                    if (it2->second.jobId == it->second.jobId 
                        && it2->second.type == TT_TRANS 
                        && it2->second.status == TS_COMPLETED
                        && it2->second.reduceTaskId == it->first){
                        nCompletedTransTasks++;
                    }else if (it2->second.type == TT_MAP
                              && it2->second.jobId == it->second.jobId){
                        nMapTasks++;
                    }
                }
                if (nCompletedTransTasks == nMapTasks && nMapTasks != 0){
                    // ready to reduce
                    //LOG4CPLUS_DEBUG(m_logger, "Get ready reduce task " << *it);
                    if((checkJobId && it->second.jobId == jobid) || !checkJobId){
                        it->second.status = TS_INPROGRESS;
                        tasks.push_back(*it);
                        reduceTaskCount++;
                        continue;
                    }
                }
            } // end else
        } // end if REDUCE

    }

    //if the worker is free and we have some IDLE map task, assign the worker to it
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.type == TT_MAP
            && it->second.status == TS_IDLE){
            if (counts[1] + counts[2] + mapTaskCount + reduceTaskCount >= MasterConfig::MaxActiveTaskNumPerWorker){
                // Is the worker's CPU too busy?
                break;
            }
            else{
                if((checkJobId && it->second.jobId == jobid) || !checkJobId){
                    // change status immediatly
                    it->second.status = TS_INPROGRESS;
                    it->second.worker = worker;
                    tasks.push_back(*it);
                    mapTaskCount++;
                    rebalanceMapTaskCount++;
                    LOG4CPLUS_INFO(m_logger, "getReadyTasks() rebalance task " << *it << " to " << worker);
                    break;
                }
            }
        } // end if
    } // end for
    if (mapTaskCount != 0 || rebalanceMapTaskCount != 0 || reduceTaskCount != 0 || transTaskCount != 0){
        LOG4CPLUS_DEBUG(m_logger, "getReadyTasks() assign " << worker << " mapTask=" << mapTaskCount << " (rebalanceMapTaskCount=" << rebalanceMapTaskCount<< ") reduceTask=" << reduceTaskCount << " transTasks=" << transTaskCount << " cleanTaskCount=" << cleanTaskCount);
    }
    return tasks;
}

vector<int32_t> TaskManager::getInproTasksNum(const Address& worker) const 
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    vector<int32_t> counts(5);
    for (int i = 0; i < 5; i++){
        counts[i] = 0;
    }

    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.status == TS_INPROGRESS){
            switch(it->second.type){
            case TT_MAP:
            {
                if (it->second.worker == worker){
                    counts[1]++;
                    counts[0]++;
                }
                break;
            }
            case TT_REDUCE:
            {
                if (it->second.worker == worker){
                    counts[2]++;
                    counts[0]++;
                }
                break;
            }
            case TT_TRANS:
            {
                id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
                if (itReduce != m_id2info.end() && itReduce->second.worker == worker){
                    counts[3]++;
                    counts[0]++;
                }
                break;
            }
            case TT_CLEAN:
            {
                if (it->second.worker == worker){
                    counts[4]++;
                    counts[0]++;
                }
                break;
            }
            case TT_NUM:;
            }
        }
    }
    return counts;
}

Tasks TaskManager::getAllTasks(const Address& worker) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.worker == worker){
            tasks.push_back(*it);
        } else if (it->second.type == TT_TRANS){
	    id2info_t::const_iterator itReduce = m_id2info.find(it->second.reduceTaskId);
	    if (itReduce != m_id2info.end() && itReduce->second.worker == worker){
		tasks.push_back(*it);
	    }
	}
    }
    return tasks;
}

Tasks TaskManager::getAllTasks() const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        tasks.push_back(*it);
    }
    return tasks;
}

Task TaskManager::getTask(int32_t taskId) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Task task;
    task.first = -1;
    
    id2info_t::const_iterator it = m_id2info.find(taskId);
    if (it != m_id2info.end()){
        task = *it;
    } else{
        LOG4CPLUS_WARN(m_logger, "TaskManager::getTask() No task found for taskId " << taskId);
    }
    
    return task;
}

Tasks TaskManager::getAllTasks(int32_t jobId, TaskType taskType) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId && it->second.type == taskType){
            tasks.push_back(*it);
        }
    }
    return tasks;
}

Tasks TaskManager::getAllTasks(int32_t jobId) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId){
            tasks.push_back(*it);
        }
    }
    return tasks;
}

void TaskManager::removeTasks(int32_t jobId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    id2info_t::iterator it = m_id2info.begin();
    while (it != m_id2info.end()){
        if (it->second.jobId == jobId){
            m_id2info.erase(it);
            it = m_id2info.begin();
        }else{
            ++it;
        }
    }
}

Task TaskManager::removeTask(int32_t taskId)
{
    IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
    Task task;
    task.first = -1;
    id2info_t::iterator it = m_id2info.find(taskId);
    if (it != m_id2info.end()){
        task = *it;
        m_id2info.erase(it);
    }
    return task;
}

Tasks TaskManager::getTransTasksForReduce(int32_t jobId, int32_t reduceTaskId) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId 
            && it->second.type == TT_TRANS
            && it->second.reduceTaskId == reduceTaskId){
            tasks.push_back(*it);
        }
    }
    return tasks;

}

Tasks TaskManager::getTransTasksForMap(int32_t jobId, int32_t mapTaskId) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    Tasks tasks;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId 
            && it->second.type == TT_TRANS
            && it->second.mapTaskId == mapTaskId){
            tasks.push_back(*it);
        }
    }
    return tasks;

}

bool TaskManager::isAllTasksCompleted(int32_t jobId, TaskType taskType) const
{
    IceUtil::RWRecMutex::RLock lock(m_mutex); // Read lock
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        if (it->second.jobId == jobId && it->second.type == taskType && it->second.status != TS_COMPLETED){
            return false;
        }
    }
    return true;
}

// void TaskManager::rebalance(const Addresses& freeWorkers)
// {
//     IceUtil::RWRecMutex::WLock lock(m_mutex); // Write lock
//     //LOG4CPLUS_INFO(m_logger, "Begin Rebalance, has " <<freeWorkers.size() <<" free workers.");
//     if (freeWorkers.empty()) return;
    
//     id2info_t::iterator it;
//     int num = 0, maxnum = freeWorkers.size();
//     for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
//         if (it->second.status == TS_IDLE && it->second.type == TT_MAP){
//             // whether the worker is busy
//             bool busy = true;
//             for (int i = 0; i < freeWorkers.size(); i++){
//                 if (it->second.worker == freeWorkers[i]){
//                     busy = false;
//                     break;
//                 }
//             }
//             // move the task if its worker is busy
//             if (busy){
//                 // randomly select a free worker
//                 double total = freeWorkers.size();
//                 int32_t k = (int)(total*rand()/(RAND_MAX+1.0)); // k: [0, total)
//                 if (it->second.status == TS_IDLE){
//                     // check again
//                     LOG4CPLUS_INFO(m_logger, "Rebalance " << *it << " to worker " << freeWorkers[k]);
//                     it->second.worker = freeWorkers[k];
//                 }
//                 ++num;
//                 if (num >= maxnum) return;
//             }
//         } // end if
//     } // end for
// }
