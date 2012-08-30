/** 
 * @file JobService.ice
 * 
 * @author YangZhifeng
 * @date 28 11月 2007
 */
#ifndef _JOBSERVICE_ICE
#define _JOBSERVICE_ICE 1

#include <MapReduceJob.ice>
#include <JobDetail.ice>

module mapreduce
{
    module slice
    {
        /**
         * service used by client to commit mapreduce job to the master
         * 
         */
        interface JobService
        {
            /** 
             * Create a job and return immediately.
             * 
             * @param job specification of the job
             * @return the job id. The value -1 means failure. A valid job id 
             * should be a integer >= 0.
             */
            int create(MapReduceJob job);
            /**
             * Get job informations. e.g. job status, job finish time
             * The client use this operation to check the status and other information of the job.
             * The system will release its resources automatically after the job completes
             * 
             * @param jobId the job id returned by `create'
             * @return JobDetail.id is -1 when the job does not exist or error occurs
             */
            JobDetail getJobDetail(int jobId);
            /** 
             * Kill a job in progress. 
             * The system will release the resources.
             * @param jobId the job id returned by `create'
             * @return 0 if success, -1 if the job does not exist or error occurs
             */
            int kill(int jobId);
        };
    };    
};


#endif /* _JOBSERVICE_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
