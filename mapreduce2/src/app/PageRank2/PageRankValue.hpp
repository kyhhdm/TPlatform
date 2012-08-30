/**
 * @file PageRankValue.hpp
 * @description: the value object which pagerank reducer generated
 *
 * @author ChenRishan
 * @date 2008-06-24
 *
 * */

#ifndef PAGERANK_PAGERANKVALUE_HPP
#define PAGERANK_PAGERANKVALUE_HPP

#include <string>
#include <vector>
#include <iostream>

namespace mapreduce{
    
    class Archive;

    class PageRankValue{
    public:
        
        PageRankValue();
        ~PageRankValue();
        
        double pagerank;
        char** linkoutURLs;
        int urlNumber;
        
        friend class Archive;

        
    };

    Archive& operator << (Archive& archive, const PageRankValue& value);
    
    Archive& operator >> (Archive& archive, PageRankValue*& value);
        
    std::ostream& operator << (std::ostream& out, const PageRankValue& value);
    
    std::istream& operator >> (std::istream& in, PageRankValue& value);
}

#endif
