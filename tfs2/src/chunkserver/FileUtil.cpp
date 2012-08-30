
#include "FileUtil.hpp"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace tfs;


int FileUtil::getFiles(const string& dir_path,vector<string> & file_list,const int full_path_flag,const string regex)
{
    struct dirent **namelist;
    int n;
    n = scandir(dir_path.c_str(), &namelist, 0, alphasort);
    if (n < 0)
        return -1;
    else {
        while(n--) {
            string strname=namelist[n]->d_name;
            free(namelist[n]);
            if(strname=="." || strname=="..")
                continue;
            struct stat statbuf;
            string str_fullpath=dir_path+"/"+strname;
            if(lstat(str_fullpath.c_str() ,&statbuf)<0)
                continue;            
            if(S_ISDIR(statbuf.st_mode))	//is dir
                continue;
            
            if(regex!=""){
                //@todo 此处处理regex方式有点勉强
                if((strname.find(regex))==-1){
                    continue;
                }
            }
            if(full_path_flag==1){
                file_list.push_back(string(str_fullpath));
            }else{
                file_list.push_back(string(strname));
            }
            
        }
        free(namelist); //use c style because namelist is malloc in system api
    }    
    return file_list.size();
}


int FileUtil::getDirs(const std::string& dir_path,std::vector<std::string>& dir_list,const int full_path_flag,const std::string regex)
{
    struct dirent **namelist;
    int n;
    n = scandir(dir_path.c_str(), &namelist, 0, alphasort);
    if (n < 0)
        return -1;
    else {
        while(n--) {
            string strname=namelist[n]->d_name;
            free(namelist[n]);
            if(strname=="." || strname=="..")
                continue;
            struct stat statbuf;
            string str_fullpath=dir_path+"/"+strname;
            if(lstat(str_fullpath.c_str() ,&statbuf)<0)
                continue;            
            if(S_ISDIR(statbuf.st_mode)){	//is dir
                // 处理目录
                if(regex!=""){
                    //@todo 此处处理regex方式有点勉强
                    if((strname.find(regex))==-1){                        
                        continue;
                    }
                }
                if(full_path_flag==1){                
                    dir_list.push_back(string(str_fullpath));
                }else{
                    dir_list.push_back(string(strname));
                }
            }
            
        }
        free(namelist); //use c style because namelist is malloc in system api
    }    
    return dir_list.size();
    
}

int FileUtil::getFileSize(const string& path)
{
    struct stat buf;
    int ret;

    ret = lstat(path.c_str(), &buf);

    if (ret != 0) return -1;  

    if (S_ISREG(buf.st_mode))
        return buf.st_size;
    else
        return 0;
}

int FileUtil::getFileKSize(const string& path)
{
    int ret=getFileSize(path);
    if(ret==-1)
        return -1;
    else
        return ret/1024;
}


int FileUtil::getFileMSize(const string& path)
{
    int ret=getFileKSize(path);
    if(ret==-1)
        return -1;
    else
        return ret/1024;    
}

int FileUtil::isFileExsist(const string& path)
{
    ifstream infile(path.c_str());
    if(!infile)
        return -1;
    else{
        infile.close();
        return 1;
    }
    
}

int FileUtil::isDir(const string & path)
{
    struct stat statbuf;
    if(lstat(path.c_str() ,&statbuf)<0){ //path error        
        return -2;
    }
    if(S_ISDIR(statbuf.st_mode)){	//is dir
        return 1;
    }
    
    return -1;
}

int FileUtil::renameFile(const string& old_filename,const string& new_filename)
{
    if(!isFileExsist(old_filename))
        return -1;
  
    link(old_filename.c_str(), new_filename.c_str());
    unlink(old_filename.c_str());
    return 1;
}


string FileUtil::getFatherDir(const string & str_path)
{
    size_t len = str_path.size();
    bool flag = false;
    int pos = -1;
    for(int i = len - 1;i >= 0; --i){

        if ((!flag) && str_path[i] != '/'){
            flag = true;
        }
        
        if (flag){
            if (str_path[i] == '/'){
                pos = i;
                break;
            }
        } //end if flag
    } //end for i

    if(pos<0 || pos >= len-1)
        return "";

    string father_dir = str_path.substr(0,pos+1);
    return father_dir;
    
    //    return "";
}
