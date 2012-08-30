/**
 * @file    MapTask.hpp
 *  Class MapTask. 
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/08/2007 06:18:27 PM CST
 *
 */

#ifndef  MAPTASK_FILE_HEADER_INC
#define  MAPTASK_FILE_HEADER_INC

#include "Worker.hpp"
#include "common/IceGenerated.hpp"
#include <string>
#include <IceUtil/Thread.h>

namespace mapreduce {

using std::string;

/// This class performs map task.
class MapTask: public IceUtil::Thread {
public:
    MapTask(const TaskConfigure &conf,
            const MasterCommand &mc, const string &taskDir, Worker *worker);

    void run();

    void map(const string &path, const string &dir);

    bool getFile(const MasterCommand &mc, string &path);

private:
    MasterCommand m_command;
    string m_taskDir;
    Worker *m_worker;
    TaskConfigure m_conf;
};  // class MapperTask

}   // namespace mapreduce
#endif   /* ----- #ifndef MAPTASK_FILE_HEADER_INC  ----- */

