/** 
 * @file WorkerManager.hpp
 * Manager all the workers informations.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _WORKERMANAGER_HPP
#define _WORKERMANAGER_HPP 1

#include "master/WorkerInfo.hpp"
#include "util/Logger.hpp"
#include "common/IceGenerated.hpp"
#include "common/AddressHelper.hpp"
#include "master/TaskInfo.hpp"
#include "master/JobInfo.hpp"

#include <ext/hash_map>
#include <IceUtil/Mutex.h>
#include <IceUtil/RWRecMutex.h>

namespace mapreduce{
    class WorkerManager
    {
        /// map workerId->info
        typedef __gnu_cxx::hash_map<Address, WorkerInfo, AddressHash, AddressEqual> address2info_t;
        address2info_t m_worker2info;
        /**
         * Those workers who don't renew heartbeat for more than
         * m_expireTime will be considered halted. 
         *
         */
        int32_t m_expireTime;
        /// we are in safe mode when there is no enough workers (less than m_safeModeThreshold)
        int32_t m_safeModeThreshold;
        /// we are also in safe mode when this variable is true
        bool m_safeMode;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// mutex for the priority setting
        IceUtil::RWRecMutex m_wMutex;
        
        /// logger
        mutable Logger m_logger;

        /// randomly select a worker.
        Address selectWorkerRandomly() const;

        // forbid copy
        WorkerManager(const WorkerManager& other);
        WorkerManager& operator=(const WorkerManager& other);
    public:
        class ToggleSafeMode{
            WorkerManager& m_workers;
        public:
            /// set safemode true
            ToggleSafeMode(WorkerManager& workers);
            /// set safemode false
            ~ToggleSafeMode();
        };
    public:
        /// constructor
        WorkerManager(int32_t expireTime, int32_t safeModeThreshold);
        /// destructor
        ~WorkerManager();
        /** 
         * update the heartbeat of the worker
         * 
         * @param worker 
         * @param heartbeat 
         */
        void renewHeartbeat(const Address& worker, const Heartbeat &heartbeat);
        /** 
         * select one worker from all 
         * 
         * @param candidateWorkers 
         * 
         * @return 
         */
        Address selectWorker(const Addresses& candidateWorkers) const;
        /** 
         * get all the workers' addresses
         * 
         * @return 
         */
        Addresses getAllWorkers() const;
        /** 
         * get the number of workers
         * 
         * @return the count
         */
        int32_t count() const;
        /**
         * get all the workers' information
         */
        Workers getWorkers() const;
        /**
         * workers which don't renew for more than m_expireTime will be removed
         * 
         * @return all the expired workers
         */
        Addresses removeExpired();
        /**
         * set safe mode
         */
        void setSafeMode(bool safeMode);
        /**
         * whether are we in safe mode
         */
        bool isSafeMode() const;
        /** 
         * increase the number of tasks been done by the worker
         * 
         * @param worker 
         * @param type task type
         */
        void increaseDoneTasks(const Address& worker, TaskType type);
        /** 
         * get all the free (not busy) workers
         * 
         * 
         * @return 
         */
        //Addresses getFreeWorkers() const;
        /**
         * whether the worker free
         * 
         */
        //bool isFree(const Address& worker) const;
        /**
         * @add by Chen Rishan
         * set the schdule list
         *
         * @param tasks, which owns unique jobid
         * @param jobPrio, priority of job
         *
         * */
        void setJobPriority(Tasks& tasks,JobPriority jobPrio);

        /**
         * job schedule, to guarantee the balance of jobs
         *
         * @param worker
         *
         * @return jobid
         * */
        int32_t getPriorJob(const Address& worker);
        
        /**
         * remove completed job from schedule lists
         * 
         * @param Jobid
         *
         * @return
         * */
        bool removeScheduledJob(int32_t jobId);

    };

    inline WorkerManager::WorkerManager(int32_t expireTime, int32_t safeModeThreshold)
        :m_expireTime(expireTime), 
         m_safeModeThreshold(safeModeThreshold),
         m_safeMode(false),
         m_logger(Logger::getInstance("master"))
    {
    }
    inline WorkerManager::ToggleSafeMode::ToggleSafeMode(WorkerManager& workers)
        :m_workers(workers)
    {
        m_workers.setSafeMode(true);
    }
    inline WorkerManager::ToggleSafeMode::~ToggleSafeMode(){
        m_workers.setSafeMode(false);
    }        

}


#endif /* _WORKERMANAGER_HPP */
