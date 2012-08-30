/**
 * @file WordFrequencyKeyComparison.hpp
 * @description it is implementation of the interface KeyComparison 
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#ifndef WORDFREQUENCYKEYCOMPARISON_HPP
#define WORDFREQUENCYKEYCOMPARISON_HPP

#include "IKeyComparison.hpp"
#include "IMapReduce.hpp"

DECLARE_FACTORY(IKeyComparison);

namespace mapreduce{
    class Buffer;
    typedef Buffer KeyValueField;

    class WordFrequencyKeyComparison : public IKeyComparison {
    public:
    	
        /**
         * @return value
         *         -1  key1 < key2
         *         0   key1 == key2
         *         1   key1 > key2
         * */
        int compare(const KeyValueField& key1, const KeyValueField& key2) const;

    };

}

#endif /* WORDFREQUENCYKEYCOMPARISON_HPP:*/
