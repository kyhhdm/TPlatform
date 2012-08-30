/** 
 * @file MonitorService.ice
 * RPC interface for web monitor to get system information
 * @author YangZhifeng
 * @date 05 12月 2007
 */
#ifndef _MONITORSERVICE_ICE
#define _MONITORSERVICE_ICE 1

#include <Address.ice>
#include <JobDetail.ice>
#include <TaskDetail.ice>
#include <WorkerDetail.ice>
module mapreduce
{
    module slice
    {
        sequence<int> TasksStatistics;
        
        /**
         * service used by monitor to get system information from master.
         * 
         */
        interface MonitorService
        {
	    //@{ 
	    /**
	     * Functions to get system statistics
	     */
            int getStartTime();
	    int getCompletedJobs();
	    int getCompletedTasks();
            //@}

            /** 
             * get all the workers information
             * 
             * @return 
             */
            WorkersDetail getWorkers();
            /** 
             * get all the jobs information
             * 
             * @return 
             */
            JobsDetail getJobs();
            /** 
             * get all the tasks information of the given job
             * 
             * @param jobId 
             * 
             * @return 
             */
            TasksDetail getTasks(int jobId);
            /** 
             * get the tasks statistic information of the job
             * 
             * @param jobId 
             * 
             * @return 
             */
            TasksStatistics getTasksStat(int jobId);
	    
        };
    };
};


#endif /* _MONITORSERVICE_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
