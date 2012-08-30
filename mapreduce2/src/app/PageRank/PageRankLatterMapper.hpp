/**
 * @file PageRankLatterMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef PAGERANKLATTERMAPPER_HPP
#define PAGERANKLATTERMAPPER_HPP

#include "Mapper.hpp"

class CParser;

namespace mapreduce{

    class PageRankLatterMapper: public Mapper{
    public:
        PageRankLatterMapper();
        ~PageRankLatterMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
        CParser *m_parser;
    };

}

#endif /* PAGERANKLATTERMAPPER_HPP:*/
