/**
 * @file SMapReduce.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2008-03-20
 * @author PengBo
 * @date 2008-08-14
 *
 */

#include "SMapReduce.hpp"
#include "mapred/mapreduce.h"
#include "mapred/TaskConfigure.hpp"
#include "mapred/SetMapper.hpp"
#include "mapred/Sorter.hpp"
#include "mapred/SetReducer.hpp"
#include "mapred/MapReduceException.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace mapreduce;
using namespace mapreduce::api;


class SMapReduceMain{
public:
    void run(MapReduceJob& jobSpec);
};

void SMapReduceMain::run(MapReduceJob& jobSpec)
{
    //setup taskConfigure    
    TaskConfigure configure(jobSpec);

    //setup partition files
    int i, recordCnt;
    vector<string> partitionFiles;
    for ( i = 0 ; i < jobSpec.reduceTaskNum; i++){
        partitionFiles.push_back(boost::lexical_cast<std::string>(i) + ".par");
        if(exists(partitionFiles[i])) remove(path(partitionFiles[i]));
    }

    //setmapper
    SetMapper *setMapper;
    LOG_INFO("Start SetMapper on " << jobSpec.inputFile << " with " << jobSpec.reduceTaskNum << " partitions");
    setMapper = new SetMapper(configure, jobSpec.inputFile, partitionFiles);
    recordCnt = setMapper->map();
    delete setMapper;
    LOG_INFO("End SetMapper return : recordCnt = " << recordCnt );

    //sorting
    string sortFile = "sorted.dat";
    LOG_INFO("Start Sorting...");
    if(exists(sortFile)) remove(path(sortFile));
    Sorter *sorter = new Sorter(configure, sortFile, partitionFiles);
    if(!sorter->sort()){
        LOG_ERROR("Error run sort fail..., bye!");
    }
    delete sorter;
    LOG_INFO("End Sorting!");

    //setreduce
    string resultFile = jobSpec.inputFile + ".result";
    if(exists(resultFile)) remove(path(resultFile));
    LOG_INFO("Start SetReduce...");
    SetReducer *setReducer;
    setReducer = new SetReducer(configure, sortFile, resultFile, true, false);
    recordCnt = setReducer->reduce();
    delete setReducer;
    LOG_INFO("End SetReducer return : recordCnt = " << recordCnt);
}

void analysisCommandLine(const char* cmd, MapReduceJob& jobSpec)
{
    string value;
    if(!strncmp(cmd, "--dll=", strlen("--dll="))){
        value = cmd + strlen("--dll=");
        jobSpec.soFile = value;
    }
    else if(!strncmp(cmd, "--input=", strlen("--input="))){
        value = cmd + strlen("--input=");
        jobSpec.inputFile = value;
    }
}
        

//=======================
int main(int argc, char* argv[])
{
    if( argc < 2 || argc > 4 ) {
        cout << "TFS/MapRed Version 0.1" << endl;
        cout << "   Usage : SMapReduce <jobSpecFile> [--dll=dllFileName] [--input=inputFileName]" << endl << endl;
        cout << "   test run mapreduce job in local machine. load configuration from jobSpecFile, and" << endl; 
        cout << "   optional command line parameters will overload the setting in the spec file." << endl;
        cout << "   output file is inputFileName.result" << endl << endl;
        cout << "       jobSpecFile = job specification file name" << endl << endl;
        cout << "       dllFileName = user's mapreduce dynamic library file name" << endl;
        cout << "       inputFileName= user's input data file" << endl << endl;
        return -1;
    }

    SMapReduceMain* app = new SMapReduceMain();

    try{
        MapReduceJob jobSpec;
        string configureFile = argv[1];
        
        LOG_INFO("load jobSpec file from " << configureFile);
        if( jobSpec.loadConfigure(configureFile) ){
            cerr << "error load spec file from " << configureFile << endl;
            return -1;
        }

        //check optional parameters
        for ( int i = 2 ; i < argc ; i ++) {
            analysisCommandLine(argv[i], jobSpec);
        }
        
        //run the application
        app->run(jobSpec);
    }
    catch(MapReduceException& e){
        LOG_ERROR("catch exception : " << e.what() );
    }

    return 0;
}

