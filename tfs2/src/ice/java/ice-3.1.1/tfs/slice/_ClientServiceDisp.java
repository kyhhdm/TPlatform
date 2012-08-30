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

public abstract class _ClientServiceDisp extends Ice.ObjectImpl implements ClientService
{
    protected void
    ice_copyStateFrom(Ice.Object __obj)
	throws java.lang.CloneNotSupportedException
    {
	throw new java.lang.CloneNotSupportedException();
    }

    public static final String[] __ids =
    {
	"::Ice::Object",
	"::tfs::slice::ClientService"
    };

    public boolean
    ice_isA(String s)
    {
	return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public boolean
    ice_isA(String s, Ice.Current __current)
    {
	return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public String[]
    ice_ids()
    {
	return __ids;
    }

    public String[]
    ice_ids(Ice.Current __current)
    {
	return __ids;
    }

    public String
    ice_id()
    {
	return __ids[1];
    }

    public String
    ice_id(Ice.Current __current)
    {
	return __ids[1];
    }

    public static String
    ice_staticId()
    {
	return __ids[1];
    }

    public final void
    abandonAddChunk(Chunk chk)
	throws NoChunkAllocated
    {
	abandonAddChunk(chk, null);
    }

    public final LocatedChunk
    addChunk(Address client, String filename)
	throws NoChunkAllocated,
	       NoSuchFileOrDir
    {
	return addChunk(client, filename, null);
    }

    public final void
    close(Address client, String filename)
    {
	close(client, filename, null);
    }

    public final void
    completeWrittenChunk(LocatedChunk lchk)
	throws NoSuchChunk,
	       UnknownChunkServer
    {
	completeWrittenChunk(lchk, null);
    }

    public final void
    concatFiles(String[] srcFiles, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	concatFiles(srcFiles, dst, null);
    }

    public final void
    create(String filename, short replication, long chunkSize)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange
    {
	create(filename, replication, chunkSize, null);
    }

    public final LocatedChunk[]
    getChunksInfo(Address client, String filename)
	throws NoSuchFileOrDir
    {
	return getChunksInfo(client, filename, null);
    }

    public final FileInfo
    getFileInfo(String filename)
	throws NoSuchFileOrDir
    {
	return getFileInfo(filename, null);
    }

    public final FileInfo[]
    lsdir(String src)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	return lsdir(src, null);
    }

    public final void
    mkdir(String src)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName
    {
	mkdir(src, null);
    }

    public final void
    open(Address client, String filename, int mode)
	throws LockFail,
	       NoSuchFileOrDir
    {
	open(client, filename, mode, null);
    }

    public final void
    remove(String src)
	throws LockFail,
	       NoSuchFileOrDir
    {
	remove(src, null);
    }

    public final void
    rename(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	rename(src, dst, null);
    }

    public final void
    renamedir(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	renamedir(src, dst, null);
    }

    public final void
    reportBadChunks(LocatedChunk[] chunks)
    {
	reportBadChunks(chunks, null);
    }

    public final void
    reportHeartbeat(Address clientAddress)
    {
	reportHeartbeat(clientAddress, null);
    }

    public final void
    rmdir(String src)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir
    {
	rmdir(src, null);
    }

    public final void
    setReplication(String filename, short replication)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange
    {
	setReplication(filename, replication, null);
    }

    public final void
    updateChunkInfo(LocatedChunk lchk)
	throws NoSuchChunk
    {
	updateChunkInfo(lchk, null);
    }

    public static IceInternal.DispatchStatus
    ___open(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	Address client;
	client = new Address();
	client.__read(__is);
	String filename;
	filename = __is.readString();
	int mode;
	mode = __is.readInt();
	try
	{
	    __obj.open(client, filename, mode, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(LockFail ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___close(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	Address client;
	client = new Address();
	client.__read(__is);
	String filename;
	filename = __is.readString();
	__obj.close(client, filename, __current);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getChunksInfo(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	Address client;
	client = new Address();
	client.__read(__is);
	String filename;
	filename = __is.readString();
	try
	{
	    LocatedChunk[] __ret = __obj.getChunksInfo(client, filename, __current);
	    LocatedChunksHelper.write(__os, __ret);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___completeWrittenChunk(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	LocatedChunk lchk;
	lchk = new LocatedChunk();
	lchk.__read(__is);
	try
	{
	    __obj.completeWrittenChunk(lchk, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoSuchChunk ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(UnknownChunkServer ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___updateChunkInfo(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	LocatedChunk lchk;
	lchk = new LocatedChunk();
	lchk.__read(__is);
	try
	{
	    __obj.updateChunkInfo(lchk, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoSuchChunk ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___addChunk(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	Address client;
	client = new Address();
	client.__read(__is);
	String filename;
	filename = __is.readString();
	try
	{
	    LocatedChunk __ret = __obj.addChunk(client, filename, __current);
	    __ret.__write(__os);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoChunkAllocated ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___abandonAddChunk(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	Chunk chk;
	chk = new Chunk();
	chk.__read(__is);
	try
	{
	    __obj.abandonAddChunk(chk, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoChunkAllocated ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___reportBadChunks(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	LocatedChunk[] chunks;
	chunks = LocatedChunksHelper.read(__is);
	__obj.reportBadChunks(chunks, __current);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___setReplication(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String filename;
	filename = __is.readString();
	short replication;
	replication = __is.readShort();
	try
	{
	    __obj.setReplication(filename, replication, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(ReplicationOutOfRange ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___getFileInfo(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String filename;
	filename = __is.readString();
	try
	{
	    FileInfo __ret = __obj.getFileInfo(filename, __current);
	    __ret.__write(__os);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___create(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String filename;
	filename = __is.readString();
	short replication;
	replication = __is.readShort();
	long chunkSize;
	chunkSize = __is.readLong();
	try
	{
	    __obj.create(filename, replication, chunkSize, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(ChunkSizeOutOfRange ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(FileOrDirAlreadyExists ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(ReplicationOutOfRange ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___rename(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	String dst;
	dst = __is.readString();
	try
	{
	    __obj.rename(src, dst, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(FileOrDirAlreadyExists ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___remove(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	try
	{
	    __obj.remove(src, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(LockFail ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___mkdir(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	try
	{
	    __obj.mkdir(src, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(FileOrDirAlreadyExists ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___renamedir(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	String dst;
	dst = __is.readString();
	try
	{
	    __obj.renamedir(src, dst, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(FileOrDirAlreadyExists ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___rmdir(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	try
	{
	    __obj.rmdir(src, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(LockFail ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___lsdir(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String src;
	src = __is.readString();
	try
	{
	    FileInfo[] __ret = __obj.lsdir(src, __current);
	    FilesInfoHelper.write(__os, __ret);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___concatFiles(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	String[] srcFiles;
	srcFiles = StringsHelper.read(__is);
	String dst;
	dst = __is.readString();
	try
	{
	    __obj.concatFiles(srcFiles, dst, __current);
	    return IceInternal.DispatchStatus.DispatchOK;
	}
	catch(FileOrDirAlreadyExists ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(InvalidFileOrDirName ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
	catch(NoSuchFileOrDir ex)
	{
	    __os.writeUserException(ex);
	    return IceInternal.DispatchStatus.DispatchUserException;
	}
    }

    public static IceInternal.DispatchStatus
    ___reportHeartbeat(ClientService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	Address clientAddress;
	clientAddress = new Address();
	clientAddress.__read(__is);
	__obj.reportHeartbeat(clientAddress, __current);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    private final static String[] __all =
    {
	"abandonAddChunk",
	"addChunk",
	"close",
	"completeWrittenChunk",
	"concatFiles",
	"create",
	"getChunksInfo",
	"getFileInfo",
	"ice_id",
	"ice_ids",
	"ice_isA",
	"ice_ping",
	"lsdir",
	"mkdir",
	"open",
	"remove",
	"rename",
	"renamedir",
	"reportBadChunks",
	"reportHeartbeat",
	"rmdir",
	"setReplication",
	"updateChunkInfo"
    };

    public IceInternal.DispatchStatus
    __dispatch(IceInternal.Incoming in, Ice.Current __current)
    {
	int pos = java.util.Arrays.binarySearch(__all, __current.operation);
	if(pos < 0)
	{
	    return IceInternal.DispatchStatus.DispatchOperationNotExist;
	}

	switch(pos)
	{
	    case 0:
	    {
		return ___abandonAddChunk(this, in, __current);
	    }
	    case 1:
	    {
		return ___addChunk(this, in, __current);
	    }
	    case 2:
	    {
		return ___close(this, in, __current);
	    }
	    case 3:
	    {
		return ___completeWrittenChunk(this, in, __current);
	    }
	    case 4:
	    {
		return ___concatFiles(this, in, __current);
	    }
	    case 5:
	    {
		return ___create(this, in, __current);
	    }
	    case 6:
	    {
		return ___getChunksInfo(this, in, __current);
	    }
	    case 7:
	    {
		return ___getFileInfo(this, in, __current);
	    }
	    case 8:
	    {
		return ___ice_id(this, in, __current);
	    }
	    case 9:
	    {
		return ___ice_ids(this, in, __current);
	    }
	    case 10:
	    {
		return ___ice_isA(this, in, __current);
	    }
	    case 11:
	    {
		return ___ice_ping(this, in, __current);
	    }
	    case 12:
	    {
		return ___lsdir(this, in, __current);
	    }
	    case 13:
	    {
		return ___mkdir(this, in, __current);
	    }
	    case 14:
	    {
		return ___open(this, in, __current);
	    }
	    case 15:
	    {
		return ___remove(this, in, __current);
	    }
	    case 16:
	    {
		return ___rename(this, in, __current);
	    }
	    case 17:
	    {
		return ___renamedir(this, in, __current);
	    }
	    case 18:
	    {
		return ___reportBadChunks(this, in, __current);
	    }
	    case 19:
	    {
		return ___reportHeartbeat(this, in, __current);
	    }
	    case 20:
	    {
		return ___rmdir(this, in, __current);
	    }
	    case 21:
	    {
		return ___setReplication(this, in, __current);
	    }
	    case 22:
	    {
		return ___updateChunkInfo(this, in, __current);
	    }
	}

	assert(false);
	return IceInternal.DispatchStatus.DispatchOperationNotExist;
    }
}
