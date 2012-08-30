/** 
 * @file TaskInfo.hpp
 * a  task.
 * Each `job' is divided into several map and reduce tasks. 
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _TASKINFO_HPP
#define _TASKINFO_HPP 1
#include "common/IceGenerated.hpp"
#include "common/AddressHelper.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

namespace mapreduce{
    enum TaskStatus{
        TS_IDLE = 0,
        TS_INPROGRESS,
        TS_COMPLETED,
        TS_CANCELLED,            // cancelled task that not yet be removed
        TS_NUM
    };
    enum TaskType{
        TT_MAP = 0,                 // map task to do map and partition
        TT_TRANS,               // data transfer task to transfer the imediate data
        TT_REDUCE,              // reduce task to do sort and reduce
        TT_CLEAN,                // clean task to kill running tasks belong to the job and release resources, this kind of task cannot be abandoned! 
        TT_NUM
    };
    /** Different type of task uses some of the different attributes. Map task is 
     * identified by `jobId' and `chunkIdx'. Trans task is identified by `jobId', 
     * `mapTaskId' and `reduceTaskId'. Reduce task is identified by
     * `jobId' and `partition'. Clean task is identified by `jobId' and `worker'
     */
    struct TaskInfo
    {
        /// there three type of task: Map, Trans, Redcue
        TaskType type;
        /// current status of the task
        TaskStatus status;
        /// job to which this task belongs
        int32_t jobId;
        /// count of failure times
        int32_t abandonCount;
        /// start time of running
        time_t startTime;
        
        /// @{ The following properties are used for different type of task. 
        /// for map/reduce/clean task, worker who is responsibile for this task
        Address worker;
        /// for map task, chunk index of the chunk of the input file
        int32_t chunkIdx;
        /// for trans task, the imediate file will be transfered from mapTaskId's worker
        int32_t mapTaskId;
        /// for trans task, the imediate file will be transfered to reduceTaskId's worker
        int32_t reduceTaskId;
        /// for reduce task, the partition of the imediate file
        int32_t partition;
        /// @}
    };
    typedef std::pair<int32_t, TaskInfo> Task;
    typedef std::vector<Task> Tasks;

    inline std::ostream& operator << (std::ostream &os, const Task& task)
    {
        os << "task[id=" << task.first 
           << " type=" << task.second.type 
           << " status=" << task.second.status 
           << " jobId=" << task.second.jobId
           << " worker=" << task.second.worker
           << " abandon=" << task.second.abandonCount
           << "]";
        return os;
    }

    inline std::ostream& operator << (std::ostream &os, const Tasks& tasks)
    {
        std::copy(tasks.begin(), tasks.end(), std::ostream_iterator<Task>(os, " "));
        return os;
    }

    struct TaskLessThan: public std::binary_function<Task, Task, bool>
    {
        bool operator() (const Task &task1, const Task &task2)
            {
                if (task1.second.jobId != task2.second.jobId){
                    return task1.second.jobId < task2.second.jobId;
                }
                // equal jobId, then
                if (task1.second.type != task2.second.type){
                    return task1.second.type < task2.second.type;
                }
                // equal jobId and type, then
                if (task1.second.status != task2.second.status){
                    return task1.second.status < task2.second.status;
                }
                // equal jobId and type and status ,then
                return task1.first < task2.first;
            }        
    };
}

#endif /* _TASKINFO_HPP */
