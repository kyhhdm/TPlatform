/**
 * @file Statistics.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2008-03-21
 */

#include "master/Statistics.hpp"

using namespace mapreduce;

time_t Statistics::getStartTime() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_startTime;
}

int32_t Statistics::getCompletedJobs() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_doneJobs;
}

int32_t Statistics::getCompletedMapTasks() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_doneMapTasks;
}

int32_t Statistics::getCompletedReduceTasks() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_doneReduceTasks;
}

int32_t Statistics::getCompletedTransTasks() const
{
    IceUtil::Mutex::Lock lock(m_mutex);
    return m_doneTransTasks;
}

void Statistics::doneJob()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    m_doneJobs++;
}

void Statistics::doneMap()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    m_doneMapTasks++;
}

void Statistics::doneReduce()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    m_doneReduceTasks++;
}

void Statistics::doneTrans()
{
    IceUtil::Mutex::Lock lock(m_mutex);
    m_doneTransTasks++;
}

