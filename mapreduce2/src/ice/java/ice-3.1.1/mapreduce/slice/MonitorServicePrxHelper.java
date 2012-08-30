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

public final class MonitorServicePrxHelper extends Ice.ObjectPrxHelperBase implements MonitorServicePrx
{
    public int
    getCompletedJobs()
    {
	return getCompletedJobs(__defaultContext());
    }

    public int
    getCompletedJobs(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getCompletedJobs");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getCompletedJobs(__ctx);
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

    public int
    getCompletedTasks()
    {
	return getCompletedTasks(__defaultContext());
    }

    public int
    getCompletedTasks(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getCompletedTasks");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getCompletedTasks(__ctx);
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

    public JobDetail[]
    getJobs()
    {
	return getJobs(__defaultContext());
    }

    public JobDetail[]
    getJobs(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getJobs");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getJobs(__ctx);
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

    public int
    getStartTime()
    {
	return getStartTime(__defaultContext());
    }

    public int
    getStartTime(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getStartTime");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getStartTime(__ctx);
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

    public TaskDetail[]
    getTasks(int jobId)
    {
	return getTasks(jobId, __defaultContext());
    }

    public TaskDetail[]
    getTasks(int jobId, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getTasks");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getTasks(jobId, __ctx);
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

    public int[]
    getTasksStat(int jobId)
    {
	return getTasksStat(jobId, __defaultContext());
    }

    public int[]
    getTasksStat(int jobId, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getTasksStat");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getTasksStat(jobId, __ctx);
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

    public WorkerDetail[]
    getWorkers()
    {
	return getWorkers(__defaultContext());
    }

    public WorkerDetail[]
    getWorkers(java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		__checkTwowayOnly("getWorkers");
		Ice._ObjectDel __delBase = __getDelegate();
		_MonitorServiceDel __del = (_MonitorServiceDel)__delBase;
		return __del.getWorkers(__ctx);
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

    public static MonitorServicePrx
    checkedCast(Ice.ObjectPrx __obj)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (MonitorServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::mapreduce::slice::MonitorService"))
		{
		    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static MonitorServicePrx
    checkedCast(Ice.ObjectPrx __obj, java.util.Map __ctx)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (MonitorServicePrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::mapreduce::slice::MonitorService", __ctx))
		{
		    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static MonitorServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::mapreduce::slice::MonitorService"))
		{
		    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
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

    public static MonitorServicePrx
    checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map __ctx)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::mapreduce::slice::MonitorService", __ctx))
		{
		    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
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

    public static MonitorServicePrx
    uncheckedCast(Ice.ObjectPrx __obj)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
	    __h.__copyFrom(__obj);
	    __d = __h;
	}
	return __d;
    }

    public static MonitorServicePrx
    uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
	MonitorServicePrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    MonitorServicePrxHelper __h = new MonitorServicePrxHelper();
	    __h.__copyFrom(__bb);
	    __d = __h;
	}
	return __d;
    }

    protected Ice._ObjectDelM
    __createDelegateM()
    {
	return new _MonitorServiceDelM();
    }

    protected Ice._ObjectDelD
    __createDelegateD()
    {
	return new _MonitorServiceDelD();
    }

    public static void
    __write(IceInternal.BasicStream __os, MonitorServicePrx v)
    {
	__os.writeProxy(v);
    }

    public static MonitorServicePrx
    __read(IceInternal.BasicStream __is)
    {
	Ice.ObjectPrx proxy = __is.readProxy();
	if(proxy != null)
	{
	    MonitorServicePrxHelper result = new MonitorServicePrxHelper();
	    result.__copyFrom(proxy);
	    return result;
	}
	return null;
    }
}
