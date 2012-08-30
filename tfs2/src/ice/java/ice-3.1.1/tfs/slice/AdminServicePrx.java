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

public interface AdminServicePrx extends Ice.ObjectPrx
{
    public String getStartTime();
    public String getStartTime(java.util.Map __ctx);

    public Address[] getChunkServers();
    public Address[] getChunkServers(java.util.Map __ctx);

    public Address[] getClients();
    public Address[] getClients(java.util.Map __ctx);

    public int[] getOperationsCount();
    public int[] getOperationsCount(java.util.Map __ctx);
}
