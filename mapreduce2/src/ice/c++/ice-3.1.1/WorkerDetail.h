// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `WorkerDetail.ice'

#ifndef _____c___ice_3_1_1_WorkerDetail_h__
#define _____c___ice_3_1_1_WorkerDetail_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Address.h>
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

struct WorkerDetail
{
    ::mapreduce::slice::Address addr;
    ::Ice::Int mapTaskCount;
    ::Ice::Int reduceTaskCount;
    ::Ice::Int transTaskCount;
    ::Ice::Int workload;
    ::Ice::Int mapDoneCount;
    ::Ice::Int reduceDoneCount;
    ::Ice::Int transDoneCount;

    bool operator==(const WorkerDetail&) const;
    bool operator!=(const WorkerDetail&) const;
    bool operator<(const WorkerDetail&) const;
    bool operator<=(const WorkerDetail& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const WorkerDetail& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const WorkerDetail& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::mapreduce::slice::WorkerDetail> WorkersDetail;

class __U__WorkersDetail { };
void __write(::IceInternal::BasicStream*, const ::mapreduce::slice::WorkerDetail*, const ::mapreduce::slice::WorkerDetail*, __U__WorkersDetail);
void __read(::IceInternal::BasicStream*, WorkersDetail&, __U__WorkersDetail);

}

}

#endif
