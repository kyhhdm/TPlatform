/**
 * @file   ChunkServerConf.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Jul  8 21:55:31 2007
 * 
 * @brief  
 * 
 * 
 */


#ifndef _CHUNKSERVER_CONF_HPP_
#define _CHUNKSERVER_CONF_HPP_

#include <string>
#include <cassert>
#include "util/Config.hpp"

namespace tfs
{
    class ChunkServerConf
    {
    private:
        static ChunkServerConf * pInstance;
        static std::string mConfPath;                
        ChunkServerConf();
        int init();

        Config mRudeConf;

    public:
        /** 
         * a sigleton. use getInstance() tou get global handle
         * 
         * 
         * @return 
         */
        static ChunkServerConf * getInstance();

        /** 
         * before you use getInstance, you shoule setConfPath
         * 
         * @param path 
         */
        static void setConfPath(std::string path);

        std::string getConfInfo();

        int DATA_SOCKET_PORT;
        std::string LOCALE_IP;
        std::string CHUNK_STORE_DIR;
        std::string CHUNK_TMP_DIR;
        std::string MASTER_PROXY_INFO;
        std::string WORK_DIR;
        std::string LOG_PATH;
    };
    
}

#endif
