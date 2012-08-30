/** 
 * @file TestFileStream.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-07
 */
#ifndef _TEST_MAPREDUCE_FILESTREAM_HPP
#define _TEST_MAPREDUCE_FILESTREAM_HPP

//#define TEST_TFS

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "FileStreamLocal.hpp"

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
  
class FileStreamFixture : public CxxTest::GlobalFixture{
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


static FileStreamFixture FileStreamFixture;


class TestFileStream: public CxxTest::TestSuite
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

    void doTestAll(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/testFileStream.dat";

        TS_ASSERT_THROWS(readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false), FSError);

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        int i, j;
        int* buffer;

        buffer = new int[1024];

        for(i = 0; i< 16; i++){

            for(j = 0 ; j< 1024; j++){
                buffer[j] = i*1024 + j;
            }

            TS_ASSERT(1024*sizeof(int) == writeStream->append((const char*)buffer, 1024*sizeof(int)));

        }

        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );

        int* buffer2;

        buffer2 = new int[1024];

        for(i = 0; i< 16; i++){

            for(j = 0 ; j< 1024; j++){
                buffer[j] = i*1024 + j;
            }

            TS_ASSERT(1024*sizeof(int) == readStream->read((char*)buffer2, 1024*sizeof(int)));
            TS_ASSERT_SAME_DATA(buffer, buffer2 , 1024*sizeof(int));

        }

        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        delete[] buffer;
        delete[] buffer2;
        remove_all(rootDirectory);
    }

    void doTestOpenOnDemand(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/testFileStream.dat";

        TS_ASSERT_THROWS(readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false), FSError);


        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType, filename, FileStream::Append, true) );

        TS_ASSERT_THROWS(readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false), FSError);

        int i, j;
        int* buffer, *buffer2;

        buffer = new int[1024];
        buffer2 = new int[1024];

        for(i = 0; i< 16; i++){

            for(j = 0 ; j< 1024; j++){
                buffer[j] = i*1024 + j;
            }

            TS_ASSERT(1024*sizeof(int) == writeStream->append((const char*)buffer, 1024*sizeof(int)));

            if(i==0){
                TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
            }

            TS_ASSERT(1024*sizeof(int) == readStream->read((char*)buffer2, 1024*sizeof(int)));
            TS_ASSERT_SAME_DATA(buffer, buffer2 , 1024*sizeof(int));

        }

        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 
        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        delete[] buffer;
        delete[] buffer2;
        remove_all(rootDirectory);

    }


    void doTestReadEof(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/testFileStream.dat";

        TS_ASSERT_THROWS(readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false), FSError);

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        int i, j;
        int* buffer;

        buffer = new int[1024];

        for(i = 0; i< 16; i++){

            for(j = 0 ; j< 1024; j++){
                buffer[j] = i*1024 + j;
            }

            TS_ASSERT(1024*sizeof(int) == writeStream->append((const char*)buffer, 1024*sizeof(int)));

        }

        TS_ASSERT_THROWS_NOTHING( writeStream->close()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );

        int* buffer2;

        buffer2 = new int[1024];

        for(i = 0; i< 16; i++){

            for(j = 0 ; j< 1024; j++){
                buffer[j] = i*1024 + j;
            }

            TS_ASSERT(1024*sizeof(int) == readStream->read((char*)buffer2, 1024*sizeof(int)));
            TS_ASSERT_SAME_DATA(buffer, buffer2 , 1024*sizeof(int));

        }

        //read more data at eof
        TS_ASSERT(0 == readStream->read((char*)buffer2, 1));

        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        delete[] buffer;
        delete[] buffer2;
        remove_all(rootDirectory);
    }


public:

    //==============test goes here =====================

    void testLocalAll(void)	{
       doTestAll( true, "foo");
    }

    void testLocalOpenOnDemand(){
        doTestOpenOnDemand( true, "foo");
    }
    
    void testReadEof(){
        doTestReadEof( true, "foo");
    }

    void testTfsAll(void){
        doTestAll(false, "/foo");
    }

    void testTfsOpenOnDemand(){
        doTestOpenOnDemand(false, "/foo");
    }

    void testTfsReadEof(){
        doTestReadEof( false, "/foo");
    }

};


#endif /* _TEST_TFSMASTER_FileStream_HPP */

