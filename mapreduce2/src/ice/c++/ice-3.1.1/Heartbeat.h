// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Heartbeat.ice'

#ifndef _____c___ice_3_1_1_Heartbeat_h__
#define _____c___ice_3_1_1_Heartbeat_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace mapreduce
{

namespace slice
{

struct Heartbeat
{
    ::Ice::Int mapJobCount;
    ::Ice::Int reduceJobCount;
    ::Ice::Int workload;

    bool operator==(const Heartbeat&) const;
    bool operator!=(const Heartbeat&) const;
    bool operator<(const Heartbeat&) const;
    bool operator<=(const Heartbeat& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Heartbeat& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Heartbeat& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

}

}

#endif
