/** 
 * @file TaskDetail.ice
 * 
 * @author YangZhifeng
 * @date 07 12月 2007
 */
#ifndef _TASKDETAIL_ICE
#define _TASKDETAIL_ICE 1
#include <Address.ice>
module mapreduce
{
    module slice
    {
        /// @see src/master/TaskInfo.hpp
        struct TaskDetail
        {
            int id;
            int status;
            int type;
            Address worker;
        };
        sequence<TaskDetail> TasksDetail;
    };
};


#endif /* _TASKDETAIL_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
