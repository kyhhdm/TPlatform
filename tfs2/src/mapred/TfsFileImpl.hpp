/** 
 * @file TfsFileImpl.hpp
 * Implemantation class for TfsFile.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-29
 */
#ifndef _TFSFILEIMPL_HPP
#define _TFSFILEIMPL_HPP 1

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "mapred/TfsFile.hpp"
#include "Ice/Ice.h"

namespace tfs{
    class TfsFileImpl
    {
        /// Address of this client.
        Address m_address;
        /// Ice proxy to use client service.
        ClientServicePrx m_service;
    public:
        TfsFileImpl(const std::string &masterHost, int32_t port);
        tfs::mapred::LocatedChunks getChunksInfo(const std::string& filename);
        bool concatFiles(const std::vector<std::string> &srcFiles, const std::string& dst);
    };
}


#endif /* _TFSFILEIMPL_HPP */
