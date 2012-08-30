/**
 * @file WordFrequencyFilter.cpp
 * @description append the html files into TFS system 
 * 
 * @author Chen Rishan
 * @date 2007-12-9
 *
 * */

#include "tfs/client/tfs.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace tfs::api;

const size_t CHUNK_SIZE = 64 * 1024 * 1024;
const int BUFFER_SIZE = 100 * 1024 * 1024;
string appendDataName = "/WordFrequency.dat";

int beforeAppend(){
    try{
	    FileSystem tfs;
	    // create datafile and append data 
	    if (!tfs.existFile(appendDataName.c_str()))
	    	tfs.createFile(appendDataName.c_str(), 0, CHUNK_SIZE);
    	else{
		    tfs.removeFile(appendDataName.c_str());
		    tfs.createFile(appendDataName.c_str(),0,CHUNK_SIZE);
	    }
    }catch(TFSException& ex){
        cout << "TFSException: " << ex.what() << endl;
    }
	return 0;
}

int main(int argc, char** argv)
{
	if(argc != 2){
		cout<<"usage: " << argv[0] << " <orignal-data-file>" <<endl;
		return 0;
	}

    beforeAppend();
    ifstream fin(argv[1], ios::in);
    if(!fin){
        cout << "open the local orignal data file failed" << endl;
        exit(-1);
    }
    AppendStream fappend(appendDataName.c_str() , BUFFER_SIZE);
    char* buffer = new char[BUFFER_SIZE];
    int i = 0;
    while(fin >> buffer[i]){
        i ++;
    }
    try{
        fappend.append(buffer, i);
    }catch(TFSException& ex){
        cout << "TFSException: " << ex.what() << endl;
    }
    
    cout << "all the data has been append into TFS" << endl;
    delete[]buffer;
    return 0;
}


