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

public final class JobDetailHolder
{
    public
    JobDetailHolder()
    {
    }

    public
    JobDetailHolder(JobDetail value)
    {
	this.value = value;
    }

    public JobDetail value;
}
