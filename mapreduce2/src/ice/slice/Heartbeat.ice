/** 
 * @file Heartbeat.ice
 * 
 * @author YangZhifeng
 * @date 28 11月 2007
 */
#ifndef _HEARTBEAT_ICE
#define _HEARTBEAT_ICE 1

module mapreduce
{
    module slice
    {
        /// information sent by ChunkServers to Master periodly. 
        struct Heartbeat
        {
            /// map job number
            int mapJobCount;
            /// reduce job number
            int reduceJobCount;
            /// current workload
            int workload;
        };
    };
    
};


#endif /* _HEARTBEAT_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
