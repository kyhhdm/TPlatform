/** @file AdminService.ice
 * The RPC interface provide administrative service of master.
 *
 * @author YangZhifeng
 * @date 2007-08-29
 */
#ifndef _ADMIN_SERVICE_ICE
#define _ADMIN_SERVICE_ICE

#include <Address.ice>

module tfs
{
    module slice{
        sequence<int> OperationsCount;
        
        interface AdminService {
            idempotent string getStartTime();
            idempotent Addresses getChunkServers();
            idempotent Addresses getClients();
            idempotent OperationsCount getOperationsCount();
        };
            
    };
};

#endif
// Local Variables: ***
// mode:c++ ***
// End: ***
