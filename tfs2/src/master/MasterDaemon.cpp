/**
 * @file MasterDaemon.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-07
 */

#include "master/MasterDaemon.hpp"
using namespace tfs;

bool MasterDaemon::isSystemIdel()
{
    if (m_db->m_activeClients.getClientNum() < 3){
        return true;
    }
    return false;
}

void MasterDaemon::run()
{
    while(true){
        IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(m_sleepSeconds));
//        cout << "MasterDaemon wake up" << endl;
        if (isSystemIdel()){
            // fs directory check point
            m_db->m_fsJournal.createCheckPoint();
            LOG4CPLUS_INFO(m_logger, "create journal checkpoint");
            
            // let chunkservers report chunks
        }        
    }
}
