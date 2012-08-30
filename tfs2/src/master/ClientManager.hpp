/** @file ClientManager.hpp
 * manage the clients informations
 * @author YangZhifeng
 * @date 23  5 2007
 */
#ifndef _CLIENTMANAGER_HPP
#define _CLIENTMANAGER_HPP 1
#include "common/Types.hpp"
#include "common/IceGenerated.hpp"
#include "master/AddressHelper.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <string>
#include <ext/hash_map>
#include <IceUtil/Mutex.h>

namespace tfs
{
    class ClientManager
    {
        /// client-> lastUpdateTime map
        typedef __gnu_cxx::hash_map<Address, time_t, AddressHash, AddressEqual> map_type;
        map_type m_clients;
        /// expire time, client which don't renew for more than this time will be removed
        int32_t m_expireTime;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// logger
        Logger m_logger;

    public:
        // constructor
        ClientManager(int32_t expireTime)
            :m_expireTime(expireTime), m_logger(Logger::getInstance("master"))
        {
        }
        
        /**
         * Renew the lease of the client. The client should periodly renew his release, 
         * or the master can delete all the resources of his opened file. If the client
         * is new, add it and initialize it last update time. 
         * 
         */
        void renewHeartbeat(const Address& clientAddress);
        /**
         * Remove client. Do nothing if the Client doesn't exist. 
         * 
         */
        void remove(const Address& clientAddress);
        /**
         * client which don't renew for more than m_expireTime will be removed
         * 
         * @param expiredClients [out] all the expired clients
         */
        void removeExpired(Addresses &expiredClients);

        /** 
         * get the number of active clients
         * 
         * 
         * @return the number of active clients
         */
        int32_t getClientNum();
        /** 
         * get all the clients' addresses
         * 
         * 
         * @return 
         */
        Addresses getClients();
        /** 
         * if the client has enrolled
         * 
         * @param clientAddress 
         * 
         * @return 
         */
        bool exists(const Address& clientAddress);
    };
}


#endif /* _CLIENTMANAGER_HPP */
