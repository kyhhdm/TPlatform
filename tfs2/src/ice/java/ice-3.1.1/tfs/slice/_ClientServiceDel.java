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

public interface _ClientServiceDel extends Ice._ObjectDel
{
    void open(Address client, String filename, int mode, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir;

    void close(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    LocatedChunk[] getChunksInfo(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir;

    void completeWrittenChunk(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk,
	       UnknownChunkServer;

    void updateChunkInfo(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk;

    LocatedChunk addChunk(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated,
	       NoSuchFileOrDir;

    void abandonAddChunk(Chunk chk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated;

    void reportBadChunks(LocatedChunk[] chunks, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    void setReplication(String filename, short replication, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir,
	       ReplicationOutOfRange;

    FileInfo getFileInfo(String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir;

    void create(String filename, short replication, long chunkSize, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange;

    void rename(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void remove(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir;

    void mkdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName;

    void renamedir(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void rmdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir;

    FileInfo[] lsdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void concatFiles(String[] srcFiles, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir;

    void reportHeartbeat(Address clientAddress, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;
}
