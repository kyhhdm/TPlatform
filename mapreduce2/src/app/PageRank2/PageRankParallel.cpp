/**
 * @file PageRankParallel.cpp
 *
 * @author Chen Rishan
 * @date 2008-06-27
 * */

#include "mapreduce.h"
#include <rude/config.h>
#include <iostream>
#include <string>
using namespace std;
using namespace mapreduce::api;

void usage()
{
    cout << "Usage: pagerank_mapred commit <master_host> <master_port> <job_spec_file> [--detach]" << endl;
    cout << "       pagerank_mapred kill <master_host> <master_port> <job_id>" << endl;
}

int job_commit(const string& masterHost, int masterPort, const string& jobSpecFile, bool bDetach)
{
    MapReduceJob jobSpec;
    // load job specifation from ini config file
    rude::Config conf;
    string first_value;
    string latter_value;
    string first_mapper;
    string latter_mapper;
    string first_reader;
    string latter_reader;

    if (!conf.load(jobSpecFile.c_str())){
        cerr << "ERROR: load job specification file:" << jobSpecFile << endl;
        return -1;
    }
    conf.setSection("job");
    if (!get_conf_string(conf, true, "input_file", jobSpec.inputFile)){
        return -1;
    }
    if (!get_conf_string(conf, true, "output_file", jobSpec.outputFile)){
        return -1;
    }
    if (!get_conf_string(conf, true, "so_file", jobSpec.soFile)){
        return -1;
    }

    if (!get_conf_string(conf, true, "first_mapper_class", first_mapper)){
        return -1;
    }
    if (!get_conf_string(conf, true, "latter_mapper_class", latter_mapper)){
        return -1;
    }
    if (!get_conf_string(conf, true, "reducer_class", jobSpec.reducerClass)){
        return -1;
    }
    if (!get_conf_string(conf, true, "mapper_out_key_class", jobSpec.mapperOutKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, true, "mapper_out_value_class", jobSpec.mapperOutValueClass)){
        return -1;
    }

    if (!get_conf_bool(conf, false, "do_local_combine", jobSpec.doLocalCombine)){
        return -1;
    }
    if (!get_conf_bool(conf, false, "do_group_by_sort", jobSpec.doGroupBySort)){
        return -1;
    }
    if (!get_conf_bool(conf, false, "do_concat_outputs", jobSpec.doConcatOutputs)){
        return -1;
    }

    if (!get_conf_int(conf, false, "reduce_task_num", jobSpec.reduceTaskNum)){
        return -1;
    }
    if (!get_conf_int(conf, false, "output_replication", jobSpec.outputReplication)){
        return -1;
    }

    if (!get_conf_string(conf, false, "mapper_in_key_class", jobSpec.mapperInKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "first_mapper_in_value_class", first_value)){
        return -1;
    }
    if (!get_conf_string(conf, false, "latter_mapper_in_value_class", latter_value)){
        return -1;
    }
    if (!get_conf_string(conf, false, "first_mapper_record_reader_class", first_reader)){
        return -1;
    }
    if (!get_conf_string(conf, false, "latter_mapper_record_reader_class", latter_reader)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_out_key_class", jobSpec.reducerOutKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_out_value_class", jobSpec.reducerOutValueClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_record_writer_class", jobSpec.reducerRecordWriterClass)){
        return -1;
    }

    
    MapReduceService service(masterHost, masterPort);
    
    char version = 0;
    string output = jobSpec.outputFile;
    for(int i = 0; i < 6; i ++){
        if(i == 0){
            version = '0';
            jobSpec.mapperInValueClass = first_value;
            jobSpec.mapperClass = first_mapper;
            jobSpec.mapperRecordReaderClass = first_reader;
            jobSpec.outputFile = output + version;
        }
        else{
            version = '0' + i - 1;
            jobSpec.mapperInValueClass = latter_value;
            jobSpec.inputFile = output + version;
            version = '0' + i;
            jobSpec.outputFile = output + version;
            jobSpec.mapperClass = latter_mapper;
            jobSpec.mapperRecordReaderClass = latter_reader;
        }
        cout << jobSpec << endl;
        int jobId = service.create(jobSpec);
        cout << "Job ID: " << jobId << endl;
        if (jobId < 0){
            return -1;
        }
    
        if (!bDetach){
            int ret = service.wait(jobId);
            if (ret == 0){
                cout << "Job successfully done." << endl;
                JobDetail jobDetail = service.getJobDetail(jobId);
                cout << "CreateTime:" << ctime((time_t*)&jobDetail.createTime);
                cout << "FinishTime:" << ctime((time_t*)&jobDetail.finishTime);
                double diffTime = difftime(jobDetail.finishTime, jobDetail.createTime);
                cout << "TotalTime:" << diffTime << " seconds" << endl;;
            }
            else if (ret == 1){
                cout << "Job was abandoned. " << endl;
                JobDetail jobDetail = service.getJobDetail(jobId);
                cout << "CreateTime:" << ctime((time_t*)&jobDetail.createTime);
                cout << "FinishTime:" << ctime((time_t*)&jobDetail.finishTime);
                double diffTime = difftime(jobDetail.finishTime, jobDetail.createTime);
                cout << "TotalTime:" << diffTime << " seconds" << endl;;
            }
            else{
                cout << "Job done with unkown errors " << endl;
            }
        
        }
    }
    return 0;
}

int job_kill(const string& masterHost, int masterPort, int jobId)
{
    MapReduceService service(masterHost, masterPort);
    service.kill(jobId);

    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 5 || argc > 6){
        usage();
        return 1;
    }
    if (strcmp(argv[1], "commit") == 0){   
        string masterHost(argv[2]);
        int masterPort = atoi(argv[3]);
        string jobSpecFile(argv[4]);
        bool bDetach = false;
        if (argc == 6 && strcmp(argv[5], "--detach")==0){
            bDetach = true;
        }
        return job_commit(masterHost, masterPort, jobSpecFile, bDetach);
    }
    else if (strcmp(argv[1], "kill") == 0){
        string masterHost(argv[2]);
        int masterPort = atoi(argv[3]);
        int jobId = atoi(argv[4]);
        return job_kill(masterHost, masterPort, jobId);
    }
    else {
        usage();
        return 1;
    }
}

