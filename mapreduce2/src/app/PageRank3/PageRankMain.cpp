/**
 * @file PageRankMain.cpp
 *
 * @author Chen Rishan
 * @date 2008-06-23
 * */

#include "TaskConfigure.hpp"
#include "SetMapper.hpp"
#include "Sorter.hpp"
#include "SetReducer.hpp"
#include "MapReduceException.hpp"
#include "TextFileFeeder.hpp"
#include "TKeyValueFeeder.hpp"
#include "PageRankValue.hpp"
#include "FileStream.hpp"
#include "FileStreamLocal.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;
using namespace mapreduce;

class PageRankMain{
public:
    void run(char* dllFile, char* inputFile, char* outputFileName);
};

void PageRankMain::run(char* dllFile, char* inputFile, char* outputFile)
{
    TaskConfigure configure;
    int recordCnt;

    configure.setDllName(dllFile);
    configure.setReducerClass("PageRankReducer");
    configure.setMapperOutKeyClass("char*");
    configure.setMapperOutValueClass("PageRankValue");
    //set up mapper reader class
    configure.setMapperRecordReaderClass("TKeyValueFeeder<char*,PageRankValue>");
    configure.setMapperClass("PageRankMapper");
    //set up reducer writer class
    configure.setReducerRecordWriterClass("TKeyValueWriter<char*,PageRankValue>");
    
    cout << "configure over" << endl;
    vector<string> partitionFiles;

    partitionFiles.push_back("0.par");
    if(exists(partitionFiles[0])) 
        remove(path(partitionFiles[0]));

    cout << "setmapper ready..." << endl;
    SetMapper *setMapper;
    setMapper = new SetMapper(configure, inputFile, partitionFiles, false);
    cout << "begin map" << endl;
    recordCnt = setMapper->map();
    delete setMapper;
    cout << "run setmapper return : recordCnt = " << recordCnt << endl;

    string sortFile = "sorted.dat";
    if(exists(sortFile)) remove(path(sortFile));
    Sorter *sorter = new Sorter(configure, sortFile, partitionFiles);
    cout << "begin sort" << endl;
    if(!sorter->sort()){
        cout << "run sort fail..., bye!" << endl;
    }
    delete sorter;

    cout << "complete sort" << endl;
    string resultFile(outputFile);

    if(exists(resultFile)) 
        remove(path(resultFile));

    SetReducer *setReducer;
    setReducer = new SetReducer(configure, sortFile, resultFile, true, false);
    cout << "begin reduce" << endl;
    recordCnt = setReducer->reduce();
    cout << "run setreducer return : recordCnt = " << recordCnt << endl;
    delete setReducer;
}

bool CheckResults(string file, bool check)
{
    TKeyValueFeeder<char*, PageRankValue> reader;
    reader.initialize(0, true);
    FileStream* stream = NULL;
    stream = new FileStreamLocal(file, FileStream::ReadOnly, false);
    reader.open(stream);
    if(!check)
        cout << "===================" << endl;
    void* key = reader.createKeys();
    void* value = reader.createValues();
    int count = 0;
    void* doKey = key;
    void* doValue = value;
    
    while(reader.next(doKey, doValue) ){
        if(!check){
            cout << *(char**)doKey << " " << ((PageRankValue*)doValue)->pagerank << " " << ((PageRankValue*)doValue)->linkoutNumber << endl;
        }
        count ++;
        reader.flush();
    }
    if(!check){
        cout << "===================" << endl;
        cout << count << endl;
    }
    
    reader.releaseKeys(key);
    reader.releaseValues(value);
    reader.close();
    delete stream;
    return false;
}


//=======================
int main(int argc, char* argv[])
{
    if(argc!=4) {
        cout << "usage : " << argv[0] << " <app basename> <inputFileName> <outputFileName>" << endl;
        return -1;
    }

    PageRankMain* app = new PageRankMain();

    bool stop = false;
    for(int iter_times = 0; iter_times < 29; iter_times ++){
        try{
            if(iter_times == 0){
                app->run(argv[1], argv[2], argv[3]);
            }
            else{
                app->run(argv[1], argv[3], argv[3]);
            }
        }
        catch(MapReduceException& e){
            cout << string("catch exception : ") + e.what() << endl;
        }
        stop = CheckResults(argv[3], true);
    }
    CheckResults(argv[3], false);
    
    return 0;
}

