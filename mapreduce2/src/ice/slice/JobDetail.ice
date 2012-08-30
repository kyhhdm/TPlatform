/** 
 * @file JobDetail.ice
 * 
 * @author YangZhifeng
 * @date 07 12月 2007
 */
#ifndef _JOBDETAIL_ICE
#define _JOBDETAIL_ICE 1

#include <MapReduceJob.ice>

module mapreduce
{
    module slice
    {
        /// @see src/master/JobInfo.hpp
        struct JobDetail
        {
            int id;
            int createTime;
            int finishTime;
            int status;
            bool detached;
            MapReduceJob jobSpec;
        };
        sequence<JobDetail> JobsDetail;
    };
};


#endif /* _JOBDETAIL_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
