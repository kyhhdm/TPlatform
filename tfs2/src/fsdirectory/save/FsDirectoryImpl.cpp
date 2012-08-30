/**
 * @file FsDirectoryImpl.cpp
 * Implementation of FileSystem Directory Service Interface.
 * 
 * @author Peng Bo
 * @date 2007-07-10
 */

#include "fsdirectory/FsDirectoryImpl.hpp"
#include "fsdirectory/INode.hpp"
#include "fsdirectory/DirNode.hpp"
#include "fsdirectory/DirTree.hpp"
#include "fsdirectory/LockTable.hpp"
#include "fsdirectory/ChunkTable.hpp"
#include "fsdirectory/NewChunkTable.hpp"
#include "fsdirectory/Path.hpp"
#include "common/Exception.hpp"
#include <deque>
#include <string>
#include <fstream>
#include <cstdlib>
#include <assert.h>

using namespace std;
using namespace tfs;

BOOST_CLASS_TRACKING(tfs::DirTree, boost::serialization::track_never)
//BOOST_CLASS_TRACKING(tfs::DirNode, boost::serialization::track_never)
//BOOST_CLASS_TRACKING(tfs::INode, boost::serialization::track_never)
//BOOST_CLASS_TRACKING(tfs::slice::Chunk, boost::serialization::track_never)


FsDirectoryImpl::FsDirectoryImpl():m_logger(Logger::getInstance("fsdirectory"))
{
    //init the randomizer
    srand((int)(time(NULL)));

    //Build a nul tree with only one root node
    m_pDirTree = new DirTree(NULL);

    m_pLockTable = new LockTable();
    m_pChunkTable = new ChunkTable();
    m_pNewChunkTable = new NewChunkTable();
}

FsDirectoryImpl::~FsDirectoryImpl()
{
    if(m_pDirTree) delete m_pDirTree;
    if(m_pLockTable) delete m_pLockTable;
    if(m_pChunkTable) delete m_pChunkTable;
    if(m_pNewChunkTable) delete m_pNewChunkTable;
}

bool FsDirectoryImpl::exists(const std::string &name)
{
    Path path(name);
    DirNode* pDirNode;

    if ( path.isPureDir() ) {
        //pure directory name
        pDirNode = m_pDirTree->findDirNode(name);
        return (pDirNode != NULL);
    }    
    else{
        //contains file name
        pDirNode = m_pDirTree->findDirNode(path.getDirName());
        
        if(!pDirNode) return false;

        return (NULL != pDirNode->findFile(path.getFileName()));
    }
}

bool FsDirectoryImpl::isDir(const std::string& dirName) const
{
    return (NULL != m_pDirTree->findDirNode(dirName + "/"));
}


void FsDirectoryImpl::createFile(const std::string& filename, int maxChunkSize, short replication)
{
    Path path(filename);
    DirNode* pDirNode;

    if (path.isPureDir()){
        LOG4CPLUS_WARN(m_logger, "the filename is pure dir :" << filename);
        throw InvalidFileOrDirName("the filename is pure dir");
    }

    if( (pDirNode = m_pDirTree->createDirNodes(path.getDirName())) ) {
        if (pDirNode->findFile(path.getFileName())){
            LOG4CPLUS_WARN(m_logger, "file already exist :" << path.getFileName());
            throw FileOrDirAlreadyExists("file already exist error");
        }

        INode inode(path.getFileName(), replication, maxChunkSize);

        //->addFile should have bool return value     
        pDirNode->addFile(inode);

    }
    else{
        LOG4CPLUS_WARN(m_logger, "the path name is invalid : " << path.getDirName());
        throw InvalidFileOrDirName("the path name is invalid");
    }
}

void FsDirectoryImpl::renameFile(const std::string& src, const std::string& dst)
{
    Path srcPath(src), dstPath(dst);
    DirNode* pDirNode, *pDstDirNode;
    INode* pINode;

    //preconditions check
    if (srcPath.isPureDir() || dstPath.isPureDir()){
        LOG4CPLUS_WARN(m_logger, "src or dst are not filename : src=" << src << " dst=" << dst);
        throw InvalidFileOrDirName("renameFile : src or dst are not filename");
    }
    if(m_pDirTree->findINode(dst)) {
        LOG4CPLUS_WARN(m_logger, "dst already exist : dst=" << dst);
        throw FileOrDirAlreadyExists("renameFile : dst");
    }
    
    //#TODO, lock

    //get source file INode
    pDirNode = m_pDirTree->findDirNode(srcPath.getDirName());
    if(!pDirNode) {
        LOG4CPLUS_WARN(m_logger, "src directory not exist :" << srcPath.getDirName());
        throw NoSuchFileOrDir("renameFile : src directory");
    }

    if (!(pINode = pDirNode->findFile(srcPath.getFileName()))){
        LOG4CPLUS_WARN(m_logger, "src file not exist :" << srcPath.getFileName());
        throw NoSuchFileOrDir("renameFile : src filename");
    }

    //create destination
    if(!( pDstDirNode = m_pDirTree->createDirNodes(dstPath.getDirName()) )) {
        LOG4CPLUS_WARN(m_logger, "invalid dst path name : "<< dstPath.getDirName());
        throw InvalidFileOrDirName("renameFile : dst");
    }

    //#TODO,this operation change meta data, make it atomic
    {
        pDirNode->deleteFile(srcPath.getFileName(), DirNode::ReserveNodeInDelete);
        pINode->setName(dstPath.getFileName());
        pDstDirNode->addFile(pINode);
        //pDstDirNode->addFile(*pINode);
        //delete pINode;
    }
}

void FsDirectoryImpl::deleteFile(const std::string& filename, Chunks& deletedChunks)
{
    Path path(filename);
    DirNode* pDirNode;
    INode* pINode;

    //preconditions check
    if (path.isPureDir() ){
        LOG4CPLUS_WARN(m_logger, "deleteFile, but filename is a pure dir " << filename);
        throw InvalidFileOrDirName("deleteFile : is pure dir");
    }
    
    //#TODO, lock

    pDirNode = m_pDirTree->findDirNode(path.getDirName());
    if(!pDirNode) {
        LOG4CPLUS_WARN(m_logger, "directory not exist :" << path.getDirName());
        throw NoSuchFileOrDir("deleteFile : directory");
    }

    if (!(pINode = pDirNode->findFile(path.getFileName()))){
        LOG4CPLUS_WARN(m_logger, "file not exist : " << path.getFileName());
        throw NoSuchFileOrDir("deleteFile : filename");
    }

    Chunks chunks = pINode->getChunks();
    deletedChunks.assign(chunks.begin(), chunks.end());

    //#BUGFIX, [#13] INode:findChunk segment fatal error
    //ChunkTable not synchronized with deleteFile
    //
    for( int i = 0; i < chunks.size() ; i++){
        m_pChunkTable->deleteItem(chunks[i].id);
    }

    //#BUGFIX, [#17] INode:findChunk segment fatal error
    //NewChunkTable not synchronized with deleteFile
    //
    vector<Long> deleteNewChunkIds;
    if(m_pNewChunkTable->deleteItem(pINode, deleteNewChunkIds)){
        string chunkIdList;
        for (int i = 0 ; i < deleteNewChunkIds.size(); i++){
            chunkIdList += deleteNewChunkIds[i];
            chunkIdList += " ";
        }
        LOG4CPLUS_WARN(m_logger, "delete newchunks not committed: " << chunkIdList);
    }

    pDirNode->deleteFile(path.getFileName());
}


void FsDirectoryImpl::concatFiles(const std::vector<std::string>& srcFiles, const std::string& dstFile)
{
    Path dstPath(dstFile);
    DirNode* pDirNode, *pDstDirNode;
    INode* pINode;

    //preconditions check
    if (dstPath.isPureDir()){
        LOG4CPLUS_WARN(m_logger, "dst are not filename : dst=" << dstFile);
        throw InvalidFileOrDirName("renameFile : dst are not filename");
    }
    if(m_pDirTree->findINode(dstFile)) {
        LOG4CPLUS_WARN(m_logger, "dst already exist : dst=" << dstFile);
        throw FileOrDirAlreadyExists("renameFile : dst");
    }
    for (int i = 0 ; i < srcFiles.size(); i++){
        Path srcPath(srcFiles[i]);
        if (srcPath.isPureDir() ){
            LOG4CPLUS_WARN(m_logger, "src are not filename : src=" << srcFiles[i] );
            throw InvalidFileOrDirName("renameFile : src are not filename");
        }

        pDirNode = m_pDirTree->findDirNode(srcPath.getDirName());
        if(!pDirNode) {
            LOG4CPLUS_WARN(m_logger, "src directory not exist :" << srcPath.getDirName());
            throw NoSuchFileOrDir("renameFile : src directory");
        }

        if (!(pINode = pDirNode->findFile(srcPath.getFileName()))){
            LOG4CPLUS_WARN(m_logger, "src file not exist :" << srcPath.getFileName());
            throw NoSuchFileOrDir("renameFile : src filename");
        }

    }
    //create destination
    if(!( pDstDirNode = m_pDirTree->createDirNodes(dstPath.getDirName()) )) {
        LOG4CPLUS_WARN(m_logger, "invalid dst path name : "<< dstPath.getDirName());
        throw InvalidFileOrDirName("renameFile : dst");
    }


    //#TODO, lock
    INode* pDstINode;
    for (int i = 0 ; i < srcFiles.size(); i++){
        Path srcPath(srcFiles[i]);
        pDirNode = m_pDirTree->findDirNode(srcPath.getDirName());
        if(!pDirNode) {
            LOG4CPLUS_WARN(m_logger, "src directory not exist :" << srcPath.getDirName());
            throw NoSuchFileOrDir("renameFile : src directory");
        }

        if (!(pINode = pDirNode->findFile(srcPath.getFileName()))){
            LOG4CPLUS_WARN(m_logger, "src file not exist :" << srcPath.getFileName());
            throw NoSuchFileOrDir("renameFile : src filename");
        }

        //#TODO,this operation change meta data, make it atomic
        {
            if(i == 0){
                pDirNode->deleteFile(srcPath.getFileName(), DirNode::ReserveNodeInDelete);
                //use the first file inode
                pINode->setName(dstPath.getFileName());
                pDstDirNode->addFile(pINode);
                pDstINode = pINode;
            }
            else{
                //const Chunks& chunks = pDstINode->getChunks();
                //chunks.insert(chunks.end(), pINode->getChunksBegin(), 
                //        pINode->getChunksEnd());
                //pDstINode->setSize( pDstINode->getSize() + pINode->getSize());
                
                for (ChunkIterator iter = pINode->getChunksBegin(); iter != pINode->getChunksEnd(); ++iter ){
                    pDstINode->addChunk(*iter);
                }
                
                //delete other iNodes
                pDirNode->deleteFile(srcPath.getFileName());
                //delete pINode;
            }
        }
    }
}

void FsDirectoryImpl::createDir(const std::string& dirname)
{
    Path path(dirname+"/");
    
    if (m_pDirTree->findDirNode(path.getDirName())) {
        LOG4CPLUS_WARN(m_logger, "directory already exist:" << path.getDirName());
        throw FileOrDirAlreadyExists("directory already exist:" + path.getDirName());   
    }

    if (!m_pDirTree->createDirNodes(path.getDirName())) {
        LOG4CPLUS_WARN(m_logger, "invalid directory name:" << path.getDirName());
        throw InvalidFileOrDirName("invalid directory name:" + path.getDirName());
    }
    
}

void FsDirectoryImpl::renameDir(const std::string& src, const std::string& dst)
{
    Path srcPath(src + "/"), dstPath(dst + "/");
    DirNode* pDirNode, *pDstDirNode;

    //#TODO, lock

    //#TODO, circle detection in src and dst, 
    // src should not be sub string to dst, otherwise there will be circle
    // exception type should be InvalidParameter
    // #BUGFIX, 1017, pb, should be dst.find(src+"/") other than dst.find(src)
    if( 0 == dstPath.getDirName().find(srcPath.getDirName()) ){
        LOG4CPLUS_WARN(m_logger, "src is child of dst : src=" << src << " dst=" << dst);
        throw InvalidFileOrDirName("renameDir: dst should not be child of src");
    }


    //get source Dir
    pDirNode = m_pDirTree->findDirNode(srcPath.getDirName());
    if(!pDirNode) {
        LOG4CPLUS_WARN(m_logger, "src directory not exist : " << srcPath.getDirName());
        throw NoSuchFileOrDir("renameDir : src directory");
    }

    //create destination
    if( (pDstDirNode = m_pDirTree->findDirNode(dstPath.getDirName())) ){
        // dst exist, then move src into dst
        //pDirNode->getParent()->deleteChild(pDirNode, DirNode::ReserveNodeInDelete);
        //pDstDirNode->addChild(pDirNode);
        LOG4CPLUS_WARN(m_logger, "dst directory already exist : " << dstPath.getDirName());
        throw FileOrDirAlreadyExists("renameDir: dst ");
    }
    else{
        //dst doesn't exist, then move src into dst's parent
        if(!( pDstDirNode = m_pDirTree->createDirNodes(dstPath.getDirName()) )) {
            LOG4CPLUS_WARN(m_logger, "invliad dst directory name : " << dstPath.getDirName());
            throw InvalidFileOrDirName("renameDir : dst");
        }

        //#TODO,this operation change meta data, make it atomic
        {
            pDirNode->getParent()->deleteChild(pDirNode, DirNode::ReserveNodeInDelete);
            pDirNode->getINode()->setName(pDstDirNode->getName());
            pDstDirNode->getParent()->addChild(pDirNode);
            pDstDirNode->getParent()->deleteChild(pDstDirNode);
        }
    }
    
}

void FsDirectoryImpl::deleteDir(const std::string& dirName)
{
    Path path(dirName+"/");
    DirNode* pDirNode;

    //#TODO, lock

    pDirNode = m_pDirTree->findDirNode(path.getDirName());

    if(!pDirNode) {
        LOG4CPLUS_WARN(m_logger, "directory not exist : " << path.getDirName());
        throw NoSuchFileOrDir("deleteDir:");
    }
    else if(pDirNode == m_pDirTree->getRoot()){
        //don't delete root node
        LOG4CPLUS_WARN(m_logger, "deleting ROOT directory canceled");
        throw InvalidFileOrDirName("deleteDir: ROOT directory can't be deleted"); 
    }

    //check empty directory
    INodeIterator iter = pDirNode->getFilesBegin();
    if( iter != pDirNode->getFilesEnd()) {
        LOG4CPLUS_WARN(m_logger, "directory not empty");
        throw InvalidFileOrDirName("deleteDir: dir not empty"); 
    }
    DirNodeIterator iterDir = pDirNode->getChildrenBegin();
    if( iterDir != pDirNode->getChildrenEnd()) {
        LOG4CPLUS_WARN(m_logger, "directory not empty");
        throw InvalidFileOrDirName("deleteDir: dir not empty"); 
    }

    pDirNode->getParent()->deleteChild(pDirNode);
    
}

FileInfo FsDirectoryImpl::getFileInfo(const std::string& name) //const
{
    FileInfo info;
    INode* pINode;

    pINode = m_pDirTree->findINode(name);    
    
    if(!pINode) {
        LOG4CPLUS_WARN(m_logger, "name not exist : " << name);
        throw NoSuchFileOrDir("name not exist!");
    }

    pINode->makeFileInfo(info);

    return info;
}

FilesInfoPtr FsDirectoryImpl::readDir(const std::string& dirname) //const
{
    FilesInfoPtr pFilesInfo(new FilesInfo());
    FileInfo info;
    //#BUGFIX #item 5, ls /root/test/dd error
    Path path(dirname + "/");
    DirNode* pDirNode;

    //#NOTICE, findDirNode() must give a path name with "/" tailed.
    pDirNode = m_pDirTree->findDirNode(path.getDirName());    
    
    if(!pDirNode){
        LOG4CPLUS_WARN(m_logger, "direcoty not exist" << path.getDirName());
        throw NoSuchFileOrDir("readDir : dirname");
    }

    //iterate through all child dirs
    for ( DirNodeIterator iter =  pDirNode->getChildrenBegin();
        iter != pDirNode->getChildrenEnd(); ++iter){  
        (*iter)->getINode()->makeFileInfo(info);
        pFilesInfo->push_back(info);
    }

    //iterate through all files in this dir
    for ( INodeIterator iter =  pDirNode->getFilesBegin();
        iter != pDirNode->getFilesEnd(); ++iter){  
        (*iter)->makeFileInfo(info);
        pFilesInfo->push_back(info);
    }

    return pFilesInfo;
}

const Chunk* FsDirectoryImpl::findChunk(const Long chunkId)
{
    INode* pInode;

    pInode = (INode*)m_pChunkTable->findItem(chunkId);
    //
    //#TODO, pb, 20070808 , it's not suitbal for batch operation, for it seams very slow.
    // so it maybe better to design another interface for batch mode scrutinizing on all chunks
    // in system.
    //
    if(pInode) return (pInode->findChunk(chunkId));

    //pInode = (INode*)m_pNewChunkTable->findItem(chunkId);
    //#TODO, pb, 20070808 , it's not suitbal for batch operation, for it seams very slow.
    //if(pInode) return (pInode->findChunk(chunkId));

    return NULL;
}

bool FsDirectoryImpl::updateChunk(const Chunk& chunk)
{
    INode* pInode;

    pInode = (INode*)m_pChunkTable->findItem(chunk.id);
    if(pInode){
        Chunk* theChunk = pInode->findChunk(chunk.id);
        if(theChunk) {
            if(( theChunk->id == chunk.id)&&(theChunk->size == chunk.size)){
                return false;
            }
            else{
                pInode->setSize(pInode->getSize() + chunk.size - theChunk->size);

                theChunk->id = chunk.id;
                theChunk->size = chunk.size;
                return true;
            }
        }
        else{
            LOG4CPLUS_WARN(m_logger, "updateChunk a non-exist chunk" 
                << "id=" << chunk.id << " version=" << chunk.version << "size=" << chunk.size);
            throw NoSuchChunk("FsDirectoryImpl::updateChunk: chunk not found in the inode.");
        }
    }
    else{
        LOG4CPLUS_WARN(m_logger, "updateChunk a non-exist chunk" 
            << "id=" << chunk.id << " version=" << chunk.version << "size=" << chunk.size);
        throw NoSuchChunk("FsDirectoryImpl::updateChunk: inode not found for this chunk.");
    }

}

Chunk FsDirectoryImpl::newChunk(const std::string& filename, const std::string& holder, Long chunkId)
{
    INode* pINode;
    Chunk chunk;

    //file existence checking
    pINode = m_pDirTree->findINode(filename);    
    if(!pINode) {
        LOG4CPLUS_WARN(m_logger, "file not exist!" << filename);
        throw NoSuchFileOrDir("file not exist!");
    }
    else if(pINode->getFlag() & FileModeTypeDir) {
        LOG4CPLUS_WARN(m_logger, "new chunk for directory!" << filename);
        throw NoSuchFileOrDir("new chunk for directory!");
    }

    //
    //check if holder already allocated a new chunk on this file
    //in multiple file open in one process, this check is no use.
    //m_pNewChunkTable->findItem();
    //

    if( chunkId == 0LL) {
        //allocate a new chunk

        do {
            //!it's not same to ((Long)rand())<<32 + (Long)rand()
            chunkId = ((Long)rand())<<32 ;
            chunkId += (Long)rand();
        }while ( chunkId == 0LL || m_pChunkTable->findItem(chunkId) || m_pNewChunkTable->findItem(chunkId) );
    }

    m_pNewChunkTable->addItem(chunkId, holder, pINode);

    //chunk structure has no constructor, that's a pity
    chunk.id = chunkId;
    chunk.size = 0;
    chunk.version = 0;

    return chunk;
}

void FsDirectoryImpl::commitChunk(const Chunk& chunk)
{
    INode* pINode;

    pINode = (INode*)m_pNewChunkTable->findItem(chunk.id);

    if ( !pINode ) {
        LOG4CPLUS_WARN(m_logger, "commit a unalloacted chunk :" 
                << "id=" << chunk.id << " version=" << chunk.version << "size=" << chunk.size);
        throw NoChunkAllocated("commit a unalloacted chunk");
    }
    pINode->addChunk(chunk);

    m_pNewChunkTable->deleteItem(chunk.id);
    m_pChunkTable->addItem(chunk.id, pINode);

}

void FsDirectoryImpl::abandonChunk(const Chunk& chunk)
{
    INode* pINode;

    pINode = (INode*)m_pNewChunkTable->findItem(chunk.id);

    if ( !pINode ) {
        LOG4CPLUS_WARN(m_logger, "abandon a unalloacted chunk" 
                << "id=" << chunk.id << " version=" << chunk.version << "size=" << chunk.size);
        throw NoChunkAllocated("abandon a unalloacted chunk");
    }

    m_pNewChunkTable->deleteItem(chunk.id);

}
        
//bool updateChunk(const Chunk& chunk)

const Chunks& FsDirectoryImpl::getFileChunks(const std::string& filename) //const
{
    INode* pINode;

    pINode = m_pDirTree->findINode(filename);    
    
    if(!pINode) {

        LOG4CPLUS_WARN(m_logger, "file not exist:" << filename);

        throw NoSuchFileOrDir("file not exist!");

    }

    //should not use smart pointer here, 
    //user can't not release memeory for the Chunks object
    //it is inside INode, must has eternal life there
    //ChunksPtr pChunks(pINode->getChunks());
    //return pChunks;

    return pINode->getChunks();
}


void FsDirectoryImpl::setFileInfo(const std::string& filename, const FileInfo& info)
{
    UNUSED(filename);
    UNUSED(info);
    //TODO,
}

Short FsDirectoryImpl::setReplication(const std::string& filename, Short replication)
{
    INode* pINode;

    pINode = m_pDirTree->findINode(filename);    
    
    if(!pINode) {
        LOG4CPLUS_WARN(m_logger, "file not exist: " << filename);
        throw NoSuchFileOrDir("file not exist!");

    }

    return pINode->setReplication(replication);
}
        

void FsDirectoryImpl::obtainLock(const std::string& filename, const std::string& holder, LockType lockType)
{

    if( !m_pLockTable->addItem(filename, holder, lockType)) {
        string errorMessage = "fail in obtainLock(" + filename + ", " + holder + 
            ((lockType==WriteLock)?"WRITELOCK":"READLOCK") + ")";
        LOG4CPLUS_WARN(m_logger, errorMessage);
        throw LockFail(errorMessage);
    }
}

void FsDirectoryImpl::releaseLock(const std::string& filename, const std::string& holder)
{
    if( !m_pLockTable->deleteItem(filename, holder)) {
        string errorMessage = "fail in releaseLock(" + filename + ", " + holder + ")";
        LOG4CPLUS_WARN(m_logger, errorMessage);
        throw LockFail(errorMessage);
    }
}

        
void FsDirectoryImpl::releaseResource(const std::string& holder)
{
    try{
        int resourceCnt = m_pLockTable->deleteItem(holder);
        LOG4CPLUS_INFO(m_logger, "release <" << resourceCnt << "> lock resources for " << holder);
    }
    catch(runtime_error& e){
        string errorMessage = "fail in releaseResource(" + holder + ")";
        LOG4CPLUS_WARN(m_logger, errorMessage);
        throw LockFail(errorMessage);
    }

    vector<Long> deleteNewChunkIds;
    if(m_pNewChunkTable->deleteItem(holder, deleteNewChunkIds)){
        string chunkIdList;
        for (int i = 0 ; i < deleteNewChunkIds.size(); i++){
            chunkIdList += deleteNewChunkIds[i] ;
            chunkIdList += " ";
        }
        LOG4CPLUS_WARN(m_logger, "release newchunks not committed: " << chunkIdList);
    }

}

void FsDirectoryImpl::save(const std::string& imgFileName)
{
    // make an archive
    std::ofstream ofs(imgFileName.c_str());
    boost::archive::binary_oarchive oa(ofs);

    //#TODO, directly << DirTree* always fail, ???
    //oa << m_pDirTree;
    DirTree tree(m_pDirTree->getRoot());
    oa << tree;
    tree.setRoot(NULL);
}

void FsDirectoryImpl::load(const std::string& imgFileName)
{
    //clear all runtime status data
    clearRuntimeData();

    // load from an archive
    if(m_pDirTree) delete m_pDirTree;
    m_pDirTree = new DirTree();

    std::ifstream ifs(imgFileName.c_str());
    boost::archive::binary_iarchive ia(ifs);
    //ia >> m_pDirTree;

    DirTree tree;
    ia >> tree;
    m_pDirTree->setRoot(tree.getRoot());
    tree.setRoot(NULL);

    // rebuild runtime status data
    rebuildRuntimeData();

}

//===============private member methods here ====================
void FsDirectoryImpl::clearRuntimeData()
{
    if(m_pLockTable) delete m_pLockTable;
    if(m_pChunkTable) delete m_pChunkTable;
    if(m_pNewChunkTable) delete m_pNewChunkTable;

    m_pLockTable = new LockTable();
    m_pChunkTable = new ChunkTable();
    m_pNewChunkTable = new NewChunkTable();
}

void FsDirectoryImpl::rebuildRuntimeData()
{
    //rebuild ChunkTable by walk through the tree
    DirNode* pDirNode = m_pDirTree->getRoot();
    deque<DirNode*> waitQueue;
    
    //waitQueue.
    waitQueue.push_back(pDirNode);

    while(waitQueue.size()!=0){
        pDirNode = waitQueue[0];
        waitQueue.pop_front();

        //add children node into queue
        tfs::DirNodeIterator iter;
        for ( iter = pDirNode->getChildrenBegin(); iter != pDirNode->getChildrenEnd(); ++iter) {
            waitQueue.push_back(*iter);
        }

        //deal with this node
        tfs::DirNodeIterator dirNodeIter;
        tfs::INodeIterator inodeIter;
        tfs::ChunkIterator chunkIter;

        for ( inodeIter = pDirNode->getFilesBegin(); inodeIter != pDirNode->getFilesEnd() ; ++inodeIter) {
            for ( chunkIter = (*inodeIter)->getChunksBegin(); chunkIter != (*inodeIter)->getChunksEnd(); ++chunkIter) {
                m_pChunkTable->addItem((*chunkIter).id, *inodeIter);
            }
        }
    }

}
