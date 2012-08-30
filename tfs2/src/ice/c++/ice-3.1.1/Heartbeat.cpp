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

#include <Heartbeat.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

bool
tfs::slice::Heartbeat::operator==(const Heartbeat& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::Heartbeat::operator!=(const Heartbeat& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(capacity != __rhs.capacity)
    {
	return true;
    }
    if(free != __rhs.free)
    {
	return true;
    }
    if(workload != __rhs.workload)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::Heartbeat::operator<(const Heartbeat& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(capacity < __rhs.capacity)
    {
	return true;
    }
    else if(__rhs.capacity < capacity)
    {
	return false;
    }
    if(free < __rhs.free)
    {
	return true;
    }
    else if(__rhs.free < free)
    {
	return false;
    }
    if(workload < __rhs.workload)
    {
	return true;
    }
    else if(__rhs.workload < workload)
    {
	return false;
    }
    return false;
}

void
tfs::slice::Heartbeat::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(capacity);
    __os->write(free);
    __os->write(workload);
}

void
tfs::slice::Heartbeat::__read(::IceInternal::BasicStream* __is)
{
    __is->read(capacity);
    __is->read(free);
    __is->read(workload);
}
