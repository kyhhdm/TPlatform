/** @file LockTable.cpp
 * LockTable stores all the file locks in system,
 * and provide fast lookup from filename and it's owner.
 *
 * @author PengBo
 * @date 24 7 2007
 *
 */

#include "fsdirectory/LockTable.hpp"
#include <stdexcept>
#include <string>

using namespace tfs;
using namespace std;


LockTable::LockTable()
{
}
            
LockTable::~LockTable()
{
}

bool LockTable::addItem(const string& filename, const string& holder, const LockType lockType)
{
    LockInfo lockInfo;
    HolderIdxIterator holderIter;
    NameIdxIterator nameIter;
    
    if(filename.length()==0 || holder.length()==0) return false;

    nameIter = m_nameIdx.find(filename);
    if(nameIter == m_nameIdx.end() ){
        lockInfo.filename = filename;
        lockInfo.lockCnt = (lockType==WriteLock)? -1: 1;

        m_nameIdx.insert( NameValueType(filename, lockInfo) );
        m_holderIdx.insert( HolderValueType(holder, lockInfo) );
    }
    else{
        if((nameIter->second).lockCnt == -1 || lockType == WriteLock){
            return false;
        }

        //add READLOCK here
        (nameIter->second).lockCnt ++;

        //find holder-filename pair now
        pair<HolderIdxIterator,HolderIdxIterator> ret;
        ret = m_holderIdx.equal_range(holder);
        for(holderIter = ret.first; holderIter != ret.second; ++holderIter ){
            if( filename == ((holderIter->second).filename) ){
                (holderIter->second).lockCnt++;
                return true;
            }
        }

        //not found ,then insert new holder-filename pair
        lockInfo.filename = filename;
        lockInfo.lockCnt = (lockType==WriteLock)? -1: 1;
        m_holderIdx.insert( HolderValueType(holder, lockInfo) );
    }
    return true;
}

bool LockTable::deleteItem(const string& filename, const string& holder)
{
    if(filename.length()==0 || holder.length()==0) return false;

    NameIdxIterator nameIter = m_nameIdx.find(filename);
    HolderIdxIterator holderIter = m_holderIdx.find(holder);
    LockInfo lockInfo;

    if(nameIter == m_nameIdx.end() || holderIter == m_holderIdx.end() ){
        return false;
    }
    else{
        if ((nameIter->second).lockCnt > 1) {
            (nameIter->second).lockCnt--;
        }
        else{
            m_nameIdx.erase(nameIter);
        }

        // multimap erase the element has been sorted by the less<string>
        pair<HolderIdxIterator,HolderIdxIterator> ret;
        ret = m_holderIdx.equal_range(holder);
        for(holderIter = ret.first; holderIter != ret.second; ++holderIter){
            if( (holderIter->second).filename == filename){

                if ((holderIter->second).lockCnt > 1) {
                    (holderIter->second).lockCnt--;
                }
                else{
                    //erase will destory iterator, be careful, 
                    m_holderIdx.erase(holderIter);
                }
                return true;
            }
        }
    }
    return false;
}

int LockTable::deleteItem(const string& holder)
{
    if(holder.length()==0) return false;

    pair<HolderIdxIterator,HolderIdxIterator> ret;
    HolderIdxIterator holderIter;
    NameIdxIterator nameIter;
    int count = 0;

    ret = m_holderIdx.equal_range(holder);
    for(holderIter = ret.first; holderIter != ret.second; ){

        nameIter = m_nameIdx.find((holderIter->second).filename);

        if(nameIter != m_nameIdx.end()){
            if ((holderIter->second).lockCnt > 0 && (nameIter->second).lockCnt >= (holderIter->second).lockCnt){
                //READLOCK here, decrease the lockCnt until zero meets
                (nameIter->second).lockCnt -= (holderIter->second).lockCnt;
                count += (holderIter->second).lockCnt;
                if((nameIter->second).lockCnt == 0){
                    m_nameIdx.erase(nameIter);
                }
            }
            else if((holderIter->second).lockCnt < 0 && (nameIter->second).lockCnt < 0){
                //WriteLock here, delete them
                m_nameIdx.erase(nameIter);
                count ++;
            }
            else {
                //invalid internal state
                throw(runtime_error("holder and file lockCnt inconsistent!"));
            }
        }
        else{
            //invalid internal state
            throw(runtime_error("holder and file table inconsistent!"));

        }

        //erase will destory iterator, be careful, 
        m_holderIdx.erase(holderIter++);
        
    }

    return count;
}

