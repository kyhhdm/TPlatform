
#ifdef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#include "TaskMgr.hpp"
#include "ClientDaemon.hpp"
#include "ChunkServerConf.hpp"
#include "datatransfer/TCPUtil.hpp"
#include "util/Logger.hpp"
#include "XDealer.hpp"
#include "String.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;
using namespace tfs;

extern Logger pLogger;


ClientDaemon::ClientDaemon(ChunkManager * chunk_manager)
{
    assert(chunk_manager!=NULL);
    pChunkManager=chunk_manager;
}

ClientDaemon::~ClientDaemon()
{    
}

int ClientDaemon::init()
{
    ChunkServerConf * pConf=ChunkServerConf::getInstance();
    assert(pConf!=NULL);
    int port=pConf->DATA_SOCKET_PORT;
    if(mServer.OpenService(port)<0){
        cout<<"ClientDaemon init() error, at port:"<<port<<endl;
        return -1;
    }
    return 1;
}

void ClientDaemon::operator()()
{
    if(init()==-1)
        return;

    while(1)
    {
        ClientInfo client_info;
        int sockfd=mServer.Accept(client_info);
        if(sockfd<=0){
            LOG4CPLUS_ERROR(pLogger,"ClientDaemon::() scoket accept error: "<<sockfd);
            continue;
        }
        LOG4CPLUS_DEBUG(pLogger,"ClientDaemon::() client connect:"<<client_info.ip<<":"<<client_info.port);
        //        cout<<"client connect:"<<client_info.ip<<":"<<client_info.port<<endl;        
        //        XDealer *p_dealer = new XDealer(sockfd,pChunkManager);
        XDealer dealer(sockfd,pChunkManager);        
        dealer.setName(string(ts("%s:%d",client_info.ip.c_str(),client_info.port)));
        dealer.setStartTime();
        boost::thread client_thread(dealer);

        //        TaskMgr * p_task_mgr = TaskMgr::getInstance();
        //        p_task_mgr->addDealer(p_dealer);
    }
    
}


#endif

