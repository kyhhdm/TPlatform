/**
 * @file PageLenReducer.cpp
 *
 * */
#include "PageLenReducer.hpp"
#include "mapred/KeyValueIterator.hpp"
#include "mapred/Collector.hpp"

using namespace std;
using namespace mapreduce;

bool PageLenReducer::reduce(const void* key, KeyValueIterator& values, Collector& collector) const
{
    //<int,char*> as reducer intput
    //<int,char*> as reducer output
    

    while(values.hasMore()){
        void* value = values.next();
        collector.collect( key, value);
    }

    return true;
}
