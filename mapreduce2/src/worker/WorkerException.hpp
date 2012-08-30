/**
 * @file    WorkerException.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    2008年03月11日 11时35分47秒 CST
 *
 */

#ifndef  WORKEREXCEPTION_FILE_HEADER_INC
#define  WORKEREXCEPTION_FILE_HEADER_INC

#include <exception>
#include <string>

namespace mapreduce {

/** Internal exceptions in worker. */  
class WorkerException : public std::exception {
public:
    WorkerException() throw() { reason = NULL; }
    ~WorkerException() throw() {}
    WorkerException(const char* str) { reason = str; }
    const char* what() const throw() { return reason; }

private:
    const char *reason;

};  // class WorkerException

}   // namespace mapreduce

#endif   /* ----- #ifndef WORKEREXCEPTION_FILE_HEADER_INC  ----- */

