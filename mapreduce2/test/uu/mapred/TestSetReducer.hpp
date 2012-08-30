/** 
 * @file TestSetReducer.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-21
 */
#ifndef _TEST_MAPREDUCE_SETREDUCER_HPP
#define _TEST_MAPREDUCE_SETREDUCER_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "Partitioner.hpp"
#include "SetReducer.hpp"
#include "Sorter.hpp"
#include "Reducer.hpp"
#include "TaskConfigure.hpp"
#include "MapReduceException.hpp"

#include <string>
#include <vector>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;

class SetReducerFixture : public CxxTest::GlobalFixture{
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


static SetReducerFixture SetReducerFixture;



class TestSetReducer: public CxxTest::TestSuite
{

    void doSetReducer(TaskConfigure& configure, char* rootDirectory)
    {
        configure.setDllName("MapReduceDll.dll");
        configure.setMapperClass("CharCountMapper");
        configure.setReducerClass("CharCountReducer");
        configure.setMapperOutKeyClass("char");
        configure.setMapperOutValueClass("int");
        //set up mapper reader class
        configure.setMapperInKeyClass("int");
        configure.setMapperInValueClass("char*");
        //set up reducer writer class
        configure.setReducerOutKeyClass("char");
        configure.setReducerOutValueClass("int");


        string className;

        className = configure.getIntermediateFileRecordWriterClass();
        TS_ASSERT(className == "TKeyValueWriter<char,int>");
        className = configure.getIntermediateFileRecordReaderClass();
        TS_ASSERT(className == "TKeyValueFeeder<char,int>");
        className = configure.getHashableComparableClass();
        TS_ASSERT(className == "THashableComparable<char>");

        //prepare mapped and sorted them
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

        //
        string inputFile = outputFile;
        outputFile = "result.dat";

        if(exists(outputFile)) remove(path(outputFile));

        SetReducer *setReducer;
        TS_ASSERT_THROWS_NOTHING( setReducer = new SetReducer(configure, inputFile, outputFile));

        TS_ASSERT( setReducer->reduce() == 12);

        TS_ASSERT_THROWS_NOTHING(delete setReducer);
    }


public:

    //==============test goes here =====================

    void testIntKey(void)	{
        TaskConfigure configure;
        doSetReducer(configure,"foo/");
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

