/** 
 * @file ChunkServerManager.hpp
 * Manage chunkserver and its chunks.
 * 
 * @author YANG Zhifeng
 * @date 23  5 2007
 */
#ifndef _CHUNKSERVERMANAGER_HPP
#define _CHUNKSERVERMANAGER_HPP 1
#include "master/ChunkServerInfo.hpp"
#include "common/Types.hpp"
#include "common/IceGenerated.hpp"
#include "common/Exception.hpp"
#include "master/AddressHelper.hpp"
#include "util/Logger.hpp"
#include <ext/hash_map>
#include <string>
#include <IceUtil/Mutex.h>

namespace tfs
{
    class ChunkServerManager
    {
        /**
         * map chunkserver id->info
         * 
         */
        typedef __gnu_cxx::hash_map<Address, ChunkServerInfo, AddressHash, AddressEqual> address2info_t;
        address2info_t m_address2info;
        /**
         * Those chunkserver who don't renew heartbeat for more than
         * m_expireTime will be considered halted. 
         *
         */
        int32_t m_expireTime;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// logger
        Logger m_logger;
        /// randomly select several chunkservers
        Addresses chooseChunkServersRandomly(int32_t num) const;
    public:
        // constructor
        ChunkServerManager(int32_t expireTime)
            :m_expireTime(expireTime), m_logger(Logger::getInstance("master"))
        {
            srand((int)time(NULL));
        }

        /** 
         * The chunkserver must register first. 
         * If the chunkserver has already registered, return the 
         * old ID associated with it. 
         *
         * @param name 
         * @param dataPort 
         * 
         * @return 
         */
        void enroll(const Address &address) throw ();
        bool isEnrolled(const Address &address) const throw ();

        void renewHeartbeat(const Address& address,const Heartbeat &hb) throw (UnknownChunkServer);
        /** 
         * Add chunks reported by chunkserver. 
         * Note that this function will clean the old m_chunks member
         * @param id 
         * @param chks 
         */
        void setChunks(const Address& address, const Chunks &chks) throw (UnknownChunkServer);

        //@{
        /** 
         * Append the chunk(s) to the existing m_chunks vector. 
         * @param id 
         * @param chk
         * @throw UnknownChunkServer
         */
        void add(const Address& address, const Chunk &chk) throw (UnknownChunkServer);
        void add(const Address& address, const Chunks &chks) throw (UnknownChunkServer);
        /** 
         * Append the chunk to the existing m_chunks vector. 
         * After a success write/append, the Client or ChunkServer may 
         * report its newly added chunk to the Master. 
         * 
         * @param lchk 
         * @throw UnknownChunkServer
         */
        void add(const LocatedChunk &lchk) throw (UnknownChunkServer);
        void add(const LocatedChunks &lchks) throw (UnknownChunkServer);
        //@}

        //@{
        /** 
         * The chunk(s) is/are removed from the chunkserver(s).
         * 
         * @throw UnknownChunkServer
         */
        void remove(const Address& address, const Chunk &chk) throw (UnknownChunkServer);
        void remove(const Address& address, const Chunks &chks) throw (UnknownChunkServer);
        void remove(const LocatedChunk &lchk) throw (UnknownChunkServer);
        void remove(const LocatedChunks &lchks) throw (UnknownChunkServer);
        /** 
         * remove all the chunks of the chunkserver.
         * 
         * @param address 
         */
        void remove(const Address& address) throw (UnknownChunkServer);
        //@}

        /** 
         * get all the enrolled chunkservers
         * 
         * 
         * @return the chunkservers
         */
        Addresses getChunkServers();
        /** 
         * get chunkserver's chunks
         * 
         * @param address 
         * 
         * @return chunks stored in the chunkserver
         */
        ChunksPtr get(const Address& address);
        
        /** 
         * remove ChunkServers which are expired
         * 
         * @param lchks [out] removed chunks with locations
         * 
         * @return removed chunks with locations
         */
        void removeExpired(LocatedChunks &lchks);

        /** 
         * Choose several best ChunkServers to allocate chunk from. 
         * Several factors are considered, e.g. workload, free space etc.
         * The returned ChunkServers may be less than the required number.
         * 
         * @param number Number of ChunkServers to choose
         * 
         * @return Selected ChunkServer
         */
        Addresses chooseBestChunkServers(int32_t number) const;
        /** 
         * Choose several worst ChunkServers to in the system. 
         * Several factors are considered, e.g. workload, free space etc.
         * The returned ChunkServers may be less than the required number.
         * 
         * @param number Number of ChunkServers to choose
         * 
         * @return Selected ChunkServers
         */
        Addresses chooseWorstChunkServers(int32_t number) const;
        /** 
         * Choose several worst ChunkServers to delete chunk from. 
         * Several factors are considered, e.g. workload, free space etc.
         * The returned ChunkServers may be less than the required number.
         * 
         * @param number Number of ChunkServers to choose
         * @param chunkServers choose the chunkservers among them
         * @return Selected ChunkServers
         */
        Addresses chooseWorstChunkServers(const Addresses &chunkServers, int32_t number) const;

    };
}

        
#endif /* _CHUNKSERVERMANAGER_HPP */
