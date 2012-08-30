/**
 * @file Region.hpp
 * @date 2008-04-17
 * @description:
 *  Region is a memory block, original design for ArchiveBuffer.
 *
 * */

#ifndef TPLATFORM_MAPREDUCE_REGION
#define TPLATFORM_MAPREDUCE_REGION

#include <mapred/MapReduceException.hpp>
#include <vector>
#include <string>

namespace mapreduce{
    class Region{
    public:
        char* pStart;
        int   len;
    };

    //typedef std::vector<Region>::iterator RegionIterator;
    class RegionIterator{
        std::vector<Region>::iterator m_iter;
        int m_count;
    public:
        RegionIterator(){m_count = 0;}
        //RegionIterator(std::vector<Region>::iterator& iter, int count):m_iter(iter),m_count(count){}
        RegionIterator(std::vector<Region>::iterator iter, int count):m_iter(iter),m_count(count){}

        /**
        * counter
        **/  
        int size(){return m_count;}

        /**
        * HasMore
        **/  
        bool hasMore(){return m_count>0;}

        /**
        * next
        **/  
        Region& next(){
            if(m_count <= 0){
                //throw std::exception("RegionIterator::next() exceed limit error!");
                throw BufferError("RegionIterator::next() exceed limit error!");
            }
            Region& region = *m_iter;
            ++m_iter;
            --m_count;
            return region;
        }

        /**
        * operators for compatibility
        */
        Region& operator *(){
            return *m_iter;
        }
        void operator ++(){
            next();
        }

    };

}

#endif
