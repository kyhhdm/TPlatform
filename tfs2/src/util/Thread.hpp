/** 
 * @file Thread.hpp
 * thread implemented using pthread.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */
#ifndef _THREAD_HPP
#define _THREAD_HPP 1
#include <pthread.h>
#include "util/Runnable.hpp"

namespace tfs{
    extern "C" void* ThreadFunc(void* arg);

    class Thread: public Runnable
    {
        pthread_t m_pthread;
        int m_guard;
    public:
        RunnableFunc m_func;

        Thread();
        virtual ~Thread();

        bool run(RunnableFunc func);
        bool wait(int &status);
        bool kill();
    private:
        // forbid copy and assignment
        Thread(const Thread&);
        const Thread& operator=(const Thread&);

    };
    inline Thread::Thread()
        :m_guard(1)
    {
    }
    
}


#endif /* _THREAD_HPP */
