/** @file ChunkTable.cpp
 * ChunkTable stores all the chunk ids that running in system,
 * and provide fast lookup from id to it's owner, inode.
 *
 * @author PengBo, ChenRiShan
 * @date 24 7 2007
 *
 */

#include "fsdirectory/ChunkTable.hpp"

tfs::ChunkTable::ChunkTable()
{

}
            
tfs::ChunkTable::~ChunkTable()
{
}

bool tfs::ChunkTable::addItem(const Long chunkId, const tfs::INode* inode)
{
    const tfs::INode* node = inode;
    typedef std::map<Long,const INode*>::value_type valType;
    std::map<Long,const INode*>::iterator iter;
    std::pair<std::map<Long,const INode*>::iterator, bool> retPair = m_table.insert(valType(chunkId,node) );
    return retPair.second;

    //std::map<Long,const INode*>::iterator iter = m_table.find(chunkId);
    //if(iter != m_table.end() )
    //    return true;
    //else
    //    return false;
}

bool tfs::ChunkTable::deleteItem(const Long chunkId)
{
    m_table.erase(chunkId);
    return true;

    //std::map<Long,const INode*>::iterator iter = m_table.find(chunkId);
    //if(iter == m_table.end() )
    //    return true;
    //else
    //    return false;
}

const tfs::INode* tfs::ChunkTable::findItem(const Long chunkId)
{
    std::map<Long,const INode*>::iterator iter = m_table.find(chunkId);
    if(iter != m_table.end() ){
        return m_table[chunkId];
    }
    else
        return NULL;
}


