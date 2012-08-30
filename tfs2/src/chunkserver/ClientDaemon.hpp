/**
 * @file   ClientDaemon.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Fri Jul 13 19:12:36 2007
 * 
 * @brief  use to open a socket, wait for client
 * 
 * 
 */

#ifdef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#ifndef _CLIENT_DAEMON_HPP_
#define _CLIENT_DAEMON_HPP_

#include "Daemon.hpp"
#include "datatransfer/TCPUtil.hpp"
#include "ChunkManager.hpp"

namespace tfs
{
    class ClientDaemon : public Daemon
    {
    public:
        ClientDaemon(ChunkManager * chunk_manager);
        ~ClientDaemon();
        void operator()();

        int init();
    private:
        TCPUtil mServer;
        ChunkManager * pChunkManager;
//         int mShouldContinue;    
        //    private:
    };
}

#endif

#endif
