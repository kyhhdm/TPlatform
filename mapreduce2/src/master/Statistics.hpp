/** 
 * @file Statistics.hpp
 * runtime statistic info of the master and the whole system.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _STATISTICS_HPP
#define _STATISTICS_HPP 1
#include "common/Types.hpp"
#include <ctime>
#include <IceUtil/Mutex.h>

namespace mapreduce{
    class Statistics
    {
        /// master start time
        time_t m_startTime;
        /// the number of completed jobs
        int32_t m_doneJobs;
        /// the number of map tasks which have been done.
        int32_t m_doneMapTasks;
        /// the number of reduce tasks which have been done.
        int32_t m_doneReduceTasks;
        /// the number of trans tasks which have been done.
        int32_t m_doneTransTasks;
        /// the total heartbeat received
        uint32_t m_heartbeatCount;
        
        IceUtil::Mutex m_mutex;
    public:
        Statistics();
        time_t getStartTime() const;
        int32_t getCompletedJobs() const;
        int32_t getCompletedMapTasks() const;
        int32_t getCompletedReduceTasks() const;
        int32_t getCompletedTransTasks() const;
        void doneJob();
        void doneMap();
        void doneReduce();
        void doneTrans();
        void increaseHeatbeat();
        uint32_t getHeartbeatCount() const;
    };

    inline Statistics::Statistics()
    {
        m_startTime = time((time_t*)NULL);
        m_doneJobs = 0;
        m_doneMapTasks = 0;
        m_doneReduceTasks = 0;
        m_doneTransTasks = 0;
        m_heartbeatCount = 0;
    }
    
}


#endif /* _STATISTICS_HPP */
