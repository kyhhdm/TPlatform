/**
 * @file SystemMonitor.cpp
 * monitor of the whole tfs system.
 * 
 * @author Zhifeng YANG
 * @date 2007-08-29
 */
#include "AdminService.h"
#include <util/Config.hpp>
#include <Ice/Ice.h>
#include <string>
#include <iostream>
#include <exception>
using namespace tfs::slice;
using namespace std;


bool setFromFile(const string& path, string& ip, string& port)
{ 
    rude::Config conf;
    if (!conf.load(path.c_str())){
        cout << "LoadConfigurationError: load" << path << "failed!" << endl;
        return false;
    }
    conf.setSection("master");
    ip = conf.getStringValue("master_ip");
    port = conf.getStringValue("master_port");

    return (ip != "" && port != "");
}

void getOperationsCount(AdminServicePrx& adminSP)
{ 
    string OperationName[]={"Op Open", "Op Close",    "Op GetChunksInfo",    "Op AddChunk",    "Op CompleteWrittenChunk",    "Op AbandonAddChunk",    "Op ReportBadChunks",    "Op SetReplication",    "Op GetFileInfo",    "Op Create",    "Op Mkdir",    "Op Rename",    "Op RenameDir",    "Op Remove",    "Op Rmdir",    "Op Lsdir"};
    
    OperationsCount counts = adminSP->getOperationsCount();
    for (int i = 0; i < counts.size(); i++){
        if ( i < sizeof(OperationName)/sizeof(string) ){
            cout << OperationName[i] << " : " << counts[i] << endl;
        }
        else{
            cout << "Op Default : " << counts[i] << endl;
        }
    }
}


void getChunkServers(AdminServicePrx& adminSP)
{
    Addresses addresses = adminSP->getChunkServers();
    
    for (int i = 0; i < addresses.size(); i++){
        cout << "ChunkServer [" << i << "]  NAME=" << addresses[i].name << " PORT=" << addresses[i].port << endl;
    }
}

int main()
{
    try{
        
        //Ice proxy to use administrative service
        AdminServicePrx adminServicePrx;

        // Get configuration.
        string ip, port;
        string homedir = getenv("HOME");
        if (!setFromFile("tfs_client.ini", ip, port) 
                    && !setFromFile(homedir + "/.tfs_client.ini", ip, port)
                    && !setFromFile("/etc/tfs_client.ini", ip , port)) {
            cout << "LoadConfigurationError: tfs_client.ini not found!" << endl;
            return -1;
        }
       
        //init ice
        Ice::CommunicatorPtr ic = Ice::initialize();
        Ice::ObjectPrx base	= ic->stringToProxy(
            "AdminService:tcp -h " + ip + " -p " + port);
        adminServicePrx = AdminServicePrx::checkedCast(base);


        cout << "Start Time: " << adminServicePrx->getStartTime() << endl;

        getOperationsCount(adminServicePrx);
        
        getChunkServers(adminServicePrx);
        
    }
    catch(const std::exception &ex) {
        cerr << ex.what() << endl;
    }
    return 0;
}
