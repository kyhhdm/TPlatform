/**
 * @file PageRankReducer.hpp
 * 
 * @author Chen Rishan
 * @date 2008-06-24
 * */
#ifndef PAGERANKREDUCER_HPP
#define PAGERANKREDUCER_HPP

#include "Reducer.hpp"

namespace mapreduce{

    class PageRankReducer : public Reducer{
    public:
    	bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const;
    };

}

#endif /* PAGERANKREDUCER_HPP:*/
