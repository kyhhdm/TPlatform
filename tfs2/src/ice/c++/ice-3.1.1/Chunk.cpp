// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Chunk.ice'

#include <Chunk.h>
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
tfs::slice::Chunk::operator==(const Chunk& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::Chunk::operator!=(const Chunk& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(id != __rhs.id)
    {
	return true;
    }
    if(size != __rhs.size)
    {
	return true;
    }
    if(version != __rhs.version)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::Chunk::operator<(const Chunk& __rhs) const
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
    if(size < __rhs.size)
    {
	return true;
    }
    else if(__rhs.size < size)
    {
	return false;
    }
    if(version < __rhs.version)
    {
	return true;
    }
    else if(__rhs.version < version)
    {
	return false;
    }
    return false;
}

void
tfs::slice::Chunk::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(id);
    __os->write(size);
    __os->write(version);
}

void
tfs::slice::Chunk::__read(::IceInternal::BasicStream* __is)
{
    __is->read(id);
    __is->read(size);
    __is->read(version);
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::Chunk* begin, const ::tfs::slice::Chunk* end, ::tfs::slice::__U__Chunks)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::Chunks& v, ::tfs::slice::__U__Chunks)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->checkFixedSeq(sz, 24);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
    }
}

bool
tfs::slice::LocatedChunk::operator==(const LocatedChunk& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::LocatedChunk::operator!=(const LocatedChunk& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(chk != __rhs.chk)
    {
	return true;
    }
    if(locations != __rhs.locations)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::LocatedChunk::operator<(const LocatedChunk& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(chk < __rhs.chk)
    {
	return true;
    }
    else if(__rhs.chk < chk)
    {
	return false;
    }
    if(locations < __rhs.locations)
    {
	return true;
    }
    else if(__rhs.locations < locations)
    {
	return false;
    }
    return false;
}

void
tfs::slice::LocatedChunk::__write(::IceInternal::BasicStream* __os) const
{
    chk.__write(__os);
    if(locations.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::tfs::slice::__write(__os, &locations[0], &locations[0] + locations.size(), ::tfs::slice::__U__Addresses());
    }
}

void
tfs::slice::LocatedChunk::__read(::IceInternal::BasicStream* __is)
{
    chk.__read(__is);
    ::tfs::slice::__read(__is, locations, ::tfs::slice::__U__Addresses());
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::LocatedChunk* begin, const ::tfs::slice::LocatedChunk* end, ::tfs::slice::__U__LocatedChunks)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::LocatedChunks& v, ::tfs::slice::__U__LocatedChunks)
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
