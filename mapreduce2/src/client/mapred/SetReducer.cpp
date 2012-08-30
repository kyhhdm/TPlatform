/**
 * @file SetReducer.cpp
 * @description the implementation of SetReducer.hpp
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */


#include "SetReducer.hpp"
#include "KeyValuePool.hpp"
#include "Reducer.hpp"
#include "FileStream.hpp"
#include "FileStreamLocal.hpp"
#include "FileStreamLFS.hpp"
#include "FileStreamTfs.hpp"
#include "RecordReader.hpp"
#include "RecordWriter.hpp"
#include "HashableComparable.hpp"
#include "Collector.hpp"
#include "DirectCollector.hpp"
#include "ClassLoader.hpp"
#include "TaskConfigure.hpp"
#include <string>
#include <iostream>

using namespace mapreduce;
using namespace std;

SetReducer::SetReducer(TaskConfigure& taskConfigure, const string& inputFile, const string& outputFile, 
        bool local, bool combine , bool useLFS)
        //:m_logger(Logger::getInstance("mapred_worker"))
{
    m_loader = new ClassLoader(taskConfigure.getDllName().c_str()); 

    //create RecordReader instance
    m_loader->createInstance(taskConfigure.getIntermediateFileRecordReaderClass().c_str(), (void*&)m_reader);
    //open read only stream with no OpenOnDemand flag
    if(useLFS){
        m_readerStream = new FileStreamLFS(inputFile, FileStream::ReadOnly, false);
    }
    else{
        m_readerStream = new FileStreamLocal(inputFile, FileStream::ReadOnly, false);
    }
    //initialize archive with default 8M buffer, and no to auto clear buffers
    m_reader->initialize(8*1024*1024, true);
    m_reader->open(m_readerStream);

    //create RecordWriter instance
    if (combine) {
        m_loader->createInstance(taskConfigure.getIntermediateFileRecordWriterClass().c_str(), (void*&)m_writer);
    } else {
        m_loader->createInstance(taskConfigure.getReducerRecordWriterClass().c_str(), (void*&)m_writer);
    }
    //open append stream with no OpenOnDemand flag
    if (local){
        if(useLFS){        
            m_writerStream = new FileStreamLFS(outputFile, FileStream::Append, false);
        }
        else{
            m_writerStream = new FileStreamLocal(outputFile, FileStream::Append, false);
        }
    }
    else{
        m_writerStream = new FileStreamTfs(outputFile, FileStream::Append, false);
    }
    //initialize archive with default 8M buffer, and no to auto clear buffers
    //m_writer->initialize();
    m_writer->initialize(8*1024*1024, true);
    m_writer->open(m_writerStream);

    m_loader->createInstance(taskConfigure.getHashableComparableClass().c_str(), (void*&)m_comparator);

    m_directCollector = new DirectCollector(m_writer);

    m_loader->createInstance(taskConfigure.getReducerClass().c_str(), (void*&)m_reducer);

    //LOG4CPLUS_INFO(m_logger,"SetReducer from" << inputFile << " to " << outputFile);
}

SetReducer::~SetReducer()
{
    m_reader->close();
    m_writer->close();


    delete m_reader;
    delete m_writer;
    delete m_readerStream;
    delete m_writerStream;

    delete m_directCollector;
    delete m_comparator;
    delete m_loader;

    //LOG4CPLUS_INFO(m_logger,"SetReducer::reduce() task done!");
}

int SetReducer::reduce()
{
    int recordCnt = 0, reduceCnt = 0;
    void *prevKey, *key, *value;
    KeyValuePool keyPool(m_reader, true);
    KeyValuePool valuePool(m_reader, false);
    vector<void*> values;
    
    //get first key value pair
    keyPool.next(key);
    valuePool.next(value);

    if( !m_reader->next(key, value) ){
        //read empty file
        return 0;
    }
    prevKey = key;
    values.push_back(value);
    recordCnt ++;

    while(1){
        keyPool.next(key);
        valuePool.next(value);

        if( m_reader->next(key, value) ){
            if(!m_comparator->equal(key, prevKey)){
                VectorKeyValueIterator iter(values);
                //do reduce for all <key,value> in kvPool except the last one.
                m_reducer->reduce(prevKey, iter, *m_directCollector);
                reduceCnt ++;
                //release resources
                valuePool.clear();
                keyPool.clear();
                values.clear();
                m_reader->flush();
            }
            prevKey = key;

            //add value to container
            values.push_back(value);
        }
        else{
            //reach eof
            //do reduce for all <key,value> left in kvPool
            VectorKeyValueIterator iter(values);
                //cout <<" reduce" <<endl;
            m_reducer->reduce(prevKey, iter, *m_directCollector);
            reduceCnt ++;
            break;
        }
    }
    
    return reduceCnt;
}
