/**
 * @file PennySortMapper.cpp
 *
 * */
#include "PennySortRecord.hpp"
#include "PennySortMapper.hpp"
#include "Collector.hpp"
#include <iostream>

using namespace std;
using namespace mapreduce;


PennySortMapper::PennySortMapper()
{
}

PennySortMapper::~PennySortMapper()
{
}

bool PennySortMapper::map(const void* key, const void* value, Collector& collector) const
{
    //<PennyRecordKey, PennyRecordValue> as mapper intput
    //<PennyRecordKey, PennyRecordValue> as mapper output

    collector.collect( key, value);
    
    //cout << *(char**)key << " : " << bodyLen << " : " << outputCnt << endl;

    return true;
}

