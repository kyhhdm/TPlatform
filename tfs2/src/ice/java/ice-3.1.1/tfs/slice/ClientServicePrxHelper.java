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

public final class ClientServicePrxHelper extends Ice.ObjectPrxHelperBase implements ClientServicePrx
{
    public void
    abandonAddChunk(Chunk chk)
	throws NoChunkAllocated
    {
	abandonAddChunk(chk, __defaultContext());
    }

    public void
    abandonAddChunk(Chunk chk, java.util.Map __ctx)
	throws NoChunkAllocated
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("abandonAddChunk");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.abandonAddChunk(chk, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public LocatedChunk
    addChunk(Address client, String filename)
	throws NoChunkAllocated,
	       NoSuchFileOrDir
    {
	return addChunk(client, filename, __defaultContext());
    }

    public LocatedChunk
    addChunk(Address client, String filename, java.util.Map __ctx)
	throws NoChunkAllocated,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("addChunk");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		return __del.addChunk(client, filename, __ctx);
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    close(Address client, String filename)
    {
	close(client, filename, __defaultContext());
    }

    public void
    close(Address client, String filename, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.close(client, filename, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    completeWrittenChunk(LocatedChunk lchk)
	throws NoSuchChunk,
	       UnknownChunkServer
    {
	completeWrittenChunk(lchk, __defaultContext());
    }

    public void
    completeWrittenChunk(LocatedChunk lchk, java.util.Map __ctx)
	throws NoSuchChunk,
	       UnknownChunkServer
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("completeWrittenChunk");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.completeWrittenChunk(lchk, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    concatFiles(String[] srcFiles, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	concatFiles(srcFiles, dst, __defaultContext());
    }

    public void
    concatFiles(String[] srcFiles, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("concatFiles");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.concatFiles(srcFiles, dst, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    create(String filename, short replication, long chunkSize)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange
    {
	create(filename, replication, chunkSize, __defaultContext());
    }

    public void
    create(String filename, short replication, long chunkSize, java.util.Map __ctx)
	throws ChunkSizeOutOfRange,
	       FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       ReplicationOutOfRange
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("create");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.create(filename, replication, chunkSize, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public LocatedChunk[]
    getChunksInfo(Address client, String filename)
	throws NoSuchFileOrDir
    {
	return getChunksInfo(client, filename, __defaultContext());
    }

    public LocatedChunk[]
    getChunksInfo(Address client, String filename, java.util.Map __ctx)
	throws NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getChunksInfo");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		return __del.getChunksInfo(client, filename, __ctx);
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public FileInfo
    getFileInfo(String filename)
	throws NoSuchFileOrDir
    {
	return getFileInfo(filename, __defaultContext());
    }

    public FileInfo
    getFileInfo(String filename, java.util.Map __ctx)
	throws NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getFileInfo");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		return __del.getFileInfo(filename, __ctx);
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public FileInfo[]
    lsdir(String src)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	return lsdir(src, __defaultContext());
    }

    public FileInfo[]
    lsdir(String src, java.util.Map __ctx)
	throws InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("lsdir");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		return __del.lsdir(src, __ctx);
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    mkdir(String src)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName
    {
	mkdir(src, __defaultContext());
    }

    public void
    mkdir(String src, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("mkdir");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.mkdir(src, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    open(Address client, String filename, int mode)
	throws LockFail,
	       NoSuchFileOrDir
    {
	open(client, filename, mode, __defaultContext());
    }

    public void
    open(Address client, String filename, int mode, java.util.Map __ctx)
	throws LockFail,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("open");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.open(client, filename, mode, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    remove(String src)
	throws LockFail,
	       NoSuchFileOrDir
    {
	remove(src, __defaultContext());
    }

    public void
    remove(String src, java.util.Map __ctx)
	throws LockFail,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("remove");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.remove(src, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    rename(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	rename(src, dst, __defaultContext());
    }

    public void
    rename(String src, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("rename");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.rename(src, dst, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    renamedir(String src, String dst)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	renamedir(src, dst, __defaultContext());
    }

    public void
    renamedir(String src, String dst, java.util.Map __ctx)
	throws FileOrDirAlreadyExists,
	       InvalidFileOrDirName,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("renamedir");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.renamedir(src, dst, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    reportBadChunks(LocatedChunk[] chunks)
    {
	reportBadChunks(chunks, __defaultContext());
    }

    public void
    reportBadChunks(LocatedChunk[] chunks, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.reportBadChunks(chunks, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    reportHeartbeat(Address clientAddress)
    {
	reportHeartbeat(clientAddress, __defaultContext());
    }

    public void
    reportHeartbeat(Address clientAddress, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.reportHeartbeat(clientAddress, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    rmdir(String src)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir
    {
	rmdir(src, __defaultContext());
    }

    public void
    rmdir(String src, java.util.Map __ctx)
	throws InvalidFileOrDirName,
	       LockFail,
	       NoSuchFileOrDir
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("rmdir");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.rmdir(src, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    setReplication(String filename, short replication)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange
    {
	setReplication(filename, replication, __defaultContext());
    }

    public void
    setReplication(String filename, short replication, java.util.Map __ctx)
	throws NoSuchFileOrDir,
	       ReplicationOutOfRange
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("setReplication");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.setReplication(filename, replication, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__cnt = __handleExceptionWrapperRelaxed(__ex, __cnt);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public void
    updateChunkInfo(LocatedChunk lchk)
	throws NoSuchChunk
    {
	updateChunkInfo(lchk, __defaultContext());
    }

    public void
    updateChunkInfo(LocatedChunk lchk, java.util.Map __ctx)
	throws NoSuchChunk
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("updateChunkInfo");
		Ice._ObjectDel __delBase = __getDelegate();
		_ClientServiceDel __del = (_ClientServiceDel)__delBase;
		__del.updateChunkInfo(lchk, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public static ClientServicePrx
    checkedCast(Ice.ObjectPrx __obj)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (ClientServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::tfs::slice::ClientService"))
		{
		    ClientServicePrxHelper __h = new ClientServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static ClientServicePrx
    checkedCast(Ice.ObjectPrx __obj, java.util.Map __ctx)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (ClientServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::tfs::slice::ClientService", __ctx))
		{
		    ClientServicePrxHelper __h = new ClientServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static ClientServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::tfs::slice::ClientService"))
		{
		    ClientServicePrxHelper __h = new ClientServicePrxHelper();
		    __h.__copyFrom(__bb);
		    __d = __h;
		}
	    }
	    catch(Ice.FacetNotExistException ex)
	    {
	    }
	}
	return __d;
    }

    public static ClientServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map __ctx)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::tfs::slice::ClientService", __ctx))
		{
		    ClientServicePrxHelper __h = new ClientServicePrxHelper();
		    __h.__copyFrom(__bb);
		    __d = __h;
		}
	    }
	    catch(Ice.FacetNotExistException ex)
	    {
	    }
	}
	return __d;
    }

    public static ClientServicePrx
    uncheckedCast(Ice.ObjectPrx __obj)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    ClientServicePrxHelper __h = new ClientServicePrxHelper();
	    __h.__copyFrom(__obj);
	    __d = __h;
	}
	return __d;
    }

    public static ClientServicePrx
    uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
	ClientServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    ClientServicePrxHelper __h = new ClientServicePrxHelper();
	    __h.__copyFrom(__bb);
	    __d = __h;
	}
	return __d;
    }

    protected Ice._ObjectDelM
    __createDelegateM()
    {
	return new _ClientServiceDelM();
    }

    protected Ice._ObjectDelD
    __createDelegateD()
    {
	return new _ClientServiceDelD();
    }

    public static void
    __write(IceInternal.BasicStream __os, ClientServicePrx v)
    {
	__os.writeProxy(v);
    }

    public static ClientServicePrx
    __read(IceInternal.BasicStream __is)
    {
	Ice.ObjectPrx proxy = __is.readProxy();
	if(proxy != null)
	{
	    ClientServicePrxHelper result = new ClientServicePrxHelper();
	    result.__copyFrom(proxy);
	    return result;
	}
	return null;
    }
}
