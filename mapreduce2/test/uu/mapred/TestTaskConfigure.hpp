/** 
 * @file TestTaskConfigure.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-07
 */
#ifndef _TEST_MAPREDUCE_TASKCONFIGURE_HPP
#define _TEST_MAPREDUCE_TASKCONFIGURE_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "TaskConfigure.hpp"
#include <time.h>
#include <string>
#include <iostream>


using namespace std;
using namespace mapreduce;
  
class TaskConfigureFixture : public CxxTest::GlobalFixture{
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


static TaskConfigureFixture TaskConfigureFixture;



class TestTaskConfigure: public CxxTest::TestSuite
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

    void doTestDefaulSettings()
    {
		TaskConfigure configure;

		configure.setMapperClass("MyMapper");
		configure.setReducerClass("MyReducer");
		configure.setMapperOutKeyClass("int");
		configure.setMapperOutValueClass("char*");
        configure.setReducerOutKeyClass("int");
        configure.setReducerOutValueClass("char*");


		string className;

		className = configure.getHashableComparableClass();
		TS_ASSERT(className == "THashableComparable<int>");
		className = configure.getMapperRecordReaderClass();
		TS_ASSERT(className == TaskConfigure::DefaultReaderClass);
		className = configure.getReducerRecordWriterClass();
		TS_ASSERT(className == "TextFileWriter<int,char*>");

		className = configure.getIntermediateFileRecordReaderClass();
		TS_ASSERT(className == "TKeyValueFeeder<int,char*>");
		className = configure.getIntermediateFileRecordWriterClass();
		TS_ASSERT(className == "TKeyValueWriter<int,char*>");

		printConfigure(configure);
    }

	void doTestUserKeyValueClass()
	{
		TaskConfigure configure;

		configure.setMapperClass("MyMapper");
		configure.setReducerClass("MyReducer");
		configure.setMapperOutKeyClass("UserKeyClass");
		configure.setMapperOutValueClass("UserValueClass");

		string className;

		className = configure.getHashableComparableClass();
		TS_ASSERT(className == "UserKeyClassHelper");
		className = configure.getMapperRecordReaderClass();
		TS_ASSERT(className == TaskConfigure::DefaultReaderClass);
		className = configure.getReducerRecordWriterClass();
		TS_ASSERT(className == TaskConfigure::DefaultWriterClass);

		className = configure.getIntermediateFileRecordReaderClass();
		TS_ASSERT(className == "TKeyValueFeeder<UserKeyClass,UserValueClass>");
		className = configure.getIntermediateFileRecordWriterClass();
		TS_ASSERT(className == "TKeyValueWriter<UserKeyClass,UserValueClass>");

		printConfigure(configure);
	}

	void doTestUseIntermediateReaderWriter()
	{
		TaskConfigure configure;

		configure.setMapperClass("MyMapper");
		configure.setReducerClass("MyReducer");
		configure.setMapperOutKeyClass("UserKeyClass");
		configure.setMapperOutValueClass("UserValueClass");
		configure.setMapperInKeyClass("int");
		configure.setMapperInValueClass("char*");
		configure.setReducerOutKeyClass("int");
		configure.setReducerOutValueClass("string");
        configure.setMapperRecordReaderClass("TKeyValueFeeder");
        configure.setReducerRecordWriterClass("TKeyValueWriter");


		string className;

		className = configure.getHashableComparableClass();
		TS_ASSERT(className == "UserKeyClassHelper");
		className = configure.getMapperRecordReaderClass();
		TS_ASSERT(className == "TKeyValueFeeder<int,char*>");
		className = configure.getReducerRecordWriterClass();
		TS_ASSERT(className == "TKeyValueWriter<int,string>");

		className = configure.getIntermediateFileRecordReaderClass();
		TS_ASSERT(className == "TKeyValueFeeder<UserKeyClass,UserValueClass>");
		className = configure.getIntermediateFileRecordWriterClass();
		TS_ASSERT(className == "TKeyValueWriter<UserKeyClass,UserValueClass>");

		printConfigure(configure);
	}

    void doTestSerialization()
    {
        TaskConfigure configureEx;
        TaskConfigure configure;
        string output;

        configureEx.setMapperClass("MyMapper");
        configureEx.setReducerClass("MyReducer");
        configureEx.setMapperOutKeyClass("int");
        configureEx.setMapperOutValueClass("char*");

        configureEx.writeToString(output);

        configure.readFromString(output);

        string className;

        className = configure.getHashableComparableClass();
        TS_ASSERT(className == "THashableComparable<int>");
        className = configure.getMapperRecordReaderClass();
        TS_ASSERT(className == TaskConfigure::DefaultReaderClass);
        className = configure.getReducerRecordWriterClass();
        TS_ASSERT(className == TaskConfigure::DefaultWriterClass);

        className = configure.getIntermediateFileRecordReaderClass();
        TS_ASSERT(className == "TKeyValueFeeder<int,char*>");
        className = configure.getIntermediateFileRecordWriterClass();
        TS_ASSERT(className == "TKeyValueWriter<int,char*>");

        printConfigure(configureEx);
        printConfigure(configure);

    }

public:

    //==============test goes here =====================

    void testDefaulSettings(void)	{
        doTestDefaulSettings();
    }

    void testUserKeyValueClass(void)	{
       doTestUserKeyValueClass();
    }
    
    void testUseIntermediateReaderWriter(void){
        doTestUseIntermediateReaderWriter();
    }

    void testSerialization(void){
        doTestSerialization();
    }

    void testLocal5(void){
    }


};


#endif /* _TEST_TFSMASTER_TASKCONFIGURE_HPP */

