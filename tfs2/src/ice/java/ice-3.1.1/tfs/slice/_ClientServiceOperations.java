// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1

package tfs.slice;

public interface _ClientServiceOperations
{
    void open(Address client, String filename, int mode, Ice.Current __current)
	throws LockFail,
	       NoSuchFileOrDir;

    void close(Address client, String filename, Ice.Current __current);

    LocatedChunk[] getChunksInfo(Address client, String filename, Ice.Current __current)
	throws NoSuchFileOrDir;

    void completeWrittenChunk(LocatedChunk lchk, Ice.Current __current)
	throws NoSuchChunk,
	       UnknownChunkServer;

    void updateChunkInfo(LocatedChunk lchk, Ice.Current __current)
	throws NoSuchChunk;

    LocatedChunk addChunk(Address client, String filename, Ice.Current __current)
	throws NoChunkAllocated,
	       NoSuchFileOrDir;

    void abandonAddChunk(Chunk chk, Ice.Current __current)
	throws NoChunkAllocated;

    void reportBadChunks(LocatedChunk[] chunks, Ice.Current __current);

    void setReplication(String filename, short replication, Ice.Current __current)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange;

    FileInfo getFileInfo(String filename, Ice.Current __current)
	throws NoSuchFileOrDir;

    void create(String filename, short replication, long chunkSize, Ice.Current __current)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange;

    void rename(String src, String dst, Ice.Current __current)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void remove(String src, Ice.Current __current)
	throws LockFail,
	       NoSuchFileOrDir;

    void mkdir(String src, Ice.Current __current)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName;

    void renamedir(String src, String dst, Ice.Current __current)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void rmdir(String src, Ice.Current __current)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir;

    FileInfo[] lsdir(String src, Ice.Current __current)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void concatFiles(String[] srcFiles, String dst, Ice.Current __current)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void reportHeartbeat(Address clientAddress, Ice.Current __current);
}
