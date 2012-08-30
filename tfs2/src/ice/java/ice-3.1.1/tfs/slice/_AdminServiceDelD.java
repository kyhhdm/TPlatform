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

public final class _AdminServiceDelD extends Ice._ObjectDelD implements _AdminServiceDel
{
    public Address[]
    getChunkServers(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getChunkServers", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		AdminService __servant = null;
		try
		{
		    __servant = (AdminService)__direct.servant();
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
		    return __servant.getChunkServers(__current);
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

    public Address[]
    getClients(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getClients", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		AdminService __servant = null;
		try
		{
		    __servant = (AdminService)__direct.servant();
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
		    return __servant.getClients(__current);
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

    public int[]
    getOperationsCount(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getOperationsCount", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		AdminService __servant = null;
		try
		{
		    __servant = (AdminService)__direct.servant();
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
		    return __servant.getOperationsCount(__current);
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

    public String
    getStartTime(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getStartTime", Ice.OperationMode.Idempotent, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		AdminService __servant = null;
		try
		{
		    __servant = (AdminService)__direct.servant();
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
		    return __servant.getStartTime(__current);
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
