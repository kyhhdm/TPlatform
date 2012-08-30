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
        
        configure.setMapperClass("WordFrequencyMapper");
        configure.setReducerClass("WordFrequencyReducer");
        configure.setMapperOutKeyClass("char*");
        configure.setMapperOutValueClass("int");
        //set up mapper reader class
        configure.setMapperRecordReaderClass("TianwangRawFileFeeder");
        //set up reducer writer class
        configure.setReducerRecordWriterClass("TextFileWriter<char*,int>");        

        //check result
		
    }

    void doSorter(TaskConfigure& configure, char* rootDirectory)
    {
        vector<string> inputFiles;
        inputFiles.push_back("0.par");
        //inputFiles.push_back(string(rootDirectory) + "0.par");
        //inputFiles.push_back(string(rootDirectory) + "1.par");
        //inputFiles.push_back(string(rootDirectory) + "2.par");
        //inputFiles.push_back(string(rootDirectory) + "3.par");
        //inputFiles.push_back(string(rootDirectory) + "4.par");

        string outputFile = "sorted.dat";
        
        if(exists(outputFile)) remove(path(outputFile));

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

};


#endif /* _TEST_MAPREDUCE_PARTITIONER_HPP */

