// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1

package tfs.slice;

public final class FileInfo implements java.lang.Cloneable
{
    public short flag;

    public String name;

    public int createTime;

    public long size;

    public short replication;

    public long chunkSize;

    public FileInfo()
    {
    }

    public FileInfo(short flag, String name, int createTime, long size, short replication, long chunkSize)
    {
	this.flag = flag;
	this.name = name;
	this.createTime = createTime;
	this.size = size;
	this.replication = replication;
	this.chunkSize = chunkSize;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	FileInfo _r = null;
	try
	{
	    _r = (FileInfo)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(flag != _r.flag)
	    {
		return false;
	    }
	    if(name != _r.name && name != null && !name.equals(_r.name))
	    {
		return false;
	    }
	    if(createTime != _r.createTime)
	    {
		return false;
	    }
	    if(size != _r.size)
	    {
		return false;
	    }
	    if(replication != _r.replication)
	    {
		return false;
	    }
	    if(chunkSize != _r.chunkSize)
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
	__h = 5 * __h + (int)flag;
	if(name != null)
	{
	    __h = 5 * __h + name.hashCode();
	}
	__h = 5 * __h + createTime;
	__h = 5 * __h + (int)size;
	__h = 5 * __h + (int)replication;
	__h = 5 * __h + (int)chunkSize;
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
	__os.writeShort(flag);
	__os.writeString(name);
	__os.writeInt(createTime);
	__os.writeLong(size);
	__os.writeShort(replication);
	__os.writeLong(chunkSize);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	flag = __is.readShort();
	name = __is.readString();
	createTime = __is.readInt();
	size = __is.readLong();
	replication = __is.readShort();
	chunkSize = __is.readLong();
    }
}
