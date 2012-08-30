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

public abstract class _MonitorServiceDisp extends Ice.ObjectImpl implements MonitorService
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
	"::mapreduce::slice::MonitorService"
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

    public final int
    getCompletedJobs()
    {
	return getCompletedJobs(null);
    }

    public final int
    getCompletedTasks()
    {
	return getCompletedTasks(null);
    }

    public final JobDetail[]
    getJobs()
    {
	return getJobs(null);
    }

    public final int
    getStartTime()
    {
	return getStartTime(null);
    }

    public final TaskDetail[]
    getTasks(int jobId)
    {
	return getTasks(jobId, null);
    }

    public final int[]
    getTasksStat(int jobId)
    {
	return getTasksStat(jobId, null);
    }

    public final WorkerDetail[]
    getWorkers()
    {
	return getWorkers(null);
    }

    public static IceInternal.DispatchStatus
    ___getStartTime(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	int __ret = __obj.getStartTime(__current);
	__os.writeInt(__ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getCompletedJobs(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	int __ret = __obj.getCompletedJobs(__current);
	__os.writeInt(__ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getCompletedTasks(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	int __ret = __obj.getCompletedTasks(__current);
	__os.writeInt(__ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getWorkers(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	WorkerDetail[] __ret = __obj.getWorkers(__current);
	WorkersDetailHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getJobs(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __os = __inS.os();
	JobDetail[] __ret = __obj.getJobs(__current);
	JobsDetailHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getTasks(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	int jobId;
	jobId = __is.readInt();
	TaskDetail[] __ret = __obj.getTasks(jobId, __current);
	TasksDetailHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    public static IceInternal.DispatchStatus
    ___getTasksStat(MonitorService __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
	__checkMode(Ice.OperationMode.Normal, __current.mode);
	IceInternal.BasicStream __is = __inS.is();
	IceInternal.BasicStream __os = __inS.os();
	int jobId;
	jobId = __is.readInt();
	int[] __ret = __obj.getTasksStat(jobId, __current);
	TasksStatisticsHelper.write(__os, __ret);
	return IceInternal.DispatchStatus.DispatchOK;
    }

    private final static String[] __all =
    {
	"getCompletedJobs",
	"getCompletedTasks",
	"getJobs",
	"getStartTime",
	"getTasks",
	"getTasksStat",
	"getWorkers",
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
		return ___getCompletedJobs(this, in, __current);
	    }
	    case 1:
	    {
		return ___getCompletedTasks(this, in, __current);
	    }
	    case 2:
	    {
		return ___getJobs(this, in, __current);
	    }
	    case 3:
	    {
		return ___getStartTime(this, in, __current);
	    }
	    case 4:
	    {
		return ___getTasks(this, in, __current);
	    }
	    case 5:
	    {
		return ___getTasksStat(this, in, __current);
	    }
	    case 6:
	    {
		return ___getWorkers(this, in, __current);
	    }
	    case 7:
	    {
		return ___ice_id(this, in, __current);
	    }
	    case 8:
	    {
		return ___ice_ids(this, in, __current);
	    }
	    case 9:
	    {
		return ___ice_isA(this, in, __current);
	    }
	    case 10:
	    {
		return ___ice_ping(this, in, __current);
	    }
	}

	assert(false);
	return IceInternal.DispatchStatus.DispatchOperationNotExist;
    }
}
