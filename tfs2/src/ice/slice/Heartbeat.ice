/** 
 * @file Heartbeat.ice
 * 
 * @author YangZhifeng
 * @date 23  5 2007
 */
#ifndef _HEARTBEAT_ICE
#define _HEARTBEAT_ICE 1

module tfs
{
    module slice
        {
            
            /// information sent by ChunkServers to Master to say that "hey, I am alive."
            struct Heartbeat
            {
                /// storage capacity (Bytes)
                long capacity;		
                /// free space (Bytes)
                long free;
                /// current workload
                int workload;
            };
        };
    
};



#endif /* _HEARTBEAT_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
