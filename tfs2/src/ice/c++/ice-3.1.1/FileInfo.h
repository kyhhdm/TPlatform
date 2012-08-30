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

#ifndef _____c___ice_3_1_1_FileInfo_h__
#define _____c___ice_3_1_1_FileInfo_h__

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

namespace tfs
{

namespace slice
{

const ::Ice::Short FileModeTypeDir = 512;

const ::Ice::Short FileModeOwnerRead = 256;

const ::Ice::Short FileModeOwnerWrite = 128;

const ::Ice::Short FileModeOwnerExec = 64;

const ::Ice::Short FileModeGroupRead = 32;

const ::Ice::Short FileModeGroupWrite = 16;

const ::Ice::Short FileModeGroupExec = 8;

const ::Ice::Short FileModeOtherRead = 4;

const ::Ice::Short FileModeOtherWrite = 2;

const ::Ice::Short FileModeOtherExec = 1;

struct FileInfo
{
    ::Ice::Short flag;
    ::std::string name;
    ::Ice::Int createTime;
    ::Ice::Long size;
    ::Ice::Short replication;
    ::Ice::Long chunkSize;

    bool operator==(const FileInfo&) const;
    bool operator!=(const FileInfo&) const;
    bool operator<(const FileInfo&) const;
    bool operator<=(const FileInfo& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const FileInfo& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const FileInfo& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::tfs::slice::FileInfo> FilesInfo;

class __U__FilesInfo { };
void __write(::IceInternal::BasicStream*, const ::tfs::slice::FileInfo*, const ::tfs::slice::FileInfo*, __U__FilesInfo);
void __read(::IceInternal::BasicStream*, FilesInfo&, __U__FilesInfo);

}

}

#endif
