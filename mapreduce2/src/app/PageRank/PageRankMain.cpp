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
    void run(char* dllFile, char* inputFile, bool isPretreat);
};

void PageRankMain::run(char* dllFile, char* inputFile, bool isPretreat)
{
    TaskConfigure configure;
    int recordCnt;

    configure.setDllName(dllFile);
    configure.setReducerClass("PageRankReducer");
    configure.setMapperOutKeyClass("char*");
    configure.setMapperOutValueClass("PageRankValue");
    //set up mapper reader class
    if(isPretreat){
        configure.setMapperRecordReaderClass("TianwangRawFileFeeder");
        configure.setMapperClass("PageRankFirstMapper");
        cout << "pretreat " << endl;
    }
    else{
        /**
         * @BUG FIXED:
         * the macro definition regisiter must be careful
         * even the blank in the <> may be the cause of error
         * */
        configure.setMapperRecordReaderClass("TKeyValueFeeder<char*,PageRankValue>");
        configure.setMapperClass("PageRankLatterMapper");
    }
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
    string resultFile = "result.dat";

    if(exists(resultFile)) 
        remove(path(resultFile));

    SetReducer *setReducer;
    setReducer = new SetReducer(configure, sortFile, resultFile, true, false);
    cout << "begin reduce" << endl;
    recordCnt = setReducer->reduce();
    cout << "run setreducer return : recordCnt = " << recordCnt << endl;
    delete setReducer;
}

void CheckResults(string file)
{
    TKeyValueFeeder<char*, PageRankValue> reader;
    reader.initialize(0, true);
    FileStream* stream = NULL;
    stream = new FileStreamLocal(file, FileStream::ReadOnly, false);
    reader.open(stream);
    cout << "===================" << endl;
    void* key = reader.createKeys();
    void* value = reader.createValues();
    int count = 0;
    void* doKey = key;
    void* doValue = value;

    while(reader.next(doKey, doValue) ){
        cout << *(char**)doKey << " " << ((PageRankValue*)doValue)->pagerank << " " << ((PageRankValue*)doValue)->linkoutURLs.size() << endl;
        count ++;
        reader.flush();
    }
    cout << "===================" << endl;
    cout << count << endl;
    //reader.close();
    //delete preader;
    //delete stream;
}


//=======================
int main(int argc, char* argv[])
{
    if(argc!=3) {
        cout << "usage : " << argv[0] << " <app basename> <inputFileName>" << endl;
        return -1;
    }

    PageRankMain* app = new PageRankMain();

    try{
        app->run(argv[1], argv[2], true);
    }
    catch(MapReduceException& e){
        cout << string("catch exception : ") + e.what() << endl;
    }
    
    for(int iter_times = 0; iter_times < 5; iter_times ++){
        try{
            app->run(argv[1], "result.dat", false);
        }
        catch(MapReduceException& e){
            cout << string("catch exception : ") + e.what() << endl;
        }
    }
    CheckResults("result.dat");
    
    return 0;
}

