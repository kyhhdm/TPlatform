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

public final class _ClientServiceDelM extends Ice._ObjectDelM implements _ClientServiceDel
{
    public void
    abandonAddChunk(Chunk chk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "abandonAddChunk", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		chk.__write(__os);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoChunkAllocated __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public LocatedChunk
    addChunk(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "addChunk", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		client.__write(__os);
		__os.writeString(filename);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoChunkAllocated __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
		LocatedChunk __ret;
		__ret = new LocatedChunk();
		__ret.__read(__is);
		return __ret;
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    close(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "close", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		client.__write(__os);
		__os.writeString(filename);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    completeWrittenChunk(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk,
	       UnknownChunkServer
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "completeWrittenChunk", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		lchk.__write(__os);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoSuchChunk __ex)
		    {
			throw __ex;
		    }
		    catch(UnknownChunkServer __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    concatFiles(String[] srcFiles, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "concatFiles", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		StringsHelper.write(__os, srcFiles);
		__os.writeString(dst);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(FileOrDirAlreadyExists __ex)
		    {
			throw __ex;
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    create(String filename, short replication, long chunkSize, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "create", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(filename);
		__os.writeShort(replication);
		__os.writeLong(chunkSize);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(ChunkSizeOutOfRange __ex)
		    {
			throw __ex;
		    }
		    catch(FileOrDirAlreadyExists __ex)
		    {
			throw __ex;
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(ReplicationOutOfRange __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public LocatedChunk[]
    getChunksInfo(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "getChunksInfo", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		client.__write(__os);
		__os.writeString(filename);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
		LocatedChunk[] __ret;
		__ret = LocatedChunksHelper.read(__is);
		return __ret;
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public FileInfo
    getFileInfo(String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "getFileInfo", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(filename);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
		FileInfo __ret;
		__ret = new FileInfo();
		__ret.__read(__is);
		return __ret;
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public FileInfo[]
    lsdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "lsdir", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
		FileInfo[] __ret;
		__ret = FilesInfoHelper.read(__is);
		return __ret;
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    mkdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "mkdir", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(FileOrDirAlreadyExists __ex)
		    {
			throw __ex;
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    open(Address client, String filename, int mode, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "open", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		client.__write(__os);
		__os.writeString(filename);
		__os.writeInt(mode);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(LockFail __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    remove(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "remove", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(LockFail __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    rename(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "rename", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
		__os.writeString(dst);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(FileOrDirAlreadyExists __ex)
		    {
			throw __ex;
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    renamedir(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "renamedir", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
		__os.writeString(dst);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(FileOrDirAlreadyExists __ex)
		    {
			throw __ex;
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    reportBadChunks(LocatedChunk[] chunks, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "reportBadChunks", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		LocatedChunksHelper.write(__os, chunks);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    reportHeartbeat(Address clientAddress, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "reportHeartbeat", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		clientAddress.__write(__os);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    rmdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "rmdir", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(src);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(InvalidFileOrDirName __ex)
		    {
			throw __ex;
		    }
		    catch(LockFail __ex)
		    {
			throw __ex;
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    setReplication(String filename, short replication, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir,
	       ReplicationOutOfRange
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "setReplication", Ice.OperationMode.Idempotent, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		__os.writeString(filename);
		__os.writeShort(replication);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoSuchFileOrDir __ex)
		    {
			throw __ex;
		    }
		    catch(ReplicationOutOfRange __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }

    public void
    updateChunkInfo(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk
    {
	IceInternal.Outgoing __og = __connection.getOutgoing(__reference, "updateChunkInfo", Ice.OperationMode.Normal, __ctx, __compress);
	try
	{
	    try
	    {
		IceInternal.BasicStream __os = __og.os();
		lchk.__write(__os);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__og.abort(__ex);
	    }
	    boolean __ok = __og.invoke();
	    try
	    {
		IceInternal.BasicStream __is = __og.is();
		if(!__ok)
		{
		    try
		    {
			__is.throwException();
		    }
		    catch(NoSuchChunk __ex)
		    {
			throw __ex;
		    }
		    catch(Ice.UserException __ex)
		    {
			throw new Ice.UnknownUserException(__ex.ice_name());
		    }
		}
	    }
	    catch(Ice.LocalException __ex)
	    {
		throw new IceInternal.LocalExceptionWrapper(__ex, false);
	    }
	}
	finally
	{
	    __connection.reclaimOutgoing(__og);
	}
    }
}
