
/**
 * @file   Main.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sat Jul 14 12:05:11 2007
 * 
 * @brief  
 * 
 * 
 */

#include "ClientDaemon.hpp"
#include "SysDaemon.hpp"
#include "ChunkServerConf.hpp"
#include "TaskMgr.hpp"
#include "MasterDaemon.hpp"
#include "TransferApp.hpp"
#include "util/Logger.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>


using namespace std;
using namespace tfs;


//供全局�? 申明exyern Logger pLogger
Logger pLogger = Logger::getInstance("chunkserver");

void usage()
{
    cout<<"usage: ./ChunkServer tfs_chunkserver.ini"<<endl;
}

int init_log()
{
    ChunkServerConf * pConf=ChunkServerConf::getInstance();
    
    helpers::LogLog::getLogLog()->setInternalDebugging(false);
    SharedAppenderPtr append_1(new RollingFileAppender((pConf->LOG_PATH).c_str(), 5*1024, 5));

    //@todo if the LOG_PATH don't exsist, return -1
//     if(append_1==NULL){
//         return -1;
//     }
    append_1->setName("appender1");
    append_1->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
    Logger::getRoot().addAppender(append_1);

    //    Logger pLogger = Logger::getInstance("chunkserver");
    LOG4CPLUS_INFO(pLogger, "ChunkServer Start...");
    LOG4CPLUS_INFO(pLogger, "configure:"<<pConf->getConfInfo());
    
//     LOG4CPLUS_DEBUG(masterLogger, "Entering loop #" << i);
//     log4cplus::getNDC().push("ndc2");

//     log4cplus::getNDC().pop();
//     LOG4CPLUS_WARN(masterLogger, "Entering loop #" << i);
//     log4cplus::getNDC().pop();
//     LOG4CPLUS_ERROR(masterLogger, "Entering loop #" << i);
//     log4cplus::getNDC().push("ndc3");
//     log4cplus::getNDC().push("ndc4");
//     LOG4CPLUS_FATAL(masterLogger, "Entering loop #" << i);    
  return 1;
}


int main(int argc,char ** argv)
{

    if(argc!=2){
        usage();
        return -1;
    }
    
    ChunkServerConf::setConfPath(argv[1]);

    //初始�?    TaskMgr::getInstance();

    if(!init_log())
        return -1;

    ChunkManager *pManager=new ChunkManager;
    if(!pManager->init()){
        cout<<"Manager init failed!"<<endl;
        return -1;
    }

//    ClientDaemon client_daemon(pManager);
    MasterDaemon master_daemon(pManager);

    SysDaemon sys_daemon(pManager);

	  
//    boost::thread client_daemon_thread(client_daemon);
    boost::thread master_daemon_thread(master_daemon);
    boost::thread sys_daemon_thread(sys_daemon);
//    client_daemon_thread.join();
 
	TransferApp transfer_app(pManager);
	try
	{
        Ice::InitializationData app_data;
        Ice::PropertiesPtr props = Ice::createProperties();
        //props->setProperty("Ice.MessageSizeMax", "2048");
        props->setProperty("Ice.MessageSizeMax", "65536");
        app_data.properties = props;
		transfer_app.main(argc,argv,app_data);
	}
	catch (...)
	{
		LOG_ERROR("Start Transfer ice moudle error, may be port is in use!");
		return -1;
	}

	master_daemon_thread.join();
	sys_daemon_thread.join();
    return 0;
}
