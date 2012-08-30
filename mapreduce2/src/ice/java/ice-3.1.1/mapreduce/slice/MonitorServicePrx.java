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

public interface MonitorServicePrx extends Ice.ObjectPrx
{
    public int getStartTime();
    public int getStartTime(java.util.Map __ctx);

    public int getCompletedJobs();
    public int getCompletedJobs(java.util.Map __ctx);

    public int getCompletedTasks();
    public int getCompletedTasks(java.util.Map __ctx);

    public WorkerDetail[] getWorkers();
    public WorkerDetail[] getWorkers(java.util.Map __ctx);

    public JobDetail[] getJobs();
    public JobDetail[] getJobs(java.util.Map __ctx);

    public TaskDetail[] getTasks(int jobId);
    public TaskDetail[] getTasks(int jobId, java.util.Map __ctx);

    public int[] getTasksStat(int jobId);
    public int[] getTasksStat(int jobId, java.util.Map __ctx);
}
