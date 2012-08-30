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

#ifndef _____c___ice_3_1_1_Address_h__
#define _____c___ice_3_1_1_Address_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
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

struct Address
{
    ::std::string name;
    ::Ice::Int port;

    bool operator==(const Address&) const;
    bool operator!=(const Address&) const;
    bool operator<(const Address&) const;
    bool operator<=(const Address& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Address& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Address& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::mapreduce::slice::Address> Addresses;

class __U__Addresses { };
void __write(::IceInternal::BasicStream*, const ::mapreduce::slice::Address*, const ::mapreduce::slice::Address*, __U__Addresses);
void __read(::IceInternal::BasicStream*, Addresses&, __U__Addresses);

}

}

#endif
