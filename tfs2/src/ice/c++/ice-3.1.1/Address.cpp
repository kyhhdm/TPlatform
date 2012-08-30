// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Address.ice'

#include <Address.h>
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
tfs::slice::Address::operator==(const Address& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::Address::operator!=(const Address& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(name != __rhs.name)
    {
	return true;
    }
    if(port != __rhs.port)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::Address::operator<(const Address& __rhs) const
{
    if(this == &__rhs)
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
    if(port < __rhs.port)
    {
	return true;
    }
    else if(__rhs.port < port)
    {
	return false;
    }
    return false;
}

void
tfs::slice::Address::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(name);
    __os->write(port);
}

void
tfs::slice::Address::__read(::IceInternal::BasicStream* __is)
{
    __is->read(name);
    __is->read(port);
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::Address* begin, const ::tfs::slice::Address* end, ::tfs::slice::__U__Addresses)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::Addresses& v, ::tfs::slice::__U__Addresses)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 5);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}
