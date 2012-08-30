/** 
 * @file Address.ice
 * 
 * @author YangZhifeng
 * @date 28 11月 2007
 */
#ifndef _ADDRESS_ICE
#define _ADDRESS_ICE 1

module mapreduce
{
    module slice
        {
            
            /**
             * The unique id of a worker
             */
            struct Address
            {
                /// host name or IP address.
                string name;
                /// data transfer port number.
                int port;
            };
            sequence<Address> Addresses;
        };
    
};


#endif /* _ADDRESS_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
