/**
 * @file    TransTask.hpp
 *  Class TransTask. 
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/08/2007 06:17:01 PM CST
 *
 */

#ifndef  TRANSTASK_FILE_HEADER_INC
#define  TRANSTASK_FILE_HEADER_INC

#include "Worker.hpp"
#include <IceUtil/Thread.h>
#include <common/IceGenerated.hpp>

namespace mapreduce {

/// This class performs transfer task.
class TransTask: public IceUtil::Thread {
public:
    TransTask(const MasterCommand &mc, const std::string &taskDir, Worker *worker);

    void run();

    int readn(int sockfd, char *p, int n);

private:
    MasterCommand m_command;
    std::string m_jobDir;
    Worker *m_worker;

};  // class TransTask

}   // namespace mapreduce

#endif   /* ----- #ifndef TRANSTASK_FILE_HEADER_INC  ----- */

