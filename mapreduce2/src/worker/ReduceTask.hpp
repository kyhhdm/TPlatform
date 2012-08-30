/**
 * @file    ReduceTask.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/08/2007 06:16:40 PM CST
 *
 */

#ifndef  REDUCETASK_FILE_HEADER_INC
#define  REDUCETASK_FILE_HEADER_INC

#include "Worker.hpp"
#include "common/IceGenerated.hpp"
#include <IceUtil/Thread.h>
#include <string>

using namespace std;

namespace mapreduce {

enum GroupMode{SEQUENCE, HASHTABLE};

class ReduceTask: public IceUtil::Thread {
    public:
        ReduceTask(const TaskConfigure &conf, 
                const MasterCommand mc, const string &taskDir, Worker *worker);

        void run();

        void reduce(const string sortedFile, const vector<string> mappedFiles, GroupMode groupMode);

        bool waitReduce(int pid);

    private:
        // Command
        MasterCommand m_command;
        string m_taskDir;
        Worker *m_worker;
        TaskConfigure m_conf;

    };  // class ReduceTask

}   // namespace mapreduce

#endif   /* ----- #ifndef REDUCETASK_FILE_HEADER_INC  ----- */

