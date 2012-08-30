/** 
 * @file TestFsDirectory.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2007-07-12
 */
#ifndef _TEST_TFSMASTER_FSDIRECTORY_HPP
#define _TEST_TFSMASTER_FSDIRECTORY_HPP

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "common/Exception.hpp"
#include "fsdirectory/FsDirectory.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include "util/Logger.hpp"
#include <time.h>
#include <iostream>

using namespace std;
using namespace tfs;

class FsDirectoryFixture : public CxxTest::GlobalFixture{
    public:    
    bool setUpWorld() { 
        //printf( "<world>" ); 
        cout << "i'm comming..." << endl;

        // setup logger
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(new RollingFileAppender("testFsDirectory.log", 5*1024, 5));
        append_1->setName("appender1");
        append_1->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
        Logger::getRoot().addAppender(append_1);
        
        return true; 
    }

    bool tearDownWorld() { 
        //printf( "</world>" ); 
        return true; 
    }

    bool setUp() { 
        //printf( "<test>" ); 
        return true; 
    }    
    bool tearDown() { 
        //printf( "</test>" ); 
        return true; 
    }
};


static FsDirectoryFixture fsDirectoryFixture;


class TestFsDirectory: public CxxTest::TestSuite
{
    FsDirectory m_dir;

    //==========helper functions=================
    void showFilesInfo(const string& dirName, FilesInfoPtr filesInfoPtr)
    {
        FileInfo info;

        cout << endl << "Current directory is : " << dirName << endl;
        cout << "Total " << filesInfoPtr->size() << endl;
        for ( unsigned int i = 0; i < filesInfoPtr->size(); ++i) {
            info = (*filesInfoPtr)[i];
            cout << info.name << "\t" 
                 << info.size << "\t" << info.size << "\t" << info.chunkSize << "\t" 
                 << info.replication << "\t"
                 << ctime((time_t*)&info.createTime) ;
        }

    }

public:

    //==============test goes here =====================

    //Test 1. createDir()
    void testCreateDir(void)
	{

        TS_ASSERT_THROWS_NOTHING( m_dir.createDir("/home/tfs/src/") );

        TS_ASSERT_THROWS ( m_dir.createDir("xxxx/tfs/src/") , InvalidFileOrDirName);

        //try{
        //    m_dir.createDir("/home/tfs/doc") ;
        //}catch( const GenericException& e){
        //    cout << e.reason << endl;
        //}

        //#TODO, this test fail!
        TS_ASSERT_THROWS_NOTHING( m_dir.createDir("/home/tfs/doc") );
        
        TS_ASSERT_THROWS ( m_dir.createDir("/home/tfs/src") , FileOrDirAlreadyExists);

    }

    //Test 2. createFile()
    void testCreateFile()
    {
        //create intermideate directory automatically
        TS_ASSERT_THROWS_NOTHING(m_dir.createFile("/home/tfs/xxx/test.dat"));

        TS_ASSERT_THROWS_NOTHING(m_dir.createFile("/home/tfs/src/test.dat"));

        //invalid path name
        TS_ASSERT_THROWS ( m_dir.createFile("xxxx/tfs/src/test.dat"),InvalidFileOrDirName );
        
        //cant' create pureDir
        TS_ASSERT_THROWS ( m_dir.createFile("/home/tfs/src/"), InvalidFileOrDirName);
        
	    //this file is for late test
        TS_ASSERT_THROWS_NOTHING(m_dir.createFile("/home/tfs/doc/UserGuide.pdf", MasterConfig::DefaultMaxChunkSize*2 , 1));
    
    }
    
    //Test 3. exist()
    void testExist()
    {
        bool retVal;

        retVal = m_dir.exists("/");
        TS_ASSERT(retVal == true);

        retVal = m_dir.exists("//");
        TS_ASSERT(retVal == true);
        
        retVal = m_dir.exists("/home/tfs/xxx/test.dat");
        TS_ASSERT(retVal == true);

        retVal = m_dir.exists("/home/tfs/src/test.dat");
        TS_ASSERT(retVal == true);

        retVal = m_dir.exists("xxxx/tfs/xxx/test.dat");
        TS_ASSERT(retVal == false);

        retVal = m_dir.exists("/home/tfs/src/");
        TS_ASSERT(retVal == true);

        retVal = m_dir.exists("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(retVal == true);

        retVal = m_dir.exists("/home/");
        TS_ASSERT(retVal == true);
        
        //path grammar, dir must have "/" at the end
        retVal = m_dir.exists("/home");
        TS_ASSERT(retVal == false);
    }

    //Test 4. isDir()
    void testIsDir()
    {
        bool retVal;

        retVal = m_dir.isDir("/home/tfs/xxx/test.dat");
        TS_ASSERT(retVal == false);

        retVal = m_dir.isDir("/home/tfs/xxx/");
        TS_ASSERT(retVal == true);

        retVal = m_dir.isDir("/home/xxx/");
        TS_ASSERT(retVal == false);

        retVal = m_dir.isDir("/home/tfs/src/test.dat");
        TS_ASSERT(retVal == false);

        retVal = m_dir.isDir("/home/tfs/src/");
        TS_ASSERT(retVal == true);

        retVal = m_dir.isDir("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(retVal == false);

    }
    
    //Test 5. setFileInfo()
    void testSetFileInfo()
    {
        Short retVal ;
        
        retVal = m_dir.setReplication("/home/tfs/doc/UserGuide.pdf", 4);
        TS_ASSERT(1 == retVal);
        
        TS_ASSERT_THROWS(m_dir.setReplication("/home/tfs/src/xxx.dat",1), tfs::NoSuchFileOrDir);
    
    }

    //Test 6. getFileInfo()
    void testGetFileInfo()
    {
        FileInfo info;

        info = m_dir.getFileInfo("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(4 == info.replication);
        TS_ASSERT("UserGuide.pdf" == info.name);
        TS_ASSERT(0 == info.size);
        TS_ASSERT( (MasterConfig::DefaultMaxChunkSize*2) == info.chunkSize);

        info = m_dir.getFileInfo("/home/tfs/src/test.dat");
        TS_ASSERT(MasterConfig::DefaultReplication == info.replication);
        TS_ASSERT("test.dat" == info.name);
        TS_ASSERT(0 == info.size);
        TS_ASSERT(MasterConfig::DefaultMaxChunkSize == info.chunkSize);


        TS_ASSERT_THROWS(m_dir.getFileInfo("/home/tfs/src/xxx.dat"), tfs::NoSuchFileOrDir);
        //try{
        //    m_dir.getFileInfo("/home/tfs/src/xxx.dat");
        //}catch(const tfs::NoSuchFileOrDir& e){
        //    //TS_ASSERT(e.reason == "") ;
        //}
	}

    //Test 7. chunks
    void testChunksInterface()
    {
        Chunk chunk1, chunk2, chunk3;

        const Chunks& chunks1 = m_dir.getFileChunks("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(chunks1.size() == 0);

        chunk1 = m_dir.newChunk("/home/tfs/doc/UserGuide.pdf", "Client-A");
        chunk2 = m_dir.newChunk("/home/tfs/doc/UserGuide.pdf", "Client-A");
        chunk3 = m_dir.newChunk("/home/tfs/doc/UserGuide.pdf", "Client-B");
        TS_ASSERT(chunk1.id != chunk2.id);
        TS_ASSERT(chunk1.id != chunk3.id);
        TS_ASSERT(chunk2.id != chunk3.id);

        const Chunks& chunks2 = m_dir.getFileChunks("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(chunks2.size() == 0);
        
        chunk1.size = 10;
        chunk1.version = 1; 
        chunk2.size = 20;
        chunk2.version = 2; 
        chunk3.size = 30;
        chunk3.version = 3; 

        cout << "New chunks as " << hex << chunk1.id << "  " << chunk2.id << "  " << chunk3.id << endl;
        
        TS_ASSERT_THROWS_NOTHING( m_dir.commitChunk(chunk1) );
        TS_ASSERT_THROWS_NOTHING( m_dir.commitChunk(chunk2) );
        TS_ASSERT_THROWS_NOTHING( m_dir.commitChunk(chunk3) );

        const Chunks& chunks3 = m_dir.getFileChunks("/home/tfs/doc/UserGuide.pdf");
        TS_ASSERT(chunks3.size() == 3);

        TS_ASSERT_SAME_DATA(&chunks3[0], &chunk1, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks3[1], &chunk2, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks3[2], &chunk3, sizeof(Chunk));
           
    }

    //Test 8. readDir()
    void testReadDir()
    {
        m_dir.createFile("/home/tfs/src/test-A.dat");
        m_dir.createFile("/home/tfs/src/test-B.dat");
        m_dir.createFile("/home/tfs/src/test-C.dat");

        FilesInfoPtr filesInfoPtr;

        filesInfoPtr = m_dir.readDir("/home/tfs/");
        showFilesInfo("/home/tfs/", filesInfoPtr);
        TS_ASSERT((*filesInfoPtr)[0].name == "src");
        TS_ASSERT(filesInfoPtr->size() == 3 );

        filesInfoPtr = m_dir.readDir("/home/tfs/src/");
        showFilesInfo("/home/tfs/src/", filesInfoPtr);
        TS_ASSERT(filesInfoPtr->size() == 4 );
    }

    //Test 9. DEPRECATED, moved into TestFsJournalManager
    void xtestSerialize()
    {
        FsDirectory dir;
        //m_dir.save("test-tfs-dir.img");
        //dir.load("test-tfs-dir.img");

        //check up
        //DirTree seralization has been test in TestDirTree
        //Here we test data in ChunkTable
        //


    }

    //Test 10. 20070810 bug report
    void testCreateRootFile()
    {
        FsDirectory dir;
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/test"));
    }

    //Test 11. 
    void testRenameFileAndDir()
    {
        FsDirectory dir;

        //renameFile
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/1.txt"));
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/2.txt"));
    
        TS_ASSERT(true == dir.exists("/home/src/1.txt"));
        TS_ASSERT(true == dir.exists("/home/src/2.txt"));


        TS_ASSERT_THROWS(dir.renameFile("/home/src/3.txt", "/home/src/4.txt"), NoSuchFileOrDir); 
        TS_ASSERT_THROWS(dir.renameFile("/home/src/1.txt", "/home/src/2.txt"), FileOrDirAlreadyExists); 
        TS_ASSERT_THROWS(dir.renameFile("/home/src/1.txt", "/home/dst/"), InvalidFileOrDirName); 

        TS_ASSERT(true == dir.exists("/home/src/1.txt"));
        TS_ASSERT(true == dir.exists("/home/src/2.txt"));
        
        TS_ASSERT_THROWS_NOTHING(dir.renameFile("/home/src/1.txt", "/home/dst/1.txt"));
        TS_ASSERT(false == dir.exists("/home/src/1.txt"));
        TS_ASSERT(true == dir.exists("/home/dst/1.txt"));
        
        TS_ASSERT_THROWS_NOTHING(dir.renameFile("/home/dst/1.txt", "/home/dst/2.txt"));
        TS_ASSERT(false == dir.exists("/home/dst/1.txt"));
        TS_ASSERT(true == dir.exists("/home/dst/2.txt"));

        TS_ASSERT_THROWS_NOTHING(dir.renameFile("/home/dst/2.txt", "/home/dst/subdir/2.txt"));
        TS_ASSERT(false == dir.exists("/home/dst/2.txt"));
        TS_ASSERT(true == dir.exists("/home/dst/subdir/2.txt"));

        //renameDir
        TS_ASSERT_THROWS(dir.renameDir("/home/src/1.txt", "/home/dst/"), NoSuchFileOrDir);
        TS_ASSERT_THROWS(dir.renameDir("/home/src/", "/home/dst/"), FileOrDirAlreadyExists);
        TS_ASSERT_THROWS_NOTHING(dir.renameDir("/home/src/", "/home/newsrc/"));
        TS_ASSERT(false == dir.exists("/home/src/"));
        TS_ASSERT(true == dir.exists("/home/newsrc/"));
        
        TS_ASSERT_THROWS(dir.renameDir("/home/dst/", "/home/dst/subdir/dst/"), InvalidFileOrDirName);
        TS_ASSERT_THROWS_NOTHING(dir.renameDir("/home/dst", "/home/newsrc/dst"));
        TS_ASSERT(false == dir.exists("/home/dst/"));
        TS_ASSERT(true == dir.exists("/home/newsrc/dst/"));

        //check up
        TS_ASSERT(false == dir.exists("/home/src/1.txt"));
        TS_ASSERT(false == dir.exists("/home/src/2.txt"));
        TS_ASSERT(false == dir.exists("/home/src/3.txt"));
        TS_ASSERT(false == dir.exists("/home/src/4.txt"));
        TS_ASSERT(false == dir.exists("/home/dst/1.txt"));
        TS_ASSERT(false == dir.exists("/home/dst/2.txt"));
        TS_ASSERT(false == dir.exists("/home/src/"));
        TS_ASSERT(false == dir.exists("/home/dst/"));
        
        TS_ASSERT(true == dir.exists("/home/newsrc/2.txt"));
        TS_ASSERT(true == dir.exists("/home/newsrc/dst/subdir/2.txt"));

    }

    //Test 12. 
    void testDeleteFileAndDir()
    {
        FsDirectory dir;
        Chunks chunks;
        Chunk  chunk1, chunk2, chunk3;

        //make up
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/1.txt"));
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/2.txt"));

        chunk1 = dir.newChunk("/home/src/1.txt", "Client-A");
        chunk1.size = 1234;
        chunk1.version = 1;
        dir.commitChunk(chunk1);

        chunk2 = dir.newChunk("/home/src/1.txt", "Client-A");
        chunk2.size = 8989;
        chunk2.version = 2;
        dir.commitChunk(chunk2);
        
        chunk3 = dir.newChunk("/home/src/1.txt", "Client-B");


        TS_ASSERT_THROWS(dir.deleteFile("/home/src/3.txt", chunks), NoSuchFileOrDir);
        
        TS_ASSERT_THROWS_NOTHING(dir.deleteFile("/home/src/1.txt", chunks));

        TS_ASSERT( chunks.size() == 2);
        TS_ASSERT_SAME_DATA(&chunks[0], &chunk1, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[1], &chunk2, sizeof(Chunk));

        //deleteDir
        TS_ASSERT_THROWS(dir.deleteDir("/home/xxx/"), NoSuchFileOrDir);
        TS_ASSERT_THROWS(dir.deleteDir("/home/src/"), InvalidFileOrDirName);

        TS_ASSERT_THROWS_NOTHING(dir.deleteFile("/home/src/2.txt", chunks));
        TS_ASSERT( chunks.size() == 0);
        
        TS_ASSERT_THROWS_NOTHING(dir.deleteDir("/home/src/"));

    }

    //Test 13
    void testNullExist()
    {   
        //#BUG 20070919 by tsunami
        //exists(string not initilized) will cause core dump
        FsDirectory dir;
        string name;

        TS_ASSERT(false == dir.exists(""));
        TS_ASSERT(false == dir.exists(name));

    }

    //Test 14, #BUG 14, deleteDir fail in none empty directory
    void testDeleteNoneEmptyDir()
    {
        FsDirectory dir;

        //delete root
        TS_ASSERT_THROWS(dir.deleteDir("/"), InvalidFileOrDirName);
        
        //setup enviroment
        TS_ASSERT_THROWS_NOTHING(dir.createDir("/a/b/"));

        TS_ASSERT_THROWS(dir.deleteDir("/a"), InvalidFileOrDirName);
        
         
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/b/1.txt"));
        TS_ASSERT_THROWS(dir.deleteDir("/b"), InvalidFileOrDirName);

    
        TS_ASSERT_THROWS(dir.deleteDir("/"), InvalidFileOrDirName);

        //delete invalid dir 
        TS_ASSERT_THROWS(dir.deleteDir("a/b"), InvalidFileOrDirName);

    }

    //#BUG 16, list , create invliad dir , no exception throws
    void testListInvalidDir()
    {   
        FsDirectory dir;
        FilesInfoPtr filesInfo;

        TS_ASSERT_THROWS_NOTHING(dir.createDir("/a/b/"));
        TS_ASSERT_THROWS_NOTHING( (filesInfo = dir.readDir("/") ));
        
        TS_ASSERT_THROWS( dir.readDir("a"), NoSuchFileOrDir);
        TS_ASSERT_THROWS( dir.createDir("c"), InvalidFileOrDirName);
        TS_ASSERT_THROWS( dir.createDir("d/d/d/"), InvalidFileOrDirName);

    }

    //Test 17, concatFiles()
    void testConcatFiels()
    {   
        FsDirectory dir;
        Chunk  chunk1, chunk2, chunk3;
        Chunk  chunk4, chunk5, chunk6;
        vector<string> srcFiles;
        string dstFile;

        //make up
        srcFiles.push_back("/home/src/1.txt");
        srcFiles.push_back("/home/src/2.txt");
        srcFiles.push_back("/home/src/3.txt");
        dstFile = "/home/dst/all.txt";

        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/1.txt"));
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/2.txt"));
        TS_ASSERT_THROWS_NOTHING(dir.createFile("/home/src/3.txt"));

        chunk1 = dir.newChunk("/home/src/1.txt", "Client-A");
        chunk1.size = 1000;
        chunk1.version = 1;
        dir.commitChunk(chunk1);
        chunk2 = dir.newChunk("/home/src/1.txt", "Client-A");
        chunk2.size = 2000;
        chunk2.version = 2;
        dir.commitChunk(chunk2);
        chunk3 = dir.newChunk("/home/src/1.txt", "Client-B");
        chunk3.size = 3000;
        dir.commitChunk(chunk3);

        chunk4 = dir.newChunk("/home/src/2.txt", "Client-A");
        chunk4.size = 1000;
        chunk4.version = 5;
        dir.commitChunk(chunk4);
        chunk5 = dir.newChunk("/home/src/2.txt", "Client-A");
        chunk5.size = 2000;
        chunk5.version = 5;
        dir.commitChunk(chunk5);
        chunk6 = dir.newChunk("/home/src/3.txt", "Client-B");
        chunk6.size = 3000;
        dir.commitChunk(chunk6);

        //do concat
        TS_ASSERT_THROWS_NOTHING(dir.concatFiles(srcFiles, dstFile));

        //check up
        TS_ASSERT_THROWS_NOTHING(dir.exists(dstFile));

        FileInfo info;
        info = dir.getFileInfo(dstFile);
        TS_ASSERT(info.size == 12000);

        const Chunks& chunks = dir.getFileChunks(dstFile);
        TS_ASSERT(chunks.size() == 6);

        TS_ASSERT_SAME_DATA(&chunks[0], &chunk1, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[1], &chunk2, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[2], &chunk3, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[3], &chunk4, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[4], &chunk5, sizeof(Chunk));
        TS_ASSERT_SAME_DATA(&chunks[5], &chunk6, sizeof(Chunk));
    }

};


#endif /* _TEST_TFSMASTER_FSDIRECTORY_HPP */

