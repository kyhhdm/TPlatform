// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1

package mapreduce.slice;

public final class _MonitorServiceDelD extends Ice._ObjectDelD implements _MonitorServiceDel
{
    public int
    getCompletedJobs(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getCompletedJobs", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getCompletedJobs(__current);
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

    public int
    getCompletedTasks(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getCompletedTasks", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getCompletedTasks(__current);
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

    public JobDetail[]
    getJobs(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getJobs", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getJobs(__current);
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

    public int
    getStartTime(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getStartTime", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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

    public TaskDetail[]
    getTasks(int jobId, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getTasks", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getTasks(jobId, __current);
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
    getTasksStat(int jobId, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getTasksStat", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getTasksStat(jobId, __current);
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

    public WorkerDetail[]
    getWorkers(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "getWorkers", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		MonitorService __servant = null;
		try
		{
		    __servant = (MonitorService)__direct.servant();
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
		    return __servant.getWorkers(__current);
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
