/* 
 * @(#)mapreduce.h
 * AUTHOR: YangZhifeng
 * CREATE DATE: 04 12月 2007
 * DESCRIPTION: the API of mapreduce system
 */

#ifndef _MAPREDUCE_H
#define _MAPREDUCE_H 1

#include <string>
#include <iostream>
#include <rude/config.h>

namespace rude{
    bool get_conf_bool(rude::Config& conf, bool required, const char* key, bool &value);
    bool get_conf_int(rude::Config& conf, bool required, const char* key, int &value);
    bool get_conf_string(rude::Config& conf, bool required, const char* key, std::string &value);
}

namespace mapreduce
{
    class Client;
    
    namespace api
    {   
        class MapReduceJob
        {
        public:
            /// TFS file as input
            std::string inputFile;
            /// TFS file as output
            std::string outputFile;
            /// the replication number of TFS file 
            int outputReplication;
            
            /// shared object file
            std::string soFile;
            /// the number of map tasks, ingored, use the number of chunks
            int mapTaskNum;
            /// the number of reduce tasks, ignored, use the number of workers
            int reduceTaskNum;

            /// whether do the local combine after map
            bool doLocalCombine;
            /// whether group by sort in reduce
            bool doGroupBySort;
            /// whether concat output files into one file when the whole job done
            bool doConcatOutputs;

            //core settings
            //std::string m_soFile;
            std::string mapperClass;
            std::string reducerClass;
            std::string mapperOutKeyClass;
            std::string mapperOutValueClass;

            //following group are optional
            std::string mapperInKeyClass;
            std::string mapperInValueClass;
            std::string mapperRecordReaderClass;
            std::string reducerOutKeyClass;
            std::string reducerOutValueClass;
            std::string reducerRecordWriterClass;
            
            MapReduceJob()
                {
                    mapTaskNum = -1;
                    reduceTaskNum = -1;
                    doLocalCombine = false;
                    doGroupBySort = true;
                    doConcatOutputs = false;
                    outputReplication = 1;
                }
            
            int loadConfigure(const std::string& jobSpecFile);           
        };

        std::ostream & operator<< (std::ostream &os, MapReduceJob &jobSpec);

        enum JobStatus{
            JS_IDLE,
            JS_INPROGRESS,
            JS_COMPLETED, 
            JS_CANCELLED
        };

        class JobDetail: public MapReduceJob
        {
        public:
            int id;
            int createTime;
            int finishTime;
            JobStatus status;
            JobDetail()
                {
                    id = -1;
                    createTime = 0;
                    finishTime = 0;
                }
        };
        
        class MapReduceService
        {
            mapreduce::Client* m_client;
        public:
            MapReduceService(const std::string &masterHost, int port);
            /** 
             * Create a job and return immediately.
             * 
             * @param job specification of the job
             * @return the job id. The value -1 means failure. A valid job id 
             * should be a integer >= 0.
             */
            int create(const MapReduceJob &jobSpec);
            /** 
             * Wait until the job completed. 
             * If the job has finished or cancelled, return immediatly. 
             *
             * @param jobId the job id returned by `create'
             * @return 0 if the job successfully done, 1 if cancelled, -1 if error ocurrs
             */
            int wait(int jobId);
            /**
             * Get job informations, e.g. job status, job finish time
             * The client use this operation to check the status and other information of the job.
             * The system will release its resources automatically after the job completes
             * 
             * @param jobId the job id returned by `create'
             * @return JobDetail.id is -1 when the job does not exist or error occurs
             */
            JobDetail getJobDetail(int jobId);
            /** 
             * Kill a job in progress. 
             * The system will release the resources.
             * 
             * @param jobId the job id returned by `create'
             * @return 0 if success, -1 if the job does not exist or error occurs
             */
            int kill(int jobId);
        };
    }
}


#endif /* _MAPREDUCE_H */

