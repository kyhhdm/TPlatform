/**
 * @file PennySortMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef PennySortMAPPER_HPP
#define PennySortMAPPER_HPP

#include "mapred/Mapper.hpp"

class CParser;

namespace mapreduce{

    class PennySortMapper: public Mapper{
    public:
        PennySortMapper();
        ~PennySortMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:

    };

}

#endif /* PennySortMAPPER_HPP:*/
