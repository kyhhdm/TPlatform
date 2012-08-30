/** 
 * @file TaskManager.hpp
 * tasks manager.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-21
 */
#ifndef _TASKMANAGER_HPP
#define _TASKMANAGER_HPP 1
#include <vector>
#include "Task.hpp"

namespace tfs{
    class TaskManager
    {
        std::vector<Task*> m_tasks;
    public:
        ~TaskManager();
        /// @return the task id specified by the task manager
        int addTask(RunnableFunc func, int priority, RunnableType type=THREAD);
        void start();
    };
}


#endif /* _TASKMANAGER_HPP */
