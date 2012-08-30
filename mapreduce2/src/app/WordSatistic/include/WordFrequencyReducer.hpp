/**
 * @file WordFrequencyReducer.hpp
 * @description it is implementation of the interface reducer 
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#ifndef WORDFREQUENCYREDUCER_HPP
#define WORDFREQUENCYREDUCER_HPP

#include "IReducer.hpp"
#include "IMapReduce.hpp"

DECLARE_FACTORY(IReducer);

namespace mapreduce{

    class WordFrequencyReducer : public IReducer
    {
    public:
    	
        int reduce(const std::vector<boost::shared_ptr<KeyValue> >& inKeyValues, 
                   std::vector<boost::shared_ptr<KeyValue> >& outKeyValues) const ;

    };

}

#endif /* WORDFREQUENCYREDUCER_HPP:*/
