/**
 * @file	HeartbeatDeamon.cpp
 * 	Heartbeat Deamon Implementation
 * 
 * @author	Fan Kai(FK), Peking University	
 * @date	08/09/2007 12:36:18 AM CST
 *
 */

#include "HeartbeatDeamon.hpp"
#include "Client.hpp"

namespace tfs {
    HeartbeatDeamon::HeartbeatDeamon(Address &addr, 
			slice::ClientServicePrx &csp) {
        m_clientServicePrx = csp;
		m_clientAddress = addr;
    }

    void HeartbeatDeamon::run() {
        try {
            while(true){
                IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
                m_clientServicePrx->reportHeartbeat(m_clientAddress);
            }
        } catch (Ice::Exception &ex) {
            LOG_FATAL("HeartBeatDeamon: Get Ice Exception: " <<ex.ice_name());
            LOG_FATAL("HeartBeatDeamon: Throw api::ConnectionError");
            throw api::ConnectionError();
        }
    }
}
