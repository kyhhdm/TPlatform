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
mapreduce::slice::__write(::IceInternal::BasicStream* __os, ::mapreduce::slice::Action v)
{
    __os->write(static_cast< ::Ice::Byte>(v));
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::Action& v)
{
    ::Ice::Byte val;
    __is->read(val);
    v = static_cast< ::mapreduce::slice::Action>(val);
}

bool
mapreduce::slice::MasterCommand::operator==(const MasterCommand& __rhs) const
{
    return !operator!=(__rhs);
}

bool
mapreduce::slice::MasterCommand::operator!=(const MasterCommand& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(command != __rhs.command)
    {
	return true;
    }
    if(taskId != __rhs.taskId)
    {
	return true;
    }
    if(jobId != __rhs.jobId)
    {
	return true;
    }
    if(soFile != __rhs.soFile)
    {
	return true;
    }
    if(mapperClass != __rhs.mapperClass)
    {
	return true;
    }
    if(mapperInKeyClass != __rhs.mapperInKeyClass)
    {
	return true;
    }
    if(mapperInValueClass != __rhs.mapperInValueClass)
    {
	return true;
    }
    if(mapperRecordReaderClass != __rhs.mapperRecordReaderClass)
    {
	return true;
    }
    if(chunkID != __rhs.chunkID)
    {
	return true;
    }
    if(chunkSize != __rhs.chunkSize)
    {
	return true;
    }
    if(chunkLocation != __rhs.chunkLocation)
    {
	return true;
    }
    if(reduceTaskNum != __rhs.reduceTaskNum)
    {
	return true;
    }
    if(doLocalCombine != __rhs.doLocalCombine)
    {
	return true;
    }
    if(mapperOutKeyClass != __rhs.mapperOutKeyClass)
    {
	return true;
    }
    if(mapperOutValueClass != __rhs.mapperOutValueClass)
    {
	return true;
    }
    if(doGroupBySort != __rhs.doGroupBySort)
    {
	return true;
    }
    if(reducerClass != __rhs.reducerClass)
    {
	return true;
    }
    if(reducerOutKeyClass != __rhs.reducerOutKeyClass)
    {
	return true;
    }
    if(reducerOutValueClass != __rhs.reducerOutValueClass)
    {
	return true;
    }
    if(reducerRecordWriterClass != __rhs.reducerRecordWriterClass)
    {
	return true;
    }
    if(outputFile != __rhs.outputFile)
    {
	return true;
    }
    if(outputReplication != __rhs.outputReplication)
    {
	return true;
    }
    if(partition != __rhs.partition)
    {
	return true;
    }
    if(transMapWorker != __rhs.transMapWorker)
    {
	return true;
    }
    if(transMapTaskId != __rhs.transMapTaskId)
    {
	return true;
    }
    return false;
}

bool
mapreduce::slice::MasterCommand::operator<(const MasterCommand& __rhs) const
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
    if(taskId < __rhs.taskId)
    {
	return true;
    }
    else if(__rhs.taskId < taskId)
    {
	return false;
    }
    if(jobId < __rhs.jobId)
    {
	return true;
    }
    else if(__rhs.jobId < jobId)
    {
	return false;
    }
    if(soFile < __rhs.soFile)
    {
	return true;
    }
    else if(__rhs.soFile < soFile)
    {
	return false;
    }
    if(mapperClass < __rhs.mapperClass)
    {
	return true;
    }
    else if(__rhs.mapperClass < mapperClass)
    {
	return false;
    }
    if(mapperInKeyClass < __rhs.mapperInKeyClass)
    {
	return true;
    }
    else if(__rhs.mapperInKeyClass < mapperInKeyClass)
    {
	return false;
    }
    if(mapperInValueClass < __rhs.mapperInValueClass)
    {
	return true;
    }
    else if(__rhs.mapperInValueClass < mapperInValueClass)
    {
	return false;
    }
    if(mapperRecordReaderClass < __rhs.mapperRecordReaderClass)
    {
	return true;
    }
    else if(__rhs.mapperRecordReaderClass < mapperRecordReaderClass)
    {
	return false;
    }
    if(chunkID < __rhs.chunkID)
    {
	return true;
    }
    else if(__rhs.chunkID < chunkID)
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
    if(chunkLocation < __rhs.chunkLocation)
    {
	return true;
    }
    else if(__rhs.chunkLocation < chunkLocation)
    {
	return false;
    }
    if(reduceTaskNum < __rhs.reduceTaskNum)
    {
	return true;
    }
    else if(__rhs.reduceTaskNum < reduceTaskNum)
    {
	return false;
    }
    if(doLocalCombine < __rhs.doLocalCombine)
    {
	return true;
    }
    else if(__rhs.doLocalCombine < doLocalCombine)
    {
	return false;
    }
    if(mapperOutKeyClass < __rhs.mapperOutKeyClass)
    {
	return true;
    }
    else if(__rhs.mapperOutKeyClass < mapperOutKeyClass)
    {
	return false;
    }
    if(mapperOutValueClass < __rhs.mapperOutValueClass)
    {
	return true;
    }
    else if(__rhs.mapperOutValueClass < mapperOutValueClass)
    {
	return false;
    }
    if(doGroupBySort < __rhs.doGroupBySort)
    {
	return true;
    }
    else if(__rhs.doGroupBySort < doGroupBySort)
    {
	return false;
    }
    if(reducerClass < __rhs.reducerClass)
    {
	return true;
    }
    else if(__rhs.reducerClass < reducerClass)
    {
	return false;
    }
    if(reducerOutKeyClass < __rhs.reducerOutKeyClass)
    {
	return true;
    }
    else if(__rhs.reducerOutKeyClass < reducerOutKeyClass)
    {
	return false;
    }
    if(reducerOutValueClass < __rhs.reducerOutValueClass)
    {
	return true;
    }
    else if(__rhs.reducerOutValueClass < reducerOutValueClass)
    {
	return false;
    }
    if(reducerRecordWriterClass < __rhs.reducerRecordWriterClass)
    {
	return true;
    }
    else if(__rhs.reducerRecordWriterClass < reducerRecordWriterClass)
    {
	return false;
    }
    if(outputFile < __rhs.outputFile)
    {
	return true;
    }
    else if(__rhs.outputFile < outputFile)
    {
	return false;
    }
    if(outputReplication < __rhs.outputReplication)
    {
	return true;
    }
    else if(__rhs.outputReplication < outputReplication)
    {
	return false;
    }
    if(partition < __rhs.partition)
    {
	return true;
    }
    else if(__rhs.partition < partition)
    {
	return false;
    }
    if(transMapWorker < __rhs.transMapWorker)
    {
	return true;
    }
    else if(__rhs.transMapWorker < transMapWorker)
    {
	return false;
    }
    if(transMapTaskId < __rhs.transMapTaskId)
    {
	return true;
    }
    else if(__rhs.transMapTaskId < transMapTaskId)
    {
	return false;
    }
    return false;
}

void
mapreduce::slice::MasterCommand::__write(::IceInternal::BasicStream* __os) const
{
    ::mapreduce::slice::__write(__os, command);
    __os->write(taskId);
    __os->write(jobId);
    __os->write(soFile);
    __os->write(mapperClass);
    __os->write(mapperInKeyClass);
    __os->write(mapperInValueClass);
    __os->write(mapperRecordReaderClass);
    __os->write(chunkID);
    __os->write(chunkSize);
    chunkLocation.__write(__os);
    __os->write(reduceTaskNum);
    __os->write(doLocalCombine);
    __os->write(mapperOutKeyClass);
    __os->write(mapperOutValueClass);
    __os->write(doGroupBySort);
    __os->write(reducerClass);
    __os->write(reducerOutKeyClass);
    __os->write(reducerOutValueClass);
    __os->write(reducerRecordWriterClass);
    __os->write(outputFile);
    __os->write(outputReplication);
    __os->write(partition);
    transMapWorker.__write(__os);
    __os->write(transMapTaskId);
}

void
mapreduce::slice::MasterCommand::__read(::IceInternal::BasicStream* __is)
{
    ::mapreduce::slice::__read(__is, command);
    __is->read(taskId);
    __is->read(jobId);
    __is->read(soFile);
    __is->read(mapperClass);
    __is->read(mapperInKeyClass);
    __is->read(mapperInValueClass);
    __is->read(mapperRecordReaderClass);
    __is->read(chunkID);
    __is->read(chunkSize);
    chunkLocation.__read(__is);
    __is->read(reduceTaskNum);
    __is->read(doLocalCombine);
    __is->read(mapperOutKeyClass);
    __is->read(mapperOutValueClass);
    __is->read(doGroupBySort);
    __is->read(reducerClass);
    __is->read(reducerOutKeyClass);
    __is->read(reducerOutValueClass);
    __is->read(reducerRecordWriterClass);
    __is->read(outputFile);
    __is->read(outputReplication);
    __is->read(partition);
    transMapWorker.__read(__is);
    __is->read(transMapTaskId);
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::MasterCommand* begin, const ::mapreduce::slice::MasterCommand* end, ::mapreduce::slice::__U__MasterCommands)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
	begin[i].__write(__os);
    }
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::MasterCommands& v, ::mapreduce::slice::__U__MasterCommands)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 65);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
	v[i].__read(__is);
	__is->checkSeq();
	__is->endElement();
    }
    __is->endSeq(sz);
}
