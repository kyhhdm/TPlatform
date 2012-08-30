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

public abstract class _AdminServiceDisp extends Ice.ObjectImpl implements AdminService
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
	"::tfs::slice::AdminService"
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

    public final Address[]
    getChunkServers()
    {
	return getChunkServers(null);
    }

    public final Address[]
    getClients()
    {
	return getClients(null);
    }

    public final int[]
    getOperationsCount()
    {
	return getOperationsCount(null);
    }

    public final String
    getStartTime()
    {
	return getStartTime(null);
    }

    public static IceInternal.DispatchStatus
    ___getStartTime(AdminService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	String __ret = __obj.getStartTime(__current);
	__os.writeString(__ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getChunkServers(AdminService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	Address[] __ret = __obj.getChunkServers(__current);
	AddressesHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getClients(AdminService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	Address[] __ret = __obj.getClients(__current);
	AddressesHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getOperationsCount(AdminService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Idempotent, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	int[] __ret = __obj.getOperationsCount(__current);
	OperationsCountHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    private final static String[] __all =
    {
	"getChunkServers",
	"getClients",
	"getOperationsCount",
	"getStartTime",
	"ice_id",
	"ice_ids",
	"ice_isA",
	"ice_ping"
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
		return ___getChunkServers(this, in, __current);
	    }
	    case 1:
	    {
		return ___getClients(this, in, __current);
	    }
	    case 2:
	    {
		return ___getOperationsCount(this, in, __current);
	    }
	    case 3:
	    {
		return ___getStartTime(this, in, __current);
	    }
	    case 4:
	    {
		return ___ice_id(this, in, __current);
	    }
	    case 5:
	    {
		return ___ice_ids(this, in, __current);
	    }
	    case 6:
	    {
		return ___ice_isA(this, in, __current);
	    }
	    case 7:
	    {
		return ___ice_ping(this, in, __current);
	    }
	}

	assert(false);
	return IceInternal.DispatchStatus.DispatchOperationNotExist;
    }
}
