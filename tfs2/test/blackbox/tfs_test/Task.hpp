/** 
 * @file Task.hpp
 * Test task interface.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */
#ifndef _TASK_HPP
#define _TASK_HPP 1
#include "util/Runnable.hpp"
#include <ctime>

namespace tfs{

    enum BOOL{
        FALSE = 0,
        TRUE = 1
    };
    
    class Task
    {
        int m_id; 
        int m_priority;

        time_t m_startTime;
        time_t m_endTime;

        Runnable* m_runnable;
        /**
         * the function which will be executed by the runnable
         * return TRUE when the test succeeds, FALSE when fail, else error
         */
        RunnableFunc m_func;
        /// guard the m_func installed
        int m_guard;
    public:
        explicit Task(int id, int priority = 0, RunnableType type=THREAD);
        ~Task();

        // call install first before run
        void install(RunnableFunc func);
        bool run();
        bool wait(int &status);
        bool kill();        

        int getID() const;
        void setID(int id);
        int getPriority() const;
        void setPriority(int priority);
        time_t getStartTime() const;
        time_t getEndTime() const;

    private:
        Task(const Task &other);
        const Task& operator= (const Task& other);
    };

    inline int Task::getID()const
    {
        return m_id;
    }

    inline void Task::setID(int id)
    {
        m_id = id;
    }

    inline int Task::getPriority()const
    {
        return m_priority;
    }

    inline void Task::setPriority(int priority)
    {
        m_priority = priority;
    }
    
    
    inline time_t Task::getStartTime()const
    {
        return m_startTime;
    }

    inline time_t Task::getEndTime()const
    {
        return m_endTime;
    }

    inline void Task::install(RunnableFunc func)
    {
        m_func = func;
        m_guard = 0;
    }
}

#endif /* _TASK_HPP */
