#include "tfs/tfs.h"
#include "CommandRename.hpp"
#include "FilePath.hpp"
#include <sstream>
#include <iostream>

using namespace std;
using namespace terminal;
using namespace tfs::api;

bool CommandRename::exe(tfs::api::FileSystem& fs, std::string parameter)
{
    istringstream param(parameter);
    string source;
    string dest;
    param >> source >> dest;
    if (source == "" || dest == ""){
        cerr << "parameters error" << endl;
        cerr << "rename <src_file> <dest_file>" << endl;
        return false;
    }
    FilePath pathGenerator;
    source = pathGenerator.getPath(m_currentDir, source);
    source = pathGenerator.change(source);
    dest = pathGenerator.getPath(m_currentDir, dest);
    dest = pathGenerator.change(dest);
    cout << "rename " << source << " " << dest << endl;
    try{
        FileInfo fileinfo = fs.getFileInfo(source);
        if (fileinfo.flag & FileModeTypeDir){
            fs.renameDirectory(source, dest);
        }
        else{
            fs.renameFile(source, dest);
        }
        return true;
    } catch(TFSException & ex){
        cerr << ex.what() << endl;
        return false;
    }
}
