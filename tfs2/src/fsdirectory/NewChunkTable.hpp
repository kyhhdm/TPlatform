/** @file NewChunkTable.hpp
 * NewChunkTable stores all the new added chunks that appending for commit in system,
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
#ifndef _TFSMASTER_NEWCHUNKTABLE_HPP
#define _TFSMASTER_NEWCHUNKTABLE_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"

namespace tfs {

    class INode;


    class NewChunkTable {
        struct NewChunk{
            Long id;   
            std::string holder;
            const INode* inode;
        };
   public:

        /** Constructor
         * @param [in] 
         * @throws
         */    
        NewChunkTable();
            
        ~NewChunkTable();

        /** Add <id,inode> pair into m_table.
         *
         * @param [in] chunkId: 
         * @param [in] holder: owner of the lock
         * @param [in] inode: the file inode which own this chunk
         * @throws
         * @return : 
         */    
        bool addItem(const Long chunkId, const std::string holder, const INode* inode);

        /** Delete <id,*> 
         *
         * @param [in] chunkId 
         * @throws
         * @return : 
         */    
        bool deleteItem(const Long chunkId);   

        /** Delete <*,*,pInode> 
         *
         * @param [in] pInode 
         * @throws
         * @return : chunkid vector that deleted
         */    
        int deleteItem(const INode* pInode, std::vector<Long> deletedIds);   

        /** 
         * Delete <*,holder,*> by holder.
         * 
         * @param holder: owner of the chunk
         * @throws
         * @return : number of chunk ids that deleted
         */
        int deleteItem(const std::string holder, std::vector<Long> deletedIds);

        /** 
         * Find Inode the chunk belongs to.
         * 
         * @param [in] chunkId 
         * @throws
         * @return : 
         */
        const INode* findItem(const Long chunkId);

    private:
        std::map<Long , NewChunk> m_table;  
    };
}

#endif /* _TFSMASTER_NEWCHUNKTABLE_HPP */
