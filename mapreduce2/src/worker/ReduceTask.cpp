/**
 * @file	ReduceTask.cpp
 *  Implementation of ReduceTask class.
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/08/2007 06:16:47 PM CST
 *
 */

#include "Worker.hpp"
#include "ReduceTask.hpp"
#include "mapred/SetReducer.hpp"
#include "mapred/Sorter.hpp"
#include <tfs/tfs.h>

#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <ctime>

using namespace mapreduce;
namespace fs = boost::filesystem;

#define LOG_RT_PREFIX "ReduceTask(" <<m_command.jobId <<"#" <<m_command.taskId <<"): "

ReduceTask::ReduceTask(const TaskConfigure &conf, 
        MasterCommand mc, const string &taskDir, Worker *worker) {
    m_command = mc;
    m_taskDir = taskDir;
    m_worker = worker;
    m_conf = conf;
}

void ReduceTask::reduce(const string sortedFile, const vector<string> mappedFiles, GroupMode groupMode) {
    try {
        Logger::getInstance("mapred_worker").removeAllAppenders();
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(
                new RollingFileAppender(m_taskDir + ".log", 4 * 1024 * 1024, 5));
        append_1->setName(m_taskDir);
        std::string pattern = "%D %p - %m\n";
        append_1->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
        Logger::getInstance("mapred_worker").addAppender(append_1);

        //if(groupMode == SEQUENCE){
            // Sort
            LOG_DEBUG(LOG_RT_PREFIX <<"Begin sorting.");
            string tmpDirForSort = m_taskDir + "/_tmp_sort_";
            Sorter s(m_conf, sortedFile, mappedFiles, tmpDirForSort);
            if (!s.sort()) {
                LOG_ERROR(LOG_RT_PREFIX <<"Sort Error.") 
                exit(1);
            }
            LOG_DEBUG(LOG_RT_PREFIX <<"End Sorting.");

            // Reduce
            tfs::api::FileSystem tfs;
            LOG_DEBUG(LOG_RT_PREFIX <<"Begin reducing.");
            string outputFile = m_command.outputFile + "/" + boost::lexical_cast<string>(m_command.partition);
            string tmpOutputFile = outputFile + ".tmp_" + boost::lexical_cast<string>(clock());
            SetReducer *sr = new SetReducer(m_conf, sortedFile, tmpOutputFile, false, false);
            int r = sr->reduce();
            delete sr;
            //fs::remove(sortedFile);
            if (tfs.existFile(outputFile)) {
                LOG_DEBUG(LOG_RT_PREFIX <<"Remove existed tfs file " <<outputFile);
                tfs.removeFile(outputFile);
            }
            tfs.renameFile(tmpOutputFile, outputFile);
            LOG_DEBUG(LOG_RT_PREFIX <<"Rename " <<tmpOutputFile <<" to " <<outputFile);
            //LOG_DEBUG(LOG_RT_PREFIX <<"End reducing.");
            if (r < 0) {
                LOG_ERROR(LOG_RT_PREFIX <<"Reduce partition " <<m_command.partition <<" Error.");
                exit(1);
            } else {
                LOG_INFO(LOG_RT_PREFIX <<"Reduce partition " <<m_command.partition <<" Completed, " <<r <<" records in total.");
                exit(0);
            }
        //}//end of if
        /*
        if(groupMode == HASHTABLE){
            // Reduce
            tfs::api::FileSystem tfs;
            HasherReducer hr(lib.reducerLib(), lib.hasherLib(), lib.writerLib(), m_command.jobId, m_command.taskId);      
            LOG_DEBUG(LOG_RT_PREFIX <<"Begin reducing.");
            string outputFile = m_command.outputFile + "/" + boost::lexical_cast<string>(m_command.partition);
            string tmpOutputFile = outputFile + ".tmp_" + boost::lexical_cast<string>(clock());
            int r = hr.reduce(tmpOutputFile, sortedFile, true);
            fs::remove(sortedFile);
            if (tfs.existFile(outputFile)) {
                LOG_DEBUG(LOG_RT_PREFIX <<"Remove existed tfs file " <<outputFile);
                tfs.removeFile(outputFile);
            }
            tfs.renameFile(tmpOutputFile, outputFile);
            LOG_DEBUG(LOG_RT_PREFIX <<"Rename " <<tmpOutputFile <<" to " <<outputFile);
            //LOG_DEBUG(LOG_RT_PREFIX <<"End reducing.");
            if (r < 0) {
                LOG_ERROR(LOG_RT_PREFIX <<"Reduce partition " <<m_command.partition <<" Error.");
                exit(1);
            } else {
                LOG_INFO(LOG_RT_PREFIX <<"Reduce partition " <<m_command.partition <<" Completed.");
                exit(0);
            }
        }//end of if
        */
    } catch (exception &ex) {
        LOG_ERROR(LOG_RT_PREFIX <<"Catch " <<ex.what() <<endl)
        exit(1);
    } catch (...) {
        LOG_ERROR(LOG_RT_PREFIX <<"Catch unknown exception")
        exit(1);
    }
}

bool ReduceTask::waitReduce(int pid) {
    int r, exitcode, nsec = 0;
    while (true) {
        // check process status
        if ((r = waitpid(pid, &exitcode, WNOHANG)) < 0) {
            LOG_ERROR(LOG_RT_PREFIX <<"Wait " <<m_command.taskId <<" error.");
            kill(pid, 9);
            waitpid(pid, NULL, 0);
            return false;
        } else if (r > 0 && WIFEXITED(exitcode) && WEXITSTATUS(exitcode) == 0) {
            LOG_DEBUG(LOG_RT_PREFIX <<"Reduce return OK.");
            if (m_worker != NULL)
                m_worker->completeTask(m_command.jobId, m_command.taskId);
            return true;
        } else if (r > 0) {
            if (!WIFEXITED(exitcode)) {
                LOG_ERROR(LOG_RT_PREFIX <<"Reduce process exited abnormally.")
            } else {
                LOG_ERROR(LOG_RT_PREFIX <<"Reduce return error code " 
                        <<WEXITSTATUS(exitcode));
            }
            return false;
        }

        // check whether this task is abandoned
        if (m_worker->killed(m_command.taskId)) {
            LOG_INFO(LOG_RT_PREFIX <<"Job cancelled, abandon task.");
            kill(pid, 9);
            waitpid(pid, NULL, 0);
            if (m_worker != NULL)
                m_worker->abandonTask(m_command.jobId, m_command.taskId);
            return true;
        }

        //sleep(1);
        IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(1));
        ++ nsec;
        if (nsec % 60 == 0) {
            LOG_DEBUG(LOG_RT_PREFIX <<"Reduce wait reach " <<nsec / 60 << " minutes.");
        }
        if (nsec > 60 * 60) {
            LOG_WARN(LOG_RT_PREFIX <<"Reduce wait exceed 60 minutes, terminated.");
            kill(pid, 9);
            waitpid(pid, NULL, 0);
            return false;
        }
    } //while
}

void ReduceTask::run() {
    LOG_INFO(LOG_RT_PREFIX <<"Reduce partition " <<m_command.partition);

    int nretry = 0;
    string outFile = m_command.outputFile + "/" + boost::lexical_cast<string>(m_command.partition);
    vector<string> mappedFiles;
    m_worker->getMappedFiles(m_command.jobId, m_command.partition, mappedFiles);
    string sortedFile = m_taskDir + "/" + boost::lexical_cast<string>(m_command.partition) 
        + "_sorted";

    for (int round = 0; round < nretry + 1; ++round) {
        // Clear enviroment
        if (fs::exists(m_taskDir)) {
            fs::remove_all(m_taskDir);
            LOG_DEBUG("Remove existed directory " <<m_taskDir);
        }
        fs::create_directory(m_taskDir);

        if(!fs::is_directory(fs::path(m_taskDir))){
            LOG_ERROR(LOG_RT_PREFIX <<"create_directory " <<m_taskDir <<" error.");
            IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
            continue;
        }

        int pid = fork();
        int r, exitcode;
        if (pid == 0) {
            // child process

            string confString;
            m_conf.writeToString(confString);

            //char pathBuffer[512];
            //char* currentPath = getcwd(pathBuffer, 512);
            //string execFileName = string(currentPath)  + "/bin/mapred_reducer";
            string execFileName = m_worker->getHomeDir() + "/mapred_reducer";
            string logFileName = m_taskDir + "/../" + boost::lexical_cast<string>(m_command.jobId);

            string mappedFileString;
            for (int i = 0 ; i < mappedFiles.size(); i++){
                mappedFileString += mappedFiles[i];
                mappedFileString += "\t";
            }

            //test fork-safety
            int ret = execl(execFileName.c_str(), execFileName.c_str(),
                m_taskDir.c_str(),confString.c_str(),
                sortedFile.c_str(), mappedFileString.c_str(),
                m_command.doGroupBySort?"1":"0",
                m_command.outputFile.c_str(), 
                (boost::lexical_cast<string>(m_command.partition)).c_str(),
                logFileName.c_str(),
                NULL);

            if(ret == -1){
                LOG_ERROR(LOG_RT_PREFIX <<"Execl ReduceTask" <<m_command.taskId <<" error.");
                perror("MapRed-ReduceTask");
            }
            return;
        }else if(pid < 0){
            LOG_ERROR(LOG_RT_PREFIX <<"Fork " <<m_command.taskId <<" error.");
            IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
            continue;
        } else {
            // parent process, wait child
            if (waitReduce(pid))
                return;
        } 
    } 
    LOG_INFO(LOG_RT_PREFIX <<"Abandon task after " <<nretry <<" retries.");
    if (m_worker != NULL)
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
}
