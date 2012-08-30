/**
* @file Partitioner.cpp
* @description 
*  Partitioner is a special kind of Collector, which collect from mapper output 
*  and create intermediate files
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "Partitioner.hpp"
#include "TaskConfigure.hpp"
#include "ClassLoader.hpp"
#include "FileStreamLFS.hpp"
#include "FileStreamLocal.hpp"
#include "HashableComparable.hpp"
#include "TKeyValueWriter.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;
using namespace mapreduce;

Partitioner::Partitioner(TaskConfigure& taskConfigure, const vector<std::string>& outputFiles, bool useLFS)
{
    m_loader = new ClassLoader(taskConfigure.getDllName().c_str()); 

    m_loader->createInstance(taskConfigure.getHashableComparableClass().c_str(), (void*&)m_hasher);

    m_nPartition = outputFiles.size();
    FileStream* stream;
    RecordWriter* writer;

    for (int i = 0; i < m_nPartition; i++){
        string filename = outputFiles[i];

        //open stream with OpenOnDemand flag
        if(useLFS){
            stream = new FileStreamLFS(filename, FileStream::Append, false);
        }
        else{
            stream = new FileStreamLocal(filename, FileStream::Append, false);
        }
        //cout <<"New stream at " <<filename <<endl;

        //create RecordWriter instance
        //cout <<taskConfigure.getIntermediateFileRecordWriterClass() <<endl;
        m_loader->createInstance(taskConfigure.getIntermediateFileRecordWriterClass().c_str(), (void*&)writer);

        //initialize archive with 64KB buffer, autoClearBuffer
        writer->initialize(512*1024, true);
        writer->open(stream);

        m_streams.push_back(stream);
        m_writers.push_back(writer);
    }    

}

Partitioner::~Partitioner()
{
    unsigned int i;

    //important sequence: first delete writer, then delete stream
    for (i = 0; i < m_writers.size(); i++){
        delete m_writers[i];
    }
    for (i = 0; i < m_streams.size(); i++){
        delete m_streams[i];
    }
    delete m_hasher;
    delete m_loader;
}

int Partitioner::collect(const void* key, const void* value)
{
    /*
    static bool flag = false;
    if (flag == false) {
        cout <<"begin collect" <<endl;
        flag=true;
    }
    */
    int id = m_hasher->hash(key, m_nPartition);
    // yzf, check it
    assert(id < m_nPartition);
    return m_writers[id]->append((void*)key, (void*)value);
}

