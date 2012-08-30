/**
 * @file TfsFile.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-29
 */

#include "mapred/TfsFile.hpp"
#include "mapred/TfsFileImpl.hpp"
using namespace tfs::mapred;

TfsFile::TfsFile(const std::string &masterHost, int32_t port)
{
    m_impl = new tfs::TfsFileImpl(masterHost, port);
}

TfsFile::~TfsFile()
{
    delete m_impl;
}

LocatedChunks TfsFile::getChunksInfo(const std::string& filename)
{
    return m_impl->getChunksInfo(filename);
}

bool TfsFile::concatFiles(const std::vector<std::string> &srcFiles, const std::string& dst)
{
    return m_impl->concatFiles(srcFiles, dst);
}
