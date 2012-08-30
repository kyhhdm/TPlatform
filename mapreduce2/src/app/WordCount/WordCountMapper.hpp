/**
 * @file WordCountMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef WORDCOUNTMAPPER_HPP
#define WORDCOUNTMAPPER_HPP

#include "Mapper.hpp"

class CParser;

namespace mapreduce{

    class WordCountMapper: public Mapper{
    public:
        WordCountMapper();
        ~WordCountMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
        CParser *m_parser;
    };

}

#endif /* WORDCOUNTMAPPER_HPP:*/
