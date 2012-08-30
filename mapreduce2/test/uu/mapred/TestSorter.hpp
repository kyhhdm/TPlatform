/** 
 * @file TestSorter.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-21
 */
#ifndef _TEST_MAPREDUCE_SORTER_HPP
#define _TEST_MAPREDUCE_SORTER_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "TaskConfigure.hpp"
#include "Partitioner.hpp"
#include "Sorter.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;

class SorterFixture : public CxxTest::GlobalFixture{
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


static SorterFixture SorterFixture;



class TestSorter: public CxxTest::TestSuite
{

    void doPrepareData(TaskConfigure& configure, char* rootDirectory)
    {
        remove_all(rootDirectory);
        create_directory( rootDirectory );

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

    void doSorter(TaskConfigure& configure, char* rootDirectory)
    {
        vector<string> inputFiles;
        inputFiles.push_back(string(rootDirectory) + "0.par");
        inputFiles.push_back(string(rootDirectory) + "1.par");
        inputFiles.push_back(string(rootDirectory) + "2.par");
        inputFiles.push_back(string(rootDirectory) + "3.par");
        inputFiles.push_back(string(rootDirectory) + "4.par");

        string outputFile = "sorted.dat";

        Sorter *sorter = new Sorter(configure, outputFile, inputFiles);

        TS_ASSERT(sorter != NULL);

        TS_ASSERT(sorter->sort() == true);

        delete sorter;
    }


public:

    //==============test goes here =====================

    void testIntKey(void)	{
        TaskConfigure configure;
        doPrepareData(configure, "foo/");
        doSorter(configure,"foo/");
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

