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

#include <mapred/Collector.hpp>
#include <mapred/HashableComparable.hpp>
#include <mapred/TKeyValueWriter.hpp>
#include "util/Logger.hpp"
#include <string>
#include <vector>

namespace mapreduce{
    class HashableComparable;
    class Archive;
    class FileStream;
 
    /**
     * Partitioner:
     * Split key value pairs of mapper output, and write into multiple archivers
     *
     * */
    template<typename KeyType, typename ValueType> 
    class TPartitioner : public Collector{
        public:
            typedef TKeyValueWriter<KeyType,ValueType> Writer;

            /**
             * Constructor
             * 
             */
            TPartitioner(HashableComparable* hasher, vector<std::string>& outputFiles);

            ~TPartitioner();

            /**
            * Collect a <Key, Value> pair
            * 
            * @param key  :
            * @param value :
            * @return : success/error code
            * @throws 
            *
            */
            virtual int collect(const void* key, const void* value) const = 0;

        private:
            int m_nPartition;
            HashableComparable* m_hasher;
            std::vector<FileStream*> m_streams;
            std::vector<Writer*> m_writers;
            
            Logger m_logger;
    };

    template<typename KeyType, typename ValueType> 
    TPartitioner::TPartitioner(HashableComparable* hasher, vector<std::string>& outputFiles)
    {
        int m_nPartition = outputFiles.size();
        FileStream* stream;
        Writer* writer;

        m_hasher = hasher;

        for (int i = 0; i < m_nPartition; i++){
            string filename = outputFiles[i];

            //open stream with OpenOnDemand flag
            stream = new FileStreamLocal(filename, FileStream::Append, true);

            //open archive with 64KB buffer
            writer = new Writer(stream, 64*1024);

            m_streams.push_back(stream);
            m_writers.push_back(writer);
        }
    }

    template<typename KeyType, typename ValueType> 
    TPartitioner::~TPartitioner()
    {
        int i;
        for (i = 0; i < m_streams.size(); i++){
            delete m_stream[i];
        }
        for (i = 0; i < m_writers.size(); i++){
            delete m_writers[i];
        }
    }



    template<typename KeyType, typename ValueType> 
    int TPartitioner::collect(const void* key, const void* value)
    {
        int id = m_hasher->hash(key, m_nPartition);
        
        return m_writers[id]->append((KeyType *)key, (ValueType *)value);

    }

}

#endif
