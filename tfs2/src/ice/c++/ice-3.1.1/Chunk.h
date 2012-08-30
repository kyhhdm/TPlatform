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

#ifndef _____c___ice_3_1_1_Chunk_h__
#define _____c___ice_3_1_1_Chunk_h__

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

namespace tfs
{

namespace slice
{

struct Chunk
{
    ::Ice::Long id;
    ::Ice::Long size;
    ::Ice::Long version;

    bool operator==(const Chunk&) const;
    bool operator!=(const Chunk&) const;
    bool operator<(const Chunk&) const;
    bool operator<=(const Chunk& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Chunk& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Chunk& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::tfs::slice::Chunk> Chunks;

class __U__Chunks { };
void __write(::IceInternal::BasicStream*, const ::tfs::slice::Chunk*, const ::tfs::slice::Chunk*, __U__Chunks);
void __read(::IceInternal::BasicStream*, Chunks&, __U__Chunks);

struct LocatedChunk
{
    ::tfs::slice::Chunk chk;
    ::tfs::slice::Addresses locations;

    bool operator==(const LocatedChunk&) const;
    bool operator!=(const LocatedChunk&) const;
    bool operator<(const LocatedChunk&) const;
    bool operator<=(const LocatedChunk& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const LocatedChunk& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const LocatedChunk& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::tfs::slice::LocatedChunk> LocatedChunks;

class __U__LocatedChunks { };
void __write(::IceInternal::BasicStream*, const ::tfs::slice::LocatedChunk*, const ::tfs::slice::LocatedChunk*, __U__LocatedChunks);
void __read(::IceInternal::BasicStream*, LocatedChunks&, __U__LocatedChunks);

}

}

#endif
