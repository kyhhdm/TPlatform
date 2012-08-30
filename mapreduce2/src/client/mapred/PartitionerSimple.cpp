/**
* @file PartitionerSimple.cpp
* @description 
*  PartitionerSimple is a special kind of Collector, which collect from mapper output 
*  and create intermediate files
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "PartitionerSimple.hpp"
#include "FileStreamLocal.hpp"
#include "HashableComparable.hpp"
#include "TKeyValueWriter.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace mapreduce;


PartitionerSimple::PartitionerSimple(HashableComparable* hasher, std::vector<RecordWriter*>& writers):
    m_writers(writers.begin(), writers.end())
{
    int m_nPartition = writers.size();

    m_hasher = hasher;

    //m_writers.copy(writers.beign(), writers.end());
    
}

PartitionerSimple::~PartitionerSimple()
{
}

int PartitionerSimple::collect(const void* key, const void* value)
{
    int id = m_hasher->hash(key, m_nPartition);

    return m_writers[id]->append(key, value);
}

