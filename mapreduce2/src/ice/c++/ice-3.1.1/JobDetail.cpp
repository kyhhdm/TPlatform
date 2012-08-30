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

#include <JobDetail.h>
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
mapreduce::slice::JobDetail::operator==(const JobDetail& __rhs) const
{
    return !operator!=(__rhs);
}

bool
mapreduce::slice::JobDetail::operator!=(const JobDetail& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id != __rhs.id)
    {
	return true;
    }
    if(createTime != __rhs.createTime)
    {
	return true;
    }
    if(finishTime != __rhs.finishTime)
    {
	return true;
    }
    if(status != __rhs.status)
    {
	return true;
    }
    if(detached != __rhs.detached)
    {
	return true;
    }
    if(jobSpec != __rhs.jobSpec)
    {
	return true;
    }
    return false;
}

bool
mapreduce::slice::JobDetail::operator<(const JobDetail& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id < __rhs.id)
    {
	return true;
    }
    else if(__rhs.id < id)
    {
	return false;
    }
    if(createTime < __rhs.createTime)
    {
	return true;
    }
    else if(__rhs.createTime < createTime)
    {
	return false;
    }
    if(finishTime < __rhs.finishTime)
    {
	return true;
    }
    else if(__rhs.finishTime < finishTime)
    {
	return false;
    }
    if(status < __rhs.status)
    {
	return true;
    }
    else if(__rhs.status < status)
    {
	return false;
    }
    if(detached < __rhs.detached)
    {
	return true;
    }
    else if(__rhs.detached < detached)
    {
	return false;
    }
    if(jobSpec < __rhs.jobSpec)
    {
	return true;
    }
    else if(__rhs.jobSpec < jobSpec)
    {
	return false;
    }
    return false;
}

void
mapreduce::slice::JobDetail::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(id);
    __os->write(createTime);
    __os->write(finishTime);
    __os->write(status);
    __os->write(detached);
    jobSpec.__write(__os);
}

void
mapreduce::slice::JobDetail::__read(::IceInternal::BasicStream* __is)
{
    __is->read(id);
    __is->read(createTime);
    __is->read(finishTime);
    __is->read(status);
    __is->read(detached);
    jobSpec.__read(__is);
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::JobDetail* begin, const ::mapreduce::slice::JobDetail* end, ::mapreduce::slice::__U__JobsDetail)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::JobsDetail& v, ::mapreduce::slice::__U__JobsDetail)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 45);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}
