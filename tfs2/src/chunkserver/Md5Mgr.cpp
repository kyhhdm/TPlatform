
#include "Md5Mgr.hpp"
#include <openssl/md5.h>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;
using namespace tfs;

namespace tfs
{
    bool operator==(const Md5 & m1,const Md5 & m2)
    {
        if(memcmp(m1.m_buf,m2.m_buf,16)==0)
            return true;
        return false;
    }
    bool operator!=(const Md5 & m1,const Md5 & m2)
    {
        return !(m1==m2);
    }
    
    bool operator==(const Md5Mgr & m1,const Md5Mgr & m2)
    {
        if(m1.m_md5_set.size()!=m2.m_md5_set.size()){
            //                       cout<<"+:"<<m1.m_md5_set.size()<<" "<<m2.m_md5_set.size()<<endl;
            return false;
        }
        int v_size=m1.m_md5_set.size();
        for(int i=0;i<v_size;++i){
            //                        cout<<"-"<<endl;
            if((m1.m_md5_set)[i]!=(m2.m_md5_set)[i])
                return false;
        }
        return true;
    }
    bool operator!=(const Md5Mgr & m1,const Md5Mgr & m2)
    {
        return !(m1==m2);
    }
}
Md5::Md5(const char * p,int size)
{
    //@todo 计算md5
    assert(p!=NULL && size>0);
    memset(m_buf,0,16);
    MD5((const unsigned char *)p,size,(unsigned char *)m_buf);    
}

Md5Mgr::Md5Mgr()
{
    m_buf=new char[MD5_BUF_SIZE];
    memset(m_buf,0,MD5_BUF_SIZE);
    m_cur_size=0;
}

Md5Mgr::~Md5Mgr()
{
    delete [] m_buf;
}

void Md5Mgr::pushData(const char *data,int size)
{
    assert(data!=NULL);
    if(m_cur_size+size<MD5_BUF_SIZE){ //缓冲区未满
        memcpy(m_buf+m_cur_size,data,size);
        m_cur_size+=size;
        return;
    }else{ //满了
        int rest_size=MD5_BUF_SIZE-m_cur_size;
        memcpy(m_buf+m_cur_size,data,rest_size);
        assert((size-rest_size)>=0);

        //@todo commit md5
        pushMd5();
        cleanBuf();
        
        if((size-rest_size)!=0){
            memcpy(m_buf,data+rest_size,size-rest_size);
            m_cur_size+=(size-rest_size);
        }
    }
}


void Md5Mgr::pushMd5()
{
    if(m_cur_size==0)
        return;
    assert(m_buf!=NULL);
    Md5 md5_(m_buf,MD5_BUF_SIZE);
    m_md5_set.push_back(md5_);
}

void Md5Mgr::cleanBuf()
{
    if(m_buf==NULL)
        return;
    memset(m_buf,0,MD5_BUF_SIZE);
    m_cur_size=0;    
}


// bool Md5Mgr::compare(const char * p1,const char * p2,int size)
// {
//     assert(p1!=NULL && p2!=NULL && size>0);
//     if(memcmp(p1,p2,size)==0)
//         return true;
//     return false;
// }





