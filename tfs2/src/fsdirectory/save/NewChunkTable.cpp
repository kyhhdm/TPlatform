/** @file NewChunkTable.cpp
 *
 * @author PengBo
 * @date 24 7 2007
 *
 */
#include "fsdirectory/NewChunkTable.hpp"
#include <algorithm>

using namespace tfs;
using namespace std;

NewChunkTable::NewChunkTable()
{
	
}
            
NewChunkTable::~NewChunkTable()
{

}

bool NewChunkTable::addItem(const Long chunkId, const string holder, const INode* inode)
{
    NewChunk chunk;
    chunk.id = chunkId;
    chunk.holder = holder;
    chunk.inode = inode;
    
    typedef map<Long , NewChunk>::value_type valType_long_chunk;
    if( m_table.find(chunkId) == m_table.end() ){
        m_table.insert(valType_long_chunk(chunkId,chunk) );
        return true;
    }
    return false;
}

bool NewChunkTable::deleteItem(const Long chunkId)
{
    if( m_table.find(chunkId) != m_table.end() ){
        m_table.erase(chunkId);
        return true;
    }
    return false;
}

int NewChunkTable::deleteItem(const INode* pInode, vector<Long> deletedIds)   
{
    int count = 0;
        
    for(map<Long , NewChunk>::iterator iter = m_table.begin(); iter != m_table.end();){
        if(iter->second.inode == pInode){

            deletedIds.push_back(iter->first);

            //erase will destory iterator, be careful, 
            m_table.erase(iter++);

            count ++;
        }
        else{
            ++iter;
        }
    }

    return count;
}

int NewChunkTable::deleteItem(const string holder, vector<Long> deletedIds)
{
    int count = 0;
        
    for(map<Long , NewChunk>::iterator iter = m_table.begin(); iter != m_table.end();){
        if(iter->second.holder.compare(holder) == 0){
            deletedIds.push_back(iter->first);

            //erase will destory iterator, be careful, 
            m_table.erase(iter++);

            count ++;
        }
        else{
            ++iter;
        }
    }
    return count;
}

const INode* NewChunkTable::findItem(const Long chunkId)
{
    map<Long , NewChunk>::iterator iter = m_table.find(chunkId);
    if(iter != m_table.end() ){
        return m_table[chunkId].inode;
    }
    else
        return NULL;
}

