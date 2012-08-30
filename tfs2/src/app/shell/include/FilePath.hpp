/**
 * @file	FilePath.hpp
 * it deals with the path of file in the system	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#ifndef TERMINAL_FILEPATH_HPP
#define TERMINAL_FILEPATH_HPP 1

#include<string>
#include<stack>
#include<iostream>

namespace terminal{

class FilePath
{
public:
    
    static const std::string RootString;
    static const std::string CurDirString;
    static const std::string ParentDirString;
    static const char PathDelimiter = '/';

    /**
     * Constructor
     * @param
     * @throws
     */
    FilePath();

    ~FilePath();
    
    /**
     * change the path to absolute path
     * @param [in] filepath
     * @throws
     * @return: the absolute path, the new path ends with no '/'
     * for example: change "/root/dd/../" to "/root"
     */
    std::string change(std::string filepath);
    
    /**
     * parse the path
     * @param [in] filepath
     * @throws
     * @return:
     */
    void parse(std::string filepath);
    
    /**
     * get complete path
     * @param [in] currentDirectory, filepath
     * @throws
     * @return: complete path
     */
    std::string getPath(std::string currentDir, std::string filepath);
    
    /**
     * get current directory path of local host
     * @param [in] currentDirectory, filepath
     * @throws
     * @return: local current path
     */
// use <unistd.h> getcwd() instead, yzf
//    std::string getLocalCurrentDir();

    /** 
     * split the path into dir and filename
     * 
     * @param path [in] the path of the file
     * @param bAbsolutePath [out] whether the path is an absolute path
     * @param dir [out] dir part
     * @param filename [out] filename part
     */
    static void split(const std::string &path, bool &bAbsolutePath, std::string &dir, std::string& filename);
    
private:
    std::stack<std::string> m_parser;
    
    /**
     * static functions to get the local directory path
     * these functions should not be used out of the class.
     */
    static ino_t get_inode(char*);
    static void printpathto(ino_t);
    static void inum_to_name(ino_t, char* , int);

    static std::string m_localCurrent;
};

}//end of namespace

#endif
