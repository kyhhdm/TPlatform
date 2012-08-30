/**
 * @file   FileSystemUtil.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Thu Nov 29 14:46:19 2007
 * 
 * @brief  the implement of FileSystemUtil.hpp
 * 
 * 
 */


#include "FileSystemUtil.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/exception.hpp>

using namespace std;
namespace  fs  =  boost::filesystem;

int FileSystemUtil::getAllFiles(vector<string> & vec_files, const string& str_path, const string& str_exten)
{
    fs::path full_path(str_path.c_str(),fs::native);
    if (fs::exists(full_path))
	{
        try{
            fs::directory_iterator item_begin(full_path);
            fs::directory_iterator item_end;
            for ( ;item_begin   !=  item_end; item_begin ++ )
            {
                if (fs::is_directory(*item_begin))
                {
                    //cout  << item_begin -> native_file_string() << " \t[dir] " << endl;
                    getAllFiles(vec_files,item_begin->string(),str_exten);
                }
                else
                {
                    //				cout<<extension(*item_begin)<<endl;
                    if( str_exten != ""){
                        if(extension(*item_begin) != str_exten)
                            continue;
                        vec_files.push_back(item_begin->string());
                        //                        cout  << item_begin->native_file_string() << endl;
                    }else{
                        vec_files.push_back(item_begin->string());
                    }                    
                }
           }
        }catch(const fs::filesystem_error & e){
            cout << "Error: getAllFiles()" << e.what() << endl;
            return -1;
        }catch(...){
            cout << "Error: getAllFiles()" << endl;
            //            cout << "getAllFiles() error"<<endl;
            return -1;
        }
	}

    return vec_files.size();
}

int FileSystemUtil::getFiles(vector<string> & vec_files, const string& str_path, const string& str_exten)
{
    fs::path full_path(str_path.c_str(),fs::native);
    if (fs::exists(full_path))
	{
        try{
            fs::directory_iterator item_begin(full_path);
            fs::directory_iterator item_end;
            for ( ;item_begin   !=  item_end; item_begin ++ )
            {
                if (fs::is_directory(*item_begin))
                {
                    //cout  << item_begin -> native_file_string() << " \t[dir] " << endl;
                    continue;
                }
                else
                {
                    //				cout<<extension(*item_begin)<<endl;
                    if( str_exten != ""){
                        if(extension(*item_begin) != str_exten)
                            continue;
                        vec_files.push_back(item_begin->string());
                        //                        cout  << item_begin->native_file_string() << endl;
                    }else{
                        vec_files.push_back(item_begin->string());
                    }                    
                }
            }
        }catch(const fs::filesystem_error & e){
            cout << "Error: getFiles()" << e.what() << endl;
            return -1;
        }catch(...){
            cout << "Error: getFiles()" << endl;
            //            cout << "getAllFiles() error"<<endl;
            return -1;
        }
	}
    
    return vec_files.size();
}


int FileSystemUtil::getDirs(vector<string> & vec_dirs, const string& str_path, bool link_flag)
{
    fs::path full_path(str_path.c_str(),fs::native);
    if (fs::exists(full_path))
	{
        try{
            fs::directory_iterator item_begin(full_path);
            fs::directory_iterator item_end;
            for ( ;item_begin   !=  item_end; item_begin ++ )
            {
                if (fs::is_directory(*item_begin))
                {
                    //cout  << item_begin -> native_file_string() << " \t[dir] " << endl;
                    if (link_flag) {
                        if (exists(*item_begin))
                            vec_dirs.push_back(item_begin->string());
                    }else{
                        if (exists(*item_begin) && !symbolic_link_exists(*item_begin))
                            vec_dirs.push_back(item_begin->string());
                    }
                }
            }
        }catch(const fs::filesystem_error & e){
            cout << "Error: getDirs()" << e.what() << endl;
            return -1;
        }catch(...){
            cout << "Error: getAllDirs()" << endl;
            //            cout << "getAllFiles() error"<<endl;
            return -1;
        }
	}
    
    return vec_dirs.size();
    
}


string FileSystemUtil::getExtension(const string & str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    return extension(full_path);
}

string FileSystemUtil::getBasename(const string & str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    return basename(full_path);
}


string FileSystemUtil::getBranchPath(const string & str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    return (full_path.branch_path()).string();
}

string FileSystemUtil::normalize(const string & str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    fs::path new_path = full_path.normalize();
    return new_path.string();
}

int FileSystemUtil::getFileSize(const string& str_path,const string & flag)
{
    fs::path full_path(str_path.c_str(),fs::native);
    try{
        unsigned int fsize = file_size(full_path);
        if(flag == "B"){
            return fsize;
        }else if(flag == "K"){
            return fsize/1024;
        }else if(flag == "M"){
            return fsize/(1024*1024);
        }else if(flag == "G"){
            return fsize/(1024*1024*1024);
        }
    }catch(const exception& e){
        cout<<e.what()<<endl;
        return -1;
    }
    
    return -1;
}


bool FileSystemUtil::createDir(const string & str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    try{
        return create_directories(full_path);
    }catch(const exception & e){
        cout << "Error:" << e.what() <<endl;
        return false;
    }
}

bool FileSystemUtil::isExists(const string& str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    try{
        return exists(full_path);
    }catch(const exception & e){
        cout << "Error:" << e.what() <<endl;
        return false;
    }
    //    return true;    
}

bool FileSystemUtil::isDir(const string& str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    try{
        return is_directory(full_path);
    }catch(const exception & e){
        cout << "Error:" << e.what() <<endl;
        return false;
    }
}

bool FileSystemUtil::renameFile(const string& str_src_path, const string & str_dest_path)
{
    fs::path src_path(str_src_path.c_str(),fs::native);
    fs::path dest_path(str_dest_path.c_str(),fs::native);
    try{
        rename(src_path,dest_path);
    }catch(const exception & e){
        cout << "Error:" << e.what() <<endl;
        return false;
    }
    return true;
}


bool FileSystemUtil::removeFile(const string& str_path)
{
    fs::path full_path(str_path.c_str(),fs::native);
    try{
        return remove(full_path);
    }catch(const exception & e){
        cout << "Error:" << e.what() <<endl;
        return false;
    }
}
