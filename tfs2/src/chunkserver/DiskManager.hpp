
/**
 * @file   DiskManager.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Tue Oct 16 10:40:12 2007
 * 
 * @brief  管理磁盘上的chunk块
 * 
 * 
 */

#ifndef _TFS_DISK_MANAGER_HPP
#define _TFS_DISK_MANAGER_HPP

//#include "ChunkManager.hpp"
#include <string>
#include <vector>
#include <map>



namespace tfs
{
    //    const std::string DIR_LIST_FILE_NAME = "dir.list";
    const std::string Str_Meta_Dir_Path_Name = "meta";
    const int Store_Dir_Nums = 50;
    
    class DiskManager
    {
    public:
        DiskManager();
        ~DiskManager();
        bool init(const char * dir_path);
        
        //        bool getChunks(std::vector<ChunkInfo> & v_chunks,const std::string regex=".chk");

        std::string getStorePath(const int64_t chunk_id);

        //just return M size of free disk space
        int64_t getFreespaceM();

        void setDiskChanged();

    private:
        bool checkDirs();

    private:
        std::string m_dir_path;
        
        //        std::vector<std::string,int> m_map_chunk_num_dir;

        //define if or not recomputer the free space
        bool m_change_flag;

        //just the chunk_store dir
        int64_t m_free_space_M; 
        //        std::map<int,
    };    
}


#endif
