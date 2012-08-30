/* 
 * @(#)ClientInfo.hpp
 * AUTHOR: YangZhifeng
 * CREATE DATE: 23  5月 2007
 * DESCRIPTION: 
 */
/** @file
 * 
 * @author YangZhifeng
 * @date 23  5月 2007
 */
#ifndef _CLIENTINFO_HPP
#define _CLIENTINFO_HPP 1
#include "common/String.hpp"
#include <string>
#include <ctime>
#include <ext/hash_set>
using __gnu_cxx::hash_set;
using std::string;

namespace tfs
{
    /**
     * @see tfs::ClientManager
     * 
     */
    class ClientInfo
    {
        typedef hash_set<string, StringHash, StringEqual> set_type;
    public:
        ClientInfo();
        
        /**
         * last update time
         */
        time_t m_lastUpdate;
        /** 
         * these files are opened for writing or appending
         */
        set_type m_openFiles;
    };
}

    

#endif /* _CLIENTINFO_HPP */
