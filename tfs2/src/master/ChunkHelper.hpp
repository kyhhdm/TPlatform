/** 
 * @file ChunkHelper.hpp
 * Helper functions of Chunk related class.
 * 
 * @author Zhifeng YANG
 * @date 2007-07-11
 */
#ifndef _CHUNKHELPER_HPP
#define _CHUNKHELPER_HPP 1

#include <iostream>
#include <ext/hash_set>
#include <ext/hash_map>
#include "common/IceGenerated.hpp"
#include "master/AddressHelper.hpp"

namespace tfs
{
    /// global operators
//     inline bool operator == (const Chunk& chk1, const Chunk& chk2)
//     {
//         return chk1.id == chk2.id;
//     }

    inline std::ostream& operator << (std::ostream &os, const Chunk& chk)
    {
        os << "chunk(id:" << chk.id << " size:" << chk.size << " version: " << chk.version << ")";
        return os;
    }

    inline std::ostream& operator << (std::ostream &os, const Chunks& chks)
    {
        os << "chunks(";
        for (int i = 0; i < chks.size(); i++){
            os << "[" << i << "]" << chks[i];
        }
        os << ")";
        return os;
    }
    
    /// functors 
    struct ChunkEqual
    {
        bool operator()(const Chunk& chk1, const Chunk& chk2) const {
            return chk1.id == chk2.id;
        }
    };
    struct ChunkHash
    {
        size_t operator()(const Chunk& chk) const{
            return chk.id;
        }
    };
    // types
    typedef __gnu_cxx::hash_set<Chunk, ChunkHash, ChunkEqual> ChunkSet;
    typedef __gnu_cxx::hash_map<Chunk, AddressSet, ChunkHash, ChunkEqual> ChunkAddressMap;
}


#endif /* _CHUNKHELPER_HPP */
