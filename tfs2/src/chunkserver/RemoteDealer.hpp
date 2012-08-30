/**
 * @file   RemoteDealer.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Fri Dec  7 16:36:37 2007
 * 
 * @brief  
 * 
 * 
 */

#ifdef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#ifndef _REMOTE_DEALER_HPP
#define _REMOTE_DEALER_HPP

#include "ChunkManager.hpp"
#include "Dealer.hpp"
#include "datatransfer/SocketMsg.hpp"
#include "datatransfer/TCPUtil.hpp"

namespace tfs
{
   
    class RemoteDealer : public Dealer
    {
    public:
        RemoteDealer(int sockfd, ChunkManager * chunk_manager);
        ~RemoteDealer();
        void closeConnect();
        void run();
    private:
        int m_sock;
        bool m_should_continue;
        ChunkManager * m_chunk_manager;
    };
}

#endif

#endif
