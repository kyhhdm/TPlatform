/**
 * @file AdminServiceImpl.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-08-29
 */

#include "AdminServiceImpl.hpp"
#include <ctime>
using namespace tfs;
using namespace tfs::slice;
using namespace std;

string AdminServiceImpl::getStartTime(const ::Ice::Current&)
{
    return string(ctime(&m_db->m_statistics.m_startTime));    
}

Addresses AdminServiceImpl::getChunkServers(const ::Ice::Current&)
{
    return m_db->m_chunkServers.getChunkServers();
}

Addresses AdminServiceImpl::getClients(const ::Ice::Current&)
{
    return m_db->m_activeClients.getClients();
}

OperationsCount AdminServiceImpl::getOperationsCount(const ::Ice::Current&)
{
    OperationsCount counts;
    for (int i = 0; i < OP_SIZE; i++){
        counts.push_back(m_db->m_statistics.m_operationsCount[i]);
    }
    return counts;
}

