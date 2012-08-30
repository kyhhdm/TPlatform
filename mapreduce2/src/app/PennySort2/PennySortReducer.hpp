/**
 * @file PennySortReducer.hpp
 *
 * */
#ifndef PennySortREDUCER_HPP
#define PennySortREDUCER_HPP

#include "Reducer.hpp"

namespace mapreduce{

    class PennySortReducer : public Reducer{
    public:
    	bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const;
    };

}

#endif /* PennySortREDUCER_HPP:*/
