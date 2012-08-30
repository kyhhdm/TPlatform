
/**
 * @file   XDealer.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Wed Jul 11 13:54:24 2007
 * 
 * @brief  a thread deal with client
 * 
 * 
 */
#ifndef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#ifndef _X_DEALER_HPP_
#define _X_DEALER_HPP_

#include "ChunkManager.hpp"
#include "Dealer.hpp"
#include "datatransfer/SocketMsg.hpp"

namespace tfs
{
    class XDealer:public Dealer
    {
    public:
        XDealer(int sockfd,ChunkManager * chunk_manager);
        void operator()();
        ~XDealer();
    private:

        /** 
         * 析构函数为private, 意味着不能显示删除这个线程,只能自身消亡
         * 
         * 
         * @return 
         */
        //        ~XDealer();
        
        int dealRead(const Client2ServerMsg & request_msg);
        int dealAppend(const Client2ServerMsg & request_msg);
        int dealWrite(const Client2ServerMsg & request_msg);

        int dealGetLocalPath(const Client2ServerMsg & request_msg);
        
        //        int dealPushData(const Client2ServerMsg & request_msg);
        
    private:
        int mSockfd;
        int mShouldContinue;
        ChunkManager *pChunkManager;
    };
}

#endif

#endif
