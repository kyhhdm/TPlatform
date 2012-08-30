// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `JobDetail.ice'

#ifndef _____c___ice_3_1_1_JobDetail_h__
#define _____c___ice_3_1_1_JobDetail_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <MapReduceJob.h>
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

struct JobDetail
{
    ::Ice::Int id;
    ::Ice::Int createTime;
    ::Ice::Int finishTime;
    ::Ice::Int status;
    bool detached;
    ::mapreduce::slice::MapReduceJob jobSpec;

    bool operator==(const JobDetail&) const;
    bool operator!=(const JobDetail&) const;
    bool operator<(const JobDetail&) const;
    bool operator<=(const JobDetail& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const JobDetail& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const JobDetail& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::mapreduce::slice::JobDetail> JobsDetail;

class __U__JobsDetail { };
void __write(::IceInternal::BasicStream*, const ::mapreduce::slice::JobDetail*, const ::mapreduce::slice::JobDetail*, __U__JobsDetail);
void __read(::IceInternal::BasicStream*, JobsDetail&, __U__JobsDetail);

}

}

#endif
