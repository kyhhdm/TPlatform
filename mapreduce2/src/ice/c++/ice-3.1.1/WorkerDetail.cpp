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

#include <WorkerDetail.h>
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
mapreduce::slice::WorkerDetail::operator==(const WorkerDetail& __rhs) const
{
    return !operator!=(__rhs);
}

bool
mapreduce::slice::WorkerDetail::operator!=(const WorkerDetail& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(addr != __rhs.addr)
    {
	return true;
    }
    if(mapTaskCount != __rhs.mapTaskCount)
    {
	return true;
    }
    if(reduceTaskCount != __rhs.reduceTaskCount)
    {
	return true;
    }
    if(transTaskCount != __rhs.transTaskCount)
    {
	return true;
    }
    if(workload != __rhs.workload)
    {
	return true;
    }
    if(mapDoneCount != __rhs.mapDoneCount)
    {
	return true;
    }
    if(reduceDoneCount != __rhs.reduceDoneCount)
    {
	return true;
    }
    if(transDoneCount != __rhs.transDoneCount)
    {
	return true;
    }
    return false;
}

bool
mapreduce::slice::WorkerDetail::operator<(const WorkerDetail& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(addr < __rhs.addr)
    {
	return true;
    }
    else if(__rhs.addr < addr)
    {
	return false;
    }
    if(mapTaskCount < __rhs.mapTaskCount)
    {
	return true;
    }
    else if(__rhs.mapTaskCount < mapTaskCount)
    {
	return false;
    }
    if(reduceTaskCount < __rhs.reduceTaskCount)
    {
	return true;
    }
    else if(__rhs.reduceTaskCount < reduceTaskCount)
    {
	return false;
    }
    if(transTaskCount < __rhs.transTaskCount)
    {
	return true;
    }
    else if(__rhs.transTaskCount < transTaskCount)
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
    if(mapDoneCount < __rhs.mapDoneCount)
    {
	return true;
    }
    else if(__rhs.mapDoneCount < mapDoneCount)
    {
	return false;
    }
    if(reduceDoneCount < __rhs.reduceDoneCount)
    {
	return true;
    }
    else if(__rhs.reduceDoneCount < reduceDoneCount)
    {
	return false;
    }
    if(transDoneCount < __rhs.transDoneCount)
    {
	return true;
    }
    else if(__rhs.transDoneCount < transDoneCount)
    {
	return false;
    }
    return false;
}

void
mapreduce::slice::WorkerDetail::__write(::IceInternal::BasicStream* __os) const
{
    addr.__write(__os);
    __os->write(mapTaskCount);
    __os->write(reduceTaskCount);
    __os->write(transTaskCount);
    __os->write(workload);
    __os->write(mapDoneCount);
    __os->write(reduceDoneCount);
    __os->write(transDoneCount);
}

void
mapreduce::slice::WorkerDetail::__read(::IceInternal::BasicStream* __is)
{
    addr.__read(__is);
    __is->read(mapTaskCount);
    __is->read(reduceTaskCount);
    __is->read(transTaskCount);
    __is->read(workload);
    __is->read(mapDoneCount);
    __is->read(reduceDoneCount);
    __is->read(transDoneCount);
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::WorkerDetail* begin, const ::mapreduce::slice::WorkerDetail* end, ::mapreduce::slice::__U__WorkersDetail)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::WorkersDetail& v, ::mapreduce::slice::__U__WorkersDetail)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 33);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}
