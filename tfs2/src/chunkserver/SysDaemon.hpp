/**
 * @file   SysDaemon.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Jul 29 14:08:30 2007
 * 
 * @brief  the system daemon thread, that maintain the system
 * 
 * 
 */

#ifndef _SYS_DAEMON_HPP
#define _SYS_DAEMON_HPP
#include "Daemon.hpp"
#include "ChunkManager.hpp"

namespace tfs
{
    class SysDaemon : public Daemon
    {
    public:
        SysDaemon(ChunkManager * chunk_manager):m_chunk_manager(chunk_manager){};
        ~SysDaemon(){};

        void operator()();

    private:        
        void logSystemStatus();

        void doSysTask();

        ChunkManager * m_chunk_manager;
        
        
    };

}
#endif
