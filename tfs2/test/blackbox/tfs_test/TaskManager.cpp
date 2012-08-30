/**
 * @file TaskManager.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-21
 */

#include "TaskManager.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;
using namespace tfs;

struct TaskComp: binary_function<Task*, Task*, bool>
{
    bool operator() (Task* t1, Task* t2)
        {
            return t1->getPriority() < t2->getPriority();
        }
    
};

TaskManager::~TaskManager()
{
    for (int i = 0; i < m_tasks.size(); i++){
        delete m_tasks[i];
    }
}

int TaskManager::addTask(RunnableFunc func, int priority, RunnableType type)
{
    Task *t = new Task(m_tasks.size(), priority, type);
    t->install(func);
    m_tasks.push_back(t);
    return t->getID();
}

void TaskManager::start()
{
    sort(m_tasks.begin(), m_tasks.end(), TaskComp());
    int start = 0;
    for (int i = 0; i < m_tasks.size(); i++){
        if (m_tasks[i]->run()){
            cout << "Test #" << m_tasks[i]->getID() << " started " << endl;
        }
        else{
            cout << "Test #" << m_tasks[i]->getID() << " cannot run" << endl;
        }

        if (i+1 == m_tasks.size() || m_tasks[i]->getPriority() != m_tasks[i+1]->getPriority()){
            cout << "====Results for Priority Group " << m_tasks[i]->getPriority() << "===="<< endl;
            for (int j = start; j <= i; j++){
                int status;
                m_tasks[j]->wait(status);
                cout << "[Test #" << m_tasks[j]->getID() << "] ";
                time_t timediff = m_tasks[j]->getEndTime() - m_tasks[j]->getStartTime();
                cout << timediff << " seconds ";
                switch(status){
                case TRUE:
                    cout << "[PASSED]";
                    break;
                case FALSE:
                    cout << "[FAILED]";
                    break;
                default:
                    cout << "[ERROR]";
                }
                cout << endl;
            }
            start = i+1;
        }
    }
}

