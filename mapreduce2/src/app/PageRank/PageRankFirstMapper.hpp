/**
 * @file PageRankFirstMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef PAGERANKFIRSTMAPPER_HPP
#define PAGERANKFIRSTMAPPER_HPP

#include "Mapper.hpp"

class CParser;

namespace mapreduce{

    class PageRankFirstMapper: public Mapper{
    public:
        PageRankFirstMapper();
        ~PageRankFirstMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
        CParser *m_parser;
    };

}

#endif /* PAGERANKFIRSTMAPPER_HPP:*/
