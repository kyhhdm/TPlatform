/**
 * @file PageLenMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef PageLenMAPPER_HPP
#define PageLenMAPPER_HPP

#include "mapred/Mapper.hpp"

namespace mapreduce{

    class PageLenMapper: public Mapper{
    public:
        PageLenMapper();
        ~PageLenMapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:
    };

}

#endif /* PageLenMAPPER_HPP:*/
