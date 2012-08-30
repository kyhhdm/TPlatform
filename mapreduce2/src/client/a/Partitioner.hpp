/**
 * @file Partitioner.hpp
 * @description 
 *  Partitioner is a special kind of Collector, which collect from mapper output 
 *  and create intermediate files
 *
 * @author Peng Bo
 * @date 2008-1-11
 *
 * */
#ifndef TPLATFORM_MAPREDUCE_PARTITIONER
#define TPLATFORM_MAPREDUCE_PARTITIONER

#include "Collector.hpp"
#include "TaskConfigure.hpp"
//#include "util/Logger.hpp"
#include <string>
#include <vector>

namespace mapreduce{
    class HashableComparable;
    class RecordWriter;
    class FileStream;
    class ClassLoader;
 
    /**
     * Partitioner:
     * Split key value pairs of mapper output, and write into multiple archivers
     *
     * */
    class Partitioner : public Collector{
        public:
            /**
             * Constructor
             * 
             */
            Partitioner(TaskConfigure& taskConfigure, const std::vector<std::string>& outputFiles, bool useLFS = true);

            ~Partitioner();

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
            ClassLoader* m_loader;
            HashableComparable* m_hasher;
            std::vector<FileStream*> m_streams;
            std::vector<RecordWriter*> m_writers;
            
            //Logger m_logger;
    };

    

}

#endif
