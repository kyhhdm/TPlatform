/** 
 * @file MasterException.hpp
 * Internal exceptions for master.
 * 
 * @author Zhifeng YANG
 * @date 2008-03-12
 */
#ifndef _MASTEREXCEPTION_HPP
#define _MASTEREXCEPTION_HPP 1

#include <exception>
#include <string>

namespace mapreduce {

class MasterException : public std::exception {
public:
    MasterException() throw() { reason = NULL; }
    ~MasterException() throw() {}
    MasterException(const char* str) { reason = str; }
    const char* what() const throw() { return reason; }

protected:
    const char *reason;

};  

class SafeModeException: public MasterException {
public:
    SafeModeException(): MasterException("SafeModeException: No enough workers available"){}
};
    
}   // namespace mapreduce


#endif /* _MASTEREXCEPTION_HPP */
