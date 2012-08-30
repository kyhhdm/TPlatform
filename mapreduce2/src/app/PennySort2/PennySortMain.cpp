/**
 * @file PennySortMain.cpp
 *
 * @author PengBo
 * @date 2007-12-18
 * */

#include "TaskConfigure.hpp"
#include "SetMapper.hpp"
#include "Sorter.hpp"
#include "SetReducer.hpp"
#include "MapReduceException.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"
#include <time.h>

using namespace std;
using namespace boost::filesystem;
using namespace mapreduce;

class PennySortMain{
public:
    void run(char* dllFile, char* inputFile, int reducerNumber = 1);
};

void PennySortMain::run(char* dllFile, char* inputFile, int reducerNumber)
{
    TaskConfigure configure;
    int recordCnt, i;
    time_t clock;
    

    //1. setup 
    configure.setDllName(dllFile);
    configure.setMapperClass("PennySortMapper");
    configure.setReducerClass("PennySortReducer");
    configure.setMapperOutKeyClass("PennyRecordKey");
    configure.setMapperOutValueClass("PennyRecordValue");
    
    //set up mapper reader class
    //configure.setMapperRecordReaderClass("TianwangRawFileFeeder");
    configure.setMapperInKeyClass("PennyRecordKey");
    configure.setMapperInValueClass("PennyRecordValue");

    //set up reducer writer class
    //configure.setReducerRecordWriterClass("TextFileWriter<char*,int>");
    configure.setReducerOutKeyClass("PennyRecordKey");
    configure.setReducerOutValueClass("PennyRecordValue");

    //2. prepare run mapper
    vector<string> partitionFiles;
    for (i = 0; i< reducerNumber; i++){
        string partitionFileName = boost::lexical_cast<std::string>(i);
        partitionFiles.push_back(partitionFileName + ".par");
        if(exists(partitionFiles[i])) remove(path(partitionFiles[i]));
    }

    clock = time(NULL);
    //if(!exists(partitionFiles[0])){
        SetMapper *setMapper;
        setMapper = new SetMapper(configure, inputFile, partitionFiles);
        recordCnt = setMapper->map();
        delete setMapper;
        cout << "run setmapper return : recordCnt = " << recordCnt << endl;
    //}
    cout << "map use time : " << time(NULL) - clock << "s" << endl;

    
    //3. sort
    clock = time(NULL);

    for (i = 0; i < reducerNumber ; i++){
        string sortFile = "sorted_";
        sortFile += boost::lexical_cast<std::string>(i);
        
        if(exists(sortFile)) remove(path(sortFile));
        vector<string> sortInputFiles;

        sortInputFiles.push_back(partitionFiles[i]);
        //if(!exists(sortFile)){
            Sorter *sorter = new Sorter(configure, sortFile, sortInputFiles);
            if(!sorter->sort()){
                cout << "run sort fail..., bye!" << endl;
            }
            delete sorter;
        //}
    }
    cout << "sort use time : " << time(NULL) - clock << "s" << endl;

    //4. reducer
    clock = time(NULL);
    string resultFile = "result.dat";
    if(exists(resultFile)) remove(path(resultFile));
    
    for(i = 0; i < reducerNumber ; i++){
        SetReducer *setReducer;
        string sortFile = "sorted_";
        sortFile += boost::lexical_cast<std::string>(i);
        
        setReducer = new SetReducer(configure, sortFile, resultFile, true, false);
        recordCnt = setReducer->reduce();
        delete setReducer;
        
        cout << "run setreducer " << i <<" return : recordCnt = " << recordCnt << endl;
    }
    
    cout << "reduce use time : " << time(NULL) - clock << "s" << endl;
}


//=======================
int main(int argc, char* argv[])
{
    if((argc != 3) && (argc != 4)) {
        cout << "usage : " << argv[0] << " <dllName> <inputFileName> [reducer number]" << endl;
        return -1;
    }

    PennySortMain* app = new PennySortMain();

    try{
        if(argc == 3){
            app->run(argv[1], argv[2]);
        }
        else{
            app->run(argv[1], argv[2], boost::lexical_cast<int>(argv[3]));
        }
    }
    catch(MapReduceException& e){
        cout << string("cactch exception : ") + e.what() << endl;
    }


    return 0;
}

