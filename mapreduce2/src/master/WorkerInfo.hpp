/** 
 * @file WorkerInfo.hpp
 * worker information.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _WORKERINFO_HPP
#define _WORKERINFO_HPP 1
#include "common/IceGenerated.hpp"
#include <list>

#define SCHE_LISTS_NUM 5
#define INIT_TIME_SLICE_URGENT  5 
#define INIT_TIME_SLICE_REAL    10 
#define INIT_TIME_SLICE_HIGH    20 
#define INIT_TIME_SLICE_MIDDLE  30 
#define INIT_TIME_SLICE_LOW     50 

namespace mapreduce{
    class Address;
    
    class ScheInfo{
    public:
        int32_t jobid;
        int32_t timeslice;
        int getTimeslice(int priority){
            switch(priority){
                case 0:
                    return INIT_TIME_SLICE_URGENT;
                case 1:
                    return INIT_TIME_SLICE_REAL;
                case 2:
                    return INIT_TIME_SLICE_HIGH;
                case 3:
                    return INIT_TIME_SLICE_MIDDLE;
                case 4:
                    return INIT_TIME_SLICE_LOW;
            };
            return -1;
        }
    };

    struct WorkerInfo
    {
        time_t m_lastUpdate;
        Heartbeat m_heartbeat;
        /// the number of map tasks which have been done.
        int32_t m_doneMapTasks;
        /// the number of reduce tasks which have been done.
        int32_t m_doneReduceTasks;
        /// the number of trans tasks which have been done.
        int32_t m_doneTransTasks;
        
        /// multi schedule-list for job scheduling
        std::list<ScheInfo> m_scheLists[SCHE_LISTS_NUM];

        WorkerInfo()
            :m_doneMapTasks(0), m_doneReduceTasks(0), m_doneTransTasks(0)
            {
            }
    };
    typedef std::pair<Address, WorkerInfo> Worker;
    typedef std::vector<Worker> Workers;

    struct WorkerLessThan
    {
        bool operator() (const Worker& address1, const Worker& address2) const
        {
            return address1.first < address2.first;
        }
    };

}


#endif /* _WORKERINFO_HPP */
