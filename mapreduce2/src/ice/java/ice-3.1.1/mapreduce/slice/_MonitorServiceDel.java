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

public interface _MonitorServiceDel extends Ice._ObjectDel
{
    int getStartTime(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    int getCompletedJobs(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    int getCompletedTasks(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    WorkerDetail[] getWorkers(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    JobDetail[] getJobs(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    TaskDetail[] getTasks(int jobId, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    int[] getTasksStat(int jobId, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;
}
