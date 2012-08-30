/**
 * @file    WorkerLogger.hpp
 *  WorkerLogger.
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    2008年03月11日 10时03分24秒 CST
 *
 */

#ifndef  WORKERLOGGER_FILE_HEADER_INC
#define  WORKERLOGGER_FILE_HEADER_INC

#include <util/Logger.hpp>

namespace mapreduce {

/**
  This class offer log service for workers.
  */
class WorkerLogger{
public:
    static Logger get() {
        static bool inited = false;
        if (!inited) {
            // Initialize worker logger.    
            helpers::LogLog::getLogLog()->setInternalDebugging(false);
            SharedAppenderPtr append_1(
                new RollingFileAppender("mapred_worker.log", 1024 * 1024, 1));
            append_1->setName("mapred_worker_append");
            append_1->setLayout(std::auto_ptr<Layout>(new TTCCLayout()));

            Logger::Logger logger = Logger::getInstance("mapred_worker");
            logger.addAppender(append_1);

            inited = true;
        } 
        return Logger::getInstance("mapred_worker");
    }

    static void setLogLevel(LogLevel level) {
        Logger::Logger logger = Logger::getInstance("mapred_worker");
        logger.setLogLevel(level);
    }

};  // class WorkerLogger

// Define several macros for convience
#define LOG_DEBUG(x)    LOG4CPLUS_DEBUG(WorkerLogger::get(), x)
#define LOG_INFO(x)     LOG4CPLUS_INFO(WorkerLogger::get(), x)
#define LOG_WARNING(x)  LOG4CPLUS_WARNING(WorkerLogger::get(), x)
#define LOG_ERROR(x)    LOG4CPLUS_ERROR(WorkerLogger::get(), x)
#define LOG_FATAL(x)    LOG4CPLUS_FATAL(WorkerLogger::get(), x)

}   // namespace mapreduce

#endif   /* ----- #ifndef WORKERLOGGER_FILE_HEADER_INC  ----- */

