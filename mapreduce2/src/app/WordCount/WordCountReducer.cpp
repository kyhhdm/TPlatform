/**
 * @file WordCountReducer.cpp
 *
 * */
#include "WordCountReducer.hpp"
#include "KeyValueIterator.hpp"
#include "Collector.hpp"

using namespace std;
using namespace mapreduce;

bool WordCountReducer::reduce(const void* key, KeyValueIterator& values, Collector& collector) const
{
    //<char*, int> as reducer intput
    //<char*, int> as reducer output
    int outValue = 0;

    while(values.hasMore()){
        outValue += *(int*)values.next();
    }
    collector.collect( key, &outValue);

    return true;
}
