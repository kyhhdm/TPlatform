/**
 * @file	HeartBeatDeamon.hpp
 * 	Heartbeat Deamon of client.
 * 
 * @author	Fan Kai(FK), Peking University	
 * @date	08/09/2007 12:26:00 AM CST
 *
 */

#ifndef  HEARTBEATDEAMON_FILE_HEADER_INC
#define  HEARTBEATDEAMON_FILE_HEADER_INC

#include "Client.hpp"

#include <IceUtil/Thread.h>

namespace tfs {

    /**
     * Heartbeat Deamon Class for Client
     */
    class HeartbeatDeamon: public IceUtil::Thread {
    public:
        HeartbeatDeamon(Address &addr, 
				slice::ClientServicePrx &csp);

        virtual void run();

    private:
		// Address of this client
		Address m_clientAddress;		

		// Ice proxy to use client service
		slice::ClientServicePrx m_clientServicePrx;	
    };
}

#endif   /* ----- #ifndef HEARTBEATDEAMON_FILE_HEADER_INC  ----- */

