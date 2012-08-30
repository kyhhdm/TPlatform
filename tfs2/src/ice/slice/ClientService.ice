/** @file
 * The RPC interface between clients and master. The clients use this 
 * interface to communicate with the Master.
 * @author YangZhifeng
 * @date 2007-03-13
 */
#ifndef _CLIENT_SERVICE_ICE
#define _CLIENT_SERVICE_ICE

#include <Exceptions.ice>
#include <Chunk.ice>
#include <FileInfo.ice>
#include <Address.ice>

module tfs
{
    module slice
        {
            
            /*
             * argument value of open function
             * @see ClientService::open
             */

            enum FileOpenMode{ FileOpenWrite, 
                               FileOpenRead, 
                               FileOpenAppend};
            
            /**
             * The type of lock on a file
             * @see ClientService::lockFile ClientService::unlockFile
             */
//             enum FileLockType{ ReadLock, 
//                                WriteLock};
    
            sequence<string> Strings;
    
            interface ClientService {
  
                ///////////////////////////////////////
                // File operations
                ///////////////////////////////////////
                /**
                 * Open an existing file, at the given name.   The master will lock
                 * the file and path according to open mode given here.
                 * 
                 * @param client name of client
                 * @param filename filename to open, includes the absolute path
                 * @param mode open mode
                 * @throw LockFail if `write after read' or `write after write' or `read after write'
                 * @throw NoSuchFileOrDir
                 *
                 * @see FileOpenMode
                 */
                void open( Address client,
                           string filename,
                           int mode
                    ) throws LockFail, NoSuchFileOrDir;

                /**
                 * Close an opened file. This operation will lead to master's release of 
                 * the corresponding locks on the file chunks.
                 * 
                 * @param client 
                 * @param filename
                 * @see ::open
                 */
                idempotent void close( Address client,
                                       string filename);

                /*
                 * Lock a file with WriteLock or ReadLock. This will lead to ReadLock be set 
                 * for all of its path nodes. The client MUST lock the file with the proper lock
                 * before reading or writing or appending it. 
                 * 
                 * @param client "ip:port"
                 * @param filename the filename must be UTF-8 encoded string
                 * @param lockType WriteLock or ReadLock
                 * 
                 * @throw LockFail if `write after read' or `write after write' or `read after write'
                 */
//                 void lockFile( Address client,
//                                string filename, 
//                                FileLockType lockType) throws LockFail;

                /* 
                 * Release the lock on a file. The client must release the lock before closing 
                 * the file. 
                 * 
                 * @param client 
                 * @param filename 
                 */
//                 void unlockFile( Address client, 
//                                  string filename);
        
                /** 
                 * Get the locations of all the chunks of a file. 
                 * Returns chunks and their
                 * ChunkServer info.  ChunkServers for each block are sorted by
                 * the distance to the client, which contains the host name.
                 * The client will then have to contact
                 * each indicated ChunkServer to read or write the actual data.
                 * 
                 * @param client
                 * @param filename 
                 * 
                 * @return Chunks with locations where they are stored
                 *
                 * @throw NoSuchFileOrDir 
                 */
                LocatedChunks getChunksInfo( Address client,
                                             string filename) throws NoSuchFileOrDir;
                /** 
                 * Report the master the chunk has been written completely.
                 * A client that has added a chunk of data can report completion
                 * back to the Master with completeWrittenChunk().  Clients should not
                 * obtain an additional chunk until the previous one has either been 
                 * reported as written or abandoned.
                 * A chunk is said to "written completely" if and only if at least one copy 
                 * of this chunk has been stored successfully. 
                 *
                 * @param lchk chunk with locations where it has been written successfully
                 * @throw NoSuchChunk
                 * @throw UnknownChunkServer
                 */

                void completeWrittenChunk(LocatedChunk lchk) throws NoSuchChunk, UnknownChunkServer;

                /** 
                 * Report to master data written successfully. If a chunk is successfully modified,
                 * the client should report it to the master, so the master can change its metadata.
                 * This method is used by client to update chunk size now, other information is 
                 * ignored by the master.
                 * 
                 * @param lchk 
                 * @throw NoSuchChunk the chunk must have been committed by completeWrittenChunk()
                 */
                void updateChunkInfo(LocatedChunk lchk) throws NoSuchChunk;

                /**
                 * Add a new chunk to the file.
                 *
                 * A client that wants to write or read an arbitrary block to the 
                 * indicated filename (which must currently be open for writing)
                 * should call addChunk().  
                 * 
                 * @pre the file must have be set ReadLock
                 * @param client
                 * @param filename
                 * 
                 * @return Chunk with locations where it is stored
                 *
                 * @throw NoSuchFileOrDir
                 * @throw NoChunkAllocated ChunkServer could not allocate a chunk,
                 *                         the caller should try again.
                 */
                LocatedChunk addChunk(Address client, string filename) throws NoSuchFileOrDir, NoChunkAllocated;        

                /**
                 * Abandon the write  to a chunk. 
                 * If the client has not yet called completeAddChunk(), it can
                 * give up on it by calling abandonAddChunk().  The client can then
                 * either obtain a new chunk, or complete the file.
                 *
                 * Any partial writes to the chunk will be garbage-collected.
                 * @param filename file the chunk belongs to
                 * @param chk the chunk to be abandoned
                 *
                 * @throw NoChunkAllocated the master does not allocated such a new chunk
                 */
                void abandonAddChunk(Chunk chk) throws NoChunkAllocated;

                /**
                 * The client wants to report corrupted chunks (chunks with specified
                 * locations on ChunkServers). The master will invalidate these chunk
                 * locations and garbage-collect them enventually. The client should 
                 * reprot bad chunks in batch to save the communication overhead.
                 * @param chunks Array of located bad chunks to report
                 */
                idempotent void reportBadChunks(LocatedChunks chunks);

                /**
                 * Set replication for an existing file.
                 * 
                 * Sets replication to the new value and returns.
                 * The actual chunk replication is not expected to be performed during  
                 * this method call. The blocks will be populated or removed in the 
                 * background as the result of the routine chunk maintenance procedures.
                 *
                 * If parameter 'replication' is 0, use the system default. 
                 * 
                 * @param filename file name
                 * @param replication new replication
                 * @throw NoSuchFileOrDir
                 * @throw ReplicationOutOfRange replication is out of range that allowed
                 */
                idempotent void setReplication( string filename, 
                                                short replication) throws NoSuchFileOrDir, ReplicationOutOfRange;
                
                /**
                 * Get information about the file
                 * @param filename 
                 * @return information about the file
                 * @throw NoSuchFileOrDir
                 */
                idempotent FileInfo getFileInfo(string filename) throws NoSuchFileOrDir;
     

                ///////////////////////////////////////
                // Namespace management
                ///////////////////////////////////////

                /**
                 * Create a new file. If there's something wrong, the 
                 * client should check the exception for details
                 * If parameter 'replication' is 0, use the system default. 
                 * If parameter 'chunkSize' is 0, use the system default.
                 * If the path to the file has not existed, they will be created.
                 * For example, When creating '/a/b/c', if directory 'a' or 'b' 
                 * does not exist, they will be created. 
                 * 
                 * @param filename file to create, the filename should start with '/'
                 * @param replication chunk replication of this file
                 * @param chunkSize the max chunk size of this file
                 *
                 * @throw FileOrDirAlreadyExists there has been a file or dir with the same name
                 * @throw InvalidFileOrDirName the filename is invalid
                 * @throw ReplicationOutOfRange the replication is out of range that allowed
                 * @throw ChunkSizeOutOfRange the chunkSize is out of range that allowed
                 *
                 */
                void create( string filename,
                             short replication,
                             long chunkSize) 
                    throws FileOrDirAlreadyExists, InvalidFileOrDirName, ReplicationOutOfRange, ChunkSizeOutOfRange;

                /**
                 * Rename a file
                 * 
                 * @throw NoSuchFileOrDir the src does not exist
                 * @throw FileOrDirAlreadyExists there is a file with the same name as dst
                 * @throw InvalidFileOrDirName the filename dst is invalid, @see create
                 */
                void rename(string src, string dst) 
                    throws FileOrDirAlreadyExists, NoSuchFileOrDir, InvalidFileOrDirName;

                /**
                 * Remove the given file from the filesystem. 
                 * @throw NoSuchFileOrDir
                 * @throw LockFail the file is locked
                 */
                void remove(string src) throws NoSuchFileOrDir, LockFail;

                /**
                 * Create new dir.
                 * If the components of the path to the new dir has not existed, 
                 * they will be created.
                 * For example, When creating '/a/b/c/', if directory 'a' or 'b' 
                 * does not exist, they will be created. 
                 *
                 * @throw FileOrDirAlreadyExists
                 * @throw InvalidFileOrDirName the dir name src is invalid
                 */
                void mkdir(string src) throws FileOrDirAlreadyExists, InvalidFileOrDirName;

                /**
                 * Rename a dir in the namespace.
                 * 
                 * @throw FileOrDirAlreadyExists there is a file or dir with the same name as dst
                 * @throw NoSuchFileOrDir src does not exist
                 * @throw InvalidFileOrDirName dst is invalid
                 */
                void renamedir(string src, string dst) 
                    throws FileOrDirAlreadyExists, NoSuchFileOrDir, InvalidFileOrDirName;

                /**
                 * Remove the given filename from the filesystem. 
                 * If the name is a dir, this operation will delete all the
                 * files in the directory! 
                 *
                 * @throw NoSuchFileOrDir
                 * @throw LockFail the dir is locked
                 * @throw InvalidFileOrDirName the dir is invalid
                 */
                void rmdir(string src) throws NoSuchFileOrDir, LockFail, InvalidFileOrDirName;
                
                /**
                 * Check whether the given file or dir exists
                 * @deprecated use getFileInfo instead
                 */
                //idempotent bool exists(string src);

                /**
                 * Check whether the given name is dir
                 * @throw NoSuchFileOrDir
                 * @deprecated use getFileInfo instead
                 */
                // idempotent bool isdir(string src) throws NoSuchFileOrDir;

                /**
                 * List dir
                 *
                 * @throw NoSuchFileOrDir the dir 'src' does not exist (maybe it is a file)
                 * @throw InvalidFileOrDirName src is invalid
                 *
                 */
                idempotent FilesInfo lsdir(string src) throws NoSuchFileOrDir, InvalidFileOrDirName;
                /** 
                 * concat the srcFiles' metadata which combine to form the dst file.
                 * The srcFiles will be removed from the namespace if the operation is successfully done.
                 * This operation can be used to generate 'hard link', but now only used by mapreduce.
                 * 
                 * @param srcFiles 
                 * @param dst 
                 * 
                 * @throw NoSuchFileOrDir one of the srcFiles does not exist
                 * @throw FileOrDirAlreadyExists there is a file with the same name as dst
                 * @throw InvalidFileOrDirName the filename dst is invalid, @see create
                 */
                void concatFiles(Strings srcFiles, string dst)
                    throws FileOrDirAlreadyExists, NoSuchFileOrDir, InvalidFileOrDirName;

                ///////////////////////////////////////
                // System issues and management
                ///////////////////////////////////////
                /**
                 * Report heartbeat of the client to master. This function
                 * must be invoked by client periodly to show that it is
                 * alive. 
                 * 
                 */
                idempotent void reportHeartbeat(Address clientAddress);
            };
        };
    
};

#endif // _CLIENT_SERVICE_ICE

// Local Variables: ***
// mode:c++ ***
// End: ***
