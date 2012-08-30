/**
 * @file MasterMain.cpp
 * main function of the master.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#include "master/WorkerServiceImpl.hpp"
#include "master/JobServiceImpl.hpp"
#include "master/MonitorServiceImpl.hpp"
#include "master/MasterConfig.hpp"
#include "master/MasterDaemon.hpp"
#include "util/Logger.hpp"

#include <Ice/Application.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace mapreduce;
using namespace mapreduce::slice;
using namespace std;

/**
 * A Hook class to count and log the number of the threads
 */
class MyThreadHook : public virtual Ice::ThreadNotification {
    /// the number of Ice thread at the moment
    static int32_t m_threadCount;
    Logger m_logger;
    static IceUtil::Mutex m_mutex;
public:
    MyThreadHook()
        :m_logger(Logger::getInstance("master"))
        {
        }
    void start()
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            m_threadCount++;
            LOG4CPLUS_INFO(m_logger, "start thread id=" << IceUtil::ThreadControl().id() << " total=" << m_threadCount);
        }
    void stop()
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            m_threadCount--;
            LOG4CPLUS_INFO(m_logger, "stop thread id=" << IceUtil::ThreadControl().id() << " total=" << m_threadCount);
        }
    static int32_t getThreadCount()
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            return m_threadCount;
        }
};

int32_t MyThreadHook::m_threadCount = 0;
IceUtil::Mutex MyThreadHook::m_mutex;
/**
 * A hook class for Ice to count data sent and received
 */
class MyStats : public virtual Ice::Stats {
    static uint32_t m_bytesSent;
    static uint32_t m_bytesReceived;
    static IceUtil::Mutex m_mutex;
    Logger m_logger;
public:
    MyStats()
        :m_logger(Logger::getInstance("master"))
        {
        }

    virtual void bytesSent(const std::string& protocol, Ice::Int num)
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            m_bytesSent += num;
            //LOG4CPLUS_INFO(m_logger, protocol << ": sent " << num << " bytes total=" << m_bytesSent);
        }
    virtual void bytesReceived(const std::string& protocol, Ice::Int num)
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            m_bytesReceived += num;
            //LOG4CPLUS_INFO(m_logger, protocol << ": received " << num << " bytes total=" << m_bytesReceived);
        }
    static uint32_t getBytesSent()
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            return m_bytesSent;
        }
    static uint32_t getBytesReceived()
        {
            IceUtil::Mutex::Lock lock(m_mutex);
            return m_bytesReceived;
        }
};

uint32_t MyStats::m_bytesSent = 0;
uint32_t MyStats::m_bytesReceived = 0;
IceUtil::Mutex MyStats::m_mutex;

class MyIceLogger: virtual public Ice::Logger{
    ::Logger m_logger;          // log4cplus logger
public:
    MyIceLogger()
        :m_logger(::Logger::getInstance("master"))
        {
        }

    void print(const std::string& message)
        {
            LOG4CPLUS_INFO(m_logger, "Ice print " << message);
        }
    void trace(const std::string& category, const std::string& message)
        {
            LOG4CPLUS_TRACE(m_logger, "Ice trace " << category << ":" << message);
        }
    void warning(const std::string& message)
        {
            LOG4CPLUS_WARN(m_logger, "Ice warning " << message);
        }
    void error(const std::string& message)
        {
            LOG4CPLUS_ERROR(m_logger, "Ice error " << message);
        }
};

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
                std::cerr << "Usage: mapred_master <config.ini>" << std::endl;
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
            SharedAppenderPtr append_1(new RollingFileAppender(MasterConfig::LogFilename.c_str(), 5*1024*1024, 5));
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
            log4cplus::NDCContextCreator ndc("MasterMain::run()");

            // configure tfs client 
            tfs::api::TFSConfiguration tfsConfig;
            tfsConfig.masterIP = MasterConfig::TfsMasterHostname;
            std::stringstream ssTmp;
            ssTmp << MasterConfig::TfsMasterPort;
            tfsConfig.masterPort = ssTmp.str();
            tfs::api::TFSConfiguration::set(tfsConfig);

            // start master daemon thread
            IceUtil::ThreadPtr t1 = new MasterDaemon(MasterConfig::MasterDaemonSleepSeconds);
            t1->start();

            // Create an object adapter
            // listen tcp request on port
            std::stringstream ss;
            ss << "tcp -p " << MasterConfig::ServicePort;
            m_adapter = communicator()->createObjectAdapterWithEndpoints("mapred_master", ss.str());
   
            // create the WorkerService servant
            WorkerServicePtr  workerService = new WorkerServiceImpl;
            m_adapter->add(workerService, communicator()->stringToIdentity("WorkerService"));

            // create the JobService servant
            JobServicePtr  jobService = new JobServiceImpl;
            m_adapter->add(jobService, communicator()->stringToIdentity("JobService"));

            // create the JobService servant
            MonitorServicePtr  monitorService = new MonitorServiceImpl;
            m_adapter->add(monitorService, communicator()->stringToIdentity("MonitorService"));

            // All objects are created, allow RPC requests now
            m_adapter->activate();

            // Wait until we are done
            //
            LOG4CPLUS_INFO(masterLogger, "mapred_master started running at " << ss.str());
            ss.clear();
            MasterConfig::print(ss);
            LOG4CPLUS_INFO(masterLogger, "With config parameters: " << ss.str());
            communicator()->waitForShutdown();
 
            if (interrupted()) {
                LOG4CPLUS_INFO(masterLogger, "Received signal, mapred_master shutting down");
            }

            m_adapter = 0;

            return 0;
        }
};

void nomorememory()
{
    LOG4CPLUS_FATAL(Logger::getInstance("master"), "Abort, unable to satisfy request for memory");
    throw std::bad_alloc();
}

int main(int argc, char* argv[])
{
    try{
        
        // set new handler, write log when new cannot alloc memory
        std::set_new_handler(nomorememory);
        
        MasterMain app;

        Ice::PropertiesPtr props = Ice::createProperties(argc, argv);
        // make sure we use ThreadPerConnection concurrency model, @see JobServiceImpl::wait for reasons
        // props->setProperty("Ice.ThreadPerConnection", "1");

        props->setProperty("Ice.ThreadPool.Client.Size", "1");
        props->setProperty("Ice.ThreadPool.Client.SizeMax", "10");
        props->setProperty("Ice.ThreadPool.Server.Size", "10");
        props->setProperty("Ice.ThreadPool.Server.SizeMax", "30");

        // retry three times
        props->setProperty("Ice.RetryIntervals", "0 100 500");
        // trace Ice 
        props->setProperty("Ice.Trace.GC", "1");
        props->setProperty("Ice.Trace.Network", "2");
        props->setProperty("Ice.Trace.Retry", "1");
        props->setProperty("Ice.Trace.Slicing", "1");
        props->setProperty("Ice.Warn.Connections", "1");
        props->setProperty("Ice.Warn.Datagrams", "1");
        props->setProperty("Ice.Warn.Dispatch", "2");

        Ice::InitializationData id;
        id.properties = props;
        id.threadHook = new MyThreadHook();
        id.stats = new MyStats();
        id.logger = new MyIceLogger();
        
        return app.main(argc, argv, id); 
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
