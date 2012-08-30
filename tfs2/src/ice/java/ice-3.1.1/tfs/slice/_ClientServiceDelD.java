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

public final class _ClientServiceDelD extends Ice._ObjectDelD implements _ClientServiceDel
{
    public void
    abandonAddChunk(Chunk chk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "abandonAddChunk", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.abandonAddChunk(chk, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public LocatedChunk
    addChunk(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoChunkAllocated,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "addChunk", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    return __servant.addChunk(client, filename, __current);
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    close(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "close", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.close(client, filename, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    completeWrittenChunk(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk,
	       UnknownChunkServer
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "completeWrittenChunk", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.completeWrittenChunk(lchk, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    concatFiles(String[] srcFiles, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "concatFiles", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.concatFiles(srcFiles, dst, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
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
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "create", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.create(filename, replication, chunkSize, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public LocatedChunk[]
    getChunksInfo(Address client, String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getChunksInfo", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    return __servant.getChunksInfo(client, filename, __current);
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public FileInfo
    getFileInfo(String filename, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getFileInfo", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    return __servant.getFileInfo(filename, __current);
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public FileInfo[]
    lsdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "lsdir", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    return __servant.lsdir(src, __current);
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    mkdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "mkdir", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.mkdir(src, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    open(Address client, String filename, int mode, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "open", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.open(client, filename, mode, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    remove(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       LockFail,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "remove", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.remove(src, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    rename(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "rename", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.rename(src, dst, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    renamedir(String src, String dst, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "renamedir", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.renamedir(src, dst, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    reportBadChunks(LocatedChunk[] chunks, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "reportBadChunks", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.reportBadChunks(chunks, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    reportHeartbeat(Address clientAddress, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "reportHeartbeat", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.reportHeartbeat(clientAddress, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    rmdir(String src, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "rmdir", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.rmdir(src, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    setReplication(String filename, short replication, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchFileOrDir,
	       ReplicationOutOfRange
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "setReplication", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.setReplication(filename, replication, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }

    public void
    updateChunkInfo(LocatedChunk lchk, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper,
	       NoSuchChunk
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "updateChunkInfo", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		ClientService __servant = null;
		try
		{
		    __servant = (ClientService)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.updateChunkInfo(lchk, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }
}
