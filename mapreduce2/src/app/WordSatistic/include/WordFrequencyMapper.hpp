/**
 * @file WordFrequencyMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#ifndef WORDFREQUENCYMAPPER_HPP
#define WORDFREQUENCYMAPPER_HPP

#include "IMapper.hpp"
#include "IMapReduce.hpp"

DECLARE_FACTORY(IMapper);

class CParser;

namespace mapreduce{

    class WordFrequencyMapper : public IMapper{
        public:
            WordFrequencyMapper();
            ~WordFrequencyMapper();

            int map(const KeyValue& inKeyValue, std::vector<boost::shared_ptr<KeyValue> >& outKeyValues) const ;

        private:
            CParser *m_parser;
    };

}

#endif /* WORDFREQUENCYMAPPER_HPP:*/
