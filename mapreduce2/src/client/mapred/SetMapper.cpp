/**
 * @file SetMapper.cpp
 * @description it read <key,value> from input file, and call mapper its records one by one
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * @author Peng Bo
 * @date 2008-1-11
 *
 *
 * */

#include "SetMapper.hpp"
#include "Mapper.hpp"
#include "Partitioner.hpp"
#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include "FileStream.hpp"
#include "FileStreamLFS.hpp"
#include "FileStreamLocal.hpp"
#include "RecordReader.hpp"
#include "ClassLoader.hpp"
#include <assert.h>
#include <iostream>

using namespace std;
using namespace mapreduce;


SetMapper::SetMapper(TaskConfigure& taskConfigure, const string& inputFile, const vector<string>& outputFiles, bool useLFS)
        //:m_logger(Logger::getInstance("mapred_worker"))
{
	m_loader = new ClassLoader(taskConfigure.getDllName().c_str()); 

    //create RecordReader instance
    m_loader->createInstance(taskConfigure.getMapperRecordReaderClass().c_str(), (void*&)m_reader);
    //open readonly stream with no OpenOnDemand flag
    if(!useLFS){
        m_readerStream = new FileStreamLocal(inputFile, FileStream::ReadOnly, false);
    }
    else{
        m_readerStream = new FileStreamLFS(inputFile, FileStream::ReadOnly, false);
    }
    //initialize archive with default 8M buffer, and auto clear buffers
    m_reader->initialize(0,true);
    m_reader->open(m_readerStream);

    m_partitioner = new Partitioner(taskConfigure, outputFiles);

    m_loader->createInstance(taskConfigure.getMapperClass().c_str(), (void*&)m_mapper);

    //LOG4CPLUS_INFO(m_logger,"SetMapper::map(): from" << inputFile << " to " << outputFiles[0]);
}

SetMapper::~SetMapper()
{
    m_reader->close();
    delete m_reader;
    delete m_readerStream;    
    delete m_partitioner;
    delete m_loader;

    //LOG4CPLUS_INFO(m_logger,"SetMapper::map() task done!");
}

int SetMapper::map()
{
    int count = 0;
    try{
        void* key = m_reader->createKeys();
        void* value = m_reader->createValues();

        //#imporat to run with pointer, not the source allocated memory pointer
        void *doKey = key;
        void *doValue = value;
        while(m_reader->next(doKey, doValue)){
            
            m_mapper->map(doKey, doValue, *m_partitioner);

            m_reader->flush();

            count ++;
        }
        // use handle object to encapsulate key, value
        m_reader->releaseKeys(key);
        m_reader->releaseValues(value);
    }
    catch (exception& e){
        //LOG4CPLUS_ERROR(m_logger,"SetMapper::map(): exception " << e.what());

        return -1;
    }
    return count;
}
