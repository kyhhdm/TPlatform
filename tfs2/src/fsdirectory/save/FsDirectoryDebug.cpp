/**
 * @file FsDirectoryDebug.cpp
 * An Debuging Implementation of FileSystem Directory Service Interface.
 * 
 * @author Peng Bo
 * @date 2007-09-18
 */

#include "fsdirectory/FsDirectoryDebug.hpp"
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


void FsDirectoryDebug::createFile(const std::string& filename, int maxChunkSize, short replication)
{
    cout << "createFile" << endl 
         << "    filename = " << filename << endl
         << "    maxChunkSize = " << maxChunkSize << endl
         << "    replication = " << replication << endl;

    FsDirectoryImpl::createFile(filename, maxChunkSize, replication);
}

void FsDirectoryDebug::renameFile(const std::string& src, const std::string& dst)
{
    cout << "renameFile " << endl
         << "    src = " << src << endl 
         << "    dst = " << dst << endl;

    FsDirectoryImpl::renameFile(src, dst);
}

void FsDirectoryDebug::deleteFile(const std::string& filename, Chunks& deletedChunks)
{
    FsDirectoryImpl::deleteFile(filename, deletedChunks);

    cout << "deleteFile " << endl
         << "    filename = " << filename << endl
         << "    deletedChunks = " << endl;
    printChunks(deletedChunks);
}

void FsDirectoryDebug::createDir(const std::string& dirname)
{
    FsDirectoryImpl::createDir(dirname);

    cout << "createDir " << endl
         << "    dirname = " << dirname << endl;
}

void FsDirectoryDebug::renameDir(const std::string& src, const std::string& dst)
{
    cout << "renameDir " << endl
         << "    src = " << src << endl
         << "    dst = " << dst << endl;

    FsDirectoryImpl::renameDir(src, dst);

}

void FsDirectoryDebug::deleteDir(const std::string& dirName)
{
    cout << "deleteDir " << endl
         << "    dirName = " << dirName << endl; 

    FsDirectoryImpl::deleteDir(dirName);

}


Chunk FsDirectoryDebug::newChunk(const std::string& filename, const std::string& holder, Long chunkId)
{
    cout << "newChunk " << endl
         << "    filename = " << filename << endl
         << "    holder = " << holder << endl
         << "    chunkId = " << chunkId << endl;

    return FsDirectoryImpl::newChunk(filename, holder, chunkId);
}

bool FsDirectoryDebug::updateChunk(const Chunk& chunk)
{
    cout << "updateChunk " << endl
        << "    chunk.id = " << chunk.id << endl
        << "    chunk.size = " << chunk.size << endl
        << "    chunk.version = " << chunk.version << endl;

    return FsDirectoryImpl::updateChunk(chunk);
}

void FsDirectoryDebug::commitChunk(const Chunk& chunk)
{
    cout << "commitChunk " << endl
         << "    chunk.id = " << chunk.id << endl
         << "    chunk.size = " << chunk.size << endl
         << "    chunk.version = " << chunk.version << endl;

    FsDirectoryImpl::commitChunk(chunk);

}

void FsDirectoryDebug::abandonChunk(const Chunk& chunk)
{
    cout << "abandonChunk " << endl
         << "    chunk.id = " << chunk.id << endl
         << "    chunk.size = " << chunk.size << endl
         << "    chunk.version = " << chunk.version << endl;

    FsDirectoryImpl::abandonChunk(chunk);

}
        

void FsDirectoryDebug::setFileInfo(const std::string& filename, const FileInfo& info)
{
    UNUSED(filename);
    UNUSED(info);

    //TODO
}

Short FsDirectoryDebug::setReplication(const std::string& filename, Short replication)
{
    cout << "setReplication " << endl
         << "    replication = " << replication << endl;

    return FsDirectoryImpl::setReplication(filename, replication);
}

//=============================
void FsDirectoryDebug::printChunks(Chunks& chunks)
{
    cout << "    <id,size,version>:";
    for (int i = 0 ; i< chunks.size() ; i++){
        cout << "<" << chunks[i].id << ", " << chunks[i].size << ", " <<  chunks[i].version << ">";
    }
    cout << endl;
}

