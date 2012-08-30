/** 
 * @file WorkerService.ice
 * 
 * @author YangZhifeng
 * @date 28 11月 2007
 */
#ifndef _WORKERSERVICE_ICE
#define _WORKERSERVICE_ICE 1

//#include <Exceptions.ice>
#include <MasterCommand.ice>
#include <Address.ice>
#include <Heartbeat.ice>

module mapreduce
{
    module slice
    {
        interface WorkerService
        {
            /**
             * sendHeartbeat() tells the Master that the Worker is still
             * alive and well.  The heartbeat message includes some status info, too. 
             * It also gives the Master a chance to return a "MasterCommand" object
             * which tells the worker to do some jobs.
             * 
             * @param workerAddress unique identity of this worker. This address is also used as the datatransfer socket. 
             * @param info heartbeat infomation 
             */
            idempotent MasterCommands sendHeartbeat(Address workerAddress,
                                        Heartbeat info);
            /** 
             * report to the master the task is successfully completed.
             * 
             * @param taskID 
             */
            idempotent void completeTask(Address workerAddress, int taskID);
            /** 
             * report to the master the task failed. 
             * The master will re-schedule the task. 
             * 
             * @param taskId 
             */
            idempotent void abandonTask(Address workerAddress, int taskId);
        };
    };
};



#endif /* _WORKERSERVICE_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
