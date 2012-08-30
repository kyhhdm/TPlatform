
/**
 * @file   MetaImgMgr.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Sep 16 21:52:12 2007
 * 
 * @brief  implement of MetaImgMgr.hpp
 *
 * 
 */


#include "MetaImgMgr.hpp"
#include "util/Logger.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
using namespace tfs;

// Logger pLogger = Logger::getInstance("chunkserver");
extern Logger pLogger;

MetaImgMgr::MetaImgMgr(const char * path)
{
    assert(path!=NULL);
    m_path=path;
}

int MetaImgMgr::init()
{
    ifstream infile(m_path.c_str());
    if(!infile){
        // LOG4CPLUS_ERROR(pLogger,"MetaImgMgr::init() cann't open file:"<<m_path);
        return -1;
    }

    //@todo 读取元信息
    return 1;
}


int MetaImgMgr::sync()
{
    //@todo 同步镜像文件
    return 1;
}

