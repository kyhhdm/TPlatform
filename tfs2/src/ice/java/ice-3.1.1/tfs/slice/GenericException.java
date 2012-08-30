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

public class GenericException extends Ice.UserException
{
    public GenericException()
    {
    }

    public GenericException(String reason)
    {
	this.reason = reason;
    }

    public String
    ice_name()
    {
	return "tfs::slice::GenericException";
    }

    public String reason;

    public void
    __write(IceInternal.BasicStream __os)
    {
	__os.writeString("::tfs::slice::GenericException");
	__os.startWriteSlice();
	__os.writeString(reason);
	__os.endWriteSlice();
    }

    public void
    __read(IceInternal.BasicStream __is, boolean __rid)
    {
	if(__rid)
	{
	    __is.readString();
	}
	__is.startReadSlice();
	reason = __is.readString();
	__is.endReadSlice();
    }

    public void
    __write(Ice.OutputStream __outS)
    {
	Ice.MarshalException ex = new Ice.MarshalException();
	ex.reason = "exception tfs::slice::GenericException was not generated with stream support";
	throw ex;
    }

    public void
    __read(Ice.InputStream __inS, boolean __rid)
    {
	Ice.MarshalException ex = new Ice.MarshalException();
	ex.reason = "exception tfs::slice::GenericException was not generated with stream support";
	throw ex;
    }
}
