/**
 * @file	CommandGet.cpp
 * implementation of CommandGet.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#define MAXGET (32 * 1024)
const int DEFAULT_BUFFER_SIZE = 64 * 1024; // 64K

#include <string>
#include <sstream>
#include <fstream>
#include "client/tfs.h"
#include "app/shell/include/CommandGet.hpp"
#include "app/shell/include/FilePath.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace terminal;
using namespace tfs::api;
namespace fs = boost::filesystem;

bool CommandGet::getDir(string tfsPath, string localPath) {
    cout << "get dir " << tfsPath << " " << localPath << endl;
    fs::create_directory(localPath);
    FileSystem fs;
    FilesInfo entries = fs.listDirectory(tfsPath);
    for (int i = 0; i < entries.size(); ++i) {
        string tPath = tfsPath + "/" + entries[i].name;
        string lPath = localPath + "/" + entries[i].name;
        if (entries[i].flag & FileModeTypeDir) {
            if (!getDir(tPath, lPath)) return false;
        } else {
            if (!getFile(tPath, lPath)) return false;
        }
    }
    return true;
}

bool CommandGet::getFile(string tfsPath, string localPath) {
    cout << "get " << tfsPath << " " << localPath << endl;
    // open output file
    ofstream fout(localPath.c_str() , ios::binary);
    if(!fout){
        cout << "ERROR: get: open file " << localPath << endl;
        return false;
    }

    InputStream tfsIn;
    tfsIn.open(tfsPath, DEFAULT_BUFFER_SIZE);
    char buffer[MAXGET];
    uint64_t nRead;
    while ((nRead = tfsIn.read(buffer,MAXGET)) > 0){
        fout.write(buffer, nRead);
    }        
    fout.close();
    return true;
}

bool CommandGet::exe(FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
	string tfsPath;
    string localPath;
    input >> tfsPath >> localPath;  //get the path
   
    /**
     * if the path is null, it gets nothing 
     */
    if(tfsPath == "" && localPath == ""){
        cout << "<USAGE>: get <tfs_file> [<local_file>]" << endl;
        cout << "EXAMPLE: get filename1" << endl;
        cout << "         get filename1 ." << endl;
        cout << "         get filename1 ./filename2" << endl;
        cout << "         get /home/abc/filename1" << endl;
        cout << "         get /home/abc/filename1 /home/def/filename2" << endl;
        return false;
    }
    bool bTfsAbsolutePath;
    string tfsDir;
    string tfsFilename;
    FilePath::split(tfsPath, bTfsAbsolutePath, tfsDir, tfsFilename);

    bool bLocalAbsolutePath;
    string localDir;
    string localFilename;
    FilePath::split(localPath, bLocalAbsolutePath, localDir, localFilename);

    if (!bTfsAbsolutePath){
        tfsDir = pathGenerator.getPath(m_currentDir, tfsDir);
        tfsDir = pathGenerator.change(tfsDir); //change into absolutely path
        if(tfsDir != "/"){
            tfsDir +=  "/";
        }
        tfsPath = tfsDir + tfsFilename;
    }
    if (localFilename.empty()){
        localFilename = tfsFilename;
    }   
    localPath = localDir + localFilename;
    
    
    try{    
        if( fs.existFile(tfsPath) ){
            if (!getFile(tfsPath, localPath))
                return false;
        } else if (fs.existDirectory(tfsPath)) {
           if (!getDir(tfsPath, localPath))
               return false; 
        } else {
            cout << "no such file or directory: " << tfsPath << endl;
            return false;
        }

    }
    catch(TFSException& ex){
        cout << "Get exception: " << ex.what() << endl;
        return false;
    }

    return true;
}

