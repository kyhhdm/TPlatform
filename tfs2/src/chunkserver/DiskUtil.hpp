/**
 * @file   DiskUtil.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Tue Dec  4 13:17:59 2007
 * 
 * @brief  Disk tool, 
 * 
 * 
 */


#ifndef TFS__DISK_UTIL_HPP
#define TFS__DISK_UTIL_HPP

#include <string>

class DiskUtil
{
public:

    /** 
     * 
     * 
     * @param path the path
     * @param flag can be G,M,K,B
     * 
     * @return 
     */
    static long long getAvailSpace(const std::string & path,const std::string& flag = "M");
    //    static long long getTotalSpace(const std::string & path,const std::string& flag = "M");
    
};

#endif

