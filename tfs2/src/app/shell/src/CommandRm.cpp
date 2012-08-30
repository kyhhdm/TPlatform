/**
 * @file	CommandRm.cpp
 * implementation of CommandRm.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <string>
#include <sstream>
#include "client/tfs.h"
#include "app/shell/include/CommandRm.hpp"
#include "app/shell/include/FilePath.hpp"

using namespace std;
using namespace terminal;
using namespace tfs::api;


bool CommandRm::exe(tfs::api::FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
    string path;
    string commandType;
    input >> commandType >>path;
    /**
     * if there is only one parameter,it should be the filepath 
     * which will be removed later, or romove the directory
     */
    if(path == ""){
        path = commandType;
        path = pathGenerator.getPath(m_currentDir, path);
        path = pathGenerator.change(path);
        return removeFile(fs, path);
    }
    else if(commandType == "-rf"){
        path = pathGenerator.getPath(m_currentDir, path);
        path = pathGenerator.change(path);
        return removeDirectory(fs, path);
    }
    cout << "<USAGE> rm <filepath>" << endl;
    cout << "<USAGE> rm -rf <filepath>" << endl;
    return false;
}

bool CommandRm::removeFile(FileSystem& fs, string filePath)
{
    try{
        fs.removeFile(filePath);
    }
    catch(TFSException& ex){
        cout << "Get exception: " << ex.what() << endl;
        return false;
    }
    return true;
}

bool CommandRm::removeDirectory(FileSystem& fs, string directoryPath)
{
    try{
        fs.removeDirectory(directoryPath,true);
    }
    catch(TFSException& ex){
        cout << "Get exception: " << ex.what() << endl;
        return false;
    }
    return true;
}
