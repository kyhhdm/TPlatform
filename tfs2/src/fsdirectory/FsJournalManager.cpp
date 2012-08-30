/** @file FsJournalManager.cpp
 *
 * @author PengBo
 * @date 20070827
 *
 *
 */

#include "fsdirectory/FsJournalManager.hpp"
#include "fsdirectory/FsDirectoryDebug.hpp"
#include "fsdirectory/FsDirectoryImpl.hpp"
#include "common/Exception.hpp"
#include <string>
#include <fstream>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <boost/archive/archive_exception.hpp>


using namespace std;
using namespace tfs;
using namespace boost::filesystem;

std::string FsJournalManager::ImageFilePrefix = "fsimg";
std::string FsJournalManager::LogFilePrefix = "fslog";

FsJournalManager::FsJournalManager():m_logger(Logger::getInstance("journal"))
{
    m_homeDir = MasterConfig::JournalFilePathName;
    m_pFsLog = NULL;
    m_pDirectory = NULL;
}

FsJournalManager::FsJournalManager(const string& dir):m_logger(Logger::getInstance("journal"))
{
    m_homeDir = dir;
    m_pFsLog = NULL;
    m_pDirectory = NULL;
}


FsJournalManager::~FsJournalManager()
{
    if(m_pFsLog) delete m_pFsLog;

}

FsDirectoryImpl* FsJournalManager::getFsDirectoryDebugInstance(const string& imgFileName, const string& logFileName)
{
    //assert(m_pDirectory = NULL);
    //assert(m_pFsLog = NULL);
    if(m_pFsLog) delete m_pFsLog;

    //#TODO, remove duplication code with getFsDirectoryInstance
    {
        m_pDirectory = new FsDirectoryDebug();
        
        //may throw boost::archive_exception here
        try{
            m_pDirectory->load(m_homeDir + imgFileName);
        }
        catch (boost::archive::archive_exception& e) {
            LOG4CPLUS_FATAL(m_logger, "FsJournalManager::getFsDirectoryInstance: load image from " 
                        << m_homeDir + imgFileName << " fail!(" << e.what() << ")");
            throw JournalException("FsJournalManager::getFsDirectoryInstance: load image exception!");
        }
        catch (exception& e){
            LOG4CPLUS_FATAL(m_logger, "FsJournalManager::getFsDirectoryInstance: load image from " 
                        << m_homeDir + imgFileName << " fail!");
            throw JournalException("FsJournalManager::getFsDirectoryInstance: load image exception!");
        }

        m_pFsLog = new FsLog(m_homeDir + logFileName);
        if(m_pFsLog->hasMore()){
            replayJournalLog();
        }
    }//end #TODO

    return m_pDirectory;
}

FsDirectoryImpl* FsJournalManager::getFsDirectoryInstance()
{
    string imgFileName, logFileName;
    char  versionBuf[32];

    //assert(m_pDirectory = NULL);
    //assert(m_pFsLog = NULL);
    if(m_pFsLog) delete m_pFsLog;

    if( !checkLatestJournalFileVersion(m_homeDir, m_curVersion)){
        //throw();
        //failed looking up image and log file, maybe system is new born
        m_curVersion = 0;
        sprintf(versionBuf, "%d", m_curVersion);
        //itoa(m_curVersion, versionBuf, 10);
        imgFileName = ImageFilePrefix + "." + versionBuf;
        logFileName = LogFilePrefix + "." + versionBuf;
        
        //create a new filesystem and return
        m_pDirectory = new FsDirectoryImpl();
        m_pDirectory->save(m_homeDir + imgFileName);
        m_pFsLog = new FsLog(m_homeDir + logFileName, FsLog::CreateNewMode);
    }
    else{
        sprintf(versionBuf, "%d", m_curVersion);
        //itoa(m_curVersion, versionBuf, 10);
        imgFileName = ImageFilePrefix + "." + versionBuf;
        logFileName = LogFilePrefix + "." + versionBuf;

        m_pDirectory = new FsDirectoryImpl();
        
        //may throw boost::archive_exception here
        try{
            m_pDirectory->load(m_homeDir + imgFileName);
        }
        catch (boost::archive::archive_exception& e) {
            LOG4CPLUS_FATAL(m_logger, "FsJournalManager::createCheckPoint: load image from " 
                        << m_homeDir + imgFileName << "fail!(" << e.what() << ")");
            throw JournalException("FsJournalManager::getFsDirectoryInstance: load image exception!");
        }
        catch (exception& e){
            LOG4CPLUS_FATAL(m_logger, "FsJournalManager::getFsDirectoryInstance: load image from " 
                        << m_homeDir + imgFileName << "fail!");
            throw JournalException("FsJournalManager::getFsDirectoryInstance: load image exception!");
        }


        m_pFsLog = new FsLog(m_homeDir + logFileName);
        if(m_pFsLog->hasMore()){
            replayJournalLog();
        }
        //now ready, can create check point here
        //createCheckPoint();
    }

    return m_pDirectory;
}
    
void FsJournalManager::createCheckPoint()
{
    string imgFileName, logFileName;
    char versionBuf[32];

    assert(m_pDirectory != NULL);
    assert(m_pFsLog != NULL);

    //#TODO,enter critical section,
    //lock FsDirectory and FsJournal here

    m_curVersion ++;
    //itoa(m_curVersion, versionBuf, 10);
    sprintf(versionBuf, "%d", m_curVersion);
    imgFileName = m_homeDir + ImageFilePrefix + "." + versionBuf;
    logFileName = m_homeDir + LogFilePrefix + "." + versionBuf;

    //may throw boost::archive_exception here
    try{
        m_pDirectory->save(imgFileName);
    }
    catch (boost::archive::archive_exception& e) {
        LOG4CPLUS_WARN(m_logger, "FsJournalManager::createCheckPoint: save image to " 
                    << imgFileName << "fail!(" << e.what() << ")");
        throw JournalException("FsJournalManager::createCheckPoint: save archive exception!");
    }
    catch (exception& e){
        LOG4CPLUS_WARN(m_logger, "FsJournalManager::createCheckPoint: save image to " 
                    << imgFileName << "fail!");
        throw JournalException("FsJournalManager::createCheckPoint: save exception!");
    }

    delete m_pFsLog;
    m_pFsLog = new FsLog(logFileName, FsLog::CreateNewMode);

    //#TODO,leave critical section

}

//==================== internal functions ======================
bool FsJournalManager::checkLatestJournalFileVersion(std::string& dirname, int& version)
{
    string baseName, extStr;
    int maxVersion = -1;

    if(!is_directory(dirname)){
        //create dir
        LOG4CPLUS_INFO(m_logger, "FsJournalManager::create journal home directory as :" << dirname);
        create_directory(boost::filesystem::path(dirname));

        //should throw JournalLog Configure exception here
        if(!is_directory(dirname)){
            LOG4CPLUS_FATAL(m_logger, "FsJournalManager::create journal home directory " << dirname << "failed" );
            throw JournalException("FsJournalManager::checkLatestJournalFileVersion: home directory create fail!");
            //return false;
        }
    }

    for (directory_iterator itr(dirname); itr != directory_iterator(); ++itr) {
        if (is_regular(itr->status())){
            baseName = basename(itr->path());
            extStr = extension(itr->path());    
            
            // get baseName = "fsimage" , extStr = ".1"
            //cout << "Debug: " << baseName << ":" << extStr << endl;
            
            if ((ImageFilePrefix == baseName) || (LogFilePrefix == baseName)){
                int i;

                if (extStr.length() == 1) continue;
                for( i = 1; i < extStr.length() ; ++i){
                    if(!isdigit(extStr[i])) break;
                }
                if (i == extStr.length()){
                    version = atoi(extStr.c_str() + 1);
                    //extStr >> version;
                    if( version > maxVersion) maxVersion = version;
                }
            }
        }
    }
    
    if(maxVersion == -1) return false;
    else{
        version = maxVersion;
        return true;
    }
}

void FsJournalManager::replayJournalLog()
{
    int magic, opCode;
    
    assert(m_pDirectory != NULL);
    assert(m_pFsLog != NULL);

    while(m_pFsLog->hasMore()){
        (*m_pFsLog) >> magic >> opCode;
        //#BUGFIX, must check eof() state of stream when read from EOF
        if(!m_pFsLog->hasMore()) break;
        if(magic != MagicWord){
            LOG4CPLUS_FATAL(m_logger, "unknown MagicWord " << hex << magic);
            throw JournalException("FsJournalManager::replayJournalLog: magic word mismatch!");
        }
        if(!((opCode > OpBegin) && (opCode < OpEnd))){
            LOG4CPLUS_FATAL(m_logger, "unknown opCode " << opCode);
            throw JournalException("FsJournalManager::replayJournalLog: opCode unknow!");
        }

        switch(opCode){
            case OpCreateFile: 
                redoCreateFile();
                break;
            case OpRenameFile:
                redoRenameFile();
                break;
            case OpDeleteFile:
                redoDeleteFile();
                break;
            case OpCreateDir:
                redoCreateDir();
                break;
            case OpRenameDir:
                redoRenameDir();
                break;
            case OpDeleteDir:
                redoDeleteDir();
                break;
            case OpNewChunk:
                redoNewChunk();
                break;
            case OpUpdateChunk:
                redoUpdateChunk();
                break;
            case OpCommitChunk:
                redoCommitChunk();
                break;
            case OpAbandonChunk:
                redoAbandonChunk();
                break;
            case OpSetFileInfo:
                redoSetFileInfo();
                break;
            case OpSetReplication:
                redoSetReplication();
                break;
        }

    }
}


