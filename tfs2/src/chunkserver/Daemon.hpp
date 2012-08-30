
/**
 * @file   Daemon.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Jul 29 13:04:19 2007
 * 
 * @brief  base class of Daemon Classes
 * 
 * 
 */


#ifndef _TQC_DAEMON_HPP
#define _TQC_DAEMON_HPP

namespace tfs
{
    class Daemon
    {
    public:
        virtual void operator()()=0;
        int sleepCurThread(int second);
        virtual ~Daemon();
    };
}

#endif
