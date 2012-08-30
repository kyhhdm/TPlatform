/**
 * @file WordFrequencyMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef WORDFREQUENCYMAPPER_HPP
#define WORDFREQUENCYMAPPER_HPP

#include "Mapper.hpp"

class CParser;

namespace mapreduce{

    class WordFrequencyMapper: public Mapper{
    public:
        WordFrequencyMapper();
        ~WordFrequencyMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
        CParser *m_parser;
    };

}

#endif /* WORDFREQUENCYMAPPER_HPP:*/
