
/**
 * @file   MetaImgMgr.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Sep 16 22:42:46 2007
 * 
 * @brief  chunk的远信息管理，包括它的磁盘镜像
 * 
 * 
 */


#ifndef _TFS_META_MGR_HPP
#define _TFS_META_MGR_HPP

#include <string>

namespace tfs
{
    class MetaImgMgr
    {
    public:
        MetaImgMgr(const char * path);
        ~MetaImgMgr();
        int init();
        int sync(); //同步到文件

        int commitChunk();
        

    private:
        std::string m_path;
        
    };

}
#endif
