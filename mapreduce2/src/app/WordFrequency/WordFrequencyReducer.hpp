/**
 * @file WordFrequencyReducer.hpp
 *
 * */
#ifndef WORDFREQUENCYREDUCER_HPP
#define WORDFREQUENCYREDUCER_HPP

#include "mapred/Reducer.hpp"

namespace mapreduce{

    class WordFrequencyReducer : public Reducer{
    public:
    	bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const;
    };

}

#endif /* WORDFREQUENCYREDUCER_HPP:*/
