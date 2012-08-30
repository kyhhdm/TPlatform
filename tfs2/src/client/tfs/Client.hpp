/**
 * @file	Client.hpp
 *  Header file for Client class.	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	09/20/2007 05:49:24 PM CST
 *
 */

#ifndef  CLIENT_FILE_HEADER_INC
#define  CLIENT_FILE_HEADER_INC

#include "tfs.h"

#include <util/Logger.hpp>
#include <common/IceGenerated.hpp>

namespace tfs {

/**
 * This class offer a thin wrapper of ClientService for convenience, 
 * and provide some basic functions for client utilities.
 */
class Client {
public:
    /// Get the address of current client.
    static Address address() { return instance()->m_address; }

    /// Get the ice proxy to use client service.
    static ClientServicePrx service() { return instance()->m_service; }

    /// Get the default buffer size.
    static int defaultBufferSize() { return instance()->m_conf.bufferSize; }

    /// Initialize a client instance.
    static void init() {
        if (m_client == NULL)
            m_client = new Client();
    }

    /// Set configuration.
    static bool set(const api::TFSConfiguration &conf) {
        if (m_configured) return false;
        m_conf = conf;
        m_configured = true;
        return true;
    }

    /// Set configuration file.
    static bool setFile(const std::string &path);

    static bool authorized(const std::string &path);

private:
    /// Constructor, initialize basic services and start heartbeat deamon.
    Client();

    /**
     * To ensure there is only one Client instance in a program, 
     * we use singleton design patten to create Client instance.
     */
    static Client *instance() {
        init();
        return m_client;
    }

    /// Get configuration from file specified by path.
    static bool setFromFile(const std::string &path);

    /// Pointer to the only instance.
    static Client *m_client;

    /// Address of this client, this is used to specify a client.
    Address m_address;        

    /// Ice proxy to use client service.
    ClientServicePrx m_service;    

    /// Store configuration.
    static api::TFSConfiguration m_conf;

    /// Whether the client has been configured.
    static bool m_configured;
};

// Define several macros for convience
#define LOG_DEBUG(x)    LOG4CPLUS_DEBUG(Logger::getInstance("tfs_client"), x)
#define LOG_INFO(x)     LOG4CPLUS_INFO(Logger::getInstance("tfs_client"), x)
#define LOG_WARN(x)     LOG4CPLUS_WARN(Logger::getInstance("tfs_client"), x)
#define LOG_ERROR(x)    LOG4CPLUS_ERROR(Logger::getInstance("tfs_client"), x)
#define LOG_FATAL(x)    LOG4CPLUS_FATAL(Logger::getInstance("tfs_client"), x)

} // namespace tfs

#endif   /* ----- #ifndef CLIENT_FILE_HEADER_INC  ----- */

