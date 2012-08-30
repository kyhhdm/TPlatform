/**
 * @file TaskConfigure.cpp
 * @description 
 *  TaskConfigure is configuration class for task operation, especially it's initialization.
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "TaskConfigure.hpp"
#include "mapreduce.h"
#include <string>
#include <vector>

using namespace std;
using namespace mapreduce;
using namespace mapreduce::api;

const string TaskConfigure::DefaultReaderClass("TextFileReader");
const string TaskConfigure::DefaultWriterClass="TextFileWriter";

void TaskConfigure::initialize()
{
	//primitive data types map to HashableComparable Class
    m_keyClassMap["char"] = "THashableComparable<char>";
	m_keyClassMap["int"] = "THashableComparable<int>";
	m_keyClassMap["short"] = "THashableComparable<short>";
	m_keyClassMap["long"] = "THashableComparable<long>";
	m_keyClassMap["long long"] = "THashableComparable<long long>";
	m_keyClassMap["unsigned char"] = "THashableComparable<unsigned char>";
	m_keyClassMap["unsigned int"] = "THashableComparable<unsigned int>";
	m_keyClassMap["unsigned short"] = "THashableComparable<unsigned short>";
	m_keyClassMap["unsigned long"] = "THashableComparable<unsigned long>";
	m_keyClassMap["unsigned long long"] = "THashableComparable<unsigned long long>";
	m_keyClassMap["float"] = "THashableComparable<float>";
	m_keyClassMap["double"] = "THashableComparable<double>";
	m_keyClassMap["long double"] = "THashableComparable<long double>";
    m_keyClassMap["std::string"] = "THashableComparable<std::string>";

	m_keyClassMap["char*"] = "TStringHashableComparable<char*>";
}

TaskConfigure::TaskConfigure()
{
	//setting default values
	m_soFile ="mapreduce.so";
	m_MapperClass = "";
	m_ReducerClass = "";	
	m_MapperOutKeyClass ="";
	m_MapperOutValueClass ="";

	m_MapperInKeyClass = ""; 
	m_MapperInValueClass = "";
	m_MapperRecordReaderClass = DefaultReaderClass ;

	m_ReducerOutKeyClass ="";
	m_ReducerOutValueClass ="";
	m_ReducerRecordWriterClass = DefaultWriterClass ;

	initialize();
}


TaskConfigure::TaskConfigure(const std::string& configureFile)
{
	//#TODO,load from configure file

	initialize();

}

TaskConfigure::TaskConfigure(MapReduceJob& jobSpec)
{
    m_soFile = jobSpec.soFile;
    m_MapperClass = jobSpec.mapperClass;
    m_ReducerClass = jobSpec.reducerClass;
    m_MapperOutKeyClass = jobSpec.mapperOutKeyClass;
    m_MapperOutValueClass = jobSpec.mapperOutValueClass;
    m_MapperInKeyClass = jobSpec.mapperInKeyClass;
    m_MapperInValueClass = jobSpec.mapperInValueClass;
    m_MapperRecordReaderClass = jobSpec.mapperRecordReaderClass;
    m_ReducerOutKeyClass = jobSpec.reducerOutKeyClass;
    m_ReducerOutValueClass = jobSpec.reducerOutValueClass;
    m_ReducerRecordWriterClass = jobSpec.reducerRecordWriterClass;
 
    if( m_MapperRecordReaderClass == "" ) m_MapperRecordReaderClass = DefaultReaderClass ;
    if( m_ReducerRecordWriterClass == "") m_ReducerRecordWriterClass = DefaultWriterClass ;  
	
    // build up the map
    initialize();
}


TaskConfigure::~TaskConfigure()
{
}

//
// Serialization
//
bool TaskConfigure::writeToString(std::string& output) const
{
    vector<const string*> object;

    object.push_back(&m_soFile);
    object.push_back(&m_MapperClass);
    object.push_back(&m_ReducerClass);
    object.push_back(&m_MapperOutKeyClass);
    object.push_back(&m_MapperOutValueClass);
    object.push_back(&m_MapperInKeyClass);
    object.push_back(&m_MapperInValueClass);
    object.push_back(&m_MapperRecordReaderClass);
    object.push_back(&m_ReducerOutKeyClass);
    object.push_back(&m_ReducerOutValueClass);
    object.push_back(&m_ReducerRecordWriterClass);

    //write out
    //#TODO, add checksum maybe necessary
    //#TODO, add escape code for delimiter '\t'
    for (int i = 0; i < object.size() ; i++ ){
        output += *(object[i]);
        output += '\t';
    }
    return true;
}

bool TaskConfigure::readFromString(const std::string& input)
{
    vector<string*> object;

    object.push_back(&m_soFile);
    object.push_back(&m_MapperClass);
    object.push_back(&m_ReducerClass);
    object.push_back(&m_MapperOutKeyClass);
    object.push_back(&m_MapperOutValueClass);
    object.push_back(&m_MapperInKeyClass);
    object.push_back(&m_MapperInValueClass);
    object.push_back(&m_MapperRecordReaderClass);
    object.push_back(&m_ReducerOutKeyClass);
    object.push_back(&m_ReducerOutValueClass);
    object.push_back(&m_ReducerRecordWriterClass);

    //read in
    string::size_type idx = 0, end;
    for (int i = 0; i < object.size() ; i++ ){
        end = input.find('\t', idx);
        if (end == string::npos){
            return false;
        }
        else{
            *(object[i]) = input.substr(idx, end - idx);
            idx = end + 1;
        }
    }
        
    return true;

}

//
//accessors
//
std::string TaskConfigure::getMapperRecordReaderClass()
{
    if ((m_MapperRecordReaderClass == DefaultReaderClass) || (m_MapperRecordReaderClass == "TKeyValueFeeder")){
        if (m_MapperInKeyClass != "" && m_MapperInValueClass != "") {
            //create from InKey,InValue class names
            return m_MapperRecordReaderClass + "<" + m_MapperInKeyClass + "," + m_MapperInValueClass + ">";
        }
    }
    return m_MapperRecordReaderClass;
}

std::string TaskConfigure::getReducerRecordWriterClass()
{
    if((m_ReducerRecordWriterClass == DefaultWriterClass) || (m_ReducerRecordWriterClass == "TKeyValueWriter")){
        if (m_ReducerOutKeyClass != "" && m_ReducerOutValueClass != "") {
            return m_ReducerRecordWriterClass + "<" + m_ReducerOutKeyClass + "," + m_ReducerOutValueClass + ">";
        }
    }
    return m_ReducerRecordWriterClass;
}

std::string TaskConfigure::getIntermediateFileRecordReaderClass()
{
    string readerClass = "TKeyValueFeeder<" + m_MapperOutKeyClass + "," + m_MapperOutValueClass + ">";
    return readerClass;
}

std::string TaskConfigure::getIntermediateFileRecordWriterClass()
{
    string writerClass = "TKeyValueWriter<" + m_MapperOutKeyClass + "," + m_MapperOutValueClass + ">";
    return writerClass;

}

std::string TaskConfigure::getHashableComparableClass()
{
    //system provide HashableComparableClass for primitive data types
    //and user class should extend HashableComparable interface
    map<string,string>::iterator pos = m_keyClassMap.find(m_MapperOutKeyClass);
    if (pos != m_keyClassMap.end()){
        return pos->second;
    }
    return m_MapperOutKeyClass + "Helper";
}
