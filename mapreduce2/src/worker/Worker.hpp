/**
 * @file    Worker.hpp
 *  Class Worker. 
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/04/2007 12:00:45 AM CST
 *
 */

#ifndef  WORKER_FILE_HEADER_INC
#define  WORKER_FILE_HEADER_INC

#include "mapred/TaskConfigure.hpp"
#include "util/Logger.hpp"
#include "common/IceGenerated.hpp"
#include <Ice/Ice.h>
#include <IceUtil/Mutex.h>

#include <string>
#include <map>
#include <vector>
#include <list>

namespace mapreduce {

/**
 * This class wrap WorkService for convenience, and provide some
 * basic functions for worker utilies.
 */
class Worker {
    Ice::CommunicatorPtr m_ic;
public:
    
    /// Constructor, initialize enviroment.
    Worker(const std::string &iniFile, const std::string& homeDir);
    ~Worker();
    /// Initialize a speicified logger
    void initLogger(const std::string &name, const std::string &homeDir);

    /// Run worker.
    void run();

    /// Get the worker name.
    static std::string name();

    /// Get the worker start up directory name.
    std::string getHomeDir() { return m_homeDir; }
    
    /// Get the worker address.
    const Address address() const { return m_address; }

    /// Record intermediate files transfered for a specified job and partition
    std::map<std::pair<int, int>, std::vector<std::string> > m_mappedFiles;

    /// Show whether a taskId should be killed.
    bool killed(int taskId) const {
        return m_uselessTasks.find(taskId) != m_uselessTasks.end();
    }

    /// Complete task.
    void completeTask(int jobId, int taskId);

    /// Abandon task.
    void abandonTask(int jobId, int taskId);

    /// Add mapped files.
    void addMappedFile(int jobId, int partition, const std::string &path);

    /// Get mapped files.
    void getMappedFiles(int jobId, int partition, std::vector<std::string> &paths);

    /// Stop all active jobs.
    void stopAllJobs();

private:
    /// Get task configure.
    TaskConfigure getConfigure(const MasterCommand &);
    
    /// The worker address.
    Address m_address;        

    /// The worker name.
    static std::string m_name;

    /// Ice proxy to use client service.
    WorkerServicePrx m_service;    

    /// Storage directory
    std::string m_storeDir;

    /// Store taskIds for a certain job
    std::map<int, std::set<int> > m_jobTasks;

    /// Tasks to be killed;
    std::set<int> m_uselessTasks;

    /// Jobs to be cleaned;
    std::vector<int> m_uselessJobs;

    /// Map tasks;
    std::set<int> m_mapTasks;
    
    /// Reduce tasks;
    std::set<int> m_reduceTasks;

    /// Transfer tasks;
    std::set<int> m_transTasks;

    /// Tasks to be reported abandoned;
    std::set<int> m_abandonedTasks;

    /// Tasks to be reported completed;
    std::set<int> m_completedTasks;

    IceUtil::Mutex m_mutex;

    //startup directory
    std::string m_homeDir;
    
}; // class worker

// Define several macros for convience
#ifndef CXX_TEST
#define LOG_DEBUG(x)    {/*cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_DEBUG(Logger::getInstance("mapred_worker"), x) }
#define LOG_INFO(x)     {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_INFO(Logger::getInstance("mapred_worker"), x) }
#define LOG_WARN(x)     {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_WARN(Logger::getInstance("mapred_worker"), x) }
#define LOG_ERROR(x)    {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_ERROR(Logger::getInstance("mapred_worker"), x); Logger::getInstance("mapred_worker").setLogLevel(DEBUG_LOG_LEVEL); }
#define LOG_FATAL(x)    {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_FATAL(Logger::getInstance("mapred_worker"), x) }
#else
    #define LOG_DEBUG(x) 
    #define LOG_INFO(x) 
    #define LOG_WARN(x) 
    #define LOG_ERROR(x) 
    #define LOG_FATAL(x) 
#endif

}  // namespace mapreduce

#endif   /* ----- #ifndef WORKER_FILE_HEADER_INC  ----- */

