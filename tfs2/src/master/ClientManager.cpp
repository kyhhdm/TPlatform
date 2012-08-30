/* 
 * @(#)ClientManager.cpp
 * AUTHOR: YangZhifeng
 * CREATED DATE: 23  5月 2007
 * DESCRIPTION: 
 */

#include "ClientManager.hpp"
#include <ctime>
using namespace tfs;

void ClientManager::renewHeartbeat(const Address& clientAddress)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    if (m_clients.find(clientAddress) == m_clients.end()){
        LOG4CPLUS_INFO(m_logger, "enrolled client: " << clientAddress);
    }
    
    m_clients[clientAddress] = time((time_t*)NULL);
}
void ClientManager::remove(const Address& clientAddress)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    m_clients.erase(clientAddress);
}

void ClientManager::removeExpired(Addresses &expiredClients)
{
    IceUtil::Mutex::Lock dirLock(m_mutex);
    expiredClients.clear();
    
    time_t now = time((time_t*)NULL);
    map_type::iterator it = m_clients.begin();
    while(it != m_clients.end()){
        if (now - it->second > m_expireTime){
            expiredClients.push_back(it->first);
            m_clients.erase(it);
            it = m_clients.begin(); // rewind the iterator!!
        }
        else{
            ++it;
        }
    }    
}

int32_t ClientManager::getClientNum()
{
    return m_clients.size();
}

Addresses ClientManager::getClients()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    Addresses addresses;
    map_type::iterator it = m_clients.begin();
    for(; it != m_clients.end(); ++it){
        addresses.push_back(it->first);
    }
    return addresses;
}

bool ClientManager::exists(const Address& clientAddress)
{
    return ( m_clients.find(clientAddress) != m_clients.end() );
}
