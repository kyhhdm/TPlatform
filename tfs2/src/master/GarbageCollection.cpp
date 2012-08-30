/**
 * @file GarbageCollection.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-08-06
 */

#include "GarbageCollection.hpp"
using namespace tfs;

void GarbageCollection::add(const Address& address, const Chunk &chk)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_garbageChunks.find(address) == m_garbageChunks.end()){
        Chunks chks;
        m_garbageChunks[address] = chks;
    }
    m_garbageChunks[address].push_back(chk);
}

void GarbageCollection::add(const LocatedChunk& lchk)
{
    for ( int i = 0; i < lchk.locations.size(); i++){
        this->add(lchk.locations[i], lchk.chk);
    }
    
}

void GarbageCollection::add(const LocatedChunks& lchks)
{
    for (int i = 0; i < lchks.size(); i++){
        this->add(lchks[i]);
    }
}

ChunksPtr GarbageCollection::get(const Address& chunkServer)
{
    ChunksPtr pChunks(new Chunks);
    
    if (m_garbageChunks.find(chunkServer) != m_garbageChunks.end()){
        *pChunks = m_garbageChunks[chunkServer];
    }
    return pChunks;
}

// void GarbageCollection::remove(const Chunk& chk)
// {
//     address2chunks_t::iterator it;
//     for ( it = m_garbageChunks.begin(); it != m_garbageChunks.end(); ++it){
//         Chunks::iterator itChunk;
//         for (itChunk = it->second.begin(); itChunk != it->second.end(); ++itChunk){
//             if (*itChunk == chk){
//                 it->second.remove(itChunk);
                
//             }
//         }
//     }
// }

void GarbageCollection::remove(const Address& chunkServer)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    m_garbageChunks.erase(chunkServer);
}
