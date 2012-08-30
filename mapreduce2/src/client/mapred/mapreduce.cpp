/**
 * @file mapreduce.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-12-04
 */

#include "mapreduce.h"
#include "Client.hpp"
#include <unistd.h>
#include <rude/config.h>
#include <iostream>
#include <string>
using namespace std;
using namespace mapreduce::api;

bool rude::get_conf_bool(rude::Config& conf, bool required, const char* key, bool &value)
{
    string tmp;
    if (conf.exists(key)){
        tmp = conf.getStringValue(key);
        if (tmp == "yes" || tmp == "Yes"
            || tmp == "YES" || tmp == "true"
            || tmp == "y"){
            value = true;
        }
        else if (tmp == "no"|| tmp == "No"
                 || tmp == "NO" || tmp == "false"
                 || tmp == "n"){
            value = false;
        }
        else {
            cerr << "ERROR: invalid value for bool key " << key << ", use `yes' or `no'" << endl;
            return false;
        }
    } else if (required){
        cerr << "ERROR: parameter " << key << " is required" << endl;
        return false;
    }
    
    return true;
}

bool rude::get_conf_int(rude::Config& conf, bool required, const char* key, int &value)
{
    if (conf.exists(key)){
        value = conf.getIntValue(key);
    }
    else if (required) {
        cerr << "ERROR: parameter " << key << " is required" << endl;
        return false;
    }
    return true;
}

bool rude::get_conf_string(rude::Config& conf, bool required, const char* key, string &value)
{
    if (conf.exists(key)){
        value = conf.getStringValue(key);
    }
    else if (required) {
        cerr << "ERROR: parameter " << key << " is required" << endl;
        return false;
    }
    return true;
}

ostream & mapreduce::api::operator<< (ostream &os, MapReduceJob &jobSpec)
{
    os << "input_file:" <<  jobSpec.inputFile << endl;
    os << "output_file:" <<  jobSpec.outputFile << endl;
    os << "so_file:" <<  jobSpec.soFile << endl;
    os << "mapper_class:"<<  jobSpec.mapperClass << endl;
    os << "reducer_class:" <<  jobSpec.reducerClass << endl;
    os << "mapper_out_key_class:" << jobSpec.mapperOutKeyClass << endl;
    os << "mapper_out_value_class:"<< jobSpec.mapperOutValueClass << endl;
    os << "do_local_combine:"<< jobSpec.doLocalCombine << endl;
    os <<"do_group_by_sort:"<< jobSpec.doGroupBySort<< endl;
    os <<"do_concat_outputs:"<< jobSpec.doConcatOutputs << endl;
    os <<"reduce_task_num:"<< jobSpec.reduceTaskNum << endl;
    os <<"output_replication:"<< jobSpec.outputReplication << endl;
    os <<"mapper_in_key_class:"<< jobSpec.mapperInKeyClass << endl;
    os <<"mapper_in_value_class:"<< jobSpec.mapperInValueClass << endl;
    os <<"mapper_record_reader_class:"<< jobSpec.mapperRecordReaderClass << endl;
    os <<"reducer_out_key_class:"<< jobSpec.reducerOutKeyClass << endl;
    os <<"reducer_out_value_class:"<< jobSpec.reducerOutValueClass << endl;
    os <<"reducer_record_writer_class:"<< jobSpec.reducerRecordWriterClass << endl;
    return os;
}

int MapReduceJob::loadConfigure(const string& jobSpecFile)
{
    // load job specifation from ini config file
    rude::Config conf;
    if (!conf.load(jobSpecFile.c_str())){
        cerr << "ERROR: load job specification file:" << jobSpecFile << endl;
        return -1;
    }
    conf.setSection("job");
    if (!get_conf_string(conf, true, "input_file", inputFile)){
        return -1;
    }
    if (!get_conf_string(conf, true, "output_file", outputFile)){
        return -1;
    }
    if (!get_conf_string(conf, true, "so_file", soFile)){
        return -1;
    }

    if (!get_conf_string(conf, true, "mapper_class", mapperClass)){
        return -1;
    }
    if (!get_conf_string(conf, true, "reducer_class", reducerClass)){
        return -1;
    }
    if (!get_conf_string(conf, true, "mapper_out_key_class", mapperOutKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, true, "mapper_out_value_class", mapperOutValueClass)){
        return -1;
    }

    if (!get_conf_bool(conf, false, "do_local_combine", doLocalCombine)){
        return -1;
    }
    if (!get_conf_bool(conf, false, "do_group_by_sort", doGroupBySort)){
        return -1;
    }
    if (!get_conf_bool(conf, false, "do_concat_outputs", doConcatOutputs)){
        return -1;
    }

    if (!get_conf_int(conf, false, "reduce_task_num", reduceTaskNum)){
        return -1;
    }
    if (!get_conf_int(conf, false, "output_replication", outputReplication)){
        return -1;
    }

    if (!get_conf_string(conf, false, "mapper_in_key_class", mapperInKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "mapper_in_value_class", mapperInValueClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "mapper_record_reader_class", mapperRecordReaderClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_out_key_class", reducerOutKeyClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_out_value_class", reducerOutValueClass)){
        return -1;
    }
    if (!get_conf_string(conf, false, "reducer_record_writer_class", reducerRecordWriterClass)){
        return -1;
    }
    return 0;
}

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
