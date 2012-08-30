/** 
 * @file Address.ice
 * 
 * @author YangZhifeng
 * @date 23  5 2007
 */
#ifndef _ADDRESS_ICE
#define _ADDRESS_ICE 1

module tfs
{
    module slice
        {
            
            /**
             * The unique id of ChunkServer or Client. 
             */
            struct Address
            {
                /** host name or IP address. 
                 * If used by a ChunkServer, it can be used by 
                 * client or another chunkserver
                 * to communicate with this chunkserver. 
                 * If used by a Client, it just used by Master as an identity. 
                 */
                string name;
                /** data transfer port number. 
                 * If used by a ChunkServer, it can be used by client or another ChunkServer to transfer data through
                 * this port. If used by a Client, it just used by Master as an identity. 
                 */
                int port;
            };
            sequence<Address> Addresses;
        };
    
};


#endif /* _ADDRESS_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
