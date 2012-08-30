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

public final class Chunk implements java.lang.Cloneable
{
    public long id;

    public long size;

    public long version;

    public Chunk()
    {
    }

    public Chunk(long id, long size, long version)
    {
	this.id = id;
	this.size = size;
	this.version = version;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	Chunk _r = null;
	try
	{
	    _r = (Chunk)rhs;
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
	    if(size != _r.size)
	    {
		return false;
	    }
	    if(version != _r.version)
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
	__h = 5 * __h + (int)id;
	__h = 5 * __h + (int)size;
	__h = 5 * __h + (int)version;
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
	__os.writeLong(id);
	__os.writeLong(size);
	__os.writeLong(version);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	id = __is.readLong();
	size = __is.readLong();
	version = __is.readLong();
    }
}
