


#include "util/Logger.hpp"
#include "TaskMgr.hpp"
#include "SysDaemon.hpp"
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using namespace tfs;

extern ::log4cplus::Logger pLogger;



void SysDaemon::operator()()
{
    while(1)
    {
        sleepCurThread(10);
        doSysTask();
        
    }
}

void SysDaemon::doSysTask()
{
    TaskMgr * p_task_mgr = TaskMgr::getInstance();

    SysTask task;
    while ( p_task_mgr->getSysTask(task)){
        LOG4CPLUS_DEBUG(pLogger,"ChunkManager::doSysTask() get a SysTask to do");
        if (task.m_action == Del_Chunk_Task){

            vector<int64_t>::iterator it = task.m_chunks.begin();
            for (;it!=task.m_chunks.end();++it){
                
                //如果该chunk块正忙
                if(p_task_mgr->isBusyChunk(*it)){
                    p_task_mgr->addSysTask(task);
                    LOG4CPLUS_INFO(pLogger,"ChunkManager::doSysTask() try to delete a busy chunk:" << *it);
                    continue;
                }

                m_chunk_manager->delChunk(*it);                
                
            }
            
        }
        
    }
}

void SysDaemon::logSystemStatus()
{
    
}


