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

public final class AdminServiceHolder
{
    public
    AdminServiceHolder()
    {
    }

    public
    AdminServiceHolder(AdminService value)
    {
	this.value = value;
    }

    public class Patcher implements IceInternal.Patcher
    {
	public void
	patch(Ice.Object v)
	{
	    value = (AdminService)v;
	}

	public String
	type()
	{
	    return "::tfs::slice::AdminService";
	}
    }

    public Patcher
    getPatcher()
    {
	return new Patcher();
    }

    public AdminService value;
}
