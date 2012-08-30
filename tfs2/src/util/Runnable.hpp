/** 
 * @file Runnable.hpp
 * interface for a runnable object.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-19
 */
#ifndef _RUNNABLE_HPP
#define _RUNNABLE_HPP 1

namespace tfs{
    enum RunnableType{
        THREAD,
        PROCESS
    };

    typedef int (*RunnableFunc)(void);
    /** 
     * a runnable is a object which can be scheduled by the operating system
     * 
     */
    class Runnable
    {
    public:
        virtual ~Runnable()
            {
            }
        
        /** 
         * go go go 
         * 
         * 
         * @return  success or fail
         */
        virtual bool run(RunnableFunc func) = 0;
        /** 
         * wait for the runnable to stop and get the return value
         * 
         * @param status [out] the return value of func
         * 
         * @return success or fail
         */
        virtual bool wait(int &status) = 0;
        /** 
         * kill the runnable if it is running
         * DO NOT USE IT !
         * May lose resources. Just for simulating crash.
         * 
         * @return success or fail
         */
        virtual bool kill() = 0;
    };
}


#endif /* _RUNNABLE_HPP */
