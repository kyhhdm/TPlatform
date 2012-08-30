/**
 * @file	appendTest.cpp
 * append 并发写正确性测�? * 
 * @author	Zhu Lei
 * @date	2007-09-24
 *
 */

#include "tfs/tfs.h"
#include "../tfs_test/TaskManager.hpp"
#include <common/IceGenerated.hpp>
#include <openssl/md5.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace tfs::api;

const size_t CHUNK_SIZE = 64*1024*1024;
int globalTestNumber = 0;
string dataPath;
string appendDataName = "/TwPages.dat";

// return the size of the line
int getLine(tfs::api::InputStream & is,string & line){
	const int maxLine = 500;
	char lineBuf[maxLine];
	int n = is.read(lineBuf,maxLine);
	if(n == 0) return 0;
	int i;
	for(i=0;i<n;i++){       
		if(lineBuf[i]=='\n')
			break;
	}
	line.clear();
	line.append(lineBuf,i);
	is.seek(-n+i+1,SEEK_CUR);    
	return i+1;
}

int beforeTest(){
	tfs::api::FileSystem tfs;

	// create datafile and append data 
	if (!tfs.existFile(appendDataName.c_str()))
		tfs.createFile(appendDataName.c_str(), 0, CHUNK_SIZE);
	else{
		tfs.removeFile(appendDataName.c_str());
		tfs.createFile(appendDataName.c_str(),0,CHUNK_SIZE);
	}
	return 0;
}

// define task function here
int appendTest()
{
	globalTestNumber ++;
	int testNumber = globalTestNumber;

	string dataName = "page";
	ostringstream os;
	os << testNumber;
	dataName += os.str();
	dataName += ".dat";


    //#BUGFIX
    //tfs::append call should be an integrate record
    char *recordBuf = new char[64*1024*1024];
    int recordBufPos;

	tfs::api::AppendStream as(appendDataName, 64*1024*1024);
	string pagePath = dataPath + dataName;
	ifstream fin(pagePath.c_str(),ios::in | ios::binary);
	if(!fin){
		cerr<< dataName << " open error!" << endl;
		return 0;
	}

	int pageNum = 0;
	string page,halfpage,line;
	int length,offset;
	while (getline(fin, line))
	{
		halfpage.clear();
		if (line.find("version: ") != 0)
			continue;
		halfpage+=line+"\n";

		if (getline(fin, line))	// get url
		{		
			if (line.find("url: ") != 0)
				continue;
			halfpage+=line+"\n";  			
		} 
		else{
			cerr<<"webpage read error!"<<endl;
			return 0;
		}

		if (getline(fin, line))	// get date
		{
			if (line.find("date: ") != 0)
				continue;
			halfpage+=line+"\n";
		}
		else{
			cerr<<"webpage read error!"<<endl;
			return 0;    		    
		}

		if (getline(fin, line))	// get ip
		{
			if (line.find("ip: ") != 0)
				continue;
			halfpage+=line+"\n";
		}
		else{
			cerr<<"webpage read error!"<<endl;
			return 0;    		    
		}

		offset = fin.tellg();
		page.clear();
		if (getline(fin, line))
		{
			if (line.find("unzip-length: ") == 0){    // get unzip-length
				page+=line+"\n";

				if (getline(fin, line)){
					if (line.find("length: ") != 0)    // get length
						continue;
					page+=line+"\n";
					istringstream iss(line.substr(strlen("length: ")).c_str());
					iss >> length;
				}
				else{
					cerr<<"webpage read error!"<<endl;
					return 0;            		    
				}
			}
			else if (line.find("length: ") == 0){     // get length
				page+=line+"\n";
				istringstream iss(line.substr(strlen("length: ")).c_str());
				iss >> length;
			}
			else continue;
		}
		else{
			cerr<<"webpage read error!"<<endl;
			return 0;
		}

		if (!getline(fin, line))	// nullLine.
		{
			cerr<<"webpage read error!"<<endl;
			return 0;
		}
		page+=line+"\n";

		// get content and calculate its MD5
		char *contentBuffer = new char[length+1];
		fin.read(contentBuffer,length);
		char md5[16];
		MD5((const unsigned char *)contentBuffer,length,(unsigned char *)md5);
		char md5Buf[40];
		memset(md5Buf,0,40);
		for(int m = 0;m < 16;m ++){
			sprintf(&(md5Buf[m*2]), "%02x",md5[m]);
		}
		md5Buf[32] = '\0';


		// append to tfs
		// 1.append page before the tag "length"
		//as.append(halfpage.c_str(),halfpage.size());
        memcpy(recordBuf, halfpage.c_str(), halfpage.size());
        recordBufPos = halfpage.size();

		// 2.append checkout data
		char temp[20];   
		sprintf(temp,"%d",testNumber);
		string checkoutData = "testNumber: ";
		checkoutData += temp;
		checkoutData += "\n";

		checkoutData += "offset: ";
		sprintf(temp,"%d",offset);
		checkoutData += temp;
		checkoutData += "\n";

		checkoutData += "md5: ";
		checkoutData += md5Buf;

		checkoutData += "\n";
		//as.append(checkoutData.c_str(),checkoutData.size());
        memcpy(recordBuf + recordBufPos, checkoutData.c_str(),checkoutData.size());
        recordBufPos += checkoutData.size();

		// 3.append the page before the tag "length"

		//as.append(page.c_str(),page.size());
		//as.append((const char *)contentBuffer,length);
        //as.append("\n",1);
        memcpy(recordBuf + recordBufPos,page.c_str(),page.size());
        recordBufPos += page.size();
        memcpy(recordBuf + recordBufPos,(const char *)contentBuffer,length);
        recordBufPos += length;
        memcpy(recordBuf + recordBufPos,"\n", 1);
        recordBufPos += 1;
        as.append(recordBuf, recordBufPos);

		delete []contentBuffer;
		contentBuffer = 0;
		pageNum++;
		//				if(pageNum == 5) break;
	}

	printf("\033[1;34m test %d : there are %d pages appended! \033[0m\n",testNumber,pageNum);
	fin.close(); 
	as.close();

    delete[] recordBuf;

	return 1;
}

bool checkout(){

	tfs::api::FileSystem tfs;

	if (!tfs.existFile(appendDataName.c_str() ) ){
		cerr<< appendDataName << "doesn't exist! "<<endl;
		return false;
	}

	tfs::api::InputStream is(appendDataName.c_str(), CHUNK_SIZE);
	is.seek(0,SEEK_SET);

	int	length=0,testNumber,offset,pageNum = 0;
	string page,line,md5;
	while ( getLine(is,line))
	{
		page.clear();
		md5.clear();

		// get appended page 
		if (line.find("version: ") != 0){
			cerr << "version missed !" <<endl;
			return false;
		}
		page+=line+"\n";

		if (getLine(is, line))	// get url
		{		
			if (line.find("url: ") != 0){
				cerr << "url missed !" <<endl;
				return false;
			}
			page+=line+"\n";
		} 
		else{
			cerr<<"url  read error!"<<endl;
			return false;
		}

		if (getLine(is, line))	// get date
		{
			if (line.find("date: ") != 0){
				cerr << "date missed !" <<endl;
				cout<<line<<endl;
				cout<<pageNum<<endl;
				return false;
			}
			page+=line+"\n";
		}
		else{
			cerr<<"date read error!"<<endl;
			return false;    		    
		}

		if (getLine(is, line))	// get ip
		{
			if (line.find("ip: ") != 0){
				cerr<<"ip missed!"<<endl;
				return false;
			}
			page+=line+"\n";
		}
		else{
			cerr<<"ip read error!"<<endl;
			return false;    		    
		}

		// get checkout information
		if(getLine(is, line)){
			if (line.find("testNumber: ") != 0 ){
				cerr << "testNumber missed!"<<endl;
				return false;
			}
		}
		else{
			cerr <<"checkout information read error!"<<endl;
			return false;
		}

		istringstream iss(line.substr(strlen("testNumber: ")).c_str());
		iss >> testNumber;

		if (getLine(is,line)){
			if (line.find("offset: ") != 0){
				cerr<<"offset missed!"<<endl;
				return false;
			}
			istringstream iss(line.substr(strlen("offset: ")).c_str());
			iss >> offset;
		}
		else{
			cerr <<"checkout information read error!"<<endl;
			return false;
		}

		if (getLine(is,line)){
			if (line.find("md5: ") != 0) return false;
			md5 = line.substr(strlen("md5: "));
			if (md5.size() != 32){
				cerr << "md5 Buffer should be 32 bytes!"<<endl;			
				return false;
			}
		}
		else{
			cerr <<"checkout information read error!"<<endl;
			return false;
		}

		// get length
		if (getLine(is, line))	
		{
			if (line.find("unzip-length: ") == 0){    // get unzip-length
				page+=line+"\n";
				if (getLine(is, line)){
					if (line.find("length: ") != 0){    // get length
						cerr <<"length read error!"<<endl;
						return false;
					}
					page+=line+"\n";
					istringstream iss(line.substr(strlen("length: ")).c_str());
					iss >> length;
				}
				else{
					cerr<<"length read error 1!"<<endl;
					return false;            		    
				}
			}
			else if (line.find("length: ") == 0){     // get length
				page+=line+"\n";
				istringstream iss(line.substr(strlen("length: ")).c_str());
				iss >> length;
			}
			else{
				cerr<<"length read error 2!"<<endl;
				return false;
			}
		}
		else{
			cerr<<"length read error 3!"<<endl;
			return false;
		}

		if (!getLine(is, line))	// nullLine.
		{
			cerr<<"nullLine read error!"<<endl;
			return false;
		}
		page+=line+"\n";

		// get content
		char *content = new char[length+1];
		memset(content, 0, length+1);
		is.read(content, length);    		
		// read an \n
		char enter[2];
		is.read(enter,1);

		// calculate md5
		char checkMd5[16];
		MD5((const unsigned char *)content,length,(unsigned char *)checkMd5);
		char checkmd5Buf[40];
		memset(checkmd5Buf,0,40);
		for(int m = 0;m < 16;m ++){
			sprintf(&(checkmd5Buf[m*2]), "%02x",checkMd5[m]);
		}
		checkmd5Buf[32] = '\0';
	
		// compare calculated md5 and recorded md5
		if(strcmp(md5.c_str(),checkmd5Buf) != 0){
			cerr<< "calculated md5 and recorded md5 compare error!"<<endl;
			return false;
		}

		string originData = "page";
		ostringstream os;
		os << testNumber;  
		originData += os.str();
		originData += ".dat";
		originData = dataPath + originData;
		ifstream fin(originData.c_str(),ios::in | ios::binary);

		fin.seekg(offset,ios::beg);
		string line;
		int length;				
		// get raw data length
		if (getline(fin, line))	
		{
			if (line.find("unzip-length: ") == 0){    // get unzip-length
				if (getline(fin, line)){
					if (line.find("length: ") != 0){    // get length
						cerr<<"raw length missed!"<<endl;
						return false;
				    }
					istringstream iss(line.substr(strlen("length: ")).c_str());
					iss >> length;
				}
				else{
					cerr<<"raw length read error 1!"<<endl;
					return false;            		    
				}
			}
			else if (line.find("length: ") == 0){     // get length
				istringstream iss(line.substr(strlen("length: ")).c_str());
				iss >> length;
			}
			else{
				cerr<<"raw length read error 2!"<<endl;
				return false;
			}
		}
		else{
			cerr<<"raw length read error 3!"<<endl;
			return false;
		}

		if (!getline(fin, line))	// nullLine.
		{
			cerr<<"raw nullLine read error!"<<endl;
			return false;
		}

		// get origin content
		char * originContent = new char[length+1];
		memset(originContent, 0, length+1);
		fin.read(originContent, length);
		fin.close();

		// calculate md5
		char originMd5[16];
		MD5((const unsigned char *)originContent,length,(unsigned char *)originMd5);
		char originmd5Buf[40];
		memset(originmd5Buf,0,40);
		for(int m = 0;m < 16;m ++){
			sprintf(&(originmd5Buf[m*2]), "%02x",originMd5[m]);
		}
		originmd5Buf[32] = '\0';

		// compare calculated md5 and origin md5
		if(strcmp(checkmd5Buf,originmd5Buf) != 0){
			cerr<< "calculated md5 and origin md5 compare error!"<<endl;
			return false;
		}
		delete []content;
		content = 0;
		delete []originContent;
		originContent = 0;
		pageNum++;
	}
	cout<< pageNum<<" pages checked at all! " <<endl;
	return true; 
}

int miniAppendTest(){
	tfs::api::FileSystem tfs;

	// create file "/minitest" and append data 
	if (!tfs.existFile("/minitest"))
		tfs.createFile("/minitest",0, CHUNK_SIZE);

	tfs::api::AppendStream as("/minitest", 3600);

	string line = "I love Sammi.";
	as.append(line.c_str(),line.size());
	as.append("\n",1);

	string line2 = "I am ZhuLei.";
	as.append(line2.c_str(),line2.size());
	as.append("\n",1);
	as.close();

	cout << "append ok" <<endl;    
	cout << "sleep 2s..." <<endl;
	system("sleep 2");	
	// read a line from "/minitest" and compare with string line	
	tfs::api::InputStream is("/minitest", 3600);
	is.seek(0,SEEK_SET);    
	string test,test2;
	getLine(is,test);
	getLine(is,test2);

	if(test == line && test2 == line2) cout<<"single THREAD test successful"<<endl;
	else{
		if(test!=line)
			cout<<"read: "<<test<<" != "<<line<<endl;
		if(test2!=line2)
			cout<<"read: "<<test2<<" != "<<line2<<endl;
		cout<<"single THREAD test failed!"<<endl;
	}
	return 0;
}

int main(int argc, char** argv)
{
	if(argc != 5){
		cout<<"usage: "<<argv[0]<<"  [--directory(-d) directory] [--thread(-t) number]"<<endl;
		return 0;
	}

	// the number of threads or processes to be tested.
	int m_number = 1;

	if(strcmp(argv[1],"--directory") != 0 && strcmp(argv[1],"-d") != 0){
		cout<<"usage: "<<argv[0]<<"  [--directory(-d) directory] [--thread(-t) number]"<<endl;
		return 0;
	}
	if(strcmp(argv[3], "--thread") != 0 && strcmp(argv[3],"-t") != 0){
		cout<<"usage: "<<argv[0]<<"  [--directory(-d) directory] [--thread(-t) number]"<<endl;
		return 0;
	}
	string option;
	option = argv[4];
	istringstream iss(option);
	iss >> m_number;

	dataPath = argv[2];

	printf("\033[1;32m append test ... \033[0m\n");
	tfs::TaskManager tm;

	//    single THREAD test
	//    printf("\033[1;31m THREAD 1 ... \033[0m\n");
	//    tm.addTask(miniAppendTest,1,tfs::THREAD);    
	beforeTest();

	for(int i = 0; i < m_number ; i++){
		//multiple THREAD test
		printf("\033[1;31m THREAD %d ... \033[0m\n",i+1);
		tm.addTask(appendTest,1,tfs::THREAD);    
	}
	tm.start();

	system("sleep 5");

	// checkout now
	printf("\033[1;31m now begin our Checkout ... \033[0m\n");
	bool result = checkout();    
	if(result) printf("\033[1;32m concurrency test succeed! \033[0m\n");
	else printf("\033[1;33m concurrency test failed! \033[0m\n");
	return 0;
}   
