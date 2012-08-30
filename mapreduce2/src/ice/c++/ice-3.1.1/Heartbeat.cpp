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
mapreduce::slice::Heartbeat::operator==(const Heartbeat& __rhs) const
{
    return !operator!=(__rhs);
}

bool
mapreduce::slice::Heartbeat::operator!=(const Heartbeat& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(mapJobCount != __rhs.mapJobCount)
    {
	return true;
    }
    if(reduceJobCount != __rhs.reduceJobCount)
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
mapreduce::slice::Heartbeat::operator<(const Heartbeat& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(mapJobCount < __rhs.mapJobCount)
    {
	return true;
    }
    else if(__rhs.mapJobCount < mapJobCount)
    {
	return false;
    }
    if(reduceJobCount < __rhs.reduceJobCount)
    {
	return true;
    }
    else if(__rhs.reduceJobCount < reduceJobCount)
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
mapreduce::slice::Heartbeat::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(mapJobCount);
    __os->write(reduceJobCount);
    __os->write(workload);
}

void
mapreduce::slice::Heartbeat::__read(::IceInternal::BasicStream* __is)
{
    __is->read(mapJobCount);
    __is->read(reduceJobCount);
    __is->read(workload);
}
