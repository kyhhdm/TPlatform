/**
 * @file WordCountMain.cpp
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


using namespace std;
using namespace boost::filesystem;
using namespace mapreduce;

class WordCountMain{
public:
    void run(char* dllFile, char* inputFile);
};

void WordCountMain::run(char* dllFile, char* inputFile)
{
    TaskConfigure configure;
    int recordCnt;

    configure.setDllName(dllFile);
    configure.setMapperClass("WordCountMapper");
    configure.setReducerClass("WordCountReducer");
    configure.setMapperOutKeyClass("char*");
    configure.setMapperOutValueClass("int");
    //set up mapper reader class
    configure.setMapperRecordReaderClass("TextFileFeeder");
  //set up reducer writer class
    configure.setReducerRecordWriterClass("TextFileWriter<char*,int>");
    //string className;

    //className = configure.getIntermediateFileRecordWriterClass();
    //TS_ASSERT(className == "TKeyValueWriter<char,int>");
    //className = configure.getHashableComparableClass();
    //TS_ASSERT(className == "THashableComparable<char>");

    vector<string> partitionFiles;
    //outputFiles.push_back(string(rootDirectory) + "0.par");
    //outputFiles.push_back(string(rootDirectory) + "1.par");
    //outputFiles.push_back(string(rootDirectory) + "2.par");
    //outputFiles.push_back(string(rootDirectory) + "3.par");
    //outputFiles.push_back(string(rootDirectory) + "4.par");

    partitionFiles.push_back("0.par");
    if(exists(partitionFiles[0])) remove(path(partitionFiles[0]));

    SetMapper *setMapper;
    setMapper = new SetMapper(configure, inputFile, partitionFiles);
    recordCnt = setMapper->map();
    delete setMapper;
    cout << "run setmapper return : recordCnt = " << recordCnt << endl;

    string sortFile = "sorted.dat";
    if(exists(sortFile)) remove(path(sortFile));
    Sorter *sorter = new Sorter(configure, sortFile, partitionFiles);
    if(!sorter->sort()){
        cout << "run sort fail..., bye!" << endl;
    }
    delete sorter;

    string resultFile = "result.dat";

    if(exists(resultFile)) remove(path(resultFile));

    SetReducer *setReducer;
    setReducer = new SetReducer(configure, sortFile, resultFile, true, false);
    recordCnt = setReducer->reduce();
    delete setReducer;
    cout << "run setreducer return : recordCnt = " << recordCnt << endl;
}


//=======================
int main(int argc, char* argv[])
{
    if(argc!=3) {
        cout << "usage : " << argv[0] << " <app basename> <inputFileName>" << endl;
        return -1;
    }

    WordCountMain* app = new WordCountMain();

    try{
        app->run(argv[1], argv[2]);
    }
    catch(MapReduceException& e){
        cout << string("catch exception : ") + e.what() << endl;
    }


    return 0;
}

