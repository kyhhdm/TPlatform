/** 
 * @file GarbageCollection.hpp
 * Record those chunks should be garbage-collected.
 * 
 * @author Zhifeng YANG
 * @date 31  5月 2007
 */
#ifndef _GARBAGECOLLECTION_HPP
#define _GARBAGECOLLECTION_HPP 1
#include "common/IceGenerated.hpp"
#include "master/AddressHelper.hpp"
#include "util/Logger.hpp"
#include <ext/hash_map>
#include <string>
#include <IceUtil/Mutex.h>


namespace tfs
{
    class GarbageCollection
    {
        /// map: chunkserver -> garbage chunks
        typedef __gnu_cxx::hash_map<Address, Chunks, AddressHash, AddressEqual> address2chunks_t;
        address2chunks_t m_garbageChunks;
        /// mutex for the map
        IceUtil::Mutex m_mutex;
        /// logger
        Logger m_logger;

    public:
        // constructor
        GarbageCollection();
        //@{
        void add(const Address& chunkServer, const Chunk& chk);
        void add(const LocatedChunk& lchk);
        void add(const LocatedChunks& lchks);
        //@}

        ChunksPtr get(const Address& chunkServer);

//         void remove(const Chunk& chk);
//         void remove(const Chunks& chks);
        void remove(const Address& chunkServer);
    };

    inline GarbageCollection::GarbageCollection()
        :m_logger(Logger::getInstance("master"))
    {
    }
}


#endif /* _GARBAGECOLLECTION_HPP */
