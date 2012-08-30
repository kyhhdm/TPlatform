/**
 * @file  Client.cpp
 *   Implementation of Client class.
 * 
 * @author  Fan Kai(fk), Peking University    
 * @date    09/21/2007 12:33:06 AM CST
 *
 */

#include "Client.hpp"
#include "HeartbeatDeamon.hpp"

#include <util/Config.hpp>
#include <Ice/Ice.h>

namespace tfs {

using std::string;

bool Client::m_configured = false;
api::TFSConfiguration Client::m_conf;
Client *Client::m_client = NULL;

bool Client::setFile(const std::string &path) {
    if (m_configured) return false;
    if (!setFromFile(path.c_str())) {
        LOG_FATAL("Client: Throw api::LoadConfigurationError");
        throw api::LoadConfigurationError();
    }
    m_configured = true;
    return true;
}

bool Client::setFromFile(const string &path) {
    Config conf;
    if (!conf.load(path.c_str()))
        return false;
    conf.setSection("master");
    m_conf.masterIP = conf.getStringValue("master_ip");
    m_conf.masterPort = conf.getStringValue("master_port");
    conf.setSection("client");
    m_conf.bufferSize = conf.getIntValue("buffer_size") * 1024;
    m_conf.logLevel = conf.getStringValue("log_level");
    m_conf.logFile = conf.getStringValue("log_file");
    conf.setSection("user");
    m_conf.username = conf.getStringValue("username");
    m_conf.userkey = conf.getStringValue("userkey");
    if (strlen(conf.getError()) > 0) {
        LOG_FATAL("Client: Throw api::ParseConfigurationError");
        throw api::ParseConfigurationError();
    }
    m_configured = true;
    return true;
}

bool Client::authorized(const string &path) {
    return true;
    if (path.find(m_conf.username) != 1) return false;
    else return true;
}

Client::Client() {
    try {
        // We use ip address and process id to identify a client.
        char hostname[100];
        gethostname(hostname, 100);
        m_address.name = hostname;
        m_address.port = getpid();

        // Get configuration.
        string homedir = getenv("HOME");
        if (!m_configured && !setFromFile("tfs_client.ini") 
                    && !setFromFile(homedir + "/.tfs_client.ini")
                    && !setFromFile("/etc/tfs_client.ini")) {
            //LOG_FATAL("Client: Throw api::LoadConfigurationError")
            throw api::LoadConfigurationError();
        }

        // Initialize client logger.    
        if (m_conf.logFile[0] == '~')
            m_conf.logFile = homedir + m_conf.logFile.substr(1);
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(
            new RollingFileAppender(m_conf.logFile, 1024 * 1024, 1));
        std::string pattern = "%D %p - %m\n";
        append_1->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
        Logger logger = Logger::getInstance("tfs_client");
        logger.addAppender(append_1);

        // Set logger level
        if (m_conf.logLevel == "FATAL") logger.setLogLevel(FATAL_LOG_LEVEL);
        if (m_conf.logLevel == "ERROR") logger.setLogLevel(ERROR_LOG_LEVEL);
        if (m_conf.logLevel == "WARN") logger.setLogLevel(WARN_LOG_LEVEL);
        if (m_conf.logLevel == "INFO") logger.setLogLevel(INFO_LOG_LEVEL);
        if (m_conf.logLevel == "DEBUG") logger.setLogLevel(DEBUG_LOG_LEVEL);
        LOG_INFO("Client: Starts TFS Client instance.");
        LOG_INFO("Client: Get master address: " <<m_conf.masterIP <<":" 
                                                <<m_conf.masterPort);
        LOG_INFO("Client: Get default buffer size: " <<m_conf.bufferSize);
        LOG_INFO("Client: Get log level: " <<m_conf.logLevel);
        LOG_INFO("Client: Get log file: " <<m_conf.logFile);

        // Initialize ice.
        Ice::CommunicatorPtr ic = Ice::initialize();
        Ice::ObjectPrx base = ic->stringToProxy(
            "ClientService:tcp -h " + m_conf.masterIP + " -p " + m_conf.masterPort);
        m_service = slice::ClientServicePrx::checkedCast(base);
        LOG_INFO("Client: Ice service initialized.")

        // Begin heartbeat.
        IceUtil::ThreadPtr deamon = new HeartbeatDeamon(m_address,
                                                        m_service);
        deamon->start();
        LOG_INFO("Client: Heartbeat Deamon started.")
    } catch (Ice::Exception &ex) {
        LOG_FATAL("Client: Get Ice Exception:" <<ex.ice_name());
        LOG_FATAL("Client: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

} // namespace tfs
