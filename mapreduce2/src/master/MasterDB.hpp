/** 
 * @file MasterDB.hpp
 * The singleton masterdb.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _MASTERDB_HPP
#define _MASTERDB_HPP 1

#include "master/JobManager.hpp"
#include "master/WorkerManager.hpp"
#include "master/TaskManager.hpp"
#include "master/Statistics.hpp"
#include <tfs/TfsFile.hpp>          // to use tfs special service for mapreduce
#include <tfs/tfs.h>                // to use tfs api 

namespace mapreduce{
    class TaskManager;
    
    class MasterDB
    {        
	Logger m_logger;
        MasterDB();
    public:
        static MasterDB* instance();
        /// the important internal data structures for scheduling the tasks
        JobManager m_jobs;
        WorkerManager m_workers;
        TaskManager m_tasks;
        /// statistical info
        Statistics m_statistics;

        /// proxy to use tfs service.
        tfs::mapred::TfsFile m_tfsFile;
        tfs::api::FileSystem m_tfs;

        //@{ functions which is not suitable for m_jobs or m_workers or m_tasks
        /** 
         * Cancel the job. 
	     * Canceling the job will also cancel all its tasks and release the resources
         * @return 0 if success, -1 if the job does not exist or error occurs
         **/
        int32_t cancelJob(int32_t jobId);
        //@}
    };
}


#endif /* _MASTERDB_HPP */
