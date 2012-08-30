/**
 * @file JobManager.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */

#include "master/JobManager.hpp"

using namespace mapreduce;
using namespace mapreduce::slice;
using namespace tfs::mapred;

JobManager::~JobManager()
{
    if (!m_id2info.empty()){
        Jobs jobs = this->getAllJobs();
        LOG4CPLUS_TRACE(m_logger, "Jobs when shutdown: " << jobs);
    }
}

inline int32_t JobManager::newId() const
{
    int32_t id;
    id2info_t::const_iterator it;
    do{
        id = rand();
        it = m_id2info.find(id);
    }while(it != m_id2info.end());
    return id;
}

int32_t JobManager::add(const MapReduceJob &job, const LocatedChunks& lchks)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    int32_t id = newId();
    JobInfo info;
    info.createTime = time((time_t*)NULL);
    info.finishTime = 0;
    info.status = JS_IDLE;
    info.jobSpec = job;
    info.bDetached = true;
    info.lchks = lchks;
    //TODO: priority configure
    info.jobInitPriority = JP_REAL;

    m_id2info[id] = info;
    return id;
}

void JobManager::remove(int32_t jobId)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    id2info_t::iterator it = m_id2info.find(jobId);
    if (it != m_id2info.end()){
        m_id2info.erase(it);
    }
}

Job JobManager::getJob(int32_t jobId) const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    Job job;
    id2info_t::const_iterator it = m_id2info.find(jobId);
    if (it != m_id2info.end()){
        job = *it;
    }else{
        job.first = -1;         // invalid job id
    }
    return job;
}

void JobManager::setJobDetached(int32_t jobId)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    id2info_t::iterator it = m_id2info.find(jobId);
    if (it != m_id2info.end()){
        it->second.bDetached = true;
    }
}

void JobManager::setJobStatus(int32_t jobId, JobStatus status)
{
    IceUtil::Mutex::Lock lock(m_mutex);
    id2info_t::iterator it = m_id2info.find(jobId);
    if (it != m_id2info.end()){
        it->second.status = status;
	if (status == JS_CANCELLED || status == JS_COMPLETED){
	    it->second.finishTime = time((time_t*)NULL);
	}
    }
}

Jobs JobManager::getAllJobs() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    Jobs jobs;
    id2info_t::const_iterator it;
    for (it = m_id2info.begin(); it != m_id2info.end(); ++it){
        jobs.push_back(*it);
    }
    return jobs;
}
