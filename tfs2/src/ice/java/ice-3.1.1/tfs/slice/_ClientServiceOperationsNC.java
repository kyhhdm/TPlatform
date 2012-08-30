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

public interface _ClientServiceOperationsNC
{
    void open(Address client, String filename, int mode)
	throws LockFail,
	       NoSuchFileOrDir;

    void close(Address client, String filename);

    LocatedChunk[] getChunksInfo(Address client, String filename)
	throws NoSuchFileOrDir;

    void completeWrittenChunk(LocatedChunk lchk)
	throws NoSuchChunk,
	       UnknownChunkServer;

    void updateChunkInfo(LocatedChunk lchk)
	throws NoSuchChunk;

    LocatedChunk addChunk(Address client, String filename)
	throws NoChunkAllocated,
	       NoSuchFileOrDir;

    void abandonAddChunk(Chunk chk)
	throws NoChunkAllocated;

    void reportBadChunks(LocatedChunk[] chunks);

    void setReplication(String filename, short replication)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange;

    FileInfo getFileInfo(String filename)
	throws NoSuchFileOrDir;

    void create(String filename, short replication, long chunkSize)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange;

    void rename(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void remove(String src)
	throws LockFail,
	       NoSuchFileOrDir;

    void mkdir(String src)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName;

    void renamedir(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void rmdir(String src)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir;

    FileInfo[] lsdir(String src)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void concatFiles(String[] srcFiles, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void reportHeartbeat(Address clientAddress);
}
