/**
* @file KeyValuePool.hpp
* @description:
*   KeyValuePool is in charge of <key,value> data management.
*   It's pool's charge to create Keys and Values on demand,
*   free them when necessary. For better performance, allocate
*   key value data in block is much better than allocate one 
*   at a time. So comes the name: pool.
*
* @date 2008-04-07
* */


#ifndef TPLATFORM_MAPREDUCE_KEYVALUEPOOL
#define TPLATFORM_MAPREDUCE_KEYVALUEPOOL

#include <mapred/KeyValueIterator.hpp>
#include <vector>

namespace mapreduce{
    class RecordReader;
    class PoolKeyValueIterator;

    struct PointerInfo{
        void* pointer;
        bool isKeys;//keys or values
    };

    class KeyValuePool{
        std::vector<PointerInfo> m_pool;
        int m_curId, m_startId;
        int m_blockSize;
        RecordReader* m_reader;
        int m_dataSize;
        bool m_createKeyPool;

    public:
        friend class PoolKeyValueIterator;
        /**
        * Constructor
        *
        * @param reader : RecordReader in charge of create keys and values
        * @param blockSize : pool block size
        *
        */
        KeyValuePool(RecordReader* reader ,bool createKeyPool, int blockSize = 512);
        ~KeyValuePool();

        /**
        * Get a new key/value data item
        *
        * @param data [out]:
        *
        * #TODO
        * return Iterator should be better
        *
        */
        void next(void *& data);

        /**
        * Release processed records
        *
        */
        void clear();

        /**
        * Get a record
        *
        */
        void* get(int id);

        /**
        * Release processed records
        *
        */
        PoolKeyValueIterator iter();

        /**
        * Accessors
        *
        */
        int curId(){return m_curId;}
        int startId(){return m_startId;}
        int itemSize(){return m_dataSize;}

    };

    class PoolKeyValueIterator : public KeyValueIterator{
        int m_startId, m_endId, m_curId;
        KeyValuePool& m_pool;
    public:
        PoolKeyValueIterator(KeyValuePool& pool);

        /**
        * Test if there are more items left
        */
        virtual bool hasMore();

        /**
        * Get next record
        *
        * @return : void*
        *
        */
        virtual void* next();

        virtual ~PoolKeyValueIterator() {};
    };

}

#endif
