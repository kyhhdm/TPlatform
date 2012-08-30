/**
* @file DirectCollector.cpp
* @description 
*  DirectCollector is a special kind of Collector, which collect from reducer output 
*  and output by user defined RecordWriter
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "DirectCollector.hpp"
#include "RecordWriter.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace mapreduce;

DirectCollector::DirectCollector(RecordWriter* writer )
{
    m_writer = writer;
}

int DirectCollector::collect(const void* key, const void* value) 
{
    //cout <<"DirectCollector: collect" <<endl;
    return m_writer->append((void*)key, (void*)value);
}

