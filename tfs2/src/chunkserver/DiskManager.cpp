
#include "DiskManager.hpp"
#include "util/Logger.hpp"
#include "String.hpp"
#include "FileSystemUtil.hpp"
#include "DiskUtil.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

using namespace std;
using namespace tfs;
namespace  fs  =  boost::filesystem;

DiskManager::DiskManager()
{
    m_dir_path = "";
    m_change_flag = true;
    m_free_space_M = 0;
}

DiskManager::~DiskManager()
{
    
}

bool DiskManager::init(const char * dir_path)
{

    m_change_flag = true;
    m_dir_path = dir_path;

    if (!checkDirs())
        return false;
    
       
    return true;
}

bool DiskManager::checkDirs()
{
    assert(m_dir_path != "");

    for (int i =0; i< Store_Dir_Nums; ++i){
        string dir_path(ts("%s/%d",m_dir_path.c_str(),i));
        if (FileSystemUtil::isExists(dir_path)){
            if (FileSystemUtil::isDir(dir_path)){
                continue;
            }else{
                //if exsit file with the same name, rename it
                FileSystemUtil::renameFile(dir_path,dir_path+".del");
                
            }
        }
        
        if (!FileSystemUtil::createDir(dir_path)){                
            return false;
        }
        //        FileSystemUtil::createDir();            
    }

    for (int i =0; i< Store_Dir_Nums; ++i){
        string dir_path(ts("%s/%d",m_dir_path.c_str(),i));
        assert(FileSystemUtil::isDir(dir_path));
    }
    
    return true;
}


void DiskManager::setDiskChanged()
{
    m_change_flag = true;
}

string DiskManager::getStorePath(const int64_t chunk_id)
{
    assert(chunk_id > 0);
    assert(m_dir_path != "");
    
    int dir_num =  chunk_id % Store_Dir_Nums;
    
    string dest_path(ts("%s/%d/%lld.chk",m_dir_path.c_str(),dir_num,chunk_id));

    return dest_path;
}


int64_t DiskManager::getFreespaceM()
{
    assert(m_dir_path != "");
    if (m_change_flag){
        //@todo get free space
        m_free_space_M = DiskUtil::getAvailSpace(m_dir_path);
        m_change_flag = false;
    }

    return m_free_space_M;
}

