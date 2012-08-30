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

public final class ChunksHelper
{
    public static void
    write(IceInternal.BasicStream __os, Chunk[] __v)
    {
	if(__v == null)
	{
	    __os.writeSize(0);
	}
	else
	{
	    __os.writeSize(__v.length);
	    for(int __i0 = 0; __i0 < __v.length; __i0++)
	    {
		__v[__i0].__write(__os);
	    }
	}
    }

    public static Chunk[]
    read(IceInternal.BasicStream __is)
    {
	Chunk[] __v;
	final int __len0 = __is.readSize();
	__is.checkFixedSeq(__len0, 24);
	__v = new Chunk[__len0];
	for(int __i0 = 0; __i0 < __len0; __i0++)
	{
	    __v[__i0] = new Chunk();
	    __v[__i0].__read(__is);
	}
	return __v;
    }
}
