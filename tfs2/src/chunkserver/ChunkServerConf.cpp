

#include "ChunkServerConf.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace tfs;
namespace tfs
{
     ChunkServerConf * ChunkServerConf::pInstance=NULL;
     string ChunkServerConf::mConfPath="";
}

ChunkServerConf::ChunkServerConf()
{
    
    init();
}


void ChunkServerConf::setConfPath(string path)
{
    mConfPath=path;
}

ChunkServerConf * ChunkServerConf::getInstance()
{
    if(pInstance==NULL)
    {
        assert(mConfPath!="");
        pInstance=new ChunkServerConf;
    }
    return pInstance;
}


int ChunkServerConf::init()
{
//     ifstream infile(mConfPath.c_str());
//     assert(infile);
    //@todo init the conf

    if(!mRudeConf.load(mConfPath.c_str())){
        cout<<"load conf file error!"<<endl;
        return -1;
    }

    mRudeConf.setSection("ChunkServer");
    DATA_SOCKET_PORT=mRudeConf.getIntValue("data_sock_port");
    LOCALE_IP=mRudeConf.getStringValue("locale_ip");
    CHUNK_STORE_DIR=mRudeConf.getStringValue("chunk_store_dir");

    CHUNK_TMP_DIR=mRudeConf.getStringValue("chunk_tmp_dir");
    
    MASTER_PROXY_INFO=mRudeConf.getStringValue("master_proxy_info");
    WORK_DIR=mRudeConf.getStringValue("work_dir");
    LOG_PATH=mRudeConf.getStringValue("log_path");
    //    cout<<DATA_SOCKET_PORT<<endl<<LOCALE_IP<<endl<<CHUNK_STORE_DIR<<endl<<MASTER_PROXY_INFO<<endl<<WORK_DIR<<endl<<LOG_PATH<<endl;    
    return 1;
}


string ChunkServerConf::getConfInfo()
{
    char buf[20];
    memset(buf,0,20);
    sprintf(buf,"%d",DATA_SOCKET_PORT);
    string str_info="data_port:"+string(buf)+"| ip:"+LOCALE_IP+" | chunk_stor_dir:"+CHUNK_STORE_DIR+"| master_ice_info: "+MASTER_PROXY_INFO+"work_dir"+WORK_DIR;
    return str_info;
}
