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

public final class JobInfo implements java.lang.Cloneable
{
    public int id;

    public MapReduceJob jobSpec;

    public JobInfo()
    {
    }

    public JobInfo(int id, MapReduceJob jobSpec)
    {
	this.id = id;
	this.jobSpec = jobSpec;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	JobInfo _r = null;
	try
	{
	    _r = (JobInfo)rhs;
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
	jobSpec.__write(__os);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	id = __is.readInt();
	jobSpec = new MapReduceJob();
	jobSpec.__read(__is);
    }
}
