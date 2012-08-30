
#ifndef _TRANSFER_IMPL_HPP
#define _TRANSFER_IMPL_HPP

#include "common/ChunkServerHeader.hpp"
#include "Transfer.h"
#include "ChunkManager.hpp"
#include <string>

#define DATA_MAX_LEN 1024*1024;

namespace tfs
{
    class TransferImpl : public tfs::slice::Transfer
    {
    public:
        TransferImpl(ChunkManager * chunk_mgr);
        ~TransferImpl();

        ByteSeq read(Long chunk_id,Int offset,Int len,const ::Ice::Current& = ::Ice::Current());

        int write(Long chunk_id,const ByteSeq & seq,Int offset,Int len,const ::Ice::Current& = ::Ice::Current());

        void addChunk(Long chunk_id,const ::Ice::Current& = ::Ice::Current());
        
        int append(Long chunk_id,const ByteSeq & seq,Int len,const ::Ice::Current& = ::Ice::Current());

        void rollback(Long op_id,const ::Ice::Current& = ::Ice::Current());

		std::string getLocalPath(Long chunk_id,const ::Ice::Current& = ::Ice::Current());

    private:
        ChunkManager * m_chunk_mgr;        
    };
}


#endif

