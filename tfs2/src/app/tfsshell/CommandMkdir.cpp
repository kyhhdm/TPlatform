/**
 * @file	CommandMkdir.cpp
 * implementation of CommandMkdir.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <string>
#include <sstream>
#include "tfs/tfs.h"
#include "CommandMkdir.hpp"
#include "FilePath.hpp"

using namespace std;
using namespace terminal;
using namespace tfs::api;


bool CommandMkdir::exe(tfs::api::FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
	string path;
    input >> path;  //get the path
    path = pathGenerator.getPath(m_currentDir, path);
    //cout << m_currentDir << "\t" << path << endl;
    try{
        fs.createDirectory(path);
    }
    catch(TFSException& ex){
        cout << "Get exception: " << ex.what() << endl;
        return false;
    }
    return true;
}
