/** @file ChunkServerService.ice
 * Services that a ChunkServer uses to communicate with the Master.
 * It's used to upload current load information and chunk reports.
 *
 * The only way a Master can communicate with the Master is by
 * returning values from these functions.
 *
 * @author YangZhifeng
 * @date 14  3  2007
 */
#ifndef _CHUNKSERVERSERVICE_ICE
#define _CHUNKSERVERSERVICE_ICE 1
#include <Exceptions.ice>
#include <MasterCommand.ice>
#include <Address.ice>
#include <Heartbeat.ice>
module tfs
{
    module slice  
    {
            
        interface ChunkServerService
        {
            /** 
             * Register this ChunkServer to Master. A ChunkServer must enroll
             * itself when start or restart service. If a ChunkServer call 
             * the others RPC before its register, the exception UnknownChunkServer
             * will raise. 
             * 
             * @param chunkServerAddress unique identity of this ChunkServer
             *        
             */
            void enroll(Address chunkServerAddress);
                    
            /**
             * sendHeartbeat() tells the Master that the ChunkServer is still
             * alive and well.  Includes some status info, too. 
             * It also gives the Master a chance to return a "MasterCommand" object.
             * A MasterCommand tells the ChunkServer to invalidate local chunk(s), 
             * or to copy them to other ChunkServer, etc.
             *
             * @param chunkServerAddress unique identity of this ChunkServer
             * @param info heartbeat infomation 
             * @throw UnknownChunkServer
             */

            MasterCommand sendHeartbeat(Address chunkServerAddress,
                                        Heartbeat info) throws UnknownChunkServer;
            /**
             * chunkReport() tells the Master about all the locally-stored chunks.
             * This function is meant to upload *all*
             * the locally-stored chunkss.  It's invoked upon startup and then
             * infrequently afterwards.
             * 
             * @param chunkServerAddress unique identity of this ChunkServer
             * @param chs the locally stored    
             * 
             * @throw UnknownChunkServer
             */
            void chunkReport(Address chunkServerAddress,
                             Chunks chks) throws UnknownChunkServer;
    
            /*
             * chunkReceived() allows the ChunkServer to tell the Master about
             * recently-received chunk data after last chunkReport call.  
             * For example, whenever client code
             * writes a new chunk here, or another ChunkServer copies a chunk to
             * this ChunkServer, it will call chunkReceived().
             * This function is used to help chunk migration task. The ChunkServer
             * needn't to report the chunks received from a client, which are reported
             * by client to Master.
             *
             * @param id the ChunkServer ID allocated by the Master
             * @param chs the recently received chunks from other ChunkServer
             * @throw UnknownChunkServer                     
             */

            //void chunkReceived(Address chunkServerAddress,
            //Chunks chks) throws UnknownChunkServer;

            /** 
             * Report to master data written successfully. If a chunk is successfully modified,
             * the client should report it to the master, so the master can change its metadata.
             * This function is used to help chunk migration task. When a chunk server has 
             * successfully written a chunk to other chunk servers, it must report to the Master.
             *
             * @param lchk chunk with locations where it has been written successfully
             * @throw NoSuchChunk the chunk in lchk is unknown 
             * @throw UnknownChunkServer one of the locations in lchk is unknown
             */
            void completeMigrateChunk(LocatedChunk lchk) throws NoSuchChunk, UnknownChunkServer;
        };

    };

};


#endif /* _CHUNKSERVERSERVICE_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
