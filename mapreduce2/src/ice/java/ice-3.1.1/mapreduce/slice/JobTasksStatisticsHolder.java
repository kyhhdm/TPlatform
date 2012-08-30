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

public final class JobTasksStatisticsHolder
{
    public
    JobTasksStatisticsHolder()
    {
    }

    public
    JobTasksStatisticsHolder(int[] value)
    {
	this.value = value;
    }

    public int[] value;
}
