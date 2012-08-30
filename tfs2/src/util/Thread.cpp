/**
 * @file Thread.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */

#include "util/Thread.hpp"
#include <iostream>
using namespace std;
using namespace tfs;

extern "C" void* ThreadFunc(void* arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    tfs::Thread * t = reinterpret_cast<tfs::Thread *>(arg) ;
    static int ret = -1;
    if (t) {
        ret = t->m_func() ;
    }
    return (void*)&ret;
}

Thread::~Thread()
{
    if (m_guard){
        return;
    }    
    // the thread may have finish or unstarted yet, but it doesn't matter
//     cerr << "Thread at " << &m_pthread << " will be detached" << endl;
//     pthread_detach(m_pthread);
//     cerr << "Thread at " << &m_pthread << " detached" << endl;
}

bool Thread::run(RunnableFunc func)
{
    m_func = func;
    
    if ( pthread_create( &m_pthread, NULL, ThreadFunc, reinterpret_cast<void *>(this)) ) {
        cerr << "Error: Thread::run() pthread create" << endl;
        return false;
    }
    m_guard = 0;
    return true;
}

bool Thread::wait(int &status)
{
    if (m_guard){
        return false;
    }
    
    void *stat;

    if ( pthread_join ( m_pthread, &stat ) ) {
        cerr << "Error: Thread::wait() pthread join" << endl;
        return false;
    }
    status = *(int*)stat;
    
    return true;
}

bool Thread::kill()
{
    if (m_guard){
        return false;
    }

    if (pthread_cancel(m_pthread)) {
        cerr << "Error: Thread::kill() pthread cancel" << endl;
        return false;
    }

    void *stat;
    if ( pthread_join ( m_pthread, &stat ) ) {
        cerr << "Error: Thread::wait() pthread join" << endl;
        return false;
    }

    cout << "killed a pthread" << endl;
    return true;
}
