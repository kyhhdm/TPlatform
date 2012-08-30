
/**
 * @file   FileSystemUtil.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Thu Nov 29 14:11:02 2007
 * 
 * @brief   boost filesystem wrapper
 * 
 * 
 */

#ifndef _FILE_SYSTERM_UTIL_HPP
#define _FILE_SYSTERM_UTIL_HPP

#include <string>
#include <vector>

class FileSystemUtil
{
public:
    /** 
     * 
     * 
     * @param vec_files return value,is full path
     * @param str_path the dir
     * @param str_exten return the file with this extension
     * 
     * @return <0 error
     */
    static int getFiles(std::vector<std::string> & vec_files, const std::string& str_path, const std::string& str_exten="");
    static int getAllFiles(std::vector<std::string> & vec_files, const std::string& str_path, const std::string& str_exten="");

    /** 
     * 
     * 
     * @param vec_dirs 
     * @param str_path 
     * @param link_flag true: count ; false: not count link file dir
     * 
     * @return 
     */
    static int getDirs(std::vector<std::string> & vec_dirs, const std::string& str_path, bool link_flag = true);
    
    static std::string getExtension(const std::string& str_path);
    static std::string getBasename(const std::string& str_path);
    static std::string getBranchPath(const std::string& str_path);

    /** 
     * 
     * 
     * @param str_path the file cann't large than 2G
     * @param flag should 'B','K','M','G', short for Byte KBtye MByte
     * 
     * @return 
     */
    static int getFileSize(const std::string& str_path,const std::string & flag = "B");

    /** 
     * @deprecated
     * 
     * @param str_path 
     * 
     * @return 
     */
    static std::string normalize(const std::string& str_path);
    static bool createDir(const std::string& str_path);

    static bool isDir(const std::string& str_path);
    static bool isExists(const std::string& str_path);

    static bool removeFile(const std::string& str_path);

    static bool renameFile(const std::string& str_src_path, const std::string & str_dest_path);
    //    static bool copyFile(const std::string& str_path);
    
};

#endif
