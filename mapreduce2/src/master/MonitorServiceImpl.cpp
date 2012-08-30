/**
 * @file MonitorServiceImpl.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-05
 */

#include "master/MonitorServiceImpl.hpp"
#include <algorithm>
using namespace mapreduce;
using namespace std;

// internal helper class
struct TaskDetailLessThan: public std::binary_function<TaskDetail, TaskDetail, bool>
{
    bool operator() (const TaskDetail &task1, const TaskDetail &task2)
        {
            if (task1.type != task2.type){
                return task1.type < task2.type;
            }
            // equal type, then
            if (task1.status != task2.status){
                return task1.status < task2.status;
            }
            // equal type and status ,then
            return task1.id < task2.id;
        }        
};


int32_t MonitorServiceImpl::getStartTime(const ::Ice::Current&)
{
    return m_db->m_statistics.getStartTime();
}

JobsDetail MonitorServiceImpl::getJobs(const ::Ice::Current&)
{
    JobsDetail details;
    Jobs jobs = m_db->m_jobs.getAllJobs();
    for (int i = 0; i < jobs.size(); i++){
        JobDetail detail;
        detail.id = jobs[i].first;
        detail.createTime = jobs[i].second.createTime;
        detail.finishTime = jobs[i].second.finishTime;
        detail.detached = jobs[i].second.bDetached;
        detail.jobSpec = jobs[i].second.jobSpec;
        detail.status = jobs[i].second.status;
        details.push_back(detail);
    }
    return details;
}

TasksDetail MonitorServiceImpl::getTasks(int32_t jobId, const ::Ice::Current&)
{
    TasksDetail details;
    Tasks tasks = m_db->m_tasks.getAllTasks(jobId);

    for (int i = 0; i < tasks.size(); i++){
        TaskDetail detail;
        detail.id = tasks[i].first;
        detail.type = tasks[i].second.type;
        detail.status = tasks[i].second.status;
        detail.worker = tasks[i].second.worker;
        details.push_back(detail);
    }
    // sort
    std::sort(details.begin(), details.end(), TaskDetailLessThan());
    return details;
}

TasksStatistics MonitorServiceImpl::getTasksStat(int32_t jobId, const ::Ice::Current&)
{
    TasksStatistics stat;
    Tasks tasks = m_db->m_tasks.getAllTasks(jobId);
    int count[4][4];
    memset(count, 0, 16*sizeof(int));
    
    for (int i = 0; i < tasks.size(); i++){
        count[tasks[i].second.type][tasks[i].second.status]++;
    }
    stat.push_back(tasks.size());
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            stat.push_back(count[i][j]);
        }
    }
    
    return stat;
}

int32_t MonitorServiceImpl::getCompletedJobs(const ::Ice::Current&)
{
    return m_db->m_statistics.getCompletedJobs();
}
int32_t MonitorServiceImpl::getCompletedTasks(const ::Ice::Current&)
{
    return m_db->m_statistics.getCompletedMapTasks()+
	m_db->m_statistics.getCompletedReduceTasks()+
	m_db->m_statistics.getCompletedTransTasks();
}

WorkersDetail MonitorServiceImpl::getWorkers(const ::Ice::Current&)
{
    WorkersDetail details;
    Workers workers = m_db->m_workers.getWorkers();
    std::sort(workers.begin(), workers.end(), WorkerLessThan());
    
    for (int i = 0; i < workers.size(); i++){
        WorkerDetail detail;
        detail.addr = workers[i].first;
        detail.workload = workers[i].second.m_heartbeat.workload;
        detail.mapDoneCount = workers[i].second.m_doneMapTasks;
        detail.reduceDoneCount = workers[i].second.m_doneReduceTasks;
        detail.transDoneCount = workers[i].second.m_doneTransTasks;
        vector<int32_t> activeTasksNum = m_db->m_tasks.getInproTasksNum(workers[i].first);
        detail.mapTaskCount = activeTasksNum[1];
        detail.reduceTaskCount = activeTasksNum[2];
        detail.transTaskCount = activeTasksNum[3];
        details.push_back(detail);
    }
    return details;
}

