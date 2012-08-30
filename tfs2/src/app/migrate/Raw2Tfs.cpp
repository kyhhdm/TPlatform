/**
 * @file   Raw2Tfs.cpp
 * @author Peng Bo
 * @date   2007 09 18
 * 
 * @brief  upload Tianwang Raw Page Data File into TFS system.
 * 
 * 
 */
#include <tfs/tfs.h>
#include <tianwang/TWReader.h>
#include <common/IceGenerated.hpp>
#include <openssl/md5.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>

using namespace std;
using namespace tfs::api;

int main(int argc, char*argv[])
{
    string inputFileName, outputFileName;

	if(argc != 5){
		cout<<"usage: "<<argv[0]<<"  [-f input_file_name] [-t output_tfs_file_name]"<<endl;
		return 0;
	}
    inputFileName = argv[2];
    outputFileName = argv[4];

    //init tfs enviroment
	tfs::api::FileSystem tfs;
    const int ChunkSize = 64*1024*1024;
    const int BufferSize = 2*1024*1024;

	// create datafile and append data 
	if (!tfs.existFile(outputFileName.c_str()))
		tfs.createFile(outputFileName.c_str(), 0, ChunkSize);
	else{
        cout << outputFileName << " already exist, appending..." << endl;
        //return -1;
	}

	tfs::api::AppendStream tfsAppender(outputFileName, BufferSize);

    //init local TWReader
    try{
        TWReader reader(inputFileName.c_str());
        char *buf = new char[BufferSize];
        int recordLen;
        int recordNum = 0;
         
        while ((recordLen = reader.nextRecord(buf, BufferSize)) != 0){
            tfsAppender.append(buf, recordLen);                           
        
            if((recordNum % 1000)==0){
                cout << "\rupload record : " << recordNum << flush;
            }
            recordNum++;
        }
        
        cout << "\rupload " << recordNum << " records done!" << endl;
        delete[] buf;

    }catch (TWReaderException &E) {
        cout << E.what() << endl;
    } catch (exception &E) {
        cout << E.what() << endl;
    }

    tfsAppender.close();

	return 0;
}





