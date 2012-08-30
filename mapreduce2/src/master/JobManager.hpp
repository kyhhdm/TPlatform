/** 
 * @file JobManager.hpp
 * Manager of jobs commited by clients.
 * Each `job' is divided into several map and reduce tasks. 
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _JOBMANAGER_HPP
#define _JOBMANAGER_HPP 1
#include "master/JobInfo.hpp"
#include "common/IceGenerated.hpp"
#include "util/Logger.hpp"
#include <IceUtil/Mutex.h>
#include <map>
#include <set>

namespace mapreduce{
    class JobManager{
        /// map: jobid->jobinfo
        typedef std::map<int32_t, JobInfo> id2info_t;
        id2info_t m_id2info;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// logger
        mutable Logger m_logger;

        /** 
         * allocate a new job id
         * @return the job id
         */
        int32_t newId() const;

        // forbid copy
        JobManager(const JobManager& other);
        JobManager& operator= (const JobManager& other);

    public:
        /// constructor
        JobManager();
        /// destructor
        ~JobManager();
        /** 
         * add a new job. 
         * 
         * @param job 
         * 
         * @return job ID
         */
        int32_t add(const mapreduce::slice::MapReduceJob &job, const tfs::mapred::LocatedChunks& lchks);
        /** 
         * remove the job.
         * 
         * @param jobId 
         */
        void remove(int32_t jobId);
        /** 
         * get the specified job. 
         * 
         * @param jobId 
         * 
         * @return the job. the jobId property is -1 if the job does not exist. 
         */
        Job getJob(int32_t jobId) const;
        /** 
         * set the job detached.
         * 
         * @param jobId 
         */
        void setJobDetached(int32_t jobId);
        /** 
         * set the job's status. 
         * 
         * @param jobId 
         * @param status 
         */
        void setJobStatus(int32_t jobId, JobStatus status);
        /** 
         * get all the jobs
         * 
         * @return 
         */
        Jobs getAllJobs() const;
        
    };

    inline JobManager::JobManager()
        :m_logger(Logger::getInstance("master"))
    {
    }
}


#endif /* _JOBMANAGER_HPP */
