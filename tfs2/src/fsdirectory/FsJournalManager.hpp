/** @file FsJournalManager.hpp
 *
 * FsJournalManager is a journaling implementation for tfs metadata managment.
 *
 * Journaling provide fast reconvery capability by recording and replaying of 
 * all metadata operations on file system directory. 
 * It's a critical feature for a robust and high performance FS.
 *
 * Journaling system contains image file and journal log file. Image file is 
 * checkpoint image of file system directory , and journal log file is all metadata
 * operation records atfer the checkpoint.
 *
 *
 * @author PengBo
 * @date 28 5 2007
 *
 * design notes: <br>
 *      1.> Simple journal log design, no circular log file necessary here.     <br>
 *          Instead, use multiple image and log pair files, each pair represent <br>
 *          the transaction series between two consecutive check points.        <br>
 *      2.> Version implemented as part of filename, and use normal filesystem  <br>
 *          to manage journal files. For example:                               <br>
 *              image.001    log.001                                            <br>
 *              image.002    log.002                                            <br>
 *                 ....        ...                                              <br>
 *              image.008    log.008   <- last one is current working one       <br>
 *
 */
#ifndef _TFSMASTER_FSJOURNALMANAGER_HPP
#define _TFSMASTER_FSJOURNALMANAGER_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include "fsdirectory/FsLog.hpp"
#include "fsdirectory/FsDirectoryImpl.hpp"
#include "util/Logger.hpp"
#include <fstream>

namespace tfs {

    class FsDirectoryImpl;
    class FsLog;

    class FsJournalManager {

    public:
        //#TODO, how to set friend test class?
        //then , internal member functions can be test though.
        //friend class TestFsJournalManager;

        static const int MagicWord = 0x55aa55aa;
        static std::string ImageFilePrefix, LogFilePrefix;

        enum FsJournalOpType {
            OpBegin,
            OpCreateFile, 
            OpRenameFile,
            OpDeleteFile,
            OpCreateDir,
            OpRenameDir,
            OpDeleteDir,
            OpNewChunk,
            OpCommitChunk,
            OpAbandonChunk,
            OpSetFileInfo,
            OpSetReplication,
            OpConcatFiles,
            OpUpdateChunk,
            OpEnd
        };

        //1.constructors and initializers
        /** Default constructor.
         */    
        FsJournalManager();

        /** Construct from working directory contains image and log files .
         *  
         */    
        FsJournalManager(const std::string& dir);


        ~FsJournalManager();

        //2. manage interface
        /** Build a FsDirectory object instance from journal files.
         *  
         * @throws JournalException
         */    
        FsDirectoryImpl* getFsDirectoryInstance();

        /** Build a Debug FsDirectory object instance from journal files.
         *  
         * @throws JournalException
         */    
        FsDirectoryImpl* getFsDirectoryDebugInstance(const std::string& imgFileName, const std::string& logFileName);
            
         /** Create a checkpoint by save image file and complete current log file.
         *
         * @throws JournalException
         */    
        void createCheckPoint();

        //4. FsDirectory log interface
        bool logCreateFile(const std::string& filename, int maxChunkSize,short replication);
        bool logRenameFile(const std::string& src, const std::string& dst);
        bool logDeleteFile(const std::string& filename);
        bool logConcatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile);
        bool logCreateDir(const std::string& dirname);
        bool logRenameDir(const std::string& src, const std::string& dst);
        bool logDeleteDir(const std::string& filename);
        bool logNewChunk(const std::string& filename, const std::string& holder, Long chunkId);
        bool logUpdateChunk(const Chunk& chunk);                                                                        
        bool logCommitChunk(const Chunk& chunk);                                                                        
        bool logAbandonChunk(const Chunk& chunk);
        bool logSetFileInfo(const std::string& filename, const FileInfo& info);
        bool logSetReplication(const std::string& filename, Short replication); 

        //5.accessors
        int                 getCurVersoin();
        std::string&        getHomeDir();
        FsDirectoryImpl*    getFsDirectory();
        FsLog*              getFsLog();

         //internal helper function
         /** Check the journal files in appointed directory, get the latest version number
         *
         * @param [in] dirname
         * @param [out] version
         * @throws 
         * @return : false if no valid journal files there
         */    
        bool checkLatestJournalFileVersion(std::string& dirname, int& version);
        
         /** Check the journal files in appointed directory, get the latest version number
         *
         * @throws : JournalException if journal log data error(magic word mismatch , or opcode unknow)
         *
         */    
        void replayJournalLog();

    private:
         /** FsDirectory(Impl) object dynamically created and returned to a handle object.
         *   Handle object is in charge of free this created instance.
         *   So, don't release this object point inside JournalManager.
         */    
        FsDirectoryImpl*    m_pDirectory;
        
        FsLog*          m_pFsLog;
        std::string     m_homeDir;
        int             m_curVersion;

        /** Redo functions according to journal log records
         *
         */    
        void redoCreateFile();
        void redoRenameFile();
        void redoDeleteFile();
        void redoConcatFiles();
        void redoCreateDir();
        void redoRenameDir();
        void redoDeleteDir();
        void redoNewChunk();
        void redoUpdateChunk();
        void redoCommitChunk();
        void redoAbandonChunk();
        void redoSetFileInfo();
        void redoSetReplication();
        
        /** logger 
         */
        Logger m_logger;
    };

    // inline implementation =================================
    inline int FsJournalManager::getCurVersoin(){ return m_curVersion;}
    inline std::string&   FsJournalManager::getHomeDir() { return m_homeDir;}
    inline FsDirectoryImpl*  FsJournalManager::getFsDirectory() {return m_pDirectory;}
    inline FsLog*            FsJournalManager::getFsLog() {return m_pFsLog;}

    inline bool FsJournalManager::logCreateFile(const std::string& filename, int maxChunkSize,Short replication){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpCreateFile;
        (*m_pFsLog) << filename << maxChunkSize << replication;
        (*m_pFsLog).flush();
        return true;
    }

    inline void FsJournalManager::redoCreateFile() {
        std::string filename;
        int maxChunkSize;
        Short replication;
        (*m_pFsLog) >> filename >> maxChunkSize >> replication;
        m_pDirectory->createFile(filename, maxChunkSize, replication);
    }

    inline bool FsJournalManager::logRenameFile(const std::string& src, const std::string& dst){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpRenameFile;
        (*m_pFsLog) << src << dst;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoRenameFile(){
        std::string src, dst;

        (*m_pFsLog) >> src >> dst;
        m_pDirectory->renameFile(src, dst);
    }

    inline bool FsJournalManager::logDeleteFile(const std::string& filename){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpDeleteFile;
        (*m_pFsLog) << filename;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoDeleteFile(){
        std::string filename;
        Chunks chunks;
        (*m_pFsLog) >> filename;
        m_pDirectory->deleteFile(filename, chunks);
    }

    inline bool FsJournalManager::logConcatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile){
        int fileNumber = srcFiles.size();
        
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpConcatFiles;
        (*m_pFsLog) << fileNumber;
        for ( int i = 0; i < fileNumber ; i++){
            (*m_pFsLog) << srcFiles[i];
        }
        (*m_pFsLog) << dstFile;

        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoConcatFiles(){
        int fileNumber;
        std::string dstFile;
        std::vector<std::string> srcFiles;

        (*m_pFsLog) >> fileNumber;
        for(int i = 0 ; i < fileNumber; i++){
            std::string filename;
            (*m_pFsLog) >> filename;
            srcFiles.push_back(filename);
        }
        (*m_pFsLog) >> dstFile;

        m_pDirectory->concatFiles(srcFiles, dstFile);
    }

    inline bool FsJournalManager::logCreateDir(const std::string& dirname){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpCreateDir;
        (*m_pFsLog) << dirname;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoCreateDir(){
        std::string dirname;
        (*m_pFsLog) >> dirname;
        m_pDirectory->createDir(dirname);
    }

    inline bool FsJournalManager::logRenameDir(const std::string& src, const std::string& dst){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpRenameDir;
        (*m_pFsLog) << src << dst;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoRenameDir(){
        std::string src, dst;

        (*m_pFsLog) >> src >> dst;
        m_pDirectory->renameDir(src, dst);
    }

    inline bool FsJournalManager::logDeleteDir(const std::string& filename){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpDeleteDir;
        (*m_pFsLog) << filename;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoDeleteDir(){
        std::string filename;
        (*m_pFsLog) >> filename;
        m_pDirectory->deleteDir(filename);
    }

    inline bool FsJournalManager::logNewChunk(const std::string& filename, const std::string& holder, Long chunkId){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpNewChunk;
        (*m_pFsLog) << filename << holder << chunkId;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoNewChunk(){
        std::string filename, holder;
        Long chunkId;
        (*m_pFsLog) >> filename >> holder >> chunkId;
        m_pDirectory->newChunk(filename, holder, chunkId);
    }

    inline bool FsJournalManager::logUpdateChunk(const Chunk& chunk){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpUpdateChunk;
        (*m_pFsLog) << chunk;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoUpdateChunk(){
        Chunk chunk;
        (*m_pFsLog) >> chunk;
        m_pDirectory->updateChunk(chunk);
    }

    inline bool FsJournalManager::logCommitChunk(const Chunk& chunk){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpCommitChunk;
        (*m_pFsLog) << chunk;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoCommitChunk(){
        Chunk chunk;
        (*m_pFsLog) >> chunk;
        m_pDirectory->commitChunk(chunk);
    }

    inline bool FsJournalManager::logAbandonChunk(const Chunk& chunk){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpAbandonChunk;
        (*m_pFsLog) << chunk;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoAbandonChunk(){
        Chunk chunk;
        (*m_pFsLog) >> chunk;
        m_pDirectory->abandonChunk(chunk);
    }

    inline bool FsJournalManager::logSetFileInfo(const std::string& filename, const FileInfo& info){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpSetFileInfo;
        (*m_pFsLog) << filename << info;
        (*m_pFsLog).flush();
        return true;
    }
    inline void FsJournalManager::redoSetFileInfo(){
        std::string filename;
        FileInfo info;
        (*m_pFsLog) >> filename >> info;
        m_pDirectory->setFileInfo(filename, info);
    }

    inline bool FsJournalManager::logSetReplication(const std::string& filename, Short replication){
        (*m_pFsLog) << FsJournalManager::MagicWord << FsJournalManager::OpSetReplication;
        (*m_pFsLog) << filename << replication;
        (*m_pFsLog).flush();
        return true;
    } 
    inline void FsJournalManager::redoSetReplication(){
        std::string filename;
        Short replication;
        (*m_pFsLog) >> filename >> replication;
        m_pDirectory->setReplication(filename, replication);
    }

}

#endif /* _TFSMASTER_FSJOURNALMANAGER_HPP */
