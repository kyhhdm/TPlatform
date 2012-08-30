/**
 * @file WordCountReducer.hpp
 *
 * */
#ifndef WORDCOUNTREDUCER_HPP
#define WORDCOUNTREDUCER_HPP

#include "Reducer.hpp"

namespace mapreduce{

    class WordCountReducer : public Reducer{
    public:
    	bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const;
    };

}

#endif /* WORDCOUNTREDUCER_HPP:*/
