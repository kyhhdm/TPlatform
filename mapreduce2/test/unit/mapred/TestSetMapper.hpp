/** 
 * @file TestSetMapper.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-21
 */
#ifndef _TEST_MAPREDUCE_SETMAPPER_HPP
#define _TEST_MAPREDUCE_SETMAPPER_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "TaskConfigure.hpp"
#include "Partitioner.hpp"
#include "SetMapper.hpp"
#include "FileStream.hpp"
#include "FileStreamLocal.hpp"
#include "ArchiveBuffer.hpp"
#include "Archive.hpp"
#include "RecordReader.hpp"
#include "RecordWriter.hpp"
#include "TKeyValueFeeder.hpp"
#include "TKeyValueWriter.hpp"
#include "MapReduceException.hpp"

#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;

class SetMapperFixture : public CxxTest::GlobalFixture{
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


static SetMapperFixture SetMapperFixture;



class TestSetMapper: public CxxTest::TestSuite
{

    void doPrepareData(char* rootDirectory, int& recordCnt, string& filename)
    {
        remove_all(rootDirectory);
        create_directory( rootDirectory );

        filename = string(rootDirectory) + "/input.dat";
        FileStream* writeStream;

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = new FileStreamLocal(filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        RecordWriter *writer = new TKeyValueWriter<int, char*>();
        writer->initialize();

        TS_ASSERT_THROWS_NOTHING(writer->open(writeStream));

        //prepare data
        int key = 0;
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

        recordCnt = sizeof(data)/sizeof(char*);
        for(key = 0 ; key <recordCnt; key++){
            char* *pData = &data[key];
            writer->append(&key, pData);
        }

        TS_ASSERT_THROWS_NOTHING( writer->close()); 

        delete writer;
        delete writeStream;
      
    }

    void doSetMapper(TaskConfigure& configure, char* rootDirectory, int recordCnt, string& inputFile)
    {
        configure.setDllName("MapReduceDll.dll");
        configure.setMapperClass("CharCountMapper");
        configure.setReducerClass("MyReducer");
        configure.setMapperOutKeyClass("char");
        configure.setMapperOutValueClass("int");
        //set up mapper reader class
        configure.setMapperInKeyClass("int");
        configure.setMapperInValueClass("char*");

        string className;

        className = configure.getIntermediateFileRecordWriterClass();
        TS_ASSERT(className == "TKeyValueWriter<char,int>");
        className = configure.getHashableComparableClass();
        TS_ASSERT(className == "THashableComparable<char>");

        vector<string> outputFiles;
        outputFiles.push_back(string(rootDirectory) + "0.par");
        outputFiles.push_back(string(rootDirectory) + "1.par");
        outputFiles.push_back(string(rootDirectory) + "2.par");
        outputFiles.push_back(string(rootDirectory) + "3.par");
        outputFiles.push_back(string(rootDirectory) + "4.par");

        SetMapper *setMapper;
        TS_ASSERT_THROWS_NOTHING( setMapper = new SetMapper(configure, inputFile, outputFiles));

        TS_ASSERT( setMapper->map() == recordCnt);

        TS_ASSERT_THROWS_NOTHING(delete setMapper);
    }


public:

    //==============test goes here =====================

    void testIntKey(void)	{
        TaskConfigure configure;
        int recordCnt;
        string filename;
        doPrepareData("foo/", recordCnt, filename);
        doSetMapper(configure,"foo/", recordCnt, filename );
    }

    void testUserKeyValueClass(void)	{
    }
    
    void testUseIntermediateReaderWriter(void){
    }

    void testLocal4(void){
    }

    void testLocal5(void){
    }


};


#endif /* _TEST_MAPREDUCE_PARTITIONER_HPP */

