/** 
 * @file TestArchiveBuffer.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-07
 */
#ifndef _TEST_MAPREDUCE_ARCHIVEBUFFER_HPP
#define _TEST_MAPREDUCE_ARCHIVEBUFFER_HPP

//#define TEST_TFS

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "FileStreamLocal.hpp"
#include "ArchiveBuffer.hpp"

#ifdef TEST_TFS 
#include "FileStreamTfs.hpp"
#endif

#include "MapReduceException.hpp"
#include "util/Logger.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;
  
class ArchiveBufferFixture : public CxxTest::GlobalFixture{
    public:    
    bool setUpWorld() { 

        return true; 
    }

    bool tearDownWorld() { 
        return true; 
    }

    bool setUp() { 
        return true; 
    }    
    bool tearDown() { 
        return true; 
    }
};


static ArchiveBufferFixture ArchiveBufferFixture;


class TestArchiveBuffer: public CxxTest::TestSuite
{

    //==========helper functions=================
    FileStream* createFileStream(bool local, string& filename, FileStream::OpenMode openMode, bool openOnDemand)
    {
#ifdef TEST_TFS 
        if(local){
            return new FileStreamLocal(filename, openMode, openOnDemand);
        }
        else{
            return new FileStreamTfs(filename, openMode, openOnDemand);
        }
#else
            return new FileStreamLocal(filename, openMode, openOnDemand);
#endif

    }

    void doTestNormalAppend(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer(64, false);

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(writeStream));

        //prepare data
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "56789abcdef1234",
            "6789abcdef12345",
            "789abcdef123456",
            "89abcdef1234567XXX"
        };

        char* key, *value;
        key = archiveBuffer->appendZString(data[0]);
        cout << hex << (int)key << endl;

        TS_ASSERT( NULL != key );
        value = archiveBuffer->appendZString(data[1]);
        TS_ASSERT( NULL != value );
        archiveBuffer->commitAppendRecord();

        char* key2, *value2;
        key2 = archiveBuffer->appendZString(data[2]);
        cout << hex << (int)key2 << endl;
        TS_ASSERT( NULL != key2 );
        value2 = archiveBuffer->appendZString(data[3]);
        TS_ASSERT( NULL != value2 );
        archiveBuffer->commitAppendRecord();

        char* key3, *value3;
        key3 = archiveBuffer->appendZString(data[4]);
        cout << hex << (int)key3 << endl;
        TS_ASSERT( key == key3 );
        value3 = archiveBuffer->appendZString(data[5]);
        TS_ASSERT( value == value3 );

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->appendZString(data[6]));
        TS_ASSERT_THROWS(archiveBuffer->appendZString(data[7]), BufferError);

        TS_ASSERT_THROWS_NOTHING( archiveBuffer->closeStream()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
        int buffer[16], i;
        for(i = 0 ; i < 7 ; i++){
            TS_ASSERT(16 == readStream->read((char*)buffer, 16));
            TS_ASSERT_SAME_DATA(buffer, data[i] , 16);
        }
        TS_ASSERT(0 == readStream->read((char*)buffer, 20));

        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        delete archiveBuffer;
        //remove_all(rootDirectory);
    }

    void doTestRecordBreakAppend(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer(64, false);

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(writeStream));

        //prepare data
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "56789abcdef1234",
            "6789abcdef12345",
            "789abcdef123456",
            "89abcdef1234567XXXX"
        };

        char* key, *value;
        key = archiveBuffer->appendZString(data[0]);
        cout << hex << (int)key << endl;

        TS_ASSERT( NULL != key );
        value = archiveBuffer->appendZString(data[1]);
        TS_ASSERT( NULL != value );
        archiveBuffer->commitAppendRecord();

        char* key2, *value2;
        key2 = archiveBuffer->appendZString(data[2]);
        cout << hex << (int)key2 << endl;
        TS_ASSERT( NULL != key2 );
        value2 = archiveBuffer->appendZString(data[3]);
        TS_ASSERT( NULL != value2 );
        archiveBuffer->commitAppendRecord();

        char* key3, *value3;
        key3 = archiveBuffer->appendZString(data[4]);
        cout << hex << (int)key3 << endl;
        TS_ASSERT( key == key3 );
        value3 = archiveBuffer->appendZString(data[5]);
        TS_ASSERT( value == value3 );

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->appendZString(data[6]));
        TS_ASSERT_THROWS(archiveBuffer->appendZString(data[7]), BufferError);

        //-----------------------
        //modify doTestNormalAppend here
        //
        archiveBuffer->commitAppendRecord();
        TS_ASSERT_THROWS_NOTHING(archiveBuffer->appendZString(data[7]));

        //test auto save un committed data here
        //------------------------

        TS_ASSERT_THROWS_NOTHING( archiveBuffer->closeStream()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
        int buffer[20], i;
        for(i = 0 ; i < 7 ; i++){
            TS_ASSERT(16 == readStream->read((char*)buffer, 16));
            TS_ASSERT_SAME_DATA(buffer, data[i] , 16);
        }

        TS_ASSERT(20 == readStream->read((char*)buffer, 20));
        TS_ASSERT_SAME_DATA(buffer, data[7] , 20);

        TS_ASSERT(0 == readStream->read((char*)buffer, 20));
        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        delete archiveBuffer;
        //remove_all(rootDirectory);
    }

    void doTestRecordBreakRead(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //prepare data
        int i ;
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "789abcdef123456",
            "89abcdef1234567XXXX",
            "9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX"
        };

        //prepare test file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType, filename, FileStream::Append, false) );
        for(i = 0 ; i < sizeof(data)/sizeof(char*) ; i++){
            TS_ASSERT(strlen(data[i])+1 == writeStream->append((char*)data[i], strlen(data[i])+1));
        }
        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        //write a file
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType,filename, FileStream::ReadOnly, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer(35, false);

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(readStream));


        char* key[sizeof(data)/sizeof(char*)];
        i = 0;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        //archiveBuffer->commitReadRecord();

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        //archiveBuffer->commitReadRecord();

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i]<< endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        TS_ASSERT_THROWS(archiveBuffer->readZString(), BufferError);

        TS_ASSERT_THROWS_NOTHING( archiveBuffer->closeStream()); 

        //validate the keys, there are all there for no autoClearBuffset set
        for(i = 0 ; i < sizeof(data)/sizeof(char*) - 1 ; i++){
            TS_ASSERT(strcmp(data[i],key[i]) == 0);
        }       

        delete archiveBuffer;
        //remove_all(rootDirectory);
    }

    void doTestAutoClearBuffer(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //prepare data
        int i ;
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "789abcdef123456",
            "89abcdef1234567XXXX",
            "9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX"
        };

        //prepare test file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType, filename, FileStream::Append, false) );
        for(i = 0 ; i < sizeof(data)/sizeof(char*) ; i++){
            TS_ASSERT(strlen(data[i])+1 == writeStream->append((char*)data[i], strlen(data[i])+1));
        }
        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        //write a file
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType,filename, FileStream::ReadOnly, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer(35, true);

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(readStream));


        char* key[sizeof(data)/sizeof(char*)];
        i = 0;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        archiveBuffer->commitReadRecord();

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        archiveBuffer->commitReadRecord();


        //validate free buffer 0 , now
        TS_ASSERT(strcmp(key[0], data[0]) == 0 );
        TS_ASSERT(strcmp(key[2], data[2]) == 0 );

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        //validate free buffer 0 , now
        TS_ASSERT(strcmp(key[0], data[0]) != 0 );
        TS_ASSERT(strcmp(key[2], data[2]) == 0 );

        archiveBuffer->commitReadRecord();

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i]<< endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        //validate free buffer 0 , now
        TS_ASSERT(strcmp(key[2], data[2]) != 0 );

        TS_ASSERT_THROWS(archiveBuffer->readZString(), BufferError);

        TS_ASSERT_THROWS_NOTHING( archiveBuffer->closeStream()); 

        delete archiveBuffer;
        //remove_all(rootDirectory);

    }

    void doTestGetRecord(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //prepare data
        int i ;
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "789abcdef123456",
            "89abcdef1234567XXXX",
            "9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX9abcdef12345678XXXX"
        };

        //prepare test file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType, filename, FileStream::Append, false) );
        for(i = 0 ; i < sizeof(data)/sizeof(char*) ; i++){
            TS_ASSERT(strlen(data[i])+1 == writeStream->append((char*)data[i], strlen(data[i])+1));
        }
        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        //write a file
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType,filename, FileStream::ReadOnly, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer(35, false);

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(readStream));


        char* key[sizeof(data)/sizeof(char*)];
        int position[sizeof(data)/sizeof(char*)];
        i = 0;

        position[0] = 0;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        
        position[i/2] = archiveBuffer->commitReadRecord();

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        TS_ASSERT( key[i-1] + 16 == key[i] );
        i++;
        position[i/2] = archiveBuffer->commitReadRecord();


        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i] << endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );


        key[i] = archiveBuffer->readZString();
        TS_ASSERT_SAME_DATA(key[i], data[i] , strlen(data[i]));
        cout << hex << (int)key[i]<< endl;
        TS_ASSERT( NULL != key[i] );
        i++;
        TS_ASSERT( key[i-1] + 16 != key[i] );

        position[i/2] = archiveBuffer->commitReadRecord();

        TS_ASSERT_THROWS(archiveBuffer->readZString(), BufferError);

        TS_ASSERT_THROWS_NOTHING( archiveBuffer->closeStream()); 


        //validate the records
        //ArchiveBuffer::RegionIterator iter;
        //int regionCnt; 
        //regionCnt = archiveBuffer->getRecord(position[0], position[1], iter);
        //TS_ASSERT( regionCnt == 1);
        //TS_ASSERT( (*iter).pStart == key[0] );
        //TS_ASSERT( (*iter).len == 32 );

        //regionCnt = archiveBuffer->getRecord(position[1], position[2], iter);
        //TS_ASSERT( regionCnt == 1);
        //TS_ASSERT( (*iter).pStart == key[2] );
        //TS_ASSERT( (*iter).len == 32 );

        //regionCnt = archiveBuffer->getRecord(position[2], position[3], iter);
        //TS_ASSERT( regionCnt == 2);
        //TS_ASSERT( (*iter).pStart == key[4] );
        //TS_ASSERT( (*iter).len == strlen(key[4]) + 1 );
        //++iter;
        //TS_ASSERT( (*iter).pStart == key[5] );
        //TS_ASSERT( (*iter).len == strlen(key[5]) + 1  );

        //regionCnt = archiveBuffer->getRecord(position[1], position[3], iter);
        //TS_ASSERT( regionCnt == 3);
        //TS_ASSERT( (*iter).pStart == key[2] );
        //TS_ASSERT( (*iter).len == 32 );
        //++iter;
        //TS_ASSERT( (*iter).pStart == key[4] );
        //TS_ASSERT( (*iter).len == strlen(key[4]) + 1 );
        //++iter;
        //TS_ASSERT( (*iter).pStart == key[5] );
        //TS_ASSERT( (*iter).len == strlen(key[5]) + 1  );


        //validate the records
        RegionIterator iter;
        int regionCnt; 
        iter = archiveBuffer->getRecord(position[0], position[1]);
        TS_ASSERT( iter.size() == 1);
        TS_ASSERT( (*iter).pStart == key[0] );
        TS_ASSERT( (*iter).len == 32 );

        iter = archiveBuffer->getRecord(position[1], position[2]);
        TS_ASSERT( iter.size() == 1);
        TS_ASSERT( (*iter).pStart == key[2] );
        TS_ASSERT( (*iter).len == 32 );

        iter = archiveBuffer->getRecord(position[2], position[3]);
        TS_ASSERT( iter.size() == 2);
        TS_ASSERT( (*iter).pStart == key[4] );
        TS_ASSERT( (*iter).len == strlen(key[4]) + 1 );
        ++iter;
        TS_ASSERT( (*iter).pStart == key[5] );
        TS_ASSERT( (*iter).len == strlen(key[5]) + 1  );

        iter = archiveBuffer->getRecord(position[1], position[3]);
        TS_ASSERT( iter.size() == 3);
        TS_ASSERT( (*iter).pStart == key[2] );
        TS_ASSERT( (*iter).len == 32 );
        ++iter;
        TS_ASSERT( (*iter).pStart == key[4] );
        TS_ASSERT( (*iter).len == strlen(key[4]) + 1 );
        ++iter;
        TS_ASSERT( (*iter).pStart == key[5] );
        TS_ASSERT( (*iter).len == strlen(key[5]) + 1  );


        delete archiveBuffer;
        //remove_all(rootDirectory);

    }

    void doTestReadMultiFile(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        ArchiveBuffer* archiveBuffer;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchiveBuffer.dat";

        //prepare data
        int i ;
        int data[]={ 0x55, 0xaa };

        //prepare test file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType, filename, FileStream::Append, false) );
        for(i = 0 ; i < sizeof(data)/sizeof(int) ; i++){
            TS_ASSERT( 4 == writeStream->append((const char*)&data[i], sizeof(int)));
        }
        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType,filename, FileStream::ReadOnly, false) );

        //test a short non-auto clear buffer
        archiveBuffer = new ArchiveBuffer();

        char* key[10 * sizeof(data)/sizeof(int)];


        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(readStream));
        
        i = 0;
        key[i] = archiveBuffer->readData(sizeof(int));
        TS_ASSERT_SAME_DATA(key[i], &data[i] , sizeof(int));
        i++;

        key[i] = archiveBuffer->readData(sizeof(int));
        TS_ASSERT_SAME_DATA(key[i], &data[i] , sizeof(int));
        TS_ASSERT( key[i-1] + 4 == key[i] );
        i++;

        TS_ASSERT(NULL == archiveBuffer->readData(sizeof(int)));

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->closeStream());

        //read file 2
        delete readStream;
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType,filename, FileStream::ReadOnly, false) );
        TS_ASSERT_THROWS_NOTHING(archiveBuffer->openStream(readStream));

        key[i] = archiveBuffer->readData(sizeof(int));
        TS_ASSERT_SAME_DATA(key[i], &data[i-2] , sizeof(int));
        TS_ASSERT( key[i-1] + 4 == key[i] );
        i++;

        key[i] = archiveBuffer->readData(sizeof(int));
        TS_ASSERT_SAME_DATA(key[i], &data[i-2] , sizeof(int));
        TS_ASSERT( key[i-1] + 4 == key[i] );
        i++;

        TS_ASSERT(NULL == archiveBuffer->readData(sizeof(int)));

        TS_ASSERT_THROWS_NOTHING(archiveBuffer->closeStream());

    }

public:

    //==============test goes here =====================

    void testLocal1(void)	{
       doTestNormalAppend( true, "foo");
    }

    void testLocal2(void)	{
        doTestRecordBreakAppend( true, "foo");
    }
    
    void testLocal3(void){
        doTestRecordBreakRead(true, "foo");
    }

    void testLocal4(void){
        doTestAutoClearBuffer(true, "foo");
    }

    void testLocal5(void){
        doTestGetRecord(true, "foo");
    }

    void testLocal6(void){
        doTestReadMultiFile(true, "foo");
    }    

    //#TODO
    // test openStream/closeStream multiple time
    // test PString 

};


#endif /* _TEST_TFSMASTER_ARCHIVEBUFFER_HPP */

