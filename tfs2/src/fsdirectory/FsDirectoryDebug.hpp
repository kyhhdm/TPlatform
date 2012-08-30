/** @file FsDirectoryDebug.hpp
 * FsDirectoryDebug is a debug class that implement FsDirectory interface.
 * Especially designed for debuging FsLog replay functionality.
 *
 */
#ifndef _TFSMASTER_FSDIRECTORYDEBUG_HPP
#define _TFSMASTER_FSDIRECTORYDEBUG_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include "fsdirectory/FsDirectoryImpl.hpp"

namespace tfs {

    class FsDirectoryDebug : public FsDirectoryImpl{

        void printChunks(Chunks & chunks);
        

    public:
        FsDirectoryDebug(){};
        
        void createFile(const std::string& filename, int maxChunkSize = MasterConfig::DefaultMaxChunkSize, 
                        short replication = MasterConfig::DefaultReplication);
        void renameFile(const std::string& src, const std::string& dst);

        void deleteFile(const std::string& filename, Chunks& deletedChunks);

        void createDir(const std::string& dirname);
        void renameDir(const std::string& src, const std::string& dst);

        void deleteDir(const std::string& filename);

        Chunk newChunk(const std::string& filename, const std::string& holder, Long chunkId = 0LL);

        bool updateChunk(const Chunk& chunk);

        void commitChunk(const Chunk& chunk);
        void abandonChunk(const Chunk& chunk);
        void setFileInfo(const std::string& filename, const FileInfo& info);
        Short setReplication(const std::string& filename, Short replication);

    };
}

#endif /* _TFSMASTER_FSDIRECTORYDEBUG_HPP */
