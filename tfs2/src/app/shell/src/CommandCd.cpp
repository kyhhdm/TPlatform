/**
 * @file	CommandCd.cpp
 * implementation of CommandCd.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <string>
#include <sstream>
#include "client/tfs.h"
#include "app/shell/include/CommandCd.hpp"
#include "app/shell/include/FilePath.hpp"

using namespace std;
using namespace terminal;
using namespace tfs::api;


bool CommandCd::exe(tfs::api::FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
	string path;
    input >> path;  //get the path
    /**
     * if the path is null, it will change to the root 
     */
    if(path != ""){
        path = pathGenerator.getPath(m_currentDir, path);
    }
    path = pathGenerator.change(path); //change into absolutely path
    //cout << m_currentDir << "\t" << path << endl;
    /**
     * for pathGenerator, it generates path that do not has the tail "/"
     * so when changing a directory, it should add the tail
     */
    int length = path.length();
    if(path[length - 1] != '/')
        path = path + "/";

    if(fs.existDirectory(path) ){
        m_currentDir = path ;
    }
    else{
        cout << "the directory " << path << " is not exsit" << endl;
        return false;
    }
    return true;
}

