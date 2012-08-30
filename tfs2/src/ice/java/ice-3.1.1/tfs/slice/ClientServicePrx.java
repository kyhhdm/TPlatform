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

public interface ClientServicePrx extends Ice.ObjectPrx
{
    public void open(Address client, String filename, int mode)
	throws LockFail,
	       NoSuchFileOrDir;
    public void open(Address client, String filename, int mode, java.util.Map __ctx)
	throws LockFail,
	       NoSuchFileOrDir;

    public void close(Address client, String filename);
    public void close(Address client, String filename, java.util.Map __ctx);

    public LocatedChunk[] getChunksInfo(Address client, String filename)
	throws NoSuchFileOrDir;
    public LocatedChunk[] getChunksInfo(Address client, String filename, java.util.Map __ctx)
	throws NoSuchFileOrDir;

    public void completeWrittenChunk(LocatedChunk lchk)
	throws NoSuchChunk,
	       UnknownChunkServer;
    public void completeWrittenChunk(LocatedChunk lchk, java.util.Map __ctx)
	throws NoSuchChunk,
	       UnknownChunkServer;

    public void updateChunkInfo(LocatedChunk lchk)
	throws NoSuchChunk;
    public void updateChunkInfo(LocatedChunk lchk, java.util.Map __ctx)
	throws NoSuchChunk;

    public LocatedChunk addChunk(Address client, String filename)
	throws NoChunkAllocated,
	       NoSuchFileOrDir;
    public LocatedChunk addChunk(Address client, String filename, java.util.Map __ctx)
	throws NoChunkAllocated,
	       NoSuchFileOrDir;

    public void abandonAddChunk(Chunk chk)
	throws NoChunkAllocated;
    public void abandonAddChunk(Chunk chk, java.util.Map __ctx)
	throws NoChunkAllocated;

    public void reportBadChunks(LocatedChunk[] chunks);
    public void reportBadChunks(LocatedChunk[] chunks, java.util.Map __ctx);

    public void setReplication(String filename, short replication)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange;
    public void setReplication(String filename, short replication, java.util.Map __ctx)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange;

    public FileInfo getFileInfo(String filename)
	throws NoSuchFileOrDir;
    public FileInfo getFileInfo(String filename, java.util.Map __ctx)
	throws NoSuchFileOrDir;

    public void create(String filename, short replication, long chunkSize)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange;
    public void create(String filename, short replication, long chunkSize, java.util.Map __ctx)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange;

    public void rename(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;
    public void rename(String src, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    public void remove(String src)
	throws LockFail,
	       NoSuchFileOrDir;
    public void remove(String src, java.util.Map __ctx)
	throws LockFail,
	       NoSuchFileOrDir;

    public void mkdir(String src)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName;
    public void mkdir(String src, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName;

    public void renamedir(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;
    public void renamedir(String src, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    public void rmdir(String src)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir;
    public void rmdir(String src, java.util.Map __ctx)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir;

    public FileInfo[] lsdir(String src)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir;
    public FileInfo[] lsdir(String src, java.util.Map __ctx)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir;

    public void concatFiles(String[] srcFiles, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;
    public void concatFiles(String[] srcFiles, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    public void reportHeartbeat(Address clientAddress);
    public void reportHeartbeat(Address clientAddress, java.util.Map __ctx);
}
