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

public final class JobDetail implements java.lang.Cloneable
{
    public int id;

    public int createTime;

    public int finishTime;

    public int status;

    public boolean detached;

    public MapReduceJob jobSpec;

    public JobDetail()
    {
    }

    public JobDetail(int id, int createTime, int finishTime, int status, boolean detached, MapReduceJob jobSpec)
    {
	this.id = id;
	this.createTime = createTime;
	this.finishTime = finishTime;
	this.status = status;
	this.detached = detached;
	this.jobSpec = jobSpec;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	JobDetail _r = null;
	try
	{
	    _r = (JobDetail)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(id != _r.id)
	    {
		return false;
	    }
	    if(createTime != _r.createTime)
	    {
		return false;
	    }
	    if(finishTime != _r.finishTime)
	    {
		return false;
	    }
	    if(status != _r.status)
	    {
		return false;
	    }
	    if(detached != _r.detached)
	    {
		return false;
	    }
	    if(jobSpec != _r.jobSpec && jobSpec != null && !jobSpec.equals(_r.jobSpec))
	    {
		return false;
	    }

	    return true;
	}

	return false;
    }

    public int
    hashCode()
    {
	int __h = 0;
	__h = 5 * __h + id;
	__h = 5 * __h + createTime;
	__h = 5 * __h + finishTime;
	__h = 5 * __h + status;
	__h = 5 * __h + (detached ? 1 : 0);
	__h = 5 * __h + jobSpec.hashCode();
	return __h;
    }

    public java.lang.Object
    clone()
    {
	java.lang.Object o = null;
	try
	{
	    o = super.clone();
	}
	catch(CloneNotSupportedException ex)
	{
	    assert false; // impossible
	}
	return o;
    }

    public void
    __write(IceInternal.BasicStream __os)
    {
	__os.writeInt(id);
	__os.writeInt(createTime);
	__os.writeInt(finishTime);
	__os.writeInt(status);
	__os.writeBool(detached);
	jobSpec.__write(__os);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	id = __is.readInt();
	createTime = __is.readInt();
	finishTime = __is.readInt();
	status = __is.readInt();
	detached = __is.readBool();
	jobSpec = new MapReduceJob();
	jobSpec.__read(__is);
    }
}
