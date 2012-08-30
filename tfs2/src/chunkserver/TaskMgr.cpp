/**
 * @file   TaskMgr.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Fri Dec  7 15:41:53 2007
 * 
 * @brief  
 * 
 * 
 */

#include "TaskMgr.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace tfs;

namespace tfs
{
    TaskMgr * TaskMgr::m_pInstance = NULL;
    
}

TaskMgr::TaskMgr()
{
    
}

TaskMgr::~TaskMgr()
{
    if (m_pInstance != NULL)
        delete m_pInstance;
}

TaskMgr * TaskMgr::getInstance()
{
    if (m_pInstance == NULL){
        m_pInstance = new TaskMgr;
        return m_pInstance;
    }else
        return m_pInstance;
}


void TaskMgr::addSysTask(const SysTask & one_task)
{
    boost::mutex::scoped_lock lock(m_task_mutex);
    m_task_queue.push(one_task);
}

bool TaskMgr::getSysTask(SysTask & task)
{
    boost::mutex::scoped_lock lock(m_task_mutex);
    if (m_task_queue.empty())
        return false;
    task = m_task_queue.front();
    m_task_queue.pop();
    return true;
}

void TaskMgr::addDealer(const string& dealer_name,const DealerStatus & status)
{
    assert(dealer_name != "");
    boost::mutex::scoped_lock lock(m_dealer_mutex);
    m_dealer_map[dealer_name] = status;    
}

bool TaskMgr::removeDealer(const string& dealer_name)
{

    assert(dealer_name != "");
    
    boost::mutex::scoped_lock lock(m_dealer_mutex);    
    map<string,DealerStatus>::iterator it = m_dealer_map.find(dealer_name);
    if (it == m_dealer_map.end()){        
        return false;
    }else{
        
        m_dealer_map.erase(it);
        return true;
    }
}

bool TaskMgr::setDealerStatus(const string& dealer_name,const DealerStatus & status)
{
    assert(dealer_name != "");
    boost::mutex::scoped_lock lock(m_dealer_mutex);
    m_dealer_map[dealer_name] = status;
    return true;

}

int TaskMgr::getDealerNum(const DealerStatus & status)
{
    if (status == All_Dealer)
        return m_dealer_map.size();
    
    boost::mutex::scoped_lock lock(m_dealer_mutex);
    int sum = 0;
    std::map<std::string,DealerStatus>::iterator it = m_dealer_map.begin();
    for (;it != m_dealer_map.end(); ++it){
        if (it->second == status)
            ++sum;
    }
    return sum;
}


void TaskMgr::addBusyChunk(const int64_t& chunk_id)
{
    boost::mutex::scoped_lock lock(m_busy_chunk_mutex);    
    map<int64_t,int>::iterator it =  m_busy_chunk_map.find(chunk_id);
    if (it != m_busy_chunk_map.end()){
        m_busy_chunk_map[it->first] = ++(it->second);
    }else{
        m_busy_chunk_map[chunk_id] = 1;
    }
}

bool TaskMgr::isBusyChunk(const int64_t& chunk_id)
{
    boost::mutex::scoped_lock lock(m_busy_chunk_mutex);    
    map<int64_t,int>::iterator it =  m_busy_chunk_map.find(chunk_id);
    if (it != m_busy_chunk_map.end()){
        return true;
    }else{
        return false;
    }
}

bool TaskMgr::removeBusyChunk(const int64_t& chunk_id)
{
    boost::mutex::scoped_lock lock(m_busy_chunk_mutex);    
    map<int64_t,int>::iterator it =  m_busy_chunk_map.find(chunk_id);
    if (it != m_busy_chunk_map.end()){
        m_busy_chunk_map.erase(it);
        return true;
    }else{
        return false;
    }
}

