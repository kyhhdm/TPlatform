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

public final class LocatedChunk implements java.lang.Cloneable
{
    public Chunk chk;

    public Address[] locations;

    public LocatedChunk()
    {
    }

    public LocatedChunk(Chunk chk, Address[] locations)
    {
	this.chk = chk;
	this.locations = locations;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	LocatedChunk _r = null;
	try
	{
	    _r = (LocatedChunk)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(chk != _r.chk && chk != null && !chk.equals(_r.chk))
	    {
		return false;
	    }
	    if(!java.util.Arrays.equals(locations, _r.locations))
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
	__h = 5 * __h + chk.hashCode();
	if(locations != null)
	{
	    for(int __i0 = 0; __i0 < locations.length; __i0++)
	    {
		__h = 5 * __h + locations[__i0].hashCode();
	    }
	}
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
	chk.__write(__os);
	AddressesHelper.write(__os, locations);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	chk = new Chunk();
	chk.__read(__is);
	locations = AddressesHelper.read(__is);
    }
}
