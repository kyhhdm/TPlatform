
/**
 * @file   Md5Mgr.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Sep 16 22:47:49 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef _TFS_MD5_MGR_HPP
#define _TFS_MD5_MGR_HPP

#include <vector>

namespace tfs
{

    const int MD5_BUF_SIZE=(1<<14); //计算buf大小16k

    class Md5
    {
    public:
        Md5(const char *, int size);
    friend bool operator==(const Md5 &,const Md5 &);
    private:
        char m_buf[16];
    };

    
    class Md5Mgr
    {
    public:
        Md5Mgr();
        ~Md5Mgr();
        void pushData(const char * data,int size);
        void pushMd5();
    friend bool operator==(const Md5Mgr &,const Md5Mgr &);
    private:
        void cleanBuf();
        char * m_buf;
        int m_cur_size;
        std::vector<Md5> m_md5_set;
    };

}
#endif
