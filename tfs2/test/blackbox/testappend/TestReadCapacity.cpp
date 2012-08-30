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
const int64_t dataSize = 2*1024*1024*1024LL;
const size_t readTime = 256;

string appendDataName = "/capacity.dat";
char * buffer;

int readTest(){

	tfs::api::FileSystem tfs;

	if (!tfs.existFile(appendDataName.c_str() ) ){
		cerr<< appendDataName << "doesn't exist! "<<endl;
		return 0;
	}
	int64_t random;
	tfs::api::InputStream is(appendDataName.c_str(), BUFFER_SIZE);
	int64_t size = is.seek(0,SEEK_END);

	srand(time(NULL));

	for(int i =0; i< readTime ;i++){
		random = ( rand()*rand()+rand() ) % (size-BUFFER_SIZE);
		is.seek(random,SEEK_SET);
		is.read(buffer,BUFFER_SIZE);
//		if(i%25==0)
//			printf("%d MB read\n",(i+1)*BUFFER_SIZE/1024/1024);
	}
	return 1; 
}

int main(int argc, char** argv)
{
	if(argc != 3){
		cout<<"usage: "<<argv[0]<<" [-t thread_number]"<<endl;
		return 0;
	}

	// the number of threads or processes to be tested.
	int m_number = 1;
	buffer = new char[BUFFER_SIZE];
	
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

	printf("\033[1;32m capacity test ... \033[0m\n");
	tfs::TaskManager tm;

	for(int i = 0; i < m_number ; i++){
		printf("\033[1;31m THREAD %d ... \033[0m\n",i+1);
		tm.addTask(readTest,1,tfs::THREAD);    
	}
	tm.start();

	gettimeofday(&tpend,NULL);
	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
		tpend.tv_usec-tpstart.tv_usec;
	timeuse/=1000000;
	printf("Read Used Time:%f \n",timeuse); 
	delete []buffer;
	return 0;
}   
