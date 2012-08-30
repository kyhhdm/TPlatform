/** 
 * @file TestFsJournalManager.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2007-08-28
 */
#ifndef _TEST_TFSMASTER_JOURNALMANAGER_HPP
#define _TEST_TFSMASTER_JOURNALMANAGER_HPP

#include <cxxtest/TestSuite.h>
#include "common/Exception.hpp"
#include "fsdirectory/FsJournalManager.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;
using namespace tfs;

class TestFsJournalManager: public CxxTest::TestSuite
{
    FsJournalManager m_journal;

    //====== test parameter setting==========

public:
    //====== environment setup =============
    TestFsJournalManager( int noUse ){
        UNUSED(noUse);  
    }

    virtual ~TestFsJournalManager(){
    }

    static TestFsJournalManager *createSuite() {
        return new TestFsJournalManager( 1 ); 
    }
    
    static void destroySuite( TestFsJournalManager *suite ) { 
        delete suite; 
    }
 

    //==========helper functions=================
    void cleanJournalDir(const string& dirname){
        string command = "rm -rf ";
        command += dirname;
        system(command.c_str());    

        cout << "clean directory : " << dirname << endl;

        mkdir(dirname.c_str(), 0777);
        //chdir(dirname.c_str());
    }

    void createJournalFile(int version){
        string filename;
        char buf[32];

        sprintf(buf, "%d", version);
        filename = m_journal.getHomeDir() + FsJournalManager::ImageFilePrefix + "." + buf;
        cout << "create image file : " << filename << endl;
        ofstream of(filename.c_str());
        of << "image";
        of.close();

        filename = m_journal.getHomeDir() + FsJournalManager::LogFilePrefix + "." + buf;
        cout << "create log file : " << filename << endl;
        ofstream ofLog(filename.c_str());
        ofLog << "log";
        ofLog.close();
    }

    void doSomeDirectoryOperation(FsDirectoryImpl* pDirectory){
        string filename = "/home/tfs/test.txt";
        string holder = "morningstar";
        Chunk chunk;

        pDirectory->createFile(filename, 64*1024, 3);
        m_journal.logCreateFile(filename, 64*1024, 3);

        chunk = pDirectory->newChunk(filename, holder);
        TS_ASSERT(chunk.id != 0LL);
        m_journal.logNewChunk(filename, holder, chunk.id);
 
        cout << "NewChunk as : " << hex << chunk.id << endl;

        chunk.version = 1;
        chunk.size = 64*1024;
        pDirectory->commitChunk(chunk);
        m_journal.logCommitChunk(chunk);

    }

    void checkReplayResult(FsDirectoryImpl* pDirectory){
        string filename = "/home/tfs/test.txt";
        string holder = "morningstar";
        FileInfo info;

        TS_ASSERT(true == pDirectory->exists(filename));
        info = pDirectory->getFileInfo(filename);
        TS_ASSERT(info.chunkSize == 64*1024);
        TS_ASSERT(info.replication == 3);

        const Chunks&  chunks = pDirectory->getFileChunks(filename);
        TS_ASSERT(chunks.size() ==1);
        TS_ASSERT(chunks[0].size == 64*1024);
        TS_ASSERT(chunks[0].version == 1);
    }

public:

    //==============test goes here =====================

    //Test 1. write log
    void testCheckLatestJournalFileVersion(void)
	{
        int version;
        bool ret;
        string filename;

        cleanJournalDir(m_journal.getHomeDir());

        ret = m_journal.checkLatestJournalFileVersion(m_journal.getHomeDir(),version);
        TS_ASSERT(ret == false);

        //create journal files
        createJournalFile(0);
        ret = m_journal.checkLatestJournalFileVersion(m_journal.getHomeDir(),version);
        TS_ASSERT(ret == true);
        TS_ASSERT(version == 0);

        createJournalFile(1);
        ret = m_journal.checkLatestJournalFileVersion(m_journal.getHomeDir(),version);
        TS_ASSERT(ret == true);
        TS_ASSERT(version == 1);

        createJournalFile(111);
        ret = m_journal.checkLatestJournalFileVersion(m_journal.getHomeDir(),version);
        TS_ASSERT(ret == true);
        TS_ASSERT(version == 111);
    }

    void testCreateDirectoryInstance()
    {
        FsDirectoryImpl* pDirectory;
        
        cleanJournalDir(m_journal.getHomeDir());

        pDirectory = m_journal.getFsDirectoryInstance();
        TS_ASSERT(m_journal.getCurVersoin() == 0);

    }

    void testReplayJournal()
    {
        //goon with last test, an empty Directory
        //log some operations here
        doSomeDirectoryOperation(m_journal.getFsDirectory());

        //check the result by rebuild a instance from current log
        FsDirectoryImpl* pDirectory;
        FsJournalManager* pJournal = new FsJournalManager;
        pDirectory = pJournal->getFsDirectoryInstance();
        TS_ASSERT(pJournal->getCurVersoin() == 0);

        //now , the contents in pDirectory should be same to m_journal's m_pDirectory
        checkReplayResult(pDirectory);        

        delete pDirectory;
        delete pJournal;
    
    }

    void testCreateCheckPoint()
    {
        //cleanJournalDir(m_journal.getHomeDir());
        //pDirectory = m_journal.getFsDirectoryInstance();
        //TS_ASSERT(m_journal.getCurVersoin() == 0);
        //doSomeDirectoryOperation(pDirectory);
        
        m_journal.createCheckPoint();
        TS_ASSERT(m_journal.getCurVersoin() == 1);
        
        //check the result
        FsDirectoryImpl* pDirectory;
        FsJournalManager* pJournal = new FsJournalManager;
        pDirectory = pJournal->getFsDirectoryInstance();
        TS_ASSERT(pJournal->getCurVersoin() == 1);

        checkReplayResult(pDirectory);

        delete pDirectory;
        delete pJournal;
        
       // delete m_journal.getFsDirectory();
    }



};


#endif /* _TEST_TFSMASTER_FSJOURNALMANAGER_HPP */

