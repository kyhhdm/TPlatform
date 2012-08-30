/** 
 * @file JobInfo.hpp
 * Information about a Job.
 * 
 * @author Zhifeng YANG
 * @date 2007-12-01
 */
#ifndef _JOBINFO_HPP
#define _JOBINFO_HPP 1
#include "common/IceGenerated.hpp" // for mapreduce::slice::MapReduceJob
#include <TfsFile.hpp>          // for tfs::mapred::*
#include <IceUtil/Mutex.h>

#include <iterator>
#include <algorithm>
#include <ctime>

namespace mapreduce{
    enum JobStatus{
        JS_IDLE,
        JS_INPROGRESS,
        JS_COMPLETED, 
        JS_CANCELLED
    };
    
    enum JobPriority{
        JP_URGENT = 0,
        JP_REAL,
        JP_HIGH,
        JP_MIDDLE,
        JP_LOW
    };

    struct JobInfo
    {
        /// create time
        time_t createTime;
	    /// finish(JS_COMPLETED or JS_CANCELLED) time
	    time_t finishTime;
        /// job status
        JobStatus status;
        /// committed job specification
        MapReduceJob jobSpec;
        /// chunks info of the input tfs file(s)
        tfs::mapred::LocatedChunks lchks;
        /// detached by the client
        bool bDetached;
        /// priority of the job
        JobPriority jobInitPriority;
    };
    
    typedef std::pair<int32_t, JobInfo> Job;
    typedef std::vector<Job> Jobs;

    inline std::ostream& operator << (std::ostream &os, const MapReduceJob& jobSpec)
    {
        os << "jobSpec[input=" << jobSpec.inputFile
           << " output=" << jobSpec.outputFile
           << " outputReplica=" << jobSpec.outputReplication
           << " so=" << jobSpec.soFile
           << " #map=" << jobSpec.mapTaskNum
           << " #reduce=" << jobSpec.reduceTaskNum
           << " combine=" << jobSpec.doLocalCombine
           << " groupBysort=" << jobSpec.doGroupBySort
           << "]";
        return os;
    }

    inline std::ostream& operator << (std::ostream &os, const Job& job)
    {
        os << "job[id=" << job.first 
           << " create=" << ctime(&job.second.createTime)
           << " status=" << job.second.status 
           << " bDetached=" << job.second.bDetached
           << " jobSpec=" << job.second.jobSpec
           << " jobPriority=" << job.second.jobInitPriority
           << " ]";
        return os;
    }

    inline std::ostream& operator << (std::ostream &os, const Jobs& jobs)
    {
        std::copy(jobs.begin(), jobs.end(), std::ostream_iterator<Job>(os, " "));
        return os;
    }

}


#endif /* _JOBINFO_HPP */
