/** 
 * @file TestTaskConfigure.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-07
 */
#ifndef _TEST_MAPREDUCE_PARTITIONER_HPP
#define _TEST_MAPREDUCE_PARTITIONER_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "TaskConfigure.hpp"
#include "Partitioner.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;

class PartitionerFixture : public CxxTest::GlobalFixture{
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


static PartitionerFixture PartitionerFixture;



class TestPartitioner: public CxxTest::TestSuite
{
	void printConfigure(TaskConfigure& configure)
	{
		cout << endl;
		cout << "DllName = " << configure.getDllName() << endl;
		cout << "Mapper Class = " << configure.getMapperClass() << endl;
		cout << "Reducer Class = " << configure.getReducerClass() << endl;
		cout << "Mapper OutKey = " << configure.getMapperOutKeyClass() << endl;
		cout << "Mapper OutValue = " << configure.getMapperOutValueClass() << endl;
		cout << "HashableComprarble Class = " << configure.getHashableComparableClass() << endl;
		cout << "Mapper Reader Class = " << configure.getMapperRecordReaderClass() <<endl;
		cout << "Reducer Writer Class = " << configure.getReducerRecordWriterClass() <<endl;
		cout << "Intermediate RecordReaderClass = " << configure.getIntermediateFileRecordReaderClass()<< endl;
		cout << "Intermediate RecordWriterClass = " << configure.getIntermediateFileRecordWriterClass()<< endl;
		cout << endl;
	}

    void doTestIntKey(char* rootDirectory)
    {
        remove_all(rootDirectory);
        create_directory( rootDirectory );

		TaskConfigure configure;

        configure.setDllName("MapReduceDll.dll");
		configure.setMapperClass("MyMapper");
		configure.setReducerClass("MyReducer");
		configure.setMapperOutKeyClass("int");
		configure.setMapperOutValueClass("char*");

		string className;

		className = configure.getIntermediateFileRecordWriterClass();
		TS_ASSERT(className == "TKeyValueWriter<int,char*>");
        className = configure.getHashableComparableClass();
        TS_ASSERT(className == "THashableComparable<int>");

        vector<string> outputFiles;
        outputFiles.push_back(string(rootDirectory) + "0.par");
        outputFiles.push_back(string(rootDirectory) + "1.par");
        outputFiles.push_back(string(rootDirectory) + "2.par");
        outputFiles.push_back(string(rootDirectory) + "3.par");
        outputFiles.push_back(string(rootDirectory) + "4.par");

        Partitioner* partitioner = new Partitioner(configure, outputFiles);

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
        int dataSize = sizeof(data)/sizeof(char*);

        for(int i=0; i< dataSize; i++){
            char** pData = &data[i];
            partitioner->collect( &i, pData);
        }

        delete partitioner;
        
        //check result
		
    }



public:

    //==============test goes here =====================

    void testIntKey(void)	{
        doTestIntKey("foo/");
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

