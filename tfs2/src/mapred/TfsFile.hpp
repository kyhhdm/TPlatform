/** 
 * @file TfsFile.hpp
 * a wrapper on ClientService to get chunk informations, 
 * used by mapreduce project.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-29
 */
#ifndef _TFSFILE_HPP
#define _TFSFILE_HPP 1

#include <vector>
#include <string>
#include <stdint.h>

namespace tfs{
    class TfsFileImpl;

    namespace mapred{
        struct Address
        {
            std::string name;
            int32_t port;
        };
        typedef std::vector<Address> Addresses;
  
        struct LocatedChunk
        {
            int64_t chkId;
            int64_t chkSize;
            // locations of the chunk where it is stored, they are addresses of the ChunkServers
            Addresses locations;
        };
        typedef std::vector<LocatedChunk> LocatedChunks;
        
        class TfsFile
        {
            tfs::TfsFileImpl* m_impl;
        public:
            TfsFile(const std::string &masterHost, int32_t port);
            ~TfsFile();
            LocatedChunks getChunksInfo(const std::string& filename);
            bool concatFiles(const std::vector<std::string> &srcFiles, const std::string& dst);
        };
    }
}


#endif /* _TFSFILE_HPP */
