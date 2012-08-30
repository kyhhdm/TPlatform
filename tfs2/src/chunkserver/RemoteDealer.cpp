
#ifdef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#include <string>
#include <vector>
#include "datatransfer/SocketMsg.hpp"
#include "datatransfer/TCPUtil.hpp"
#include "util/Logger.hpp"
#include "RemoteDealer.hpp"

using namespace std;
using namespace tfs;

extern Logger pLogger;

RemoteDealer::RemoteDealer(int sockfd, ChunkManager * chunk_manager)
{
    m_sock = sockfd;
    m_should_continue = true;
    m_chunk_manager = chunk_manager;
}

RemoteDealer::~RemoteDealer()
{
    closeConnect();
}

void RemoteDealer::closeConnect()
{
    if (m_sock > 0){
        close(m_sock);
        m_sock = -1;
    }
}

void RemoteDealer::run()
{
    try{
        while(m_should_continue){
            RemoteCMD cmd;
            TCPUtil::RecvDataE(m_sock,(char *)&cmd,sizeof(RemoteCMD),"read command from peer failed");
            if (cmd == LIST_CHUNK_INFO){
                //@todo return chunk id
                map<int64_t,ChunkInfo> map_chunk = m_chunk_manager->getChunks();
                int num = map_chunk.size();

                //                LOG4CPLUS_DEBUG(pLogger, "chunks sum: "<<num);
        
                TCPUtil::SendDataE(m_sock,(char *)&num,sizeof(int),"send chunk num to peer failed");
                if (num > 0){
                    map<int64_t,ChunkInfo>::iterator it = map_chunk.begin();
                    for (;it != map_chunk.end(); ++it){
                        ChunkInfo info = it->second;
                        ChunkStatus msg(info.mID,info.mSize,info.mVersion);
                        TCPUtil::SendDataE(m_sock,(char *)&msg,sizeof(ChunkStatus),"send chunk id to peer failed");
                    }
                }
                break;
            }else if (cmd == LIST_CHUNK_ID){
                break;
            }else if (cmd == REMOTE_DISCONNECT){
                break;
            }
        } //end of while
    }catch(TCPException & e){
        LOG4CPLUS_ERROR(pLogger, e.what());
    }
        closeConnect();
}

#endif
