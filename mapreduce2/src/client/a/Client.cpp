/**
 * @file Client.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-04
 */

#include "client/Client.hpp"
#include <iostream>
#include <sstream>
using namespace std;
using namespace mapreduce;

Client::Client(const string& masterHost, int32_t port)
    :m_ic(NULL)
{
    stringstream ss;
    ss << "JobService:tcp -h " << masterHost << " -p " << port;
    try{
        // Initialize ice.
        m_ic = Ice::initialize();
        Ice::ObjectPrx base = m_ic->stringToProxy(ss.str());
        m_service = mapreduce::slice::JobServicePrx::checkedCast(base);
    } catch (Ice::Exception &ex) {
        cerr << "WARN mapreduce::client " << ex << endl;
    }
}

Client::~Client()
{
    if (m_ic) {
        try {
            m_ic->destroy();
        } catch (const std::string& msg) {
            cerr << msg << endl;
        }
    }
}

int Client::create(const mapreduce::api::MapReduceJob &jobSpec)
{
    mapreduce::slice::MapReduceJob job;
    job.inputFile = jobSpec.inputFile;
    job.outputFile = jobSpec.outputFile;
    job.soFile = jobSpec.soFile;
    job.mapTaskNum = jobSpec.mapTaskNum;
    job.reduceTaskNum = jobSpec.reduceTaskNum;
    job.outputReplication = jobSpec.outputReplication;

    job.doLocalCombine = jobSpec.doLocalCombine;
    job.doGroupBySort = jobSpec.doGroupBySort;
    job.doConcatOutputs = jobSpec.doConcatOutputs;    

    job.mapperClass = jobSpec.mapperClass;
    job.reducerClass = jobSpec.reducerClass;
    job.mapperOutKeyClass = jobSpec.mapperOutKeyClass;
    job.mapperOutValueClass = jobSpec.mapperOutValueClass;

    job.reducerOutKeyClass = jobSpec.reducerOutKeyClass;
    job.reducerOutValueClass = jobSpec.reducerOutValueClass;
    job.mapperInKeyClass = jobSpec.mapperInKeyClass;
    job.mapperInValueClass = jobSpec.mapperInValueClass;
    job.mapperRecordReaderClass = jobSpec.mapperRecordReaderClass;
    job.reducerRecordWriterClass = jobSpec.reducerRecordWriterClass;

    int jobId = -1;
    try{
        jobId = m_service->create(job);
    } catch (Ice::Exception &ex) {
        cerr << "WARN mapreduce::client " << ex << endl;
    }
    return jobId;
}

// int Client::wait(int jobId)
// {
//     try{
//         return m_service->wait(jobId);
//     } catch (Ice::Exception &ex) {
//         cerr << "mapreduce::client " << ex << endl;
//         return -1;
//     }    
// }

mapreduce::api::JobDetail Client::getJobDetail(int jobId)
{
    mapreduce::api::JobDetail detail2;
    detail2.id = -1;

    try{
        mapreduce::slice::JobDetail detail1 =  m_service->getJobDetail(jobId);

        detail2.inputFile = detail1.jobSpec.inputFile;
        detail2.outputFile = detail1.jobSpec.outputFile;
        detail2.soFile = detail1.jobSpec.soFile;
        detail2.mapTaskNum = detail1.jobSpec.mapTaskNum;
        detail2.reduceTaskNum = detail1.jobSpec.reduceTaskNum;
        detail2.outputReplication = detail1.jobSpec.outputReplication;

        detail2.doLocalCombine = detail1.jobSpec.doLocalCombine;
        detail2.doGroupBySort = detail1.jobSpec.doGroupBySort;
        detail2.doConcatOutputs = detail1.jobSpec.doConcatOutputs;    

        detail2.mapperClass = detail1.jobSpec.mapperClass;
        detail2.reducerClass = detail1.jobSpec.reducerClass;
        detail2.mapperOutKeyClass = detail1.jobSpec.mapperOutKeyClass;
        detail2.mapperOutValueClass = detail1.jobSpec.mapperOutValueClass;

        detail2.reducerOutKeyClass = detail1.jobSpec.reducerOutKeyClass;
        detail2.reducerOutValueClass = detail1.jobSpec.reducerOutValueClass;
        detail2.mapperInKeyClass = detail1.jobSpec.mapperInKeyClass;
        detail2.mapperInValueClass = detail1.jobSpec.mapperInValueClass;
        detail2.mapperRecordReaderClass = detail1.jobSpec.mapperRecordReaderClass;
        detail2.reducerRecordWriterClass = detail1.jobSpec.reducerRecordWriterClass;
        
        detail2.createTime = detail1.createTime;
        detail2.finishTime = detail1.finishTime;
        detail2.id = detail1.id;
        detail2.status = (mapreduce::api::JobStatus)detail1.status;
        
    } catch (Ice::Exception &ex) {
        cerr << "mapreduce::client " << ex << endl;
    }
    return detail2;
}

// void Client::detach(int jobId)
// {
//     try{
//         m_service->detach(jobId);
//     } catch (Ice::Exception &ex) {
//         cerr << "mapreduce::client " << ex << endl;
//     }
// }

int Client::kill(int jobId)
{
    try{
        return m_service->kill(jobId);
    } catch (Ice::Exception &ex) {
        cerr << "mapreduce::client " << ex << endl;
        return -1;
    }
}

