/** @file INode.hpp
 * INode stores matadata of object in namespace,including file and directory.
 *
 * @author PengBo
 * @date 20 7 2007
 *
 *   <br>
 * design notes: <br>
 *   1.use vector to store chunks info, it's fine for there are little search and erase opration on it. <br>  
 *   2.but there are memeory preserving in vector implementation, usally 2K each vector <br>
 *     which means high level of memeory wastes.  <br>
 *   <br>
 */
#ifndef _TFSMASTER_INODE_HPP
#define _TFSMASTER_INODE_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <time.h>

namespace tfs {
    
    typedef std::vector<Chunk>::iterator  ChunkIterator;
    
    class FileInfo;

    class INode {
        //internal data structure
        std::string     m_name;
        std::string     m_description;
        Long            m_size;
        time_t          m_createTime;
        time_t          m_lastModifyTime;
        //bool          m_dirFlag;
        Short           m_flag;     //refer to tfs::slice::FileModeXXX
        Long            m_chunkSize;
        Short           m_replication;
        Chunks          m_chunks;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

    public:
        //1.constructors
        /** Constructor.
         */    
        INode(std::string name, Short replication = MasterConfig::DefaultReplication, 
            Long chunkSize = MasterConfig::DefaultMaxChunkSize, Short flag = 0);

        INode(const INode& other);    
        INode();
            
        ~INode();

        //2. read only accessors
        const std::string& getName() const ;
        const std::string& getDescription() const;
        Long      getSize() const ;
        time_t    getCreateTime() const ;
        time_t    getLastModifyTime() const ;
        Short     getFlag() const;
        const Chunks& getChunks() const;
        
        //3. iterators
        ChunkIterator   getChunksBegin();
        ChunkIterator   getChunksEnd();

        //4. mutable accessors
        void setName(std::string name) ;
        void setDescription(std::string description) ;
        void setSize(Long size) ;
        void setCreateTime(time_t createTime) ;
        void setLastModifyTime(time_t lastModifyTime) ;
        void setFlag(Short flag);
        Short setReplication(Short replication);
        void setChunkSize(Long ChunkSize);

        Chunk* findChunk(Long chunkId);
        void   addChunk(Chunk chunk);
        void   deleteChunk(Chunk chunk);

        //5.helper functions
        void makeFileInfo(FileInfo& fileInfo);

    };

    // inline implementation =================================
    inline INode::~INode(){}            
    inline INode::INode(){
        m_name = "";
        m_description = "";
        m_size = 0;
        m_chunkSize = 0;
        //m_dirFlag = false;
        m_flag = MasterConfig::DefaultFileModeMask;  //0666
        //m_flag &= ~FileModeTypeDir;  //clear dir flag 
        m_replication = 1;
        m_createTime = time(NULL);
        m_lastModifyTime = time(NULL);
    }

    inline INode::INode(const INode& other):m_chunks(other.m_chunks) {
        m_name = other.m_name;
        m_description = other.m_description;
        m_size = other.m_size;
        m_createTime = other.m_createTime;
        m_lastModifyTime = other.m_lastModifyTime;
        //m_dirFlag = other.m_dirFlag;
        m_flag = other.m_flag;
        m_chunkSize = other.m_chunkSize;
        m_replication = other.m_replication;
    }
    
    inline INode::INode(std::string name, Short replication, Long chunkSize, Short flag){
        m_name = name;
        m_size = 0;
        m_chunkSize = chunkSize;
        m_flag = MasterConfig::DefaultFileModeMask | flag;
        if ( m_flag & FileModeTypeDir) {
            m_replication = 1;
        }
        else{
            m_replication = replication;
        }
        m_description = "";
        m_createTime = time(NULL);
        m_lastModifyTime = time(NULL);
    }

    inline  const std::string& INode::getName() const { return m_name; }
    inline  const std::string& INode::getDescription() const { return m_description; }
    inline  Long INode::getSize() const { return m_size; }
    inline  time_t INode::getCreateTime() const { return m_createTime; }
    inline  time_t INode::getLastModifyTime() const { return m_lastModifyTime; }
    inline  Short INode::getFlag() const { return m_flag; }
    inline  const Chunks&  INode::getChunks() const { return m_chunks; }

    inline  ChunkIterator INode::getChunksBegin() { return m_chunks.begin(); }
    inline  ChunkIterator INode::getChunksEnd() { return m_chunks.end(); }

    inline  void INode::setName(std::string name) { m_name = name; }
    inline  void INode::setDescription(std::string description) { m_description = description; }
    inline  void INode::setSize(Long size) { m_size = size; }
    inline  void INode::setCreateTime(time_t createTime) { m_createTime = createTime; }
    inline  void INode::setLastModifyTime(time_t lastModifyTime) { m_lastModifyTime = lastModifyTime; }
    inline  void INode::setFlag(Short flag) { m_flag = flag; }
    inline  Short INode::setReplication(Short replication) { 
        Short retVal = m_replication;
        m_replication = replication;
        return retVal;
    }
    inline  void INode::setChunkSize(Long chunkSize) {m_chunkSize = chunkSize;}

    inline  void INode::addChunk(Chunk chunk) { 
        m_size += chunk.size;
        m_chunks.push_back(chunk); 
    }
    inline  void INode::deleteChunk(Chunk chunk) { 
        for ( ChunkIterator iter = m_chunks.begin(); iter != m_chunks.end(); ++iter){
            if ( (*iter).id == chunk.id ) {
                m_chunks.erase(iter);
                return;
            }
        }
    }

    inline Chunk* INode::findChunk(Long chunkId) {
        for ( ChunkIterator iter = m_chunks.begin(); iter != m_chunks.end(); ++iter){
            if ( (*iter).id == chunkId ) {
                //
                //#TODO, pb, 20070808
                // vector may realign it's items, so the &(*iter) is not stable when 
                // items in collection are moved. It will cause fatal error then.
                //
                return &(*iter);
            }
        }
        return NULL;
    }

    template<class Archive>
    inline void INode::serialize(Archive & ar, const unsigned int version) {
        UNUSED(version);
        ar & m_name & m_description & m_size & m_createTime & m_lastModifyTime & m_flag;
        ar & m_chunkSize & m_replication;
        ar & m_chunks;
    }
}

//
// Non Intrusive Version of Serialization of Chunk class.
// Refer to Boost Serialization Lib Tutorial =>
//      http://www.boost.org/libs/serialization/doc/tutorial.html
//
namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, tfs::slice::Chunk & chunk, const unsigned int version)
{
    UNUSED(version);

    ar & chunk.id;
    ar & chunk.size;
    ar & chunk.version;
}

} // namespace serialization
} // namespace boost

#endif /* _TFSMASTER_INODE_HPP */
