/** @file FsDirectory.hpp
 *  FSDirectory is file system directory interface class.
 *  This is a hanlde class, implemented in FsDirectoryImpl class.
 *  Add synchronization and journal logging function support in this handle class.
 *
 *
 * Design Notes :   <br>
 *      1.> This is the interface class of directory subsystem.                         <br>
 *          In fact, it's a wrapper or handle class, which use FsJournalManager and     <br>
 *          FsDirectoryImpl as concrete implementation.                                 <br>
 *      2.> #BUGFIXED#         -- 20070903                                              <br>
 *          There is a flaw in interface member function design, it's return value.     <br>
 *          At last, we decide to use exceptions instead of error code. Pleae read      <br>
 *          the comments in @throws line for details, and the return value of many      <br>
 *          functions are nouse, thus it's @return line be empty.                       <br>
 *          Be careful!                                                                 <br>
 *      3.> Thread-Safe Problem -- 20070906                                             <br>
 *          Use multireader-singlewrite lock mechanism which Ice support with           <br>
 *          RWRecMutex. This mutex is little slower than normal one, but it may give    <br>
 *          better performance on SMP servers, I think.                                 <br>
 *          And we didn't implement finer locks here, such as lock directory node as    <br>
 *          needed dynamically, is that possible? I wonder now. Anyway, it will not     <br>
 *          so bad in performance because read is the prevailing operation.             <br>
 *
 */     
#ifndef _TFSMASTER_FSDIRECTORY_HPP
#define _TFSMASTER_FSDIRECTORY_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <IceUtil/RWRecMutex.h>

namespace tfs {

    class FsJournalManager;
    class FsDirectoryImpl;

    class FsDirectory {

    public:
        //yzf, I have delete locktype in ice define
        //typedef tfs::common::LockType LockType;
        enum LockType {READLOCK, WRITELOCK};

        //1.constructors
        /** Default constructor.
         */    
        FsDirectory();

        /** Construct from an FsJournalManager object.
         * @param [in] pFsJournal : pointer to an exist FsJournalManager object 
         * @throws JournalException
         */    
        FsDirectory(FsJournalManager* pFsJournal);

        ~FsDirectory();

        //2. NameSpace management, include file and dir names
        /** Check the given name if exist
         * if the name has already exsited in the namespace
         * 
         * @param [in] name 
         * 
         * @return true/false
         */
        bool exists(const std::string &name);

         /** Check if the given dirname is a valid dir.
         *
         * @param [in] dirname: 
         * @throws 
         * @return : true  or false 
         */    
        bool isDir(const std::string& dirname) const;


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
        void createFile(const std::string& filename, int maxChunkSize = MasterConfig::DefaultMaxChunkSize, 
                        short replication = MasterConfig::DefaultReplication);

        /** Rename the source file to destination filename.
         *  
         * 
         * @param [in] src: source 
         * @param [in] dst: destination
         * @throws FileOrDirAlreadyExists(dst already exist), or LockFail(LOCK failure)
         * @return : 
         */    
        void renameFile(const std::string& src, const std::string& dst);

        /** Delete a file.
         * return chunks belong to the deleted files.
         * @param [in] filename: 
         * @param [out] deletedChunks: the chunks belong to the deleted files 
         * @throws NoSuchFileOrDir(filename does't exist), LockFail(LOCK failure)
         * @return : 
         */    
        void deleteFile(const std::string& filename, Chunks& deletedChunks);

        /** Concat a group of files into a single file.
        * 
        * @param [in] srcFiles:  source file names
        * @param [in] dstFile: destination file
        * @throws NoSuchFileOrDir(filename does't exist), LockFail(LOCK failure), 
        * @throw FileOrDirAlreadyExists (filename already exist)
        * @throw InvalidFileOrDirName
        * @return : 
        */    
        void concatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile);

        /** Create a directory by name.
         * Create the directory if it does not exist, and automatically create any intermediate directory
         * if it does not exist.
         * This call only create directory but not file objects, be careful.
         * Example:
         *      createDir("/home/mydir/test.doc"), should create /home/mydir/ if it doest not exist,
         *      but it does nothing on test.doc.
         *
         * @param [in] dirname: 
         * @throws FileOrDirAlreadyExists(filename exist already)
         * @throw InvalidFileOrDirName
         * @return : 
         */    
        void createDir(const std::string& dirname);

        /** Rename the source dir to destination name.
         * In fact, it has a different semantic comparing to moveDir. If dst already exist, it just 
         * throws FileOrDirAlreadyExists, otherwise it rename srouce dir to destination.
         *
         * @param [in] src: source 
         * @param [in] dst: destination
         * @throw FileOrDirAlreadyExists(dst already exist), or LockFail(LOCK failure)
         * @return : 
         */    
        void renameDir(const std::string& src, const std::string& dst);

        /** Delete a directory.
         * Only empty directory can be deleted.
         *
         * @param [in] filename: 
         * @throws NoSuchFileOrDir(dst already exist), or LockFail(LOCK failure)
         * @throws InvalidFileOrDirName(Dir is not empty)
         * @return : 
         */    
        void deleteDir(const std::string& filename);

         /** Read contents in the given dir.
         * return a smart pointer to a filelist info object.
         * @param [in] dirname: 
         * @throws NoSuchFileOrDir (dirname not exist)
         * @return : a FileInfo object contains the file list info in the given dir.
         */    
        FilesInfoPtr readDir(const std::string& dirname) const;

        //3. chunk data management
        /** Check if a chunk is already exist in system.
         * 
         * @param [in] chunkId: chunk's id that was looked up
         * @return : const Chunk* points to found chunk, otherwise return NULL
         */    
        const Chunk* findChunk(const Long chunkId);

        /** Update chunk version when write operation is done.
        * only use the id and size member of Chunk, version is maintained internally.
        * @param [in] chunk: 
        * @throws NoSuchChunk (chunk not exist)
        * @return : true if id/size updated, false if there are no new data updated
        */    
        bool updateChunk(const Chunk& chunk);


        /** Allocate a new chunk for the given filename.
         * return an object directly for Chunk is just a simple structure.
         *
         * @param [in] filename: 
         * @throws NoSuchFileOrDir (filename not exist, or filename is a directory name instead a file name)
         * @return : new created chunk
         */    
        Chunk newChunk(const std::string& filename, const std::string& holder);

        /** Commit a chunk when appending operation is committed.
         * make this chunk available to succeeding file operations.
         * only use the id and size member of Chunk, version is maintained internally.
         * @param [in] chunk: 
         * @throws NoSuchChunk (chunk not exist), or NoChunkAllocated(not in appedning state)
         * @return : 
         */    
        void commitChunk(const Chunk& chunk);

        /** remove a chunk when a pending write is cancelled.
         *
         * @param chunk
         * @throws NoSuchChunk (chunk not exist), or NoChunkAllocated(not in appedning state)
         * @return : 
         */
        void abandonChunk(const Chunk& chunk);
        
        /** Update chunk version when write operation is done.
         * only use the id and size member of Chunk, version is maintained internally.
         * @param [in] chunk: 
         * @throws NoSuchChunk (chunk notexist)
         * @return : 
         */    
        //bool updateChunk(const Chunk& chunk);

        /** Get chunks info belong to the given file.
         * 
         * @param [in] filename: 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return : return a const reference to chunk vector object
         */    
        const Chunks& getFileChunks(const std::string& filename) const;


        //4. Metadata managment
        /** Get file metadata information, including size, createtime etc. 
         *
         * Extended to support directory name also. It's now standard interface
         * to get name object info inside metadata space. And this call replaced
         * exists() and isDir()
         *
         * File object and directory object can have the same name, when getFileInfo
         * calls, file object is always returned first. If directory object is wanted,
         * caller should add "/" to the name which tells it's a directory name.
         *
         * Example:
         *      getFileInfo("/home/test") returns info of file test first,if it doest 
         *                                not exist, then try to find test directory
         *      getFileInfo("/home/test/") returns info of test directory
         *
         * @param name : name of file path or directory path 
         * @throws NoSuchFileOrDir (path notexist)
         * @return The FileInfo struct
         */
        FileInfo getFileInfo(const std::string& name) const;

        /** Set file metadata information, including size, createtime etc. 
         * 
         * @param [in]  filename 
         * @param [out] info : The FileInfo struct
         * @return:
         */
        void setFileInfo(const std::string& filename, const FileInfo& info);

        /** Set the replication number of a file.
         *
         * @param [in] filename: 
         * @param [in] replication: 
         * @throws NoSuchFileOrDir (filename notexist)
         * @return the old replication
         */    
        Short setReplication(const std::string& filename, Short replication);
        

        //5. locks and garbage collection
        /** Lock the file .
         *
         * @param [in] filename: 
         * @param [in] holder: owner of the lock
         * @param [in] lockType: read lock or write lock
         * @throws LockFail( LOCK failure)
         * @return : 
         */    
        void obtainLock(const std::string& filename, const std::string& holder, LockType lockType);

        /** Release the lock on the file which is owned by the holder.
         *
         * @param [in] filename: 
         * @param [in] holder: owner of the lock
         * @throws LockFail( LOCK failure)
         * @return : 
         */    
        void releaseLock(const std::string& filename, const std::string& holder);                 

        /** 
         * Release all the resources owned by the holder.
         * 
         * @param holder 
         */
        void releaseResource(const std::string& holder);

        //6.serialization interface
        /** 
         * Save FsDirectory object into image file.
         * 
         * @throws JournalException
         */
        void createCheckPoint();

    private:
        IceUtil::RWRecMutex m_dirRwMutex;   
        FsJournalManager*   m_pFsJournal;
        FsDirectoryImpl*    m_pDirectory;
        int m_dirty;
    };
}

#endif /* _TFSMASTER_FSDIRECTORY_HPP */
