/** @file FsDirectoryImpl.hpp
 * FsDirectoryImpl stores the filesystem directory state.
 * It handles writing/loading values to disk, and logging
 * changes as we go.
 *
 * It keeps the filename->blockset mapping always-current
 * and logged to disk.
 *
 * @author PengBo
 * @date 28 5 2007
 *
 * Design Notes: <br>
 *    1. use errorcode or exception? 
 *       ==> use exception.                                                     <br>
 *    2. use HoldA other than HasA ==> HoldA                                    <br>
 *    3. use string, or FileName object, like the Java File oject               <br>
 *       ==> use string vector for simplicity, but I like Java's facilit        <br>
 *    4. ptr or references in parameter?                                        <br>
 *       ==> refer to [Sutter,2005].Ch25                                        <br>
 *    5. return an pointer to object, caller should delete it,not exception safe! <br>
 *       ==>so use shared_ptr here for automatically resouce management.        <br>
 *    6. add logger, but it breaks the const decorator of interface function    <br>
 *  <br>
 *
 */
#ifndef _TFSMASTER_FSDIRECTORYIMPL_HPP
#define _TFSMASTER_FSDIRECTORYIMPL_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include "util/Logger.hpp"

namespace tfs {

    class ChunkTable;
    class NewChunkTable;
    class LockTable;
    class DirTree;

    class FsDirectoryImpl {
    public:
        //yzf, I have delete locktype in ice define
        //typedef tfs::common::LockType LockType;
        //enum LockType {READLOCK, WRITELOCK};

        //1.constructors
        /** Default constructor.
         */    
        FsDirectoryImpl();

  
        virtual ~FsDirectoryImpl();

        //2. NameSpace management, include file and dir names
        /** Check the given name if exist
         * if the name has already exsited in the namespace
         * 
         * @param [in] name 
         * 
         * @return true/false
         */
        virtual bool exists(const std::string &name);

         /** Check if the given dirname is a valid dir.
         *
         * @param [in] dirname: 
         * @throws 
         * @return : true  or false 
         */    
        virtual bool isDir(const std::string& dirname) const;


        /** Add the given filename to the filesystem.
         * create the file if it does not exist, and automatically create any intermediate directory
         * if it does not exist.
         *
         * @param [in] filename: 
         * @param [in] chunkSize: max chunk size
         * @param [in] replication: replication number of the file
         * @throw FileOrDirAlreadyExists (filename already exist)
         * @throw InvalidFileOrDirName
         * @return : nothing
         */    
        virtual void createFile(const std::string& filename, int maxChunkSize = MasterConfig::DefaultMaxChunkSize, 
                        short replication = MasterConfig::DefaultReplication);

        /** Rename the source file to destination filename.
         *  
         * 
         * @param [in] src: source 
         * @param [in] dst: destination
         * @throws FileOrDirAlreadyExists(dst already exist), or LockFail(LOCK failure)
         * @return : 
         */    
        virtual void renameFile(const std::string& src, const std::string& dst);

        /** Delete a file.
         * return chunks belong to the deleted files.
         * @param [in] filename: 
         * @param [out] deletedChunks: the chunks belong to the deleted files 
         * @throws NoSuchFileOrDir(filename does't exist), LockFail(LOCK failure)
         * @return : 
         */    
        virtual void deleteFile(const std::string& filename, Chunks& deletedChunks);

        /** Create a directory by name.
         * create the directory if it does not exist, and automatically create any intermediate directory
         * if it does not exist.
         *
         * @param [in] dirname: 
         * @throws FileOrDirAlreadyExists(filename exist already)
         * @throw InvalidFileOrDirName
         * @return : 
         */    
        virtual void createDir(const std::string& dirname);

        /** Rename the source dir to destination name.
         * In fact, it has a different semantic comparing to moveDir. If dst already exist, it just 
         * throws FileOrDirAlreadyExists, otherwise it rename srouce dir to destination.
         *
         * @param [in] src: source 
         * @param [in] dst: destination
         * @throw FileOrDirAlreadyExists(dst already exist), or LockFail(LOCK failure)
         * @return : 
         */    
        virtual void renameDir(const std::string& src, const std::string& dst);

        /** Delete a directory.
         * Only empty directory can be deleted.
         * @param [in] filename: 
         * @throws NoSuchFileOrDir(dst already exist), or LockFail(LOCK failure)
         * @throws DirNotEmpty
         * @return : 
         */    
        virtual void deleteDir(const std::string& filename);

        /** Concat a group of files into a single file.
        * 
        * @param [in] srcFiles:  source file names
        * @param [in] dstFile: destination file
        * @throws NoSuchFileOrDir(filename does't exist), LockFail(LOCK failure), 
        * @throw FileOrDirAlreadyExists (filename already exist)
        * @throw InvalidFileOrDirName
        * @return : 
        */    
        virtual void concatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile);

         /** Read contents in the given dir.
         * return a smart pointer to a filelist info object.
         * @param [in] dirname: 
         * @throws NoSuchFileOrDir (dirname not exist)
         * @return : a FileInfo object contains the file list info in the given dir.
         */    
        virtual FilesInfoPtr readDir(const std::string& dirname); //const;

        //3. chunk data managment
        /** Check if a chunk is already exist in system.
         * 
         * @param [in] chunkId: chunk's id that was looked up
         * @return : const Chunk* points to found chunk, otherwise return NULL
         */    
        virtual const Chunk* findChunk(const Long chunkId);

        /** Update chunk version when write operation is done.
        * only use the id and size member of Chunk, version is maintained internally.
        * @param [in] chunk: 
        * @throws NoSuchChunk (chunk not exist)
        * @return : 
        */    
        virtual bool updateChunk(const Chunk& chunk);

        /** Allocate a new chunk for the given filename.
         * return an object directly for Chunk is just a simple structure.
         * @param [in] filename: 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return : new created chunk
         */    
        virtual Chunk newChunk(const std::string& filename, const std::string& holder, Long chunkId = 0LL);

        /** Commit a chunk when appending operation is committed.
         * make this chunk available to succeeding file operations.
         * only use the id and size member of Chunk, version is maintained internally.
         * @param [in] chunk: 
         * @throws NoSuchChunk (chunk not exist), or NoChunkAllocated(not in appedning state)
         * @return : 
         */    
        virtual void commitChunk(const Chunk& chunk);

        /** remove a chunk when a pending write is cancelled.
         *
         * @param chunk
         * @throws NoSuchChunk (chunk not exist), or NoChunkAllocated(not in appedning state)
         * @return : 
         */
        virtual void abandonChunk(const Chunk& chunk);
        
        /** Update chunk version when write operation is done.
         * only use the id and size member of Chunk, version is maintained internally.
         * @param [in] chunk: 
         * @throws FsDirectoryException (chunk notexist)
         * @return : 
         */    
        //bool updateChunk(const Chunk& chunk);

        /** Get chunks info belong to the given file.
         * 
         * @param [in] filename: 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return : return a const reference to chunk vector object
         */    
        virtual const Chunks& getFileChunks(const std::string& filename); //const;


        //4. Metadata managment
        /** Get file metadata information, including size, createtime etc. 
         * 
         * @param filename 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return The FileInfo struct
         */
        virtual FileInfo getFileInfo(const std::string& name); //const;

        /** Set file metadata information, including size, createtime etc. 
         * 
         * @param [in]  filename 
         * @param [out] info : The FileInfo struct
         * @return:
         */
        virtual void setFileInfo(const std::string& filename, const FileInfo& info);

        /** Set the replication number of a file.
         *
         * @param [in] filename: 
         * @param [in] replication: 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return the old replication
         */    
        virtual Short setReplication(const std::string& filename, Short replication);
        

        //5. locks and garbage collection
        /** Lock the file .
         *
         * @param [in] filename: 
         * @param [in] holder: owner of the lock
         * @param [in] lockType: read lock or write lock
         * @throws LockFail( LOCK failure)
         * @return : 
         */    
        virtual void obtainLock(const std::string& filename, const std::string& holder, LockType lockType);

        /** Release the lock on the file which is owned by the holder.
         *
         * @param [in] filename: 
         * @param [in] holder: owner of the lock
         * @throws LockFail( LOCK failure)
         * @return : 
         */    
        virtual void releaseLock(const std::string& filename, const std::string& holder);                 

        /** 
         * Release all the resources owned by the holder.
         * 
         * @param holder 
         */
        virtual void releaseResource(const std::string& holder);

        //6.serialization interface
        /** 
         * Save FsDirectoryImpl object into image file.
         * 
         * @param imgFileName : image file name which save the object data 
         * @throws boost::archive_exception
         */
        virtual void save(const std::string& imgFileName);

        /** 
         * Load FsDirectoryImpl object from image file.
         * 
         * @param imgFileName : image file name which save the object data 
         * @throws boost::archive_exception
         */
        virtual void load(const std::string& imgFileName);

    private:
        //
        DirTree*    m_pDirTree;

        //runtime supporting data structures
        ChunkTable* m_pChunkTable;
        NewChunkTable*  m_pNewChunkTable;
        LockTable*  m_pLockTable;

        //runtime data structures helper functions
        /** 
         * clear up the runtime supporting data.
         * 
         */
        void clearRuntimeData();

        /** 
         * Rebuild runtime supporting data from DirTree.
         * 
         */
        void rebuildRuntimeData();

        /** Logger
         */
        Logger m_logger;

    };
}

#endif /* _TFSMASTER_FSDIRECTORYIMPL_HPP */
