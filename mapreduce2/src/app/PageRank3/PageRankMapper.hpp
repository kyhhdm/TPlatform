/**
 * @file PageRankMapper.hpp
 * @description it is implementation of the interface mapper 
 * the input is <char*,PageRankValue>
 * 
 * @author Chen Rishan
 * @date 2008-07-10
 * */
#ifndef PAGERANKMAPPER_HPP
#define PAGERANKMAPPER_HPP

#include "Mapper.hpp"


namespace mapreduce{

    class PageRankMapper: public Mapper{
    public:
        PageRankMapper();
        ~PageRankMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
    };

}

#endif /* PAGERANKFIRSTMAPPER_HPP:*/
