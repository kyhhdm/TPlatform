/** @file MasterDB.hpp
 * a singleton which stores numbers of data structure used by master.
 * @author YangZhifeng
 * @date 11  5 2007
 */
#ifndef _MASTERDB_HPP
#define _MASTERDB_HPP 1
#include "master/ChunkServerManager.hpp"
#include "master/ActiveChunkManager.hpp"
#include "master/ClientManager.hpp"
#include "fsdirectory/FsJournalManager.hpp"
#include "fsdirectory/FsDirectory.hpp"
#include "master/GarbageCollection.hpp"
#include "master/Statistics.hpp"

namespace tfs{
    class MasterDB
    {
    public:
        static MasterDB* instance();
        /**
         * manage ChunkServer information and chunks belongs to a ChunkServer.
         * map: chunkserver->chunks
         */
        ChunkServerManager m_chunkServers;
        /**
         * map: chunk->chunkservers
         * 
         */
        ActiveChunkManager m_activeChunks;
        /**
         * heartbeat info of all the active clients
         * 
         */
        ClientManager m_activeClients;
        /**
         * file system journal
         * 
         */
        FsJournalManager m_fsJournal;
        /**
         * the directory of TFS
         * 
         */
        FsDirectory m_dir;
        /**
         * garbage collection of chunks
         * 
         */
        GarbageCollection m_gc;
        /**
         * When the system is in safe mode, we are not ready to
         * response to the client's request yet
         * 
         */
        bool m_bSafeMode;
        /**
         * runtime statistics
         * 
         */
        Statistics m_statistics;
    protected:
        MasterDB();
    private:
        /// the only instance of MasterDB
        static MasterDB* _instance;
    };
}

#endif /* _MASTERDB_HPP */
