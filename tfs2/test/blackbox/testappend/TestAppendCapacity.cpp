/**
 * @file	TestCapacity.cpp
 * 
 * @author	Zhu Lei
 * @date	2007-11-12
 *
 */

#include "tfs/tfs.h"
#include "../tfs_test/TaskManager.hpp"
#include <common/IceGenerated.hpp>
#include <openssl/md5.h>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace tfs::api;

const size_t CHUNK_SIZE = 64*1024*1024;
const size_t BUFFER_SIZE = 4*1024*1024;
//const int64_t dataSize = 0.5*1024*1024*1024LL;
int64_t dataSize = 0.5*1024*1024*1024LL;

string appendDataName = "/capacity.dat";
char * buffer;

int beforeTest(){
	tfs::api::FileSystem tfs;
	// create datafile and append data 
	if (!tfs.existFile(appendDataName.c_str()))
		tfs.createFile(appendDataName.c_str(), 0, CHUNK_SIZE);
	else{
//		tfs.removeFile(appendDataName.c_str());
//		tfs.createFile(appendDataName.c_str(),0,CHUNK_SIZE);
	}
	buffer = new char[BUFFER_SIZE];
	srand(time(NULL));
	for(int j = 0 ;j<BUFFER_SIZE; j++){
		buffer[j] = rand() & 0xFF;
	}
	return 0;
}

// define task function here
int appendTest()
{
	tfs::api::AppendStream as(appendDataName, BUFFER_SIZE);
	
	for(int i = 0; i < dataSize/BUFFER_SIZE ;i++){
		as.append(buffer,BUFFER_SIZE);
		if(i%25 == 0){
			printf("%d MB appended!\n",4*i);
		}
	}

	as.close();
	return 1;
}

int main(int argc, char** argv)
{
	if(argc != 3 && argc!= 5 ){
		cout<<"usage: "<<argv[0]<<" [-t thread_number] [-n appendDataName]|[-s data size(GB)]"<<endl;
		return 0;
	}
    if(argc == 5){
        if(!strcmp(argv[3], "-n")){
            appendDataName = argv[4]; 
        }
        else if (!strcmp(argv[3], "-s")){
            int size;
        	//istringstream idatasize(string(argv[4]));
        	istringstream idatasize(argv[4]);
        	idatasize >> size;
            dataSize = size * 1024*1024*1024LL;           
        }
    }

	// the number of threads or processes to be tested.
	int m_number = 1;

	if(strcmp(argv[1],"-t") != 0){
		cout<<"usage: "<<argv[0]<<"  [-t thread_number]"<<endl;
		return 0;
	}
	string option;
	option = argv[2];
	istringstream iss(option);
	iss >> m_number;

	struct timeval tpstart,tpend;
	float timeuse;
	gettimeofday(&tpstart,NULL);

	printf("\033[1;32m capacity test %s for %d (GB)... \033[0m\n", appendDataName.c_str(), dataSize/(1024*1024*1024LL));
	tfs::TaskManager tm;

	beforeTest();

	for(int i = 0; i < m_number ; i++){
		printf("\033[1;31m THREAD %d ... \033[0m\n",i+1);
		tm.addTask(appendTest,1,tfs::THREAD);    
	}
	tm.start();

	gettimeofday(&tpend,NULL);
	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
		tpend.tv_usec-tpstart.tv_usec;
	timeuse/=1000000;
	printf("Append Used Time:%f \n",timeuse); 

	delete []buffer;
	return 0;
}   
