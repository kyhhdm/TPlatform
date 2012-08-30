/**
 * @file Task.cpp
 * implementation of Task.hpp.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */

#include "Task.hpp"
#include "util/Thread.hpp"
#include "util/Process.hpp"

using namespace tfs;

Task::Task(int id, int priority, RunnableType type)
    :m_id(id), m_priority(priority), m_runnable(NULL), m_guard(1)
{
    if (type == THREAD){
        m_runnable = new Thread();
    }
    else{                       // PROCESS
        m_runnable = new Process();
    }
}

Task::~Task()
{
    delete m_runnable;
}

bool Task::run()
{
    if (m_guard){
        return false;
    }
    
    bool ret = false;
    // install the runnable function
    m_startTime = time(NULL);
    ret = m_runnable->run(m_func);
    return ret;
}

bool Task::wait(int &status)
{
    if (m_guard){
        return false;
    }
    bool ret = m_runnable->wait(status);
    m_endTime = time(NULL);
    return ret;
}

bool Task::kill()
{
    if (m_guard){
        return false;
    }
    
    bool ret= m_runnable->kill();
    m_endTime = time(NULL);
    return ret;
}
