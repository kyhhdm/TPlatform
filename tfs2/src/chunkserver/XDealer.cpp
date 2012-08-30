/**
 * @file   XDealer.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Jul 22 22:31:17 2007
 * 
 * @brief  implement of XDealer.hpp
 * 
 * 
 */

#ifdef USE_DATATRANSFER_HPP
#define USE_DATATRANSFER_HPP

#include "XDealer.hpp"
#include "datatransfer/SocketMsg.hpp"
#include "datatransfer/TCPUtil.hpp"
#include "datatransfer/ChunkTransfer.hpp"
#include "util/Logger.hpp"
#include "RemoteDealer.hpp"
#include "TaskMgr.hpp"
#include <unistd.h>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace tfs;

extern Logger pLogger;

XDealer::XDealer(int sockfd,ChunkManager * chunk_manager)
{
    assert(sockfd>0 && chunk_manager!=NULL);
    mSockfd=sockfd;
    pChunkManager=chunk_manager;  
    mShouldContinue=1;
}

XDealer::~XDealer()
{
    LOG4CPLUS_DEBUG(pLogger, "{"<<getName()<<"} ~XDealer() thread finish");        
}

void XDealer::operator()()
{
    while(mShouldContinue)
    {
        Client2ServerMsg request_msg;
        int ret=TCPUtil::RecvData(mSockfd,(char *)&request_msg,sizeof(request_msg));
        if (ret == 0){ //recv socket fin            
            break;
        }else if(ret < 0){ //socket error
            LOG4CPLUS_ERROR(pLogger, "XDealer() {"<<getName()<<"} socket error when resv request msg! errno:"<<errno<<" means:"<<strerror(errno));            
            break;
        }
        
        if (request_msg.mCMD == READ){
            //@todo read operation
            if (dealRead(request_msg)<0)
                break;
            
        }else if (request_msg.mCMD == APPEND){
            //@todo append operation
            if (dealAppend(request_msg)<0)
                break;            
        }else if (request_msg.mCMD == WRITE){
            //@todo write operation
        }else if (request_msg.mCMD == DISCONNECT){
            //@todo process error
            LOG4CPLUS_DEBUG(pLogger, "XDealer() {"<<getName()<<"} recv Client Disconnect");
            break;
        }else if (request_msg.mCMD == REMOTE_OP){
            
            LOG4CPLUS_DEBUG(pLogger, "XDealer() {"<<getName()<<"} remote operation connect.");
            RemoteDealer remote_dealer(mSockfd,pChunkManager);
            remote_dealer.run();
            break;
            //            return;
        }
        // else if(request_msg.mCMD == PUSH_DATA){
        // 	LOG4CPLUS_DEBUG(pLogger, "XDealer() {"<<getName()<<"} recv data");
        // 	if (dealPushData(request_msg) < 0){
        // 		break;
        // 	}
        	
        // }
        else if (request_msg.mCMD == GET_LOCAL_PATH){
            LOG4CPLUS_DEBUG(pLogger, "XDealer() {"<<getName()<<"} get local path.");
            if (dealGetLocalPath(request_msg) < 0)
                break;
        }
        else{
            break;
        }
        
    }
    if (mSockfd){
        LOG4CPLUS_DEBUG(pLogger, "XDealer() {"<<getName()<<"} task finish! running time:"<<getRunningTime()<<" seconds");
        TCPUtil::Close(mSockfd);
        //        close(mSockfd);
        mSockfd=-1;
    }

    TaskMgr * p_task_mgr = TaskMgr::getInstance();
    p_task_mgr->removeDealer(getName());
    //标志自身已消亡
    //    setDead();
    //线程销毁自身
    //    delete this;
}

int XDealer::dealRead(const Client2ServerMsg& request_msg)
{
    
    //    LOG4CPLUS_DEBUG(pLogger, "Enter XDealer::dealRead()");
    TaskMgr * p_task_mgr = TaskMgr::getInstance();
    p_task_mgr->setDealerStatus(getName(),Read_Dealer);
    LOG4CPLUS_INFO(pLogger,"XDealer::dealRead {"<<getName()<<"} read chunk id:"<<request_msg.mChunkID);
    
    ifstream chunk_reader;
    int ret=pChunkManager->getChunkInStream(chunk_reader,request_msg.mChunkID);
    if(ret<0){
        //        cout<<"XDealer::dealRead getChunkInStream error, chunk_id:"<<request_msg.mChunkID<<"ret:"<<ret<<endl;
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealRead {"<<getName()<<"} getChunkInStream error, chunk_id:"<<request_msg.mChunkID<<" ret:"<<ret);
        Server2ClientMsg error_msg(ERROR,NOSUCHCHUNK);
        if(TCPUtil::SendData(mSockfd,(const char *)&error_msg,sizeof(error_msg))<0){
            mShouldContinue=0;
        }
        return ret;
    }

    Server2ClientMsg return_msg(OK,OTHER);
    if(TCPUtil::SendData(mSockfd,(const char *)&return_msg,sizeof(return_msg))<0){
        //        cout<<"dealread, send back msg errot"<<endl;
        LOG4CPLUS_ERROR(pLogger,"in XDealer::dealRead():1 {"<<getName()<<"} send back msg error!");        
        return -1;
    }

    
    //@todo check if the dat outof range;check file error in the process of sending file
    
    assert( request_msg.mShiftPos>=0 && request_msg.mDataLen>0 && chunk_reader);
    chunk_reader.seekg(request_msg.mShiftPos);
    char buf[PACKAGE_LEN+1];
	memset(buf, 0, PACKAGE_LEN+1);

    try{        
        //发送数据
        int send_size=0;
        while(send_size<request_msg.mDataLen){
            int read_size=PACKAGE_LEN;
            if((request_msg.mDataLen - send_size)<PACKAGE_LEN){
                read_size=request_msg.mDataLen - send_size;
            }

            assert(read_size>0);
        
            chunk_reader.read(buf,read_size);

            if(!chunk_reader){
                LOG4CPLUS_ERROR(pLogger,"in XDealer::dealRead():2 {"<<getName()<<"} read data from file error");
            
                SockDataType data_type=S2C_MSG;
                TCPUtil::SendData(mSockfd,(const char *)&data_type,sizeof(SockDataType));
                Server2ClientMsg return_msg(ERROR,DISKFAIL);
                TCPUtil::SendData(mSockfd,(const char *)&return_msg,sizeof(return_msg));

                //@todo 读取文件错误,根据错误类型处理
                return -1;
            }

            //@todo 附带发送一个字节的标志位数据,以区分数据和命令
            SockDataType data_type=DATA_MSG;
//             LOG4CPLUS_DEBUG(pLogger,"in XDealer::dealRead() {"<<getName()<<"} size of SockDataType:"
//                             <<sizeof(SockDataType)<<" "<<sizeof(data_type));
            int ret=TCPUtil::SendDataE(mSockfd,(const char * )&data_type,sizeof(data_type),"send SockDataType error:3");

            //发送数据
            ret=TCPUtil::SendDataE(mSockfd,buf,read_size,"send data error:4");


            //        assert(ret==read_size);
            //assert(ret!=0);
        
//             if(ret<=0){
//                 LOG4CPLUS_ERROR(pLogger,"in XDealer::dealRead():3, send back data error, ret:"<<ret<<" sendsize:"<<send_size);        
//                 return -1;
//             }
        
            send_size+=read_size;
        }
        LOG4CPLUS_DEBUG(pLogger,"in XDealer::dealRead() {"<<getName()<<"} read complete. size:"<<send_size);
        return send_size;
    }catch(TCPException & e){
        LOG4CPLUS_ERROR(pLogger,"in XDealer::dealRead() {"<<getName()<<"} "<<e.what());        
        return -1;
    }

}

int XDealer::dealAppend(const Client2ServerMsg& request_msg)
{
    TaskMgr * p_task_mgr = TaskMgr::getInstance();
    p_task_mgr->setDealerStatus(getName(),Append_Dealer);
    
    //    LOG4CPLUS_DEBUG(pLogger, "Enter XDealer::dealAppend() chunk id:"<<request_msg.mChunkID);
    LOG4CPLUS_INFO(pLogger,"XDealer::dealAppend {"<<getName()<<"} append chunk id:"<<request_msg.mChunkID);
    
    ofstream outfile;

    //得到一个新的Chunk块
    int ret = pChunkManager->getNewChunkOutStream(outfile,request_msg.mChunkID);
    
    if(ret < 0){ //错误, 告知client
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend() {"<<getName()<<"} getChunkInStream error, chunk_id:"<<request_msg.mChunkID<<"ret:"<<ret);
        Server2ClientMsg error_msg(ERROR,DISKFAIL);
        if(TCPUtil::SendData(mSockfd,(const char *)&error_msg,sizeof(error_msg)) < 0){
            mShouldContinue=0;
        }
        return ret;
    }

    //返回OK消息
    Server2ClientMsg return_msg(OK,OTHER);
    if(TCPUtil::SendData(mSockfd,(const char *)&return_msg,sizeof(return_msg))<0){
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():1 {"<<getName()<<"}  send back msg error");
        return -1;
    }

    //pipeline chunkserver的个数
    int pipe_line_num=request_msg.mPipeLineNum;
    vector<ChunkServerAddr> vec_servers;
    bool should_pipeline=false;

    int i=0;
    while(i<pipe_line_num){
        //接受pipeline的chunkserver地址
        ChunkServerAddr server_addr;
        int ret=TCPUtil::RecvData(mSockfd,(char *)&server_addr,sizeof(server_addr));
        if(ret<=0){
            LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():2 {"<<getName()<<"}  recv pipeline server addr error! ret: "<<ret);
            //            cout<<"XDealer::dealAppend() socket close, ret:"<<ret<<endl;
            return -1;
        }
        vec_servers.push_back(server_addr);
        should_pipeline=true;
        ++i;

        LOG4CPLUS_DEBUG(pLogger,"XDealer::dealAppend() {"<<getName()<<"}  pipeline No."<<i<<"-->"<<server_addr.getIP()<<":"<<server_addr.getPort());
    }

    //初始化pipeline
    ChunkTransfer chunk_transfer;
    if(should_pipeline){
        if(chunk_transfer.initConnect(vec_servers)<0){
            LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():3 {"<<getName()<<"}  init pipeline error");
            should_pipeline=false;
        }else{
            if(chunk_transfer.addChunk(request_msg.mChunkID) < 0){
                LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():4 {"<<getName()<<"}  pipeline add chunk error");
                should_pipeline=false;
            }
        }
    }

    //开始接收数据
    char buf[PACKAGE_LEN+1];
    memset(buf,0,PACKAGE_LEN+1);
//     int sum_size=request_msg.mDataLen;
//     int recv_size=0;
//     int should_read_size=0;

    int sum_size = 0;

    try{
        int this_time_data_len = -1;
        TCPUtil::RecvDataE(mSockfd,(char *)&this_time_data_len,sizeof(int)," recv this_time_data_len error");
        while (this_time_data_len > 0){
            int recv_size = 0;
            int should_read_size = 0;
            while (recv_size < this_time_data_len){                
                if(this_time_data_len - recv_size >= PACKAGE_LEN)
                    should_read_size = PACKAGE_LEN;
                else
                    should_read_size = this_time_data_len - recv_size;
                
                memset(buf,0,PACKAGE_LEN+1);
                TCPUtil::RecvDataE(mSockfd,buf,should_read_size," recv data error");
                outfile.write(buf,should_read_size); //写入chunk @todo 写入错误是否处理
                recv_size += should_read_size;

                if(should_pipeline){
                    if(chunk_transfer.appendData(buf,should_read_size)<0){
                        should_pipeline=false;
                        LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():6 {"<<getName()<<"}  pipeline append data error, break pipeline");
                        //                cout<<"dealAppend() pipeline break;"<<endl;
                    }
                }

            } //end of while recv_size < this_time_data_len

            sum_size += this_time_data_len;
            TCPUtil::RecvDataE(mSockfd,(char *)&this_time_data_len,sizeof(int)," recv this_time_data_len error");
        } //end of while this_time_data_len > 0

        if (should_pipeline){
            if (chunk_transfer.finishAppend() < 0){
                should_pipeline = false;
                LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():6 {"<<getName()<<"}  pipeline finish error, break pipeline");
            }
        }
        
    }catch(TCPException &e){
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend() {"<<getName()<<"} "<<e.what()<<" when append data len:"<<sum_size);
        return -1;
    }

    //数据接受完成
    outfile.flush();

//     while(recv_size<sum_size){

//         if(sum_size - recv_size >= PACKAGE_LEN)
//             should_read_size = PACKAGE_LEN;
//         else
//             should_read_size = sum_size - recv_size;
//         int ret=TCPUtil::RecvData(mSockfd,buf,should_read_size);
        
//         if(ret<0){
//             //@todo 接受数据中出错,
//             LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():5, recvdata error");
//             //            cout<<"dealAppend() error"<<endl;
//             return -1;
//         }
//         outfile.write(buf,ret); //写入chunk @todo 写入错误是否处理
//         recv_size+=ret;
        
//         //流水给下一个
//         if(should_pipeline){
//             if(chunk_transfer.appendData(buf,ret)<0){
//                 should_pipeline=false;
//                 LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():6, pipeline append data error, break pipeline");
//                 //                cout<<"dealAppend() pipeline break;"<<endl;
//             }
//         }

//         //@todo 计算md5
        
//         memset(buf,0,PACKAGE_LEN+1);
//     }


    //@todo 等待md5值并比较
    //@todo pipeline传递md5值
    //@todo 等待md5比较结果反馈

    //@todo commit此Chunk块    
    if(pChunkManager->commitChunk(request_msg.mChunkID)<0){
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealAppend():7 {"<<getName()<<"} commit chunk error");
        //        cout<<"commit chunk error"<<endl;
    }
    LOG4CPLUS_DEBUG(pLogger,"XDealer::dealAppend() {"<<getName()<<"} finish recv a new chunk, id:"<< request_msg.mChunkID <<" data len:"<<sum_size);    
    return 1;
}


int XDealer::dealGetLocalPath(const Client2ServerMsg & request_msg)
{
    LOG4CPLUS_DEBUG(pLogger,"XDealer::dealGetLocalPath() {"<<getName()<<"} get chunkid path: "<<request_msg.mChunkID);
    try{
        string local_path;
        if (pChunkManager->getChunkFilePath(local_path,request_msg.mChunkID) < 0){
            int len = -1;
            TCPUtil::SendDataE(mSockfd,(const char *)&len,sizeof(int),"send data len error");
            LOG4CPLUS_ERROR(pLogger,"XDealer::dealGetLocalPath() {"<<getName()<<"} chunk don't exsit");
            return 1;
        }
        assert(local_path != "");
        
        if (local_path[0] == '.') {
        	char tmp[1000];
        	local_path.erase(0, 1);
        	local_path.insert(0, getcwd(tmp, sizeof(tmp)));
        }
        
        int len = local_path.size();
        TCPUtil::SendDataE(mSockfd,(const char *)&len,sizeof(int),"send data len error");
        TCPUtil::SendDataE(mSockfd,local_path.c_str(),len,"send path data error");
    }catch(TCPException &e){
        LOG4CPLUS_ERROR(pLogger,"XDealer::dealGetLocalPath() {"<<getName()<<"} "<<e.what());
        return -1;
    }
    return 1;
}

// int XDealer::dealPushData(const Client2ServerMsg& request_msg)
// {
// 	try{
// 		int data_len = -1;
// 		TCPUtil::RecvDataE(mSockfd,&data_len,sizeof(int)," recv data error");
// 		if (data_len < 0){
// 			LOG4CPLUS_ERROR(pLogger,"XDealer::dealPushData() data len have some problem");			    
// 			return -1;
// 		}
		
//         int recv_size = 0;
//         int should_read_size = 0;

//         //        bool should_pipeline=false;
        
//         char buf[PACKAGE_LEN+1];
//         memset(buf,0,PACKAGE_LEN+1);
        
//         while (recv_size < data_len){                
//             if(data_len - recv_size >= PACKAGE_LEN)
//                 should_read_size = PACKAGE_LEN;
//             else
//                 should_read_size = data_len - recv_size;
            
//             memset(buf,0,PACKAGE_LEN+1);
            
//             TCPUtil::RecvDataE(mSockfd,buf,should_read_size," recv data error");
//             recv_size += should_read_size;
            
            
//             if(should_pipeline){
//                 if(chunk_transfer.appendData(buf,should_read_size)<0){
//                     should_pipeline=false;
//                     LOG4CPLUS_ERROR(pLogger,"XDealer::dealPushData() {"<<getName()<<"}  pipeline append data error, break pipeline");
//                     //                cout<<"dealAppend() pipeline break;"<<endl;
//                 }
//             }

//         }
// 	}catch(TCPException &e){
//         LOG4CPLUS_ERROR(pLogger,"XDealer::dealPushData() {"<<getName()<<"} "<<e.what());
//         return -1;
//     }
// 	return 1;
// }


#endif
