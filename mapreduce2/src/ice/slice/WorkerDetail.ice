/** 
 * @file WorkerDetail.ice
 * 
 * @author YangZhifeng
 * @date 2008-03-21
 */
#ifndef _WORKERDETAIL_ICE
#define _WORKERDETAIL_ICE 1

#include <Address.ice>

module mapreduce
{
    module slice
	{
	    struct WorkerDetail
	    {
		/// worker address
		Address addr;
		/// map task number
		int mapTaskCount;
		/// reduce task number
		int reduceTaskCount;
		/// trans task number
		int transTaskCount;
		/// current workload
		int workload;
		/// completed map task number
		int mapDoneCount;
		/// completed reduce task number
		int reduceDoneCount;
		/// completed trans task number
		int transDoneCount;
	    };
	    sequence<WorkerDetail> WorkersDetail;
	};
};


#endif /* _JOBDETAIL_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
