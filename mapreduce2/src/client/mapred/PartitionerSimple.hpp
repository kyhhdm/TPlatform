/**
 * @file PartitionerSimple.hpp
 * @description 
 *  PartitionerSimple is a special kind of Collector, which collect from mapper output 
 *  and create intermediate files
 *
 * @author Peng Bo
 * @date 2008-1-11
 *
 * */
#ifndef TPLATFORM_MAPREDUCE_PartitionerSimple
#define TPLATFORM_MAPREDUCE_PartitionerSimple

#include <mapred/Collector.hpp>
//#include "util/Logger.hpp"
#include <string>
#include <vector>

namespace mapreduce{
    class HashableComparable;
    class RecordWriter;
 
    /**
     * PartitionerSimple:
     * Split key value pairs of mapper output, and write into multiple archivers
     *
     * */
    class PartitionerSimple : public Collector{
        public:
            /**
             * Constructor
             * 
             */
            PartitionerSimple(HashableComparable* hasher, std::vector<RecordWriter*>& writers);

            ~PartitionerSimple();

            /**
            * Collect a <Key, Value> pair
            * 
            * @param key  :
            * @param value :
            * @return : success/error code
            * @throws 
            *
            */
            int collect(const void* key, const void* value);

        private:
            int m_nPartition;
            HashableComparable* m_hasher;
            std::vector<RecordWriter*> m_writers;
            
            //Logger m_logger;
    };

    

}

#endif
