/**
 * @file   ChunkManager.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sun Jul  8 21:55:45 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef _CHUNK_MANAGER_HPP_
#define _CHUNK_MANAGER_HPP_
#include "common/ChunkServerHeader.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "ChunkServerConf.hpp"
#include "DiskManager.hpp"
#include "String.hpp"
#include <stdint.h>
#include <string>
#include <fstream>
#include <map>

namespace tfs
{
    class ChunkInfo
    {
    public:
        ChunkInfo(){}
        int64_t mID;
        int mSize;
        std::string mPath;
        int mVersion;
    };
    class ChunkManager
    {
    public:
        ChunkManager();
        ~ChunkManager();
        //        ChunkManager(ChunkServerConf * conf);

        int init();
        
        int getChunkFilePath(std::string &path,int64_t chunk_id);
        
        int getNewChunkFilePath(int64_t chunk_id);

		int addNewChunk(int64_t chunk_id);
        int getChunkWriteStream(std::ofstream & outfile,int64_t chunk_id);
        int getChunkAppendStream(std::ofstream & outfile,int64_t chunk_id);
        int getChunkInStream(std::ifstream & infile,int64_t chunk_id);

		//refresh chunk info
		int updateChunk(int64_t chunk_id);

        
        int getNewChunkOutStream(std::ofstream & outfile,int64_t chunk_id); //生成一个新的临时的Chunk�?
        

        int getCapacity();
        int getFreespace();
        int getWorkload();
 
		bool getChunkInfo(int64_t chunk_id,ChunkInfo & chunk_info);
        std::map<int64_t,ChunkInfo> getChunks();        

        int commitChunk(int64_t chunk_id);

        bool exsit(int64_t chunk_id);
        
        bool delChunk(int64_t chunk_id);


		bool addIOChunk(int64_t chunk_id);
		bool delIOChunk(int64_t chunk_id);
		bool exsitIOChunk(int64_t chunk_id);

    private:
        int loadChunks(const std::string & str_path);
        
    private:
        ChunkServerConf * pConf;

        DiskManager m_disk_manager;        
        
        std::map<int64_t,ChunkInfo> m_chunks;

        std::map<int64_t,ChunkInfo> m_tmp_chunks;

        std::map<int64_t,int> m_io_chunks;

        boost::mutex m_chunk_map_mutex;
        boost::mutex m_tmp_chunk_map_mutex;

		boost::mutex m_io_chunks_mutex;
        
    };

}
#endif
