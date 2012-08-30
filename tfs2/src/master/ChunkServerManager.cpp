/**
 * @file ChunkServerManager.cpp
 * Implemantation of ChunkServerManager.
 * 
 * @author Zhifeng YANG
 * @date 23  5 2007
 */

#include "master/ChunkServerManager.hpp"
#include "master/ChunkHelper.hpp"
#include "master/AddressHelper.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace tfs;

void ChunkServerManager::enroll(const Address& address) throw ()
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_address2info.find(address) == m_address2info.end()){ // new chunk server
        ChunkServerInfo info;
        info.m_lastUpdate = time((time_t*)NULL);
        m_address2info[address] = info;
    }
}

bool ChunkServerManager::isEnrolled(const Address& address) const throw ()
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    return m_address2info.find(address) != m_address2info.end();
}

void ChunkServerManager::renewHeartbeat(const Address& address,const Heartbeat &hb) throw (UnknownChunkServer)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_address2info.find(address) == m_address2info.end()){
        LOG4CPLUS_WARN(m_logger, "throw UnknownChunkServer " << address);
        throw UnknownChunkServer("From ChunkServerManager::renewHeartbeat().");
    }
    
    m_address2info[address].m_heartbeat = hb;
    m_address2info[address].m_lastUpdate = time((time_t*)NULL);
}

void ChunkServerManager::setChunks(const Address& address, const Chunks &chks) throw (UnknownChunkServer)
{
    

    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_address2info.find(address) == m_address2info.end()){
        LOG4CPLUS_WARN(m_logger, "throw UnknownChunkServer " << address);
        throw UnknownChunkServer("From ChunkServerManager::setChunks().");
    }    
    m_address2info[address].m_chunks.clear();
    m_address2info[address].m_chunks.insert(chks.begin(), chks.end());

    LOG4CPLUS_DEBUG(m_logger, chks << " 's location is " << address);
    
}

void ChunkServerManager::add(const Address& address, const Chunk &chk) throw (UnknownChunkServer)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_address2info.find(address) == m_address2info.end()){
        LOG4CPLUS_WARN(m_logger, "throw UnknownChunkServer" << address);
        throw UnknownChunkServer("From ChunkServerManager::addChunks().");
    }
    m_address2info[address].m_chunks.insert(chk);
}

void ChunkServerManager::add(const Address& address, const Chunks &chks) throw (UnknownChunkServer)
{
    for (int i = 0; i < chks.size(); i++){
        this->add(address, chks[i]);
    }
}

void ChunkServerManager::add(const LocatedChunk &lchk) throw (UnknownChunkServer)
{
    for (int i = 0; i < lchk.locations.size(); i++){
        this->add(lchk.locations[i], lchk.chk);
    }
}

void ChunkServerManager::add(const LocatedChunks &lchks) throw (UnknownChunkServer)
{
    for (int i = 0; i < lchks.size(); i++){
        this->add(lchks[i]);
    }
}

void ChunkServerManager::remove(const Address& address, const Chunk &chk) throw (UnknownChunkServer)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_address2info.find(address) == m_address2info.end()){
        LOG4CPLUS_WARN(m_logger, "throw UnknownChunkServer " << address);
        throw UnknownChunkServer("From ChunkServerManager::remove().");
    }
    m_address2info[address].m_chunks.erase(chk);
}

void ChunkServerManager::remove(const Address& address, const Chunks &chks) throw (UnknownChunkServer)
{
    for (int i = 0; i < chks.size(); i++){
        this->remove(address, chks[i]);
    }
}
void ChunkServerManager::remove(const LocatedChunk &lchk) throw (UnknownChunkServer)
{
    for (int i = 0; i < lchk.locations.size(); i++){
        this->remove(lchk.locations[i], lchk.chk);
    }
}

void ChunkServerManager::remove(const LocatedChunks &lchks) throw (UnknownChunkServer)
{
    for (int i = 0; i < lchks.size(); i++){
        this->remove(lchks[i]);
    }
}

void ChunkServerManager::remove(const Address& address) throw (UnknownChunkServer)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    address2info_t::iterator it = m_address2info.find(address);
    if (it == m_address2info.end()){
        LOG4CPLUS_WARN(m_logger, "throw UnknownChunkServer " << address);
        throw UnknownChunkServer("From ChunkServerManager::removeChunkServer().");
    }
    m_address2info.erase(it);
}
// remove only one expired chunkserver once
void ChunkServerManager::removeExpired(LocatedChunks &lchks)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);

    lchks.clear();    
    time_t now = time((time_t*)NULL);
    address2info_t::iterator it;
   
    for (it = m_address2info.begin(); it != m_address2info.end(); ++it){
        time_t lastUpdate = it->second.m_lastUpdate;
        if (now - lastUpdate > m_expireTime){

            ChunkSet::iterator it4;
            for (it4 = it->second.m_chunks.begin(); it4 != it->second.m_chunks.end(); ++it4){
                LocatedChunk lchk;
                lchk.chk = *it4;
                lchk.locations.push_back(it->first);
            }
            LOG4CPLUS_INFO(m_logger, "removed expired chunkserver:" << it->first);
            m_address2info.erase(it);
            break;
        }
    }
}

Addresses ChunkServerManager::getChunkServers()
{
    Addresses addresses;
    address2info_t::iterator it;
    for (it = m_address2info.begin(); it != m_address2info.end(); ++it){
        addresses.push_back(it->first);
    }
    return addresses;
}

ChunksPtr ChunkServerManager::get(const Address& address)
{
    ChunksPtr pChunks(new Chunks);
    
    if (m_address2info.find(address) != m_address2info.end()){
        pChunks->insert(pChunks->end(), m_address2info[address].m_chunks.begin(), m_address2info[address].m_chunks.end());
    }
    return pChunks;
}

Addresses ChunkServerManager::chooseChunkServersRandomly(int32_t num) const
{
    Addresses allAddresses;
    std::vector<int> flags;
    address2info_t::const_iterator it;
    for (it = m_address2info.begin(); it != m_address2info.end(); ++it){
        allAddresses.push_back(it->first);
        flags.push_back(0);
    }
    double total = allAddresses.size();
    // there are less chunkservers available than expected
    if (total <= num){
        return allAddresses;
    }

    Addresses addresses;   
    int k;
    for (int i = 0; i < num; i++){
        do{
            k = (int)(total*rand()/(RAND_MAX+1.0));
        }while(flags[k]);
        flags[k] = 1;
        addresses.push_back(allAddresses[k]);
    }
    return addresses;
}

#define MIN_FREE_SPACE 100*1024*1024
/// @todo the current selection method is too naive
Addresses ChunkServerManager::chooseBestChunkServers(int32_t number) const
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    return chooseChunkServersRandomly(number);
}

/// @todo not finished
Addresses ChunkServerManager::chooseWorstChunkServers(int32_t number) const
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    return chooseChunkServersRandomly(number);
}

/// @todo not finished
Addresses ChunkServerManager::chooseWorstChunkServers(const Addresses &chunkServers, int32_t number) const
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    Addresses addresses;
    for (int i = 0; i < chunkServers.size(); i++){
        addresses.push_back(chunkServers[i]);
        if (addresses.size() == number){
            break;
        }
    }
    return addresses;
}
