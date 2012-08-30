
#ifndef _TRANSFER_CHUNKSERVER_ICE
#define _TRANSFER_CHUNKSERVER_ICE 1

module tfs
{
    module slice
        {
            
            exception ErrorBase
            {
                string reason;
            };
            // exception TransferError extends ErrorBase
            // {
            // };
            
            exception DataError extends ErrorBase
            {
            };
            exception ChunkError extends ErrorBase
            {
            };
            exception ChunkNotExist extends ErrorBase
            {
            };

            
            sequence<byte> ByteSeq;
            
            interface Transfer
            {
                ByteSeq read(long chunkid,int offset,int len) throws ChunkNotExist,ChunkError;

                int write(long chunkid,ByteSeq bytes,int offset,int len) throws ChunkNotExist,ChunkError,DataError;

                void addChunk(long chunkid) throws ChunkError;
                
                int append(long chunkid,ByteSeq bytes,int len) throws ChunkNotExist,ChunkError,DataError;

                void rollback(long opid) throws ErrorBase;                

				string getLocalPath(long chunkid) throws ChunkError;
            };
        };
    
};

#endif /* _Transfer_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
