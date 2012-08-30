
/**
 * @file   FileUtil.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Fri Jul 13 09:31:47 2007
 * 
 * @brief  a function set of file operation
 * 
 * 
 */

#ifndef _FILE_UTIL_HPP_
#define _FILE_UTIL_HPP_

#include <string>
#include <vector>

namespace tfs
{
    class FileUtil
    {
    public:
        FileUtil();
        /** 
         * @param dir_path  the input
         * @param file_list the return filename list
         * @param full_path_flag need to give full path? defalult yes
         * @param regex filter the file name with regex; example:
         regex=".dat", the file_list will hava the file a.dat b.dat.tmp and etc.
         * 
         * @return  < error; >=0 right and represent the num of file 
         */
        static int getFiles(const std::string& dir_path,std::vector<std::string>& file_list,const int full_path_flag=1,const std::string regex="");
        
        static int getDirs(const std::string& dir_path,std::vector<std::string>& dir_list,const int full_path_flag=1,const std::string regex="");
        
        static int scanDirRecursive(const std::string& dir_path,std::vector<std::string>& file_list,const int full_path_flag=1,const std::string regex="");

        //        static int getAllFiles(std::vector<std::string> & vec_file_list, const std::string & dir_path, const string & exten_str="");


        
        //get the size(byte) of file
        static int getFileSize(const std::string& path);
        //get kbyte
        static int getFileKSize(const std::string& path);
        static int getFileMSize(const std::string& path);
        
        static int isFileExsist(const std::string& path); //1: right -1:wrong
        static int isDir(const std::string& path); //不能判断连接文件

        static int renameFile(const std::string& old_filename,const std::string& new_filename);

        //返回一个路径的父目录路径
        //@deprecated
        // use boost filesystem path.branch_path
        static std::string getFatherDir(const std::string& str_path);

        
    };
}
#endif

