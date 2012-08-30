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

public final class WorkerDetail implements java.lang.Cloneable
{
    public Address addr;

    public int mapTaskCount;

    public int reduceTaskCount;

    public int transTaskCount;

    public int workload;

    public int mapDoneCount;

    public int reduceDoneCount;

    public int transDoneCount;

    public WorkerDetail()
    {
    }

    public WorkerDetail(Address addr, int mapTaskCount, int reduceTaskCount, int transTaskCount, int workload, int mapDoneCount, int reduceDoneCount, int transDoneCount)
    {
	this.addr = addr;
	this.mapTaskCount = mapTaskCount;
	this.reduceTaskCount = reduceTaskCount;
	this.transTaskCount = transTaskCount;
	this.workload = workload;
	this.mapDoneCount = mapDoneCount;
	this.reduceDoneCount = reduceDoneCount;
	this.transDoneCount = transDoneCount;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	WorkerDetail _r = null;
	try
	{
	    _r = (WorkerDetail)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(addr != _r.addr && addr != null && !addr.equals(_r.addr))
	    {
		return false;
	    }
	    if(mapTaskCount != _r.mapTaskCount)
	    {
		return false;
	    }
	    if(reduceTaskCount != _r.reduceTaskCount)
	    {
		return false;
	    }
	    if(transTaskCount != _r.transTaskCount)
	    {
		return false;
	    }
	    if(workload != _r.workload)
	    {
		return false;
	    }
	    if(mapDoneCount != _r.mapDoneCount)
	    {
		return false;
	    }
	    if(reduceDoneCount != _r.reduceDoneCount)
	    {
		return false;
	    }
	    if(transDoneCount != _r.transDoneCount)
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
	__h = 5 * __h + addr.hashCode();
	__h = 5 * __h + mapTaskCount;
	__h = 5 * __h + reduceTaskCount;
	__h = 5 * __h + transTaskCount;
	__h = 5 * __h + workload;
	__h = 5 * __h + mapDoneCount;
	__h = 5 * __h + reduceDoneCount;
	__h = 5 * __h + transDoneCount;
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
	addr.__write(__os);
	__os.writeInt(mapTaskCount);
	__os.writeInt(reduceTaskCount);
	__os.writeInt(transTaskCount);
	__os.writeInt(workload);
	__os.writeInt(mapDoneCount);
	__os.writeInt(reduceDoneCount);
	__os.writeInt(transDoneCount);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	addr = new Address();
	addr.__read(__is);
	mapTaskCount = __is.readInt();
	reduceTaskCount = __is.readInt();
	transTaskCount = __is.readInt();
	workload = __is.readInt();
	mapDoneCount = __is.readInt();
	reduceDoneCount = __is.readInt();
	transDoneCount = __is.readInt();
    }
}
