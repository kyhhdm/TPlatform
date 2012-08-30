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

public interface _AdminServiceOperations
{
    String getStartTime(Ice.Current __current);

    Address[] getChunkServers(Ice.Current __current);

    Address[] getClients(Ice.Current __current);

    int[] getOperationsCount(Ice.Current __current);
}
