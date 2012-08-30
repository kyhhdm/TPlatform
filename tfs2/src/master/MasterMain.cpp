/* 
 * @(#)MasterMain.cpp
 * AUTHOR: YangZhifeng
 * CREATED DATE: 19  3ÔÂ 2007
 * DESCRIPTION: main function of Master 
 */
/**
 * @file   MasterMain.cpp
 * @author Zhifeng YANG
 * @date   Tue Mar 20 18:30:50 2007
 * 
 * @brief  main function of the Master
 * 
 * 
 */
#include "master/ClientServiceImpl.hpp"
#include "master/ChunkServerServiceImpl.hpp"
#include "master/AdminServiceImpl.hpp"

#include "util/Logger.hpp"
#include "master/MasterConfig.hpp"
#include "master/ClientMonitor.hpp"
#include "master/ChunkServerMonitor.hpp"
#include "master/MasterDaemon.hpp"

#include <iostream>
#include <sstream>
#include <Ice/Application.h>

using namespace tfs;
using namespace tfs::slice;

/**
 * This class uses the standard Ice::Application class to create the main function.
 * 
 */
class MasterMain : virtual public Ice::Application 
{
    Ice::ObjectAdapterPtr m_adapter;

public:

    int run(int argc, char* argv[]) 
        {
            // configuration file
            if (argc != 2){
                std::cerr << "Usage: tfs_master <config.ini>" << std::endl;
                return 1;
            }

            if (!MasterConfig::load(argv[1])){
                std::cerr << "ERROR: load configuration file: " << argv[1] << std::endl;
                return 2;
            }

            // setup logger
            // output log statements from within the log4cplus package, set true if you want
            helpers::LogLog::getLogLog()->setInternalDebugging(false);
            // output log into szLogFile and backup the log files when they reach
            // 500*1024 bytes, there can be at most 5 backup files.
            SharedAppenderPtr append_1(new RollingFileAppender(MasterConfig::LogFilename.c_str(), 500*1024, 5));
            append_1->setName("appender1");
            /* set the output layout
             *  <p>The first field is the number of milliseconds elapsed since the
             *  start of the program. The second field is the thread outputting the
             *  log statement. The third field is the LogLevel, the fourth field is
             *  the logger to which the statement belongs.
             * 
             *  <p>The fifth field (just before the '-') is the nested diagnostic
             *  context.  Note the nested diagnostic context may be empty as in the
             *  first two statements. The text after the '-' is the message of the
             *  statement.
             */
            append_1->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
            Logger::getRoot().addAppender(append_1);

            // get logger and set log level
            Logger masterLogger = Logger::getInstance("master");
            masterLogger.setLogLevel(MasterConfig::RuntimeLogLevel);

            log4cplus::getNDC().push("MasterMain::run");

            // start monitor thread
            IceUtil::ThreadPtr t1 = new ClientMonitor(MasterConfig::ClientMonitorSleepSeconds);
            t1->start();
            IceUtil::ThreadPtr t2 = new ChunkServerMonitor(MasterConfig::ChunkServerMonitorSleepSeconds);
            t2->start();

            // start master daemon thread
            IceUtil::ThreadPtr t3 = new MasterDaemon(MasterConfig::MasterDaemonSleepHours);
            t3->start();

            // Create an object adapter
            // listen tcp request on port 10000
            std::stringstream ss;
            ss << "tcp -p " << MasterConfig::ServicePort;
            m_adapter = communicator()->createObjectAdapterWithEndpoints("tfs_master", ss.str());
   
            // create the client servant
            ChunkServerServicePtr  chunkServerService = new ChunkServerServiceImpl;
            m_adapter->add(chunkServerService, communicator()->stringToIdentity("ChunkServerService"));
            // create the chunkserver servant
            ClientServicePtr clientService = new ClientServiceImpl;
            m_adapter->add(clientService, communicator()->stringToIdentity("ClientService"));

            // create the admin service servant
            AdminServicePtr adminService = new AdminServiceImpl;
            m_adapter->add(adminService, communicator()->stringToIdentity("AdminService"));            

            // All objects are created, allow RPC requests now
            m_adapter->activate();

            // Wait until we are done
            //
            LOG4CPLUS_INFO(masterLogger, "master start running at " << ss.str());
            communicator()->waitForShutdown();
 
            if (interrupted()) {
                LOG4CPLUS_INFO(masterLogger, "received signal, shutting down");
            }

            m_adapter = 0;

            log4cplus::getNDC().pop();
            return 0;
        }
};

void nomorememory()
{
    LOG4CPLUS_ERROR(Logger::getInstance("master"), "Abort, unable to satisfy request for memory");
    throw std::bad_alloc();
}

int main(int argc, char* argv[])
{
    try{
        MasterMain app;
        return app.main(argc, argv); 
    }
    catch(std::exception &ex){
        LOG4CPLUS_ERROR(Logger::getInstance("master"), "Abort, catch exception: " << ex.what());
        return -1;
    }
    catch(...){
        LOG4CPLUS_ERROR(Logger::getInstance("master"), "Abort, catch unknown exception");
        return -1;
    }
}
