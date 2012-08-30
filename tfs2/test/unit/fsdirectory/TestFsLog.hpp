/** 
 * @file TestFsLog.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2007-08-28
 */
#ifndef _TEST_TFSMASTER_FSLOG_HPP
#define _TEST_TFSMASTER_FSLOG_HPP

#include <cxxtest/TestSuite.h>
#include "common/Exception.hpp"
#include "fsdirectory/FsLog.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <time.h>
#include <stdio.h>

using namespace std;
using namespace tfs;

class TestFsLog: public CxxTest::TestSuite
{
    FsLog m_log;

    //====== test parameter setting==========
    enum OpCode{
        OpBegin,
        OpCreateFile,
        OpRenameFile,
        OpTest
    };
    
    int m_magic;
    Short m_short;
    Long  m_long;  
    string m_filename;
    string m_holder; 
    string m_src;
    string m_dst; 
    FileInfo m_info;
    Chunk m_chunk;

public:
    //====== environment setup =============
    TestFsLog( int noUse ):m_log("TestFsLog.log", FsLog::CreateNewMode){
    //TestFsLog( int noUse ){
        UNUSED(noUse);
        m_magic = 0x55aa55aa;
        m_short = 3;
        m_long = 0xaabbccddeeff0011LL; 
        m_filename = "/home/tfs/test.doc";
        m_holder = "morningstar";
        m_src = m_filename;
        m_dst = "/home/tfs/pass.doc";

        m_chunk.id = 0x008866442200LL;
        m_chunk.size = 0x01020304;
        m_chunk.version = 1;

        m_info.name = "/home/tfs/fileinfo.txt";
        m_info.size = 0x112233445566ll;
        m_info.chunkSize = 0x8899aabb;
        m_info.replication = 3;
        m_info.createTime = time(NULL);
    
    }

    virtual ~TestFsLog(){
    }

    static TestFsLog *createSuite() {
        return new TestFsLog( 1 ); 
    }
    
    static void destroySuite( TestFsLog *suite ) { 
        delete suite; 
    }
 

    //==========helper functions=================

public:

    //==============test goes here =====================

    //Test 1. write log
    void testWriteLogBasic(void)
	{
        int magic;
        //OpCode opCode;
        int opCode;
        string filename;

        TS_ASSERT_THROWS_NOTHING(m_log << m_magic);
        TS_ASSERT_THROWS_NOTHING(m_log << OpCreateFile);
        TS_ASSERT_THROWS_NOTHING(m_log << m_filename);
        TS_ASSERT_THROWS_NOTHING(m_log.flush());

        TS_ASSERT_THROWS_NOTHING(m_log >> magic);
        TS_ASSERT_THROWS_NOTHING(m_log >> opCode);
        TS_ASSERT_THROWS_NOTHING(m_log >> filename);

        TS_ASSERT( magic == m_magic);
        TS_ASSERT( opCode == OpCreateFile);
        TS_ASSERT( filename == m_filename );
    }

    void testCatStreamOpertor()
    {
        int magic;
        int opCode;
        string filename, src, dst;

        m_log << m_magic << OpRenameFile << m_src << m_dst;
        m_log.flush();

        m_log >> magic >> opCode >> src >> dst;
        TS_ASSERT( magic == m_magic);
        TS_ASSERT( opCode == OpRenameFile );
        TS_ASSERT( src == m_src );
        TS_ASSERT( dst == m_dst );

    }


    void testShortLong()
    {
        int magic;
        int opCode;
        Short shortData;
        Long longData;

        m_log << m_magic << OpTest ;
        TS_ASSERT_THROWS_NOTHING( m_log << m_short); 
        TS_ASSERT_THROWS_NOTHING( m_log << m_long);
        m_log.flush();

        m_log >> magic >> opCode;
        TS_ASSERT_THROWS_NOTHING( m_log >> shortData); 
        TS_ASSERT_THROWS_NOTHING( m_log >> longData);
        
        //cout << " opCode = " << hex << opCode  
        //     << " short  = " << hex << shortData
        //     << " long   = " << hex << longData
        //     << endl;


        TS_ASSERT( magic == m_magic);
        TS_ASSERT( opCode == OpTest );
        TS_ASSERT( shortData == m_short );
        TS_ASSERT( longData == m_long );

    }

    void testClassType()
    {
        int magic;
        int opCode;
        Chunk chunk;
        FileInfo info;


        m_log << m_magic << OpTest ;
        TS_ASSERT_THROWS_NOTHING( m_log << m_chunk);
        m_log.flush();

        m_log >> magic >> opCode;
        TS_ASSERT_THROWS_NOTHING( m_log >> chunk); 
        
        TS_ASSERT( magic == m_magic);
        TS_ASSERT( opCode == OpTest );
        TS_ASSERT_SAME_DATA( &chunk ,&m_chunk, sizeof(Chunk) );

        m_log << m_magic << OpTest;
        TS_ASSERT_THROWS_NOTHING( m_log << m_info);
        m_log.flush();

        m_log >> magic >> opCode;
        TS_ASSERT_THROWS_NOTHING( m_log >> info); 
        
        TS_ASSERT( magic == m_magic);
        TS_ASSERT( opCode == OpTest );
        TS_ASSERT( info.name == m_info.name );
        TS_ASSERT( info.createTime == m_info.createTime );
        TS_ASSERT( info.size == m_info.size );
        TS_ASSERT( info.chunkSize == m_info.chunkSize );
        TS_ASSERT( info.replication == m_info.replication );

    }

};


#endif /* _TEST_TFSMASTER_FSLOG_HPP */

