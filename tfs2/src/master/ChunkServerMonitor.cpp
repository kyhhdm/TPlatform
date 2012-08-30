/**
 * @file ChunkServerMonitor.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-08-08
 */

#include "master/ChunkServerMonitor.hpp"
#include <iostream>
using namespace std;

using namespace tfs;

void ChunkServerMonitor::run()
{
    while(true){
        IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(m_sleepSeconds));
//        cout << "ChunkServerMonitor wake up" << endl;
        LocatedChunks lchks;
        m_db->m_chunkServers.removeExpired(lchks);
        m_db->m_activeChunks.remove(lchks);
    }
}


