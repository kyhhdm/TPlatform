/**
 * @file WordFrequencyKeyHasher.hpp
 * @description it is implementation of the interface mapper 
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#ifndef WORDFREQUENCYKEYHASHER_HPP
#define WORDFREQUENCYKEYHASHER_HPP

#include "IKeyHasher.hpp"
#include "IMapReduce.hpp"

DECLARE_FACTORY(IKeyHasher);

namespace mapreduce{

    class WordFrequencyKeyHasher : public IKeyHasher{
    public:
    	
        int hash(const KeyValueField& key) const;

    };

}

#endif /* WORDFREQUENCYKEYHASHER_HPP:*/
