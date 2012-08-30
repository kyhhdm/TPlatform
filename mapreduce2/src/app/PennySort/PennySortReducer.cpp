/**
 * @file PennySortReducer.cpp
 *
 * */
#include "PennySortRecord.hpp"
#include "PennySortReducer.hpp"
#include "mapred/KeyValueIterator.hpp"
#include "mapred/Collector.hpp"

using namespace std;
using namespace mapreduce;

bool PennySortReducer::reduce(const void* key, KeyValueIterator& values, Collector& collector) const
{
    //<PennyRecordKey, PennyRecordValue> as mapper intput
    //<PennyRecordKey, PennyRecordValue> as mapper output

    while(values.hasMore()){
        void* value = values.next();
        collector.collect( key, value);
    }

    return true;
}
