/**
 * @file	CommandLs.cpp
 * implementation of CommandLs.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <string>
#include <sstream>
#include <iomanip>
#include "client/tfs.h"
#include "app/shell/include/CommandLs.hpp"
#include "app/shell/include/FilePath.hpp"


using namespace std;
using namespace terminal;
using namespace tfs::api;

ostream& operator << (ostream& os, const FileInfo& fileinfo)
{
    cout << ((fileinfo.flag & FileModeTypeDir)?'d':'-')
         << ((fileinfo.flag & FileModeOwnerRead)?'r':'-')
         << ((fileinfo.flag & FileModeOwnerWrite)?'w':'-')
         << ((fileinfo.flag & FileModeOwnerExec)?'x':'-')
         << ((fileinfo.flag & FileModeGroupRead)?'r':'-')
         << ((fileinfo.flag & FileModeGroupWrite)?'w':'-')
         << ((fileinfo.flag & FileModeGroupExec)?'x':'-')
         << ((fileinfo.flag & FileModeOtherRead)?'r':'-')
         << ((fileinfo.flag & FileModeOtherWrite)?'w':'-')
         << ((fileinfo.flag & FileModeOtherExec)?'x':'-');

    cout << setw(3) << fileinfo.replication;
    cout << setw(15) << fileinfo.size;
    cout << setw(9) << fileinfo.chunkSize << " ";

    struct tm *createTime = localtime((time_t*)&fileinfo.createTime);
    cout << createTime->tm_year+1900 << "-" 
         << setw(2) << setfill('0') << createTime->tm_mon << "-" 
         << setw(2) << createTime->tm_mday << " "
         << setw(2) << createTime->tm_hour << ":" 
         << setw(2) << createTime->tm_min << setfill(' ') << " ";

    if (fileinfo.flag & FileModeTypeDir){
        cout << "\033[1;34m" << fileinfo.name << "\033[0m";
    }
    else{
        cout << fileinfo.name;
    }
    
    return os;
}

bool CommandLs::exe(tfs::api::FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
	string path;
    string tempfile;
    input >> path;  //get the path
    path = pathGenerator.getPath(m_currentDir, path);
    path = pathGenerator.change(path);
    FilesInfo sub;
    FileInfo fileinfo;
    if(path != "/"){
        tempfile = path;
        path = path + "/";
    }

    if( fs.existFile(tempfile) && path != "/" ){
        try{
            fileinfo = fs.getFileInfo(tempfile);
        }
        catch(TFSException& ex){
            cout << "Get exception: " << ex.what() << endl;
            return false;
        }
        cout << fileinfo << endl;
        return true;
    }
    //cout << m_currentDir << "\t" << path << endl;
    //it is directory;
    try{
    	sub = fs.listDirectory(path);
	}
    catch(TFSException &ex){
        cout << "Get exception: " << ex.what() << endl;
        return false;
    }

    for (int i = 0; i < sub.size(); ++i) {
        cout << sub[i] << endl;
    }
    return true;
}

