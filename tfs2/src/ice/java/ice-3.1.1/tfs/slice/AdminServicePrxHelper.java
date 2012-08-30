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

public final class AdminServicePrxHelper extends Ice.ObjectPrxHelperBase implements AdminServicePrx
{
    public Address[]
    getChunkServers()
    {
	return getChunkServers(__defaultContext());
    }

    public Address[]
    getChunkServers(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getChunkServers");
		Ice._ObjectDel __delBase = __getDelegate();
		_AdminServiceDel __del = (_AdminServiceDel)__delBase;
		return __del.getChunkServers(__ctx);
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

    public Address[]
    getClients()
    {
	return getClients(__defaultContext());
    }

    public Address[]
    getClients(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getClients");
		Ice._ObjectDel __delBase = __getDelegate();
		_AdminServiceDel __del = (_AdminServiceDel)__delBase;
		return __del.getClients(__ctx);
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

    public int[]
    getOperationsCount()
    {
	return getOperationsCount(__defaultContext());
    }

    public int[]
    getOperationsCount(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getOperationsCount");
		Ice._ObjectDel __delBase = __getDelegate();
		_AdminServiceDel __del = (_AdminServiceDel)__delBase;
		return __del.getOperationsCount(__ctx);
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

    public String
    getStartTime()
    {
	return getStartTime(__defaultContext());
    }

    public String
    getStartTime(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getStartTime");
		Ice._ObjectDel __delBase = __getDelegate();
		_AdminServiceDel __del = (_AdminServiceDel)__delBase;
		return __del.getStartTime(__ctx);
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

    public static AdminServicePrx
    checkedCast(Ice.ObjectPrx __obj)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (AdminServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::tfs::slice::AdminService"))
		{
		    AdminServicePrxHelper __h = new AdminServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static AdminServicePrx
    checkedCast(Ice.ObjectPrx __obj, java.util.Map __ctx)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (AdminServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::tfs::slice::AdminService", __ctx))
		{
		    AdminServicePrxHelper __h = new AdminServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static AdminServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::tfs::slice::AdminService"))
		{
		    AdminServicePrxHelper __h = new AdminServicePrxHelper();
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

    public static AdminServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map __ctx)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::tfs::slice::AdminService", __ctx))
		{
		    AdminServicePrxHelper __h = new AdminServicePrxHelper();
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

    public static AdminServicePrx
    uncheckedCast(Ice.ObjectPrx __obj)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    AdminServicePrxHelper __h = new AdminServicePrxHelper();
	    __h.__copyFrom(__obj);
	    __d = __h;
	}
	return __d;
    }

    public static AdminServicePrx
    uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
	AdminServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    AdminServicePrxHelper __h = new AdminServicePrxHelper();
	    __h.__copyFrom(__bb);
	    __d = __h;
	}
	return __d;
    }

    protected Ice._ObjectDelM
    __createDelegateM()
    {
	return new _AdminServiceDelM();
    }

    protected Ice._ObjectDelD
    __createDelegateD()
    {
	return new _AdminServiceDelD();
    }

    public static void
    __write(IceInternal.BasicStream __os, AdminServicePrx v)
    {
	__os.writeProxy(v);
    }

    public static AdminServicePrx
    __read(IceInternal.BasicStream __is)
    {
	Ice.ObjectPrx proxy = __is.readProxy();
	if(proxy != null)
	{
	    AdminServicePrxHelper result = new AdminServicePrxHelper();
	    result.__copyFrom(proxy);
	    return result;
	}
	return null;
    }
}
