/** 
 * @file TaskManager.hpp
 * Manager all the tasks' status and other info.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _TASKMANAGER_HPP
#define _TASKMANAGER_HPP 1

#include "master/TaskInfo.hpp"
#include "util/Logger.hpp"
#include <IceUtil/RWRecMutex.h>
#include <map>
#include <vector>
#include <utility>

namespace mapreduce{
    
    class TaskManager
    {
        /// map: taskid->taskinfo
        typedef std::map<int32_t, TaskInfo> id2info_t;
        id2info_t m_id2info;
        /// mutex for the map
        IceUtil::RWRecMutex m_mutex;
        /// logger
        mutable Logger m_logger;

        /** 
         * allocate a new task id
         * @return the task id
         */
        int32_t newId() const;

        // forbid copy
        TaskManager(const TaskManager& other);
        TaskManager& operator= (const TaskManager& other);

    public:
        /// constructor
        TaskManager();
        /// destructor
        ~TaskManager();
        
        /** 
         * add a new map task
         * 
         * @param jobID 
         * @param chunkIdx
         * 
         * @return taskID
         */
        int32_t addMapTask(int32_t jobId, int32_t chunkIdx, const Address &worker);
        /** 
         * add a new trans task.
         * The task transfer data from mapTaskId's worker to reduceTaskId's worker. 
         * 
         * @param jobId 
         * @param mapTaskId from this mapTask
         * @param reduceTaskId to this reduceTask
         * 
         * @return the task id
         */
        int32_t addTransTask(int32_t jobId, int32_t fromTaskId, int32_t toTaskId);
        /** 
         * add a new reduce task.
         * 
         * @param jobId job that this task belongs to
         * @param partition partition for which this reduce task is responsible
         * @param worker 
         * 
         * @return 
         */
        int32_t addReduceTask(int32_t jobId, int32_t partition, const Address& worker);
        /** 
         * add a new clean task
         * 
         * @param jobId 
         * @param worker 
         * 
         * @return taskId
         */
        int32_t addCleanTask(int32_t jobId, const Address&worker);
        /** 
         * set all the tasks belong to the job as cancelled, which should not be assigned any more
         * 
         * @param jobId 
         */
        void setTasksCancelled(int jobId);
        /** 
         * get one ready task for the given worker
         * a map task is `ready' if it is in IDLE mode,
         * a trans task is `ready' if it is in IDLE mode and its map task completed
         * a reduce task is `ready' if it is in IDLE mode and all its trans tasks completed
         * @param worker 
         * @param jobid
         * @param checkJobId: whether check jobid
         *
         * @return the task id and info
         *
         * @add by Chen Rishan
         * add job schdule algorithm: multi schdule-list feedback
         */
        Task getReadyTask(const Address& worker, int32_t jobid, bool checkJobId);
        Tasks getReadyTasks(const Address& worker, int32_t jobid, bool checkJobId);
        /** 
         * get the number of the INPROGRESS tasks for the worker
         * 
         * @param worker 
         * 
         * @return <total, map, reduce, trans, clean>
         */
        std::vector<int32_t> getInproTasksNum(const Address& worker) const;
        /** 
         * get all the tasks for the given worker
         * 
         * @param worker 
         * 
         * @return the task id and info
         */
        Tasks getAllTasks(const Address& worker) const;
        /** 
         * get all the tasks belong to the given job
         * 
         * @param jobId 
         * 
         * @return 
         */
        Tasks getAllTasks(int32_t jobId) const;
        /** 
         * get all the tasks
         * 
         * @return 
         */
        Tasks getAllTasks() const;
        /** 
         * get all the tasks for the given job of the given type.
         * 
         * @param jobId 
         * @param tasktype
         * @return 
         */
        Tasks getAllTasks(int32_t jobId, TaskType taskType) const;
        /** 
         * whether all the tasks of the given job and given type are completed
         * 
         * @param jobId 
         * @param taskType
         * @return 
         */
        bool isAllTasksCompleted(int32_t jobId, TaskType taskType) const;
        /** 
         * get the task identified by the ID
         * 
         * @param taskId 
         * 
         * @return the task. if the task doesn't exist, task.first == -1
         */
        Task getTask(int32_t taskId) const;
        /** 
         * get all completed reduce task for the given job.
         * 
         * @param jobId 
         * 
         * @return 
         */
        //Tasks getCompletedReduceTasks(int32_t jobId) const;
        /** 
         * get all the trans tasks coresponding to the reduce task
         * 
         * @param worker 
         * @param reduceTaskId
         * 
         * @return 
         */
        Tasks getTransTasksForReduce(int32_t jobId, int32_t reduceTaskId) const;
        /** 
         * get all the trans tasks coresponding to the map tasks with the given taskId
         * 
         * @param worker 
         * @param mapTaskId
         * 
         * @return 
         */
        Tasks getTransTasksForMap(int32_t jobId, int32_t mapTaskId) const;
        /** 
         * remove all the tasks belong to the given job.
         * 
         * @param jobId 
         */
        void removeTasks(int32_t jobId);
        /** 
         * remove the task identified by the ID and return it
         * 
         * @param taskId 
         * 
         * @return the task
         */
        Task removeTask(int32_t taskId);
        /** 
         * set the task.
         * 
         * @param taskId 
         * @param taskInfo
         */
        void setTask(int32_t taskId, const TaskInfo &taskInfo);
        /** 
         * re-balance tasks. Move the idle map tasks from busy worker to free worker
         * 
         * @param freeWorkers the free workers
         */
        void rebalance(const Addresses& freeWorkers);
    };

    inline TaskManager::TaskManager()
        :m_logger(Logger::getInstance("master"))
    {
    }
}


#endif /* _TASKMANAGER_HPP */
