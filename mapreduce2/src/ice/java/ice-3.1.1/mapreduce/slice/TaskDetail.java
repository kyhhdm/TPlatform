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

public final class TaskDetail implements java.lang.Cloneable
{
    public int id;

    public int status;

    public int type;

    public Address worker;

    public TaskDetail()
    {
    }

    public TaskDetail(int id, int status, int type, Address worker)
    {
	this.id = id;
	this.status = status;
	this.type = type;
	this.worker = worker;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	TaskDetail _r = null;
	try
	{
	    _r = (TaskDetail)rhs;
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
	    if(status != _r.status)
	    {
		return false;
	    }
	    if(type != _r.type)
	    {
		return false;
	    }
	    if(worker != _r.worker && worker != null && !worker.equals(_r.worker))
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
	__h = 5 * __h + status;
	__h = 5 * __h + type;
	__h = 5 * __h + worker.hashCode();
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
	__os.writeInt(status);
	__os.writeInt(type);
	worker.__write(__os);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	id = __is.readInt();
	status = __is.readInt();
	type = __is.readInt();
	worker = new Address();
	worker.__read(__is);
    }
}
