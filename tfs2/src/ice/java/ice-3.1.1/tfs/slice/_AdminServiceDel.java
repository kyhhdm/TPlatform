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

public interface _AdminServiceDel extends Ice._ObjectDel
{
    String getStartTime(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    Address[] getChunkServers(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    Address[] getClients(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;

    int[] getOperationsCount(java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper;
}
