/**
 * @file WorkerManager.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/WorkerManager.hpp"
#include "master/MasterException.hpp"
#include <map>

using namespace mapreduce;
using namespace std;

WorkerManager::~WorkerManager()
{
    if (!m_worker2info.empty()){
        Addresses workers = this->getAllWorkers();
        LOG4CPLUS_WARN(m_logger, "Workers still alive when shutdown: " << workers);
    }
}

void WorkerManager::renewHeartbeat(const Address& worker, const Heartbeat &heartbeat)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    
    if (m_worker2info.find(worker) == m_worker2info.end()){
        // new worker
        WorkerInfo info;
        info.m_lastUpdate = time(NULL);
        info.m_heartbeat = heartbeat;
        m_worker2info[worker] = info;
        LOG4CPLUS_INFO(m_logger, "Worker enrolled: " << worker);
    }
    else{
        m_worker2info[worker].m_lastUpdate = time(NULL);
        m_worker2info[worker].m_heartbeat = heartbeat;
    }
}

Address WorkerManager::selectWorker(const Addresses& candidateWorkers) const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    if (m_worker2info.size() < m_safeModeThreshold) {
        throw SafeModeException();
    }
    Addresses bestWorkers;
    for (int i = 0; i < candidateWorkers.size(); i++){
        address2info_t::const_iterator it;
        for (it = m_worker2info.begin(); it != m_worker2info.end(); ++it){
            if(candidateWorkers[i].name == it->first.name){
                bestWorkers.push_back(it->first);
            }
        }
    }
    double total = bestWorkers.size();
    if (total > 0){
        int32_t k = (int)(total*rand()/(RAND_MAX+1.0)); // k: [0, total)
        return bestWorkers[k];
    }
    
    return this->selectWorkerRandomly();
}

Address WorkerManager::selectWorkerRandomly() const
{
    double total = m_worker2info.size();
    if (total < m_safeModeThreshold) {
        throw SafeModeException();
    }
    int32_t k = (int)(total*rand()/(RAND_MAX+1.0));

    address2info_t::const_iterator it;
    int i = 0;
    for (it = m_worker2info.begin(); it != m_worker2info.end(); ++it){
        if (i++ == k){
            return (*it).first;
        }
    }

    throw SafeModeException();
}

Addresses WorkerManager::getAllWorkers() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    //IceUtil::RWRecMutex::WLock lock(m_mutex);
    Addresses addresses;
    for (address2info_t::const_iterator it = m_worker2info.begin(); it != m_worker2info.end(); ++it){
        addresses.push_back(it->first);
    }
    return addresses;
}

Workers WorkerManager::getWorkers() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    Workers workers;
    for (address2info_t::const_iterator it = m_worker2info.begin(); it != m_worker2info.end(); ++it){
        workers.push_back(*it);
    }
    return workers;
}


int32_t WorkerManager::count() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_worker2info.size();
}

Addresses WorkerManager::removeExpired()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    Addresses expiredWorkers;
    
    time_t now = time((time_t*)NULL);
    address2info_t::iterator it = m_worker2info.begin();
    while(it != m_worker2info.end()){
        if (now - it->second.m_lastUpdate > m_expireTime){
            expiredWorkers.push_back(it->first);
            m_worker2info.erase(it);
            it = m_worker2info.begin(); // rewind the iterator!!
        }
        else{
            ++it;
        }
    }    
    return expiredWorkers;
}

void WorkerManager::setSafeMode(bool safeMode)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    m_safeMode = safeMode;
}

bool WorkerManager::isSafeMode() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return (m_safeMode || m_worker2info.size() < m_safeModeThreshold);
}

void WorkerManager::increaseDoneTasks(const Address& worker, TaskType type)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    address2info_t::iterator it = m_worker2info.find(worker);
    
    if (it == m_worker2info.end()){
        LOG4CPLUS_WARN(m_logger, "WorkerManager::increaseDoneTasks() no worker found " << worker);
        return;
    }
    switch(type){
    case TT_MAP:
    {
        it->second.m_doneMapTasks++;
        break;
    }
    case TT_REDUCE:
    {
        it->second.m_doneReduceTasks++;
        break;
    }
    case TT_TRANS:
    {
        it->second.m_doneTransTasks++;
        break;
    }
    default:
        break;
    }
}

// Addresses WorkerManager::getFreeWorkers() const
// {
//     IceUtil::Mutex::Lock lock(m_mutex);
//     Addresses addresses;
//     for (address2info_t::const_iterator it = m_worker2info.begin(); it != m_worker2info.end(); ++it){
//         if (it->second.m_heartbeat.workload < m_workloadFreeThreshold){
//             addresses.push_back(it->first);
//         }
//     }
//     return addresses;    
// }


//@add by Chen Rishan
void WorkerManager::setJobPriority(Tasks& tasks,JobPriority jobPrio)
{
    IceUtil::RWRecMutex::WLock lock(m_wMutex); // Write lock
    std::vector<Address> recordJobs;
    for(Tasks::iterator iter = tasks.begin(); iter != tasks.end(); iter ++){
        Address worker = iter->second.worker;
        //neglect trans task 
        /**
         * BUG FIXED
         * the flag worker in data structure of trans task wasn't marked at all
         * */
        if(find(recordJobs.begin(), recordJobs.end(), worker) == recordJobs.end() && m_worker2info.find(worker) != m_worker2info.end() ){//workerManager can find it
            ScheInfo scheinfo;
            scheinfo.jobid = iter->second.jobId;
            scheinfo.timeslice = scheinfo.getTimeslice(jobPrio);
            recordJobs.push_back(worker);
            //LOG4CPLUS_DEBUG(m_logger, " setJob " << worker);
            m_worker2info[worker].m_scheLists[jobPrio].push_back(scheinfo);
        }
    }//end of for
}

int32_t WorkerManager::getPriorJob(const Address& worker)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    ScheInfo scheinfo;
    for(int i = 0; i < SCHE_LISTS_NUM; i ++){
        if(!m_worker2info[worker].m_scheLists[i].empty() ){
            scheinfo = m_worker2info[worker].m_scheLists[i].front();
            if(scheinfo.timeslice <= 0){
                int prio = i + 1;
                if(i == 4){
                    prio = i;
                }
                scheinfo.timeslice = scheinfo.getTimeslice(prio);
                m_worker2info[worker].m_scheLists[i].pop_front();
                m_worker2info[worker].m_scheLists[prio].push_back(scheinfo);
                return scheinfo.jobid;
            }
            scheinfo.timeslice --;
            m_worker2info[worker].m_scheLists[i].pop_front();
            m_worker2info[worker].m_scheLists[i].push_back(scheinfo);
            return scheinfo.jobid;
        }
    }
    return 0;
}

bool WorkerManager::removeScheduledJob(int32_t jobId)
{
    IceUtil::RWRecMutex::WLock lock(m_wMutex); // Write lock
    Addresses addresses = getAllWorkers();
    Addresses::iterator iter = addresses.begin();
    list<ScheInfo>::iterator it;
    for(; iter != addresses.end(); iter ++){
        for(int i = 0; i < SCHE_LISTS_NUM; i ++){
            it = m_worker2info[*iter].m_scheLists[i].begin();
            while(it != m_worker2info[*iter].m_scheLists[i].end() ){
                if(it->jobid == jobId){
                    m_worker2info[*iter].m_scheLists[i].erase(it);
                    break;
                }
                it ++;
            }
        }
    }
    return true;
}
