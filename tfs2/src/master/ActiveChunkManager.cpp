/**
 * @file ActiveChunkManager.cpp
 * Implementation of ActiveChunkManager.
 * 
 * @author Zhifeng YANG
 * @date 2007-06-18
 */

#include "master/ActiveChunkManager.hpp"
#include "master/AddressHelper.hpp"
#include <algorithm>
using namespace tfs;

void ActiveChunkManager::add(const Chunk &chk, const Address &location)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);

    if (m_chunk2location.find(chk) == m_chunk2location.end()){
        AddressSet locations;
        m_chunk2location[chk] = locations;
    } 
    m_chunk2location[chk].insert(location);
}

void ActiveChunkManager::add(const Address& location, const Chunks &chks)
{
    Chunks::const_iterator it;
    for (it = chks.begin(); it != chks.end(); ++it){
        this->add(*it, location);
    }
}

void ActiveChunkManager::add(const LocatedChunk& lchk)
{
    for (int i = 0; i < lchk.locations.size(); i++){
        this->add(lchk.chk, lchk.locations[i]);
    }
}

void ActiveChunkManager::remove(const Chunk &chk, const Address& address) throw(NoSuchChunk)
{
   IceUtil::Mutex::Lock lock(m_mutex);
   if (m_chunk2location.find(chk) == m_chunk2location.end()){
       throw NoSuchChunk("From ActiveChunkManager::remove()");
   }
   m_chunk2location[chk].erase(address);
   if (m_chunk2location[chk].empty()){
       m_chunk2location.erase(chk);
   }
}

void ActiveChunkManager::remove(const LocatedChunk& lchk) throw(NoSuchChunk)
{
    for (int i = 0; i < lchk.locations.size(); i++){
        this->remove(lchk.chk, lchk.locations[i]);
    }
}

void ActiveChunkManager::remove(const LocatedChunks& lchks) throw(NoSuchChunk)
{
    for (int i = 0; i < lchks.size(); i++){
        this->remove(lchks[i]);
    }
}


LocatedChunk ActiveChunkManager::getLocatedChunk(const Chunk& chk) throw(NoSuchChunk)
{
    if (m_chunk2location.find(chk) == m_chunk2location.end()){
        throw NoSuchChunk("From ActiveChunkManager::getLocatedChunk");
    }

    LocatedChunk lchk;
    lchk.chk = chk;
    lchk.locations.insert(lchk.locations.end(), m_chunk2location[chk].begin(), m_chunk2location[chk].end());

    LOG4CPLUS_DEBUG(m_logger, lchk.chk << " is available at " << lchk.locations);

    return lchk;
}

LocatedChunks ActiveChunkManager::getLocatedChunks(const Chunks& chks) throw(NoSuchChunk)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    LocatedChunks lchks;
    for (int i = 0; i < chks.size(); i++){
        lchks.push_back(this->getLocatedChunk(chks[i]));
    }
    return lchks;
}
