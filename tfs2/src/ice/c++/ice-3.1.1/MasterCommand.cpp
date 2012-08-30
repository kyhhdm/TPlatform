// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `MasterCommand.ice'

#include <MasterCommand.h>
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

void
tfs::slice::__write(::IceInternal::BasicStream* __os, ::tfs::slice::Action v)
{
    __os->write(static_cast< ::Ice::Byte>(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::Action& v)
{
    ::Ice::Byte val;
    __is->read(val);
    v = static_cast< ::tfs::slice::Action>(val);
}

bool
tfs::slice::MasterCommand::operator==(const MasterCommand& __rhs) const
{
    return !operator!=(__rhs);
}

bool
tfs::slice::MasterCommand::operator!=(const MasterCommand& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(command != __rhs.command)
    {
	return true;
    }
    if(chks != __rhs.chks)
    {
	return true;
    }
    if(targets != __rhs.targets)
    {
	return true;
    }
    return false;
}

bool
tfs::slice::MasterCommand::operator<(const MasterCommand& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(command < __rhs.command)
    {
	return true;
    }
    else if(__rhs.command < command)
    {
	return false;
    }
    if(chks < __rhs.chks)
    {
	return true;
    }
    else if(__rhs.chks < chks)
    {
	return false;
    }
    if(targets < __rhs.targets)
    {
	return true;
    }
    else if(__rhs.targets < targets)
    {
	return false;
    }
    return false;
}

void
tfs::slice::MasterCommand::__write(::IceInternal::BasicStream* __os) const
{
    ::tfs::slice::__write(__os, command);
    if(chks.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::tfs::slice::__write(__os, &chks[0], &chks[0] + chks.size(), ::tfs::slice::__U__Chunks());
    }
    if(targets.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::tfs::slice::__write(__os, &targets[0], &targets[0] + targets.size(), ::tfs::slice::__U__Addresses());
    }
}

void
tfs::slice::MasterCommand::__read(::IceInternal::BasicStream* __is)
{
    ::tfs::slice::__read(__is, command);
    ::tfs::slice::__read(__is, chks, ::tfs::slice::__U__Chunks());
    ::tfs::slice::__read(__is, targets, ::tfs::slice::__U__Addresses());
}
