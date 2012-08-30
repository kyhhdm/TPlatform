/**
 * @file ClientInfo.cpp
 * Implementaion of ClientInfo.
 * 
 * @author Zhifeng YANG
 * @date 23  5月 2007
 */

#include "ClientInfo.hpp"
#include <ctime>

::tfs::ClientInfo::ClientInfo()
{
    m_lastUpdate = time((time_t*)NULL);
}
