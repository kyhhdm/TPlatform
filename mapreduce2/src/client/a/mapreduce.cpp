/**
 * @file mapreduce.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-04
 */

#include "client/mapreduce.h"
#include "client/Client.hpp"
#include <unistd.h>
using namespace mapreduce::api;

MapReduceService::MapReduceService(const std::string &masterHost, int port)
{
    m_client = new mapreduce::Client(masterHost, port);
}

int MapReduceService::create(const MapReduceJob &jobSpec)
{
    return m_client->create(jobSpec);
}

int MapReduceService::wait(int jobId)
{
    while(true){
        JobDetail jobDetail = m_client->getJobDetail(jobId);
        if (jobDetail.id == -1){
            return -1;
        }
        else if (jobDetail.status == JS_COMPLETED){
            return 0;
        }
        else if (jobDetail.status == JS_CANCELLED){
            return 1;
        }
        // sleep 5 seconds
        sleep(5);
    }
}

JobDetail MapReduceService::getJobDetail(int jobId)
{
    return m_client->getJobDetail(jobId);
}

int MapReduceService::kill(int jobId)
{
    return m_client->kill(jobId);
}
