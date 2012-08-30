/** @file Chunk.ice
 * The basic data type which presents a chunk of data. It corresponds to a file on local filesystem. 
 * @author YangZhifeng
 * @date 13  3 2007
 */
#ifndef _CHUNK_ICE
#define _CHUNK_ICE 1
#include <Address.ice>
module tfs
{
    module slice
        {
            struct Chunk
            {
                long id;
                long size;
                long version;
            };
            sequence<Chunk> Chunks;
  
            struct LocatedChunk
            {
                Chunk chk;
                // locations of the chunk where it is stored, they are addresses of the ChunkServers
                Addresses locations;
            };
            sequence<LocatedChunk> LocatedChunks;
        };
    
};

#endif /* _CHUNK_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
