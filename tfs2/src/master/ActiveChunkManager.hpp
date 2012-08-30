/** 
 * @file ActiveChunkManager.hpp
 * Manage active chunks. This data structure records storage location
 * (ChunkServer) of each chunk recorded in FsDirectory. 
 * 
 * @author Zhifeng YANG
 * @date 23  5 2007
 */
#ifndef _ACTIVECHUNKMANAGER_HPP
#define _ACTIVECHUNKMANAGER_HPP 1
#include "common/Types.hpp"
#include "common/IceGenerated.hpp"
#include "common/Exception.hpp"
#include "master/ChunkHelper.hpp"
#include "util/Logger.hpp"
#include <ext/hash_map>
#include <IceUtil/Mutex.h>

namespace tfs
{
    class ActiveChunkManager
    {
        ChunkAddressMap m_chunk2location;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// logger
        Logger m_logger;

    private:
        LocatedChunk getLocatedChunk(const Chunk &chk) throw(NoSuchChunk);

    public:
        /// constructor
        ActiveChunkManager()
            :m_logger(Logger::getInstance("master"))
        {
        }
        //@{
        /** 
         * Add chunk's location. If the chunk does not exist yet,
         * add the entry. 
         * 
         * @param chk 
         * @param location 
         *
         */
        void add(const Chunk &chk, const Address &location);

        /** 
         * Add chunks from chunkserver's chunk report
         * 
         * @param location 
         * @param chks 
         *
         */
        void add(const Address& location, const Chunks &chks);

        /** 
         * Add chunks from client's completeWrite request and
         * chunkserver's completeMigrate request
         * 
         * @param lchk 
         */
        void add(const LocatedChunk& lchk);
        //@}

        //@{
        /** 
         * Remove chunk's location(s) from the map. If a client has found a bad
         * chunk, it can reportBadChunks to the Master. When the client delete
         * a file or decrease the replication of a file, remove the coresponding
         * chunks. If a chunk has no locations after delete the locations, remove
         * the chunk entry too. 
         * 
         * @param lchk 
         */
        void remove(const Chunk &chk, const Address& address) throw(NoSuchChunk);
        void remove(const LocatedChunk& lchk) throw(NoSuchChunk);
        void remove(const LocatedChunks& lchks) throw(NoSuchChunk);
        //@}

        /** 
         * Get chunks' locations information.
         * 
         * @param chks
         * @throw NoSuchChunk
         * @return chunks with locations information
         */
        LocatedChunks getLocatedChunks(const Chunks& chks) throw(NoSuchChunk);
    };
}


#endif /* _ACTIVECHUNKMANAGER_HPP */
