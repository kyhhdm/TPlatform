/**
 * @file MapReduceJob.cpp
 * A sample application to use mapreduce client.
 * This application commits a job specification to the mapreduce system.
 * 
 * @author Zhifeng YANG
 * @date 2007-12-04
 */

#include "mapred/mapreduce.h"
#include <rude/config.h>
#include <iostream>
#include <string>
using namespace std;
using namespace mapreduce::api;

void usage()
{
    
    cout << "TFS/MapRed Version 0.1" << endl;
    cout << "   Usage: mapred_job commit <job_spec_file> <job_name> [--detach] [--input=inputFile] [--output=outputFile]" << endl;
    cout << "          mapred_job kill <job_id>" << endl << endl;
    cout << "   job controller to commit a user job, or kill a running user job." << endl << endl;
    cout << "       job_spec_file : job specification file " << endl;
    cout << "       job_name      : job directory name pushed to the cluster." << endl;
    cout << "       job_id        : system returned job id which is the identity of the running job." << endl;
    cout << "       --detach      : run the job in the background" << endl;
    cout << "       --dllFileName : user's mapreduce dynamic library file name" << endl;
    cout << "       --inputFileName: user's input data file" << endl << endl;

}

bool setFromFile(const string& path, string& ip, string& port, string& homeDir, string& userName)
{ 
    rude::Config conf;
    if (!conf.load(path.c_str())){
        cout << "LoadConfigurationError: load" << path << "failed!" << endl;
        return false;
    }
    conf.setSection("mapred master");
    ip = conf.getStringValue("master_ip");
    port = conf.getStringValue("master_port");

    conf.setSection("user");
    homeDir = conf.getStringValue("home_dir");
    userName = conf.getStringValue("user_name");
    return (ip != "" && port != "" && homeDir != "" && userName != "");
}


int job_commit(const string& masterHost, int masterPort, MapReduceJob& jobSpec, bool bDetach)
{
    
    cout << jobSpec << endl;
    cout << "masterHost:masterPort as " << masterHost << ":" << masterPort << endl;
    
    MapReduceService service(masterHost, masterPort);
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
    return 0;
}

int job_kill(const string& masterHost, int masterPort, int jobId)
{
    MapReduceService service(masterHost, masterPort);
    service.kill(jobId);

    return 0;
}

int loadMasterConfigure(string& ip, string& port, string& homeDir, string& userName)
{
    string homedir = getenv("HOME");
    if (!setFromFile("tfs_client.ini", ip, port, homeDir, userName) 
        && !setFromFile(homedir + "/.tfs_client.ini", ip, port, homeDir, userName)
        && !setFromFile("/etc/tfs_client.ini", ip , port, homeDir, userName)) {
            
        cout << "LoadConfigurationError: load tfs_client.ini error." << endl;
        return -1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 2 ) {
        usage();
        return 1;
    }
    
    if (strcmp(argv[1], "commit") == 0){   
        
        if (argc < 4) {
            usage();
            return -1;
        }
        
        // Get configuration.
        string ip, port, homeDir, userName;
        if(loadMasterConfigure(ip, port, homeDir, userName)){
            return -1;
        }
        
        // Load jobSpec
        MapReduceJob jobSpec;

        string jobSpecFile(argv[2]);
        string jobName(argv[3]);
        
        if( jobSpec.loadConfigure(jobSpecFile) ){
            return -1;
        }
        
        //optional parameters
        bool bDetach = false;
        string value;
        for (int i = 4; i < argc ; i++){  
            char* cmd = argv[i];
            if (!strcmp(cmd, "--detach")){
                bDetach = true;
            }
            else if(!strncmp(cmd, "--output=", strlen("--output="))){
                value = cmd + strlen("--output=");
                jobSpec.outputFile = value;
            }
            else if(!strncmp(cmd, "--input=", strlen("--input="))){
                value = cmd + strlen("--input=");
                jobSpec.inputFile = value;
            }
        
        }

        //overcheck the file path in TFS
        if( jobSpec.soFile[0] != '/'){
            jobSpec.soFile = homeDir + "/user/" + userName + "/" + jobName + "/" + jobSpec.soFile;
        }
        if( jobSpec.outputFile[0] != '/'){
            jobSpec.outputFile = "/home/" + userName + "/" + jobSpec.outputFile;
        }
        if( jobSpec.inputFile[0] != '/'){
            jobSpec.inputFile = "/home/" + userName + "/" + jobSpec.inputFile;
        }
        
        return job_commit(ip, atoi(port.c_str()), jobSpec, bDetach);
    }
    else if (strcmp(argv[1], "kill") == 0){
        
        if (argc != 3 ) {
            usage();
            return -1;
        }
        
        string ip, port, homeDir, userName;
        loadMasterConfigure(ip, port, homeDir, userName);
        int jobId = atoi(argv[2]);
        return job_kill(ip, atoi(port.c_str()), jobId);
    }
    else {
        usage();
        return 1;
    }
}
