// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `TaskDetail.ice'

#ifndef _____c___ice_3_1_1_TaskDetail_h__
#define _____c___ice_3_1_1_TaskDetail_h__

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

struct TaskDetail
{
    ::Ice::Int id;
    ::Ice::Int status;
    ::Ice::Int type;
    ::mapreduce::slice::Address worker;

    bool operator==(const TaskDetail&) const;
    bool operator!=(const TaskDetail&) const;
    bool operator<(const TaskDetail&) const;
    bool operator<=(const TaskDetail& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const TaskDetail& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const TaskDetail& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::mapreduce::slice::TaskDetail> TasksDetail;

class __U__TasksDetail { };
void __write(::IceInternal::BasicStream*, const ::mapreduce::slice::TaskDetail*, const ::mapreduce::slice::TaskDetail*, __U__TasksDetail);
void __read(::IceInternal::BasicStream*, TasksDetail&, __U__TasksDetail);

}

}

#endif
