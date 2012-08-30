/**
 * @file ChunkServerServiceImpl.cpp
 * Implementation of ChunkServerServiceImpl.
 * 
 * @author Zhifeng YANG
 * @date 05  6 2007
 */
#include <iostream>
#include "master/ChunkServerServiceImpl.hpp"
#include "master/ChunkHelper.hpp"
using namespace tfs;
using namespace std;
void ChunkServerServiceImpl::enroll(const Address& chunkServerAddress, const ::Ice::Current& )
{
    
    LOG4CPLUS_INFO(m_logger, "chunkserver " << chunkServerAddress << " enrolled");
    m_db->m_chunkServers.enroll(chunkServerAddress);
    
}

MasterCommand ChunkServerServiceImpl::sendHeartbeat(const Address& chunkServerAddress, const Heartbeat& hb, const ::Ice::Current& ){
    
    //LOG4CPLUS_DEBUG(m_logger, "chunkserver " << chunkServerAddress << " send heartbeat");

    m_db->m_chunkServers.renewHeartbeat(chunkServerAddress, hb);
    MasterCommand mc;
    mc.command = McDoNothing;
    ChunksPtr pChunks = m_db->m_gc.get(chunkServerAddress);
    if (!pChunks->empty()){
        mc.command = McRemoveChunks;
        mc.chks = *pChunks;
        m_db->m_gc.remove(chunkServerAddress);
        LOG4CPLUS_DEBUG(m_logger, "remove " << *pChunks << "from chunkserver" << chunkServerAddress);
    }

    
    return mc;
}

void ChunkServerServiceImpl::chunkReport(const Address& chunkServerAddress, const Chunks& chks, const ::Ice::Current& ){
    
    LOG4CPLUS_DEBUG(m_logger, "chunkserver " << chunkServerAddress << " report chunks");
    // check exsistence
    Chunks validChunks;
    const Chunk *pChunk;
    for (int i = 0; i < chks.size(); i++){
        if ((pChunk = m_db->m_dir.findChunk(chks[i].id)) == NULL){
            m_db->m_gc.add(chunkServerAddress, chks[i]);
        }
        else{                   // chunk exists
            if (chks[i].size != pChunk->size){
                /// @todo
            }

            if (chks[i].version != pChunk->version){
                /// @todo
            }
            validChunks.push_back(chks[i]);
        }
    }

    m_db->m_chunkServers.setChunks(chunkServerAddress, validChunks);
    m_db->m_activeChunks.add(chunkServerAddress, validChunks);

    
}

void ChunkServerServiceImpl::completeMigrateChunk(const LocatedChunk& lchk, const ::Ice::Current&)
{
    
    LOG4CPLUS_DEBUG(m_logger, "chunkserver complete migrate chunk " << lchk.chk << " to " << lchk.locations);

    const Chunk *pChunk;
    if ((pChunk = m_db->m_dir.findChunk(lchk.chk.id)) == NULL){
        LOG4CPLUS_INFO(m_logger, "No such a chunk " << lchk.chk );
        throw NoSuchChunk("ChunkServerServiceImpl::completeMigrateChunk() unknown chunk");
    }
    m_db->m_activeChunks.add(lchk);
    m_db->m_chunkServers.add(lchk);

    
}
