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

public final class FileOpenMode
{
    private static FileOpenMode[] __values = new FileOpenMode[3];
    private int __value;

    public static final int _FileOpenWrite = 0;
    public static final FileOpenMode FileOpenWrite = new FileOpenMode(_FileOpenWrite);
    public static final int _FileOpenRead = 1;
    public static final FileOpenMode FileOpenRead = new FileOpenMode(_FileOpenRead);
    public static final int _FileOpenAppend = 2;
    public static final FileOpenMode FileOpenAppend = new FileOpenMode(_FileOpenAppend);

    public static FileOpenMode
    convert(int val)
    {
	assert val < 3;
	return __values[val];
    }

    public static FileOpenMode
    convert(String val)
    {
	for(int __i = 0; __i < __values.length; ++__i)
	{
	    if(__values[__i].toString().equals(val))
	    {
		return __values[__i];
	    }
	}
	assert false;
	return null;
    }

    public int
    value()
    {
	return __value;
    }

    public String
    toString()
    {
	return __T[__value];
    }

    private
    FileOpenMode(int val)
    {
	__value = val;
	__values[val] = this;
    }

    public void
    __write(IceInternal.BasicStream __os)
    {
	__os.writeByte((byte)__value);
    }

    public static FileOpenMode
    __read(IceInternal.BasicStream __is)
    {
	int __v = __is.readByte();
	if(__v < 0 || __v >= 3)
	{
	    throw new Ice.MarshalException();
	}
	return FileOpenMode.convert(__v);
    }

    final static private String[] __T =
    {
	"FileOpenWrite",
	"FileOpenRead",
	"FileOpenAppend"
    };
}
