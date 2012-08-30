/**
 * @file ClientMonitor.cpp
 * implementation of ClientManager.
 * 
 * @author Zhifeng YANG
 * @date 2007-07-17
 */

#include "master/ClientMonitor.hpp"
#include <sstream>
#include <iostream>
using namespace std;
using namespace tfs;

void ClientMonitor::run()
{
    while(true){
        IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(m_sleepSeconds));
//        cout << "ClientMonitor wake up" << endl;
        
        Addresses expiredClients;
        m_db->m_activeClients.removeExpired(expiredClients);

        if (!expiredClients.empty()){
            LOG4CPLUS_INFO(m_logger, "remove expired clients: " << expiredClients);
        }
        
        for (int i = 0; i < expiredClients.size(); i++){
            stringstream ssHolder;
            ssHolder << expiredClients[i].name << ":" << expiredClients[i].port;    
            m_db->m_dir.releaseResource(ssHolder.str());
        }
        
    }
}

