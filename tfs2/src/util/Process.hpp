/** 
 * @file Process.hpp
 * a process implements Runnable interface.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */
#ifndef _PROCESS_HPP
#define _PROCESS_HPP 1

#include "util/Runnable.hpp"
#include <sys/types.h>

namespace tfs{
    class Process: public Runnable
    {
        pid_t m_pid;
    public:

        Process();
        virtual ~Process();

        bool run(RunnableFunc func);
        bool wait(int &status);
        bool kill();

    };

    inline Process::Process()
        :m_pid(0)
    {
    }
}


#endif /* _PROCESS_HPP */
