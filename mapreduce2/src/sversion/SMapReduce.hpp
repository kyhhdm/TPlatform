/** 
 * @file SMapReduce.hpp
 * 
 *  A simple serial version of MapReduce to test the application's code and debug.
 * 
 * @author Zhifeng YANG
 * @date 2008-03-20
 */
#ifndef _SMAPREDUCE_HPP
#define _SMAPREDUCE_HPP 

#include <iostream>
#include <string>
#include <ctime>

#define LOG_INFO(x) {time_t t= time((time_t*)NULL);             \
        struct tm *now = localtime(&t);                                    \
        std::cerr << "INFO: " << now->tm_mon+1 <<"-" << now->tm_mday << " " << now->tm_hour << ":" \
                  << now->tm_min << ":" << now->tm_sec << " " << x << std::endl; \
    }
#define LOG_ERROR(x) {time_t t= time((time_t*)NULL);                    \
        struct tm *now = localtime(&t);                                    \
        std::cerr << "ERROR: " << now->tm_mon+1 <<"-" << now->tm_mday << " " << now->tm_hour << ":" \
                  << now->tm_min << ":" << now->tm_sec << " "  << x << std::endl; \
        }


#endif /* _SMAPREDUCE_HPP */
