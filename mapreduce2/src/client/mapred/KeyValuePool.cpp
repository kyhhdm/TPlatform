/**
 * @file KeyValuePool.cpp
 * @description 
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "KeyValuePool.hpp"
#include "FileStream.hpp"
#include "RecordReader.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace mapreduce;


PoolKeyValueIterator::PoolKeyValueIterator(KeyValuePool& pool):m_pool(pool)
{
    m_startId = pool.startId();
    m_endId = pool.curId();
    m_curId = m_startId;
}

bool PoolKeyValueIterator::hasMore()
{
    return (m_endId > m_curId);
}

void* PoolKeyValueIterator::next()
{
    void* data = m_pool.get(m_curId);
    m_curId++;
    return data;
}

KeyValuePool::KeyValuePool(RecordReader* reader ,bool createKeyPool, int blockSize)
{
    m_reader = reader;
    m_blockSize = blockSize;
    m_createKeyPool = createKeyPool;

    PointerInfo data;

    if(createKeyPool){
        data.pointer = reader->createKeys(m_blockSize);
        data.isKeys = true;
        m_dataSize = reader->getKeySize();
    }
    else{
        data.pointer = reader->createValues(m_blockSize);
        data.isKeys = false;
        m_dataSize = reader->getValueSize();
    }

    m_pool.push_back(data);

    m_curId = m_startId = 0;
}

KeyValuePool::~KeyValuePool()
{
    for (int i = 0 ; i < (int)m_pool.size(); i++){
        //delete[] m_pool[i];
        if(m_pool[i].isKeys)
            m_reader->releaseKeys(m_pool[i].pointer);
        else
            m_reader->releaseValues(m_pool[i].pointer);
    }
}

void KeyValuePool::next(void *& data)
{
    PointerInfo info;
    if(m_curId >= (int)m_pool.size() * m_blockSize){
        //add new block
        if(m_createKeyPool){
            data = m_reader->createKeys(m_blockSize);
            info.isKeys = true;
        }
        else{
            data = m_reader->createValues(m_blockSize);
            info.isKeys = false;
        }
  
        info.pointer = data;
        m_pool.push_back(info);
    }
    else{
        data =  get(m_curId);
    }

    m_curId ++;
}

void KeyValuePool::clear()
{
    m_curId = m_curId % m_blockSize;
    m_startId = m_curId;

    if(m_pool.size() <= 1) return;
    for (int i = 0 ; i< (int)m_pool.size() - 1; i++){
        //delete[] m_pool[i];
        if(m_pool[i].isKeys)
            m_reader->releaseKeys(m_pool[i].pointer);
        else
            m_reader->releaseValues(m_pool[i].pointer);
    }
    m_pool.erase(m_pool.begin(), m_pool.end() - 1);

}

void* KeyValuePool::get(int id)
{
    int poolId = id / m_blockSize;
    if(poolId >= (int)m_pool.size()) return NULL;

    return (char*)m_pool[poolId].pointer + m_dataSize * (id % m_blockSize);
}


PoolKeyValueIterator KeyValuePool::iter()
{
    return PoolKeyValueIterator(*this);
}



