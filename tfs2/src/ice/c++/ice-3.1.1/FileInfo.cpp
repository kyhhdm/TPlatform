// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `FileInfo.ice'

#include <FileInfo.h>
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
tfs::slice::FileInfo::operator==(const FileInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::FileInfo::operator!=(const FileInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(flag != __rhs.flag)
    {
	return true;
    }
    if(name != __rhs.name)
    {
	return true;
    }
    if(createTime != __rhs.createTime)
    {
	return true;
    }
    if(size != __rhs.size)
    {
	return true;
    }
    if(replication != __rhs.replication)
    {
	return true;
    }
    if(chunkSize != __rhs.chunkSize)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::FileInfo::operator<(const FileInfo& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(flag < __rhs.flag)
    {
	return true;
    }
    else if(__rhs.flag < flag)
    {
	return false;
    }
    if(name < __rhs.name)
    {
	return true;
    }
    else if(__rhs.name < name)
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
    if(size < __rhs.size)
    {
	return true;
    }
    else if(__rhs.size < size)
    {
	return false;
    }
    if(replication < __rhs.replication)
    {
	return true;
    }
    else if(__rhs.replication < replication)
    {
	return false;
    }
    if(chunkSize < __rhs.chunkSize)
    {
	return true;
    }
    else if(__rhs.chunkSize < chunkSize)
    {
	return false;
    }
    return false;
}

void
tfs::slice::FileInfo::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(flag);
    __os->write(name);
    __os->write(createTime);
    __os->write(size);
    __os->write(replication);
    __os->write(chunkSize);
}

void
tfs::slice::FileInfo::__read(::IceInternal::BasicStream* __is)
{
    __is->read(flag);
    __is->read(name);
    __is->read(createTime);
    __is->read(size);
    __is->read(replication);
    __is->read(chunkSize);
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::FileInfo* begin, const ::tfs::slice::FileInfo* end, ::tfs::slice::__U__FilesInfo)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::FilesInfo& v, ::tfs::slice::__U__FilesInfo)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 25);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}
