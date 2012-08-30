/** 
 * @file Client.hpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-04
 */
#ifndef _CLIENT_HPP
#define _CLIENT_HPP 1

#include "common/IceGenerated.hpp"
#include "client/mapreduce.h"
#include "Ice/Ice.h"

namespace mapreduce{
    class Client
    {
        /// Ice commmunicator
        Ice::CommunicatorPtr m_ic;
        /// Ice proxy to use JobService.
        JobServicePrx m_service;
    public:
        Client(const std::string& masterHost, int32_t port);
        ~Client();
        int create(const mapreduce::api::MapReduceJob &jobSpec);
        //int wait(int jobId);
        mapreduce::api::JobDetail getJobDetail(int jobId);
        //void detach(int jobId);
        int kill(int jobId);
    };
}


#endif /* _CLIENT_HPP */
