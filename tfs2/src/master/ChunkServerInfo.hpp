/** 
 * @file ChunkServerInfo.hpp
 * All information about a chunkserver.
 * 
 * @author Zhifeng YANG
 * @date 23  5 2007
 */
#ifndef _CHUNKSERVERINFO_HPP
#define _CHUNKSERVERINFO_HPP 1
#include "common/IceGenerated.hpp"
#include "master/ChunkHelper.hpp"
namespace tfs
{
    class ChunkServerInfo
    {
    public:
        time_t m_lastUpdate;
        Heartbeat m_heartbeat;
        ChunkSet m_chunks;
    };
}


#endif /* _CHUNKSERVERINFO_HPP */
