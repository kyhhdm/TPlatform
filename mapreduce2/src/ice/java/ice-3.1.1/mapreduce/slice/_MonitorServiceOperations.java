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

public interface _MonitorServiceOperations
{
    int getStartTime(Ice.Current __current);

    int getCompletedJobs(Ice.Current __current);

    int getCompletedTasks(Ice.Current __current);

    WorkerDetail[] getWorkers(Ice.Current __current);

    JobDetail[] getJobs(Ice.Current __current);

    TaskDetail[] getTasks(int jobId, Ice.Current __current);

    int[] getTasksStat(int jobId, Ice.Current __current);
}
