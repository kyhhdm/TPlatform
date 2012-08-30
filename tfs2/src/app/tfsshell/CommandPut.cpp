/**
 * @file	CommandPut.cpp
 * implementation of CommandPut.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include "tfs/tfs.h"
#include "CommandPut.hpp"
#include "FilePath.hpp"

#include <string>
#include <sstream>
#include <fstream>

#include <sys/types.h>          // for fstat()
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace terminal;
using namespace tfs::api;

const int DEFAULT_BUFFER_SIZE = 64 * 1024; // 64K
const int MAX_BUFFER_SIZE = 1024 * 1024; // 1M
const int DEFAULT_CHUNK_SIZE = 8 * 1024 * 1024; // 8M
const int MAX_CHUNK_SIZE = 64 * 1024 * 1024;    // 64M


bool CommandPut::exe(FileSystem& fs, string parameter)
{
    istringstream input(parameter);
	string tfsPath;
    string localPath;
    int blocksize = -1; // add by fk
    input >> localPath >> tfsPath >>blocksize;  //get the parameters
    if (blocksize == -1) blocksize = 1;
   
    /**
     * if the path is null, it puts nothing 
     */
    if(tfsPath == "" && localPath == ""){
        cout << "USAGE: put <local_file> [<tfs_file>]" << endl;
        cout << "EXAMPLE: put filename1" << endl;
        cout << "         put filename1 ." << endl;
        cout << "         put filename1 ./filename2" << endl;
        cout << "         put /home/abc/filename1" << endl;
        cout << "         put /home/abc/filename1 ./filename2" << endl;
        return false;
    }
    // check local file
    struct stat fileStat;
    if (stat(localPath.c_str(), &fileStat) != 0){
        cout << "Error: put: no such file " << localPath << endl;
        return false;
    }
    bool bAbsolutePath;
    string localDir;
    string localFilename;
    FilePath::split(localPath, bAbsolutePath, localDir, localFilename);

    string tfsDir;
    string tfsFilename;
    FilePath::split(tfsPath, bAbsolutePath, tfsDir, tfsFilename);
    if (!bAbsolutePath){            // reletive path
        FilePath pathGenerator;
        tfsDir = pathGenerator.getPath(m_currentDir, tfsDir);
        tfsDir = pathGenerator.change(tfsDir); //change into absolutely path
        if(tfsDir != "/"){
            tfsDir +=  "/";
        }
    }
    if (tfsFilename.empty()){
        tfsFilename = localFilename;
    }
    tfsPath = tfsDir + tfsFilename;
    
    cout << "put " << localPath << " " << tfsPath << endl;
    
    try{
        if( !fs.existDirectory(tfsDir) ){
            cout << "Error: no such directory " << tfsDir << endl;
            return false;
        }

        //if the file is exist , the local file will be appended
        if( !fs.existFile(tfsPath) ){
            int chunkSize = (fileStat.st_size > MAX_CHUNK_SIZE) ? MAX_CHUNK_SIZE:DEFAULT_CHUNK_SIZE;
            chunkSize = chunkSize - chunkSize % blocksize;
            fs.createFile(tfsPath, 2 , chunkSize);
        }

        AppendStream tfsAppend;
        int bufferSize = (fileStat.st_size < MAX_BUFFER_SIZE) ? MAX_BUFFER_SIZE:DEFAULT_BUFFER_SIZE;
        tfsAppend.open(tfsPath, bufferSize);

        ifstream fin(localPath.c_str() , ios::binary);
        if(!fin){
            cout << "ERROR: put: open file " << localPath << endl;
            return false;
        }

        size_t MAXGET = 1024 * 1024 / blocksize * blocksize;
        if (MAXGET == 0) throw (TFSException("Block Size Exceed 1 M"));
        char *buffer = new char[MAXGET];

        while(fin){
            fin.read(buffer, MAXGET);
            //cout << "read " << fin.gcount() << endl;
            tfsAppend.append(buffer, fin.gcount());
        }
    }
    catch(TFSException& ex){
        cout << "ERROR: put: Get exception: " << ex.what() << endl;
        return false;
    }

    return true;
}

