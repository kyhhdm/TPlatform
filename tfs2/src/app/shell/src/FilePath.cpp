/**
 * @file	FilePath.cpp
 * it deals with the path of file in the system	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "app/shell/include/FilePath.hpp"


using namespace terminal;
using namespace std;

const std::string terminal::FilePath::RootString = "/";
const std::string terminal::FilePath::CurDirString = ".";
const std::string terminal::FilePath::ParentDirString = "..";
std::string terminal::FilePath::m_localCurrent;

//==================class implematation==================

FilePath::FilePath()
{
}

FilePath::~FilePath()
{
}

void FilePath::parse(std::string filepath)
{
    //TODO: file path checking
    std::string directory;
    int len = filepath.length();
    int end = len - 1;
    if(filepath[len - 1] == '/')
        end = len - 2;
    int size  = 0;
    for(int i = len-2; i >= 0 ; i--){
        if(filepath[i] == '/'){
            size = end - i;
            directory = filepath.substr(i+1, size);
            end = i-1;
            m_parser.push(directory);
        }
    }
    //the last directory 
    m_parser.push(RootString);
}
//
std::string FilePath::change(std::string filepath)
{  
    parse(filepath);
    std::string directory;
    std::string newPath;
    std::string temp;
    std::stack<std::string> temp_stack;
    // remove ".." and '.' in the path
    while( !m_parser.empty() ){
        directory = m_parser.top();
        if(directory == CurDirString){
            m_parser.pop();
        }
        else if(directory == ParentDirString){
            m_parser.pop();
            // #fixbug 19
            // http://tianwang.grids.cn/tracker/?func=detail&atid=229&aid=19&group_id=38
            if (temp_stack.size() != 1){ 
                temp_stack.pop();
            }
        }
        else{
            m_parser.pop();
            temp_stack.push(directory);
        }
    }
    temp = temp_stack.top();
    temp_stack.pop();
    temp.append(newPath);
    newPath = temp;
    while( !temp_stack.empty() ){
        temp = temp_stack.top();
        if(temp != RootString){
            temp = temp + "/";
        }
        temp.append(newPath);
        newPath = temp;
        temp_stack.pop();
    }
    return newPath;
}

string FilePath::getPath(string currentDir, string filepath)
{
    string path;
    //TODO: if the filepath is null, what's the meaning of the situaion
    if(filepath == "" || filepath == "."){
        path = currentDir;//command execute with the currentDir
    }
    else{
        if(filepath[0] == '/'){
            path = filepath;
            //filename used as absolute path
        }
        else{
            path = currentDir + filepath;
            //filename uesd as relative path
        }
    }
    return path;
}

// string FilePath::getLocalCurrentDir()
// {
//     printpathto(get_inode(".") );
//     m_localCurrent = m_localCurrent + "/";
//     return FilePath::m_localCurrent;
// }

//======================static function========================

void FilePath::printpathto(ino_t this_inode)
{
    ino_t my_inode;
    char its_name[BUFSIZ];
    if(get_inode("..") != this_inode){
        chdir("..");
        inum_to_name(this_inode, its_name , BUFSIZ);
        my_inode = get_inode(".");
        printpathto(my_inode);
        string temp(its_name);
        temp = "/" + temp;
        m_localCurrent.append(temp);
    }    
}

void FilePath::inum_to_name(ino_t inode_to_find, char * namebuf, int buflen)
{
    DIR * dir_ptr;
    struct dirent* direntp;
    dir_ptr = opendir(".");
    if(dir_ptr == NULL){
        perror(".");
        cout << "errors" << endl;
        return;
    }
    while( (direntp = readdir(dir_ptr) ) != NULL)
        if( direntp->d_ino == inode_to_find){
            strncpy(namebuf, direntp->d_name, buflen);
            namebuf[buflen-1] = '\0';
            closedir(dir_ptr);
            return;
        }
    cout << "error to find " << inode_to_find << endl;
    //fprintf(stderr, "error %d\n", inode_to_find);
    return;
}

ino_t FilePath::get_inode(char* fname)
{
    struct stat info;
    if( stat(fname, &info) == -1){
        fprintf(stderr, "cannot stat");
        perror(fname);
        cout << "cannot stat" << endl;
    }
    return info.st_ino;
}

void FilePath::split(const std::string &path, bool &bAbsolutePath, std::string &dir, std::string& filename)
{
    string::size_type pos = path.rfind(PathDelimiter);
    if (pos == string::npos){
        if (path == CurDirString || path == ParentDirString){
            bAbsolutePath = false;
            dir = path + '/';
            filename = "";
        }
        else{
            bAbsolutePath = false;
            dir = "";
            filename = path;
        }
    }else{
        dir = path.substr(0, pos + 1);
        filename = path.substr(pos + 1);
        bAbsolutePath = (path[0] == PathDelimiter) ? true: false;
    }
}

