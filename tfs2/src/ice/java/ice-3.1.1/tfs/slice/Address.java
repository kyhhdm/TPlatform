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

public final class Address implements java.lang.Cloneable
{
    public String name;

    public int port;

    public Address()
    {
    }

    public Address(String name, int port)
    {
	this.name = name;
	this.port = port;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	Address _r = null;
	try
	{
	    _r = (Address)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(name != _r.name && name != null && !name.equals(_r.name))
	    {
		return false;
	    }
	    if(port != _r.port)
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
	if(name != null)
	{
	    __h = 5 * __h + name.hashCode();
	}
	__h = 5 * __h + port;
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
	__os.writeString(name);
	__os.writeInt(port);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	name = __is.readString();
	port = __is.readInt();
    }
}
