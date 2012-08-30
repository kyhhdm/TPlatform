/** @file ChunkTable.hpp
 * ChunkTable stores all the chunk ids that running in system,
 * and provide fast lookup from id to it's owner, inode.
 *
 * @author PengBo
 * @date 24 7 2007
 *
 * design notes: <br>
 *    1. it is a collection data structure supporting fast lookup ability,  <br>
 *       such as map/hash_map.     <br>
 *  <br>
 *
 */
#ifndef _TFSMASTER_CHUNKTABLE_HPP
#define _TFSMASTER_CHUNKTABLE_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"

namespace tfs {

    class INode;

    class ChunkTable {

    public:

        /** Constructor
         * @param [in] 
         * @throws
         */    
        ChunkTable();
            
        ~ChunkTable();

        /** Add in <id,inode> pair.
         *
         * @param [in] chunkId: 
         * @param [in] inode: the file inode which own this chunk
         * @throws
         * @return : 
         */    
        bool addItem(const Long chunkId, const INode* inode);

        /** Delete <id,*> 
         *
         * @param [in] chunkId 
         * @throws
         * @return : 
         */    
        bool deleteItem(const Long chunkId);                 

        /** 
         * Find Inode the chunk belongs to.
         * 
         * @param [in]  chunkId 
         */
        const INode* findItem(const Long chunkId);

    private:
        std::map<Long,const INode*> m_table;
    };
}

#endif /* _TFSMASTER_CHUNKTABLE_HPP */
