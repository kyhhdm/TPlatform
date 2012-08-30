
#include "ChunkManager.hpp"
#include "util/Logger.hpp"
#include "String.hpp"
#include "FileSystemUtil.hpp"
#include "TaskMgr.hpp"
#include <stdlib.h>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include "String.hpp"

using namespace std;
using namespace tfs;

extern Logger pLogger;


ChunkManager::ChunkManager()
{
//     assert(conf!=NULL);
//     pConf=conf;
}

// int ChunkManager::init()
// {
//     ChunkServerConf * pConf = ChunkServerConf::getInstance();    
//     string chunk_dir=pConf->CHUNK_STORE_DIR;

//     vector<string> vec_chunk;
//     vector<string> vec_chunk_fullpath;
    
//     if(FileUtil::getFiles(chunk_dir,vec_chunk,0)<0){
//         LOG4CPLUS_ERROR(pLogger, "ChunkManager::init():1 sacanDir failed."<<chunk_dir);
//         return -1;
//     }
//     if(FileUtil::getFiles(chunk_dir,vec_chunk_fullpath)<0){
//         LOG4CPLUS_ERROR(pLogger, "ChunkManager::init():2 sacanDir failed."<<chunk_dir);
//         return -1;
//     }

// //     vector<string>::iterator it = vec_chunk.begin();
//     int vec_size=vec_chunk.size();

//     string chunk_log_info;
    
//     for(int i=0;i<vec_size;i++){
//         int64_t id=(int64_t)atoll(vec_chunk[i].c_str());

//         ChunkInfo info;
//         info.mID=id;
//         info.mSize=FileUtil::getFileSize(vec_chunk_fullpath[i]);
//         info.mPath=vec_chunk_fullpath[i];
//         m_chunks[id]=info;

//         chunk_log_info=chunk_log_info+"("+String::Type2String(id)+","+String::Type2String(info.mSize)+")";
//     }
//     LOG4CPLUS_DEBUG(pLogger, "Chunks:"<<chunk_log_info);
    
//     return 1;
// }


int ChunkManager::init()
{
    ChunkServerConf * pConf = ChunkServerConf::getInstance();    
    string chunk_dir=pConf->CHUNK_STORE_DIR;

    if (!m_disk_manager.init(chunk_dir.c_str()))
        return -1;
    
    if (loadChunks(chunk_dir) < 0 )
        return -1;

    LOG4CPLUS_INFO(pLogger, "Disk Avail: "<< m_disk_manager.getFreespaceM()<<" MB");
    return 1;
}

int ChunkManager::loadChunks(const string & str_dir_path)
{
    m_chunks.clear(); //@todo clear or not?
    
    vector<string> vec_chunk_fullpath;

    if ( FileSystemUtil::getAllFiles(vec_chunk_fullpath,str_dir_path,".chk") < 0){
        LOG4CPLUS_ERROR(pLogger, "ChunkManager::loadChunks failed. dir path:"<< str_dir_path);
        return -1;
    }
    
    string chunk_log_info;
    int64_t size_sum = 0LL;
    
    int vec_size = vec_chunk_fullpath.size();
    for (int i=0; i < vec_size; ++i){
        string str_full_path = vec_chunk_fullpath[i];
        int64_t id = (int64_t)atoll( (FileSystemUtil::getBasename(str_full_path)).c_str());
        int file_size = FileSystemUtil::getFileSize(str_full_path);
        
        if (id < 0 || file_size <= 0){
            LOG4CPLUS_ERROR(pLogger, "ChunkManager::loadChunks chunk error, path: "<<str_full_path<<", size:"<<file_size);
            continue;
        }

        //@todo verify the md5 of the chunk

        ChunkInfo info;
        info.mID = id;
        info.mSize = file_size;
        info.mPath = str_full_path;
        //@todo info.mVersion =
        
        m_chunks[id] = info;

        size_sum += file_size;
        chunk_log_info=chunk_log_info+"("+String::Type2String(id)+","+String::Type2String(info.mSize)+")";
    }
    
    LOG4CPLUS_DEBUG(pLogger, "Chunks:"<<chunk_log_info);
    LOG4CPLUS_INFO(pLogger, "Status: "<< m_chunks.size() << " chunks, "<< (size_sum/(1024*1024)) << " M Byte");
    
    return 1;
}

int ChunkManager::getChunkFilePath(string & path,int64_t chunk_id)
{
    boost::mutex::scoped_lock lock2(m_chunk_map_mutex);
    map<int64_t,ChunkInfo>::iterator it =  m_chunks.find(chunk_id);
    if(it == m_chunks.end())
        return -1;
    path = (it->second).mPath;
    return 1;
}


int ChunkManager::getNewChunkFilePath(int64_t chunk_id)
{

			   
    return 1;                   
}

int ChunkManager::addNewChunk(int64_t chunk_id)
{
	if (exsit(chunk_id))
	{
		LOG_ERROR("ChunkManager::addNewChunk() chunk id:"<<chunk_id<<" exsit!");        
		return -1;
	}

	string chunk_path = m_disk_manager.getStorePath(chunk_id);
	ofstream outfile(chunk_path.c_str(),ios::out | ios::trunc);

	ChunkInfo info;
	info.mID = chunk_id;
	info.mPath = chunk_path;
	info.mSize = 0;
	info.mVersion = 1;

	LOG_INFO("ChunkManager::addNewChunk() add new chunk "<< chunk_id << ", path: " << chunk_path);

	boost::mutex::scoped_lock lock(m_chunk_map_mutex);
	m_chunks.insert(make_pair(chunk_id,info));

	return 1;
}

int ChunkManager::getChunkAppendStream(std::ofstream & outfile,int64_t chunk_id)
{
	ChunkInfo chunk_info;
	if (!getChunkInfo(chunk_id,chunk_info))
	{
		return -1;
	}	

	outfile.open(chunk_info.mPath.c_str(),ios::app|ios::binary);
	if(!outfile){
		LOG_ERROR("ChunkManager::getChunkAppendStream() open file path failed:"<<chunk_info.mPath);        
		return -1;
	}

	//    cout<<"Generate tmp file path: "<<tmp_path<<endl;
	LOG_DEBUG("ChunkManager::getChunkAppendStream() file path:"<<chunk_info.mPath);  
    return 1;
}

int ChunkManager::getChunkWriteStream(ofstream & outfile,int64_t chunk_id)
{
    //@todo stream that will write the chunk, so here should have mutex
	
	ChunkInfo chunk_info;
	if (!getChunkInfo(chunk_id,chunk_info))
	{
		return -1;
	}	
    
    outfile.open(chunk_info.mPath.c_str(),ios::app|ios::binary);
    if(!outfile){
        LOG_ERROR("ChunkManager::getChunkWriteStream() open file path failed:"<<chunk_info.mPath);        
        return -1;
    }
    
    //    cout<<"Generate tmp file path: "<<tmp_path<<endl;
    LOG_DEBUG("ChunkManager::getChunkWriteStream() file path:"<<chunk_info.mPath);            

    return 1;
}


/** 
 * 生成新的临时chunk�? * 
 * @param outfile 
 * @param chunk_id 
 * 
 * @return 
 */
int ChunkManager::getNewChunkOutStream(std::ofstream & outfile,int64_t chunk_id)
{
    //@todo 判断chunk_id 是否已经在m_tmp_chunks�? 是否可以resume
    ChunkServerConf * pConf = ChunkServerConf::getInstance();    
    string chunk_dir=pConf->CHUNK_TMP_DIR;

    string id_str=String::Type2String(chunk_id);
    
    string tmp_path=chunk_dir + "/" + id_str + ".chk";
    
    outfile.open(tmp_path.c_str());
    if(!outfile){
        LOG4CPLUS_ERROR(pLogger, "ChunkManager::getNewChunkOutStream() open tmp file path failed:"<<tmp_path);        
        return -1;
    }
    
    //    cout<<"Generate tmp file path: "<<tmp_path<<endl;
    LOG4CPLUS_INFO(pLogger, "ChunkManager::getNewChunkOutStream() generate tmp file path:"<<tmp_path);            

    ChunkInfo info;
    info.mID = chunk_id;
    info.mPath = tmp_path;
    
    boost::mutex::scoped_lock lock(m_tmp_chunk_map_mutex);
    m_tmp_chunks[chunk_id]=info;
    
    return 1;
}

int ChunkManager::getChunkInStream(ifstream & infile,int64_t chunk_id)
{
    boost::mutex::scoped_lock lock(m_chunk_map_mutex);
    
    map<int64_t,ChunkInfo>::iterator it = m_chunks.find(chunk_id);
    if(it==m_chunks.end()){
        LOG4CPLUS_ERROR(pLogger,"ChunkManager::getChunkInStream() can't find chunk id:"<<chunk_id);
        return -1;
    }

    ChunkInfo info=it->second;
    
    infile.open((info.mPath).c_str());
    
    if(!infile){
        LOG4CPLUS_ERROR(pLogger,"ChunkManager::getChunkInStream() can't open file path:"<<info.mPath);
        //@todo 处理出错
        return -1;
    }
    LOG4CPLUS_DEBUG(pLogger,"ChunkManager::getChunkInStream() open file for read:"<<info.mPath);    

    return 1;
}

int ChunkManager::getCapacity()
{
    return 1000;
}

int ChunkManager::getFreespace()
{
    return m_disk_manager.getFreespaceM();
}

int ChunkManager::getWorkload()
{
    TaskMgr * p_task_mgr = TaskMgr::getInstance();
    return p_task_mgr->getDealerNum();
}

map<int64_t,ChunkInfo> ChunkManager::getChunks()
{
    return m_chunks;
}

bool ChunkManager::getChunkInfo(int64_t chunk_id,ChunkInfo & chunk_info)
{
	boost::mutex::scoped_lock lock(m_chunk_map_mutex);
	map<int64_t,ChunkInfo>::iterator it = m_chunks.find(chunk_id);
	if (it == m_chunks.end())
	{
		return false;
	}
	
	chunk_info = it->second;
	return true;
}

/** 
 * 将传输完成的chunk提交到数据管理中
 * 即：将chunk信息�?m_tmp_chunks-->m_chunks
 * @param chunk_id 
 * 
 * @return 
 */
int ChunkManager::commitChunk(int64_t chunk_id)
{
    boost::mutex::scoped_lock lock(m_tmp_chunk_map_mutex);
    
    map<int64_t,ChunkInfo>::iterator it=m_tmp_chunks.find(chunk_id);
    assert(it!=m_tmp_chunks.end());

    if(it==m_tmp_chunks.end())
        return -1;
    
    ChunkInfo chunk_info=(it->second);

//     char buf[128];
//     memset(buf,0,128);
//     snprintf(buf,127,"%ll",chunk_id);
//     string dest_path=buf;
//    ChunkServerConf * pConf = ChunkServerConf::getInstance();
    
//     string chunk_dir=pConf->CHUNK_STORE_DIR;    
//     string dest_path(ts("%s/%lld.chk",chunk_dir.c_str(),chunk_id));
    string dest_path = m_disk_manager.getStorePath(chunk_id);
    
    //    if(FileUtil::renameFile(chunk_info.mPath,dest_path)<0){
    if (!FileSystemUtil::renameFile(chunk_info.mPath,dest_path)){
        LOG4CPLUS_ERROR(pLogger,"ChunkManager::commitChunk() rename file error!"<<chunk_info.mPath<<" -> "<<dest_path);
        //        cout<<"rename file error:"<<chunk_info.mPath<<" to: "<<dest_path<<endl;
        return -1;
    }
    

    LOG4CPLUS_INFO(pLogger,"ChunkManager::commitChunk() move"<<chunk_info.mPath<<" -> "<<dest_path);

    boost::mutex::scoped_lock lock2(m_chunk_map_mutex);
    
    chunk_info.mPath=dest_path;
    chunk_info.mVersion=1;
    chunk_info.mSize = FileSystemUtil::getFileSize(dest_path);
    m_chunks[chunk_id]=chunk_info;
    m_tmp_chunks.erase(it);

    LOG_INFO("ChunkManager::commitChunk() add to table:("<<chunk_info.mID<<","<<chunk_info.mSize<<", V."<<chunk_info.mVersion<<", "<<chunk_info.mPath<<")");

    //设置硬盘大小改变标至
    m_disk_manager.setDiskChanged();
    
    //@todo 把元信息写入meta文件    
    return 1;
}

bool ChunkManager::delChunk(int64_t chunk_id)
{
    
    boost::mutex::scoped_lock lock2(m_chunk_map_mutex);
    map<int64_t,ChunkInfo>::iterator it = m_chunks.find(chunk_id);
    if (it == m_chunks.end()){
        return false;
    }else{
        if (!FileSystemUtil::removeFile((it->second).mPath)){
            LOG_ERROR("ChunkManager::delChunk() delete chunk:" << chunk_id << "failed");            
            return false;
        }
        m_chunks.erase(it);
        LOG_INFO("ChunkManager::delChunk() delete chunk:" << chunk_id << "succ");                    
    }
    return true;
}

bool ChunkManager::exsit(int64_t chunk_id)
{
	boost::mutex::scoped_lock lock2(m_chunk_map_mutex);
	map<int64_t,ChunkInfo>::iterator it = m_chunks.find(chunk_id);
	if (it == m_chunks.end()){
		return false;
	}
    return true;
}

bool ChunkManager::addIOChunk(int64_t chunk_id)
{
	boost::mutex::scoped_lock lock(m_io_chunks_mutex);
	map<int64_t,int>::iterator it = m_io_chunks.find(chunk_id);
	if (it != m_io_chunks.end()){
		return false;
	}
	m_io_chunks.insert(make_pair(chunk_id,1));
	return true;
}

bool ChunkManager::delIOChunk(int64_t chunk_id)
{
	boost::mutex::scoped_lock lock(m_io_chunks_mutex);
	map<int64_t,int>::iterator it = m_io_chunks.find(chunk_id);
	if (it != m_io_chunks.end()){
		m_io_chunks.erase(it);
		return true;
	}

	return false;
}

bool ChunkManager::exsitIOChunk(int64_t chunk_id)
{
	boost::mutex::scoped_lock lock(m_io_chunks_mutex);
	map<int64_t,int>::iterator it = m_io_chunks.find(chunk_id);
	if (it != m_io_chunks.end()){
		return true;
	}
	return false;
}

int ChunkManager::updateChunk(int64_t chunk_id)
{
	ChunkInfo chunk_info;
	if (!getChunkInfo(chunk_id,chunk_info))
	{
		LOG_ERROR("ChunkManager::updateChunk() get Chunk info error!");
		return -1;
	}
	
	int file_size = FileSystemUtil::getFileSize(chunk_info.mPath);
	if (file_size < 0)
	{
		LOG_ERROR("ChunkManager::updateChunk() update Chunk size info error!");
	}

	if (chunk_info.mSize == file_size)
	{
		return 2;
	}
	
	boost::mutex::scoped_lock lock(m_chunk_map_mutex);
	m_chunks.insert(make_pair(chunk_id,chunk_info));

	return 1;
}
