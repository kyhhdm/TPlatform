/** @file MasterCommand.ice
 * MasterCommand return to ChunkServer by Master
 * @author YangZhifeng
 * @date 14  3  2007
 */
#ifndef _MASTERCOMMAND_ICE
#define _MASTERCOMMAND_ICE 1
#include <Chunk.ice>
#include <Address.ice>

module tfs
{
    module slice
        {
            enum Action{
                McDoNothing, McRegister, McRemoveChunks, McTransferChunks, McShutdown
            };
  
            struct MasterCommand
            {
                Action command;
                /// chunks to be removed or transfered
                Chunks chks;		
                /// ChunkServers to transfer the chunks to	
                Addresses targets;	
            };
        };
};

  

#endif /* _MASTERCOMMAND_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
