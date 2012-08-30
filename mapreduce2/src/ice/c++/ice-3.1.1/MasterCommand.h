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

#ifndef _____c___ice_3_1_1_MasterCommand_h__
#define _____c___ice_3_1_1_MasterCommand_h__

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

namespace mapreduce
{

namespace slice
{

enum Action
{
    McDoNothing,
    McDoMap,
    McDoTrans,
    McDoReduce,
    McDoClean,
    McShutdown
};

void __write(::IceInternal::BasicStream*, Action);
void __read(::IceInternal::BasicStream*, Action&);

struct MasterCommand
{
    ::mapreduce::slice::Action command;
    ::Ice::Int taskId;
    ::Ice::Int jobId;
    ::std::string soFile;
    ::std::string mapperClass;
    ::std::string mapperInKeyClass;
    ::std::string mapperInValueClass;
    ::std::string mapperRecordReaderClass;
    ::Ice::Long chunkID;
    ::Ice::Long chunkSize;
    ::mapreduce::slice::Address chunkLocation;
    ::Ice::Int reduceTaskNum;
    bool doLocalCombine;
    ::std::string mapperOutKeyClass;
    ::std::string mapperOutValueClass;
    bool doGroupBySort;
    ::std::string reducerClass;
    ::std::string reducerOutKeyClass;
    ::std::string reducerOutValueClass;
    ::std::string reducerRecordWriterClass;
    ::std::string outputFile;
    ::Ice::Int outputReplication;
    ::Ice::Int partition;
    ::mapreduce::slice::Address transMapWorker;
    ::Ice::Int transMapTaskId;

    bool operator==(const MasterCommand&) const;
    bool operator!=(const MasterCommand&) const;
    bool operator<(const MasterCommand&) const;
    bool operator<=(const MasterCommand& __rhs) const
    {
	return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const MasterCommand& __rhs) const
    {
	return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const MasterCommand& __rhs) const
    {
	return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::mapreduce::slice::MasterCommand> MasterCommands;

class __U__MasterCommands { };
void __write(::IceInternal::BasicStream*, const ::mapreduce::slice::MasterCommand*, const ::mapreduce::slice::MasterCommand*, __U__MasterCommands);
void __read(::IceInternal::BasicStream*, MasterCommands&, __U__MasterCommands);

}

}

#endif
