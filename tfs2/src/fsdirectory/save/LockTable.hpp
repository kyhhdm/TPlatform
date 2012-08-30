/** @file LockTable.hpp
 * LockTable stores all the file locks in system,
 * and provide fast lookup from filename and it's owner.
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
#ifndef _TFSMASTER_LOCKTABLE_HPP
#define _TFSMASTER_LOCKTABLE_HPP 


#include "common/IceGenerated.hpp"
#include "common/Types.hpp"

#include <map>

namespace tfs {
    //enum LockType {ReadLock, WriteLock};    
    class LockTable {

        struct LockInfo{
            std::string filename;
            // 
            // lockCnt value: 
            //      -1 means WriteLock, it's a exclusive lock flag
            //   1...n means ReadLock counter
            int lockCnt;
        };
    public:

        /** Constructor
         * @param [in] 
         * @throws
         */    
        LockTable();
            
        ~LockTable();

        /** Add a lock of lockType for a given file holded by holder.
         * Holder can add duplicated lock for one filename, which occurs 
         * when a client open a file multiple times in one process.
         * lockCnt are designed for this case.
         *
         * @param [in] filename: lock on which file
         * @param [in] holder: owner of the lock
         * @param [in] lockType: read or write lock
         * @throws
         * @return false: when the lock is exist, and parameter lockType is different, or the lockType of the lock is write
         * @return true: read lock can be added for multiple times, but write lock only once
         */    
        bool addItem(const std::string& filename, const std::string& holder, const LockType lockType);

        /** Delete a lock by filename/holder pair
         * Actually, only dec lockCnt and do real deletion when lockCnt meets Zero.
         *
         *
         * @param [in] filename 
         * @param holder: owner of the lock
         * @throws
         * @return :when the operation is going to delete the lock that didn't exist in the map, it'll return false
         */    
        bool deleteItem(const std::string& filename, const std::string& holder);   

        /** Delete all locks hold by holder.
         * 
         * @param holder: owner of the lock
         * @throws std::runtime_error when internal data structure inconsistent
         * @return : number of locks that deleted
         */
        int deleteItem(const std::string& holder);

        /** 
         * Find a lock info by...
         *
         * @param [in]
         * @throws
         * @return : 
         */
        //void findItem(const LockType lockType);

    private:
        std::map<std::string , LockInfo> m_nameIdx;
        std::multimap<std::string , LockInfo, std::less<std::string> > m_holderIdx;

    typedef std::map<std::string , LockInfo>::iterator NameIdxIterator;
    typedef std::multimap<std::string , LockInfo, std::less<std::string> >::iterator HolderIdxIterator;
    typedef std::map<std::string , LockInfo>::value_type NameValueType;
    typedef std::multimap<std::string , LockInfo, std::less<std::string> >::value_type HolderValueType;
    };
}

#endif /* _TFSMASTER_LOCKTABLE_HPP */
