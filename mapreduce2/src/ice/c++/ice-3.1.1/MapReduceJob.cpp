// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `MapReduceJob.ice'

#include <MapReduceJob.h>
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
mapreduce::slice::MapReduceJob::operator==(const MapReduceJob& __rhs) const
{
    return !operator!=(__rhs);
}

bool
mapreduce::slice::MapReduceJob::operator!=(const MapReduceJob& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(inputFile != __rhs.inputFile)
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
    if(soFile != __rhs.soFile)
    {
	return true;
    }
    if(mapTaskNum != __rhs.mapTaskNum)
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
    if(doGroupBySort != __rhs.doGroupBySort)
    {
	return true;
    }
    if(doConcatOutputs != __rhs.doConcatOutputs)
    {
	return true;
    }
    if(mapperClass != __rhs.mapperClass)
    {
	return true;
    }
    if(reducerClass != __rhs.reducerClass)
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
    return false;
}

bool
mapreduce::slice::MapReduceJob::operator<(const MapReduceJob& __rhs) const
{
    if(this == &__rhs)
    {
	return false;
    }
    if(inputFile < __rhs.inputFile)
    {
	return true;
    }
    else if(__rhs.inputFile < inputFile)
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
    if(soFile < __rhs.soFile)
    {
	return true;
    }
    else if(__rhs.soFile < soFile)
    {
	return false;
    }
    if(mapTaskNum < __rhs.mapTaskNum)
    {
	return true;
    }
    else if(__rhs.mapTaskNum < mapTaskNum)
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
    if(doGroupBySort < __rhs.doGroupBySort)
    {
	return true;
    }
    else if(__rhs.doGroupBySort < doGroupBySort)
    {
	return false;
    }
    if(doConcatOutputs < __rhs.doConcatOutputs)
    {
	return true;
    }
    else if(__rhs.doConcatOutputs < doConcatOutputs)
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
    if(reducerClass < __rhs.reducerClass)
    {
	return true;
    }
    else if(__rhs.reducerClass < reducerClass)
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
    return false;
}

void
mapreduce::slice::MapReduceJob::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(inputFile);
    __os->write(outputFile);
    __os->write(outputReplication);
    __os->write(soFile);
    __os->write(mapTaskNum);
    __os->write(reduceTaskNum);
    __os->write(doLocalCombine);
    __os->write(doGroupBySort);
    __os->write(doConcatOutputs);
    __os->write(mapperClass);
    __os->write(reducerClass);
    __os->write(mapperOutKeyClass);
    __os->write(mapperOutValueClass);
    __os->write(mapperInKeyClass);
    __os->write(mapperInValueClass);
    __os->write(mapperRecordReaderClass);
    __os->write(reducerOutKeyClass);
    __os->write(reducerOutValueClass);
    __os->write(reducerRecordWriterClass);
}

void
mapreduce::slice::MapReduceJob::__read(::IceInternal::BasicStream* __is)
{
    __is->read(inputFile);
    __is->read(outputFile);
    __is->read(outputReplication);
    __is->read(soFile);
    __is->read(mapTaskNum);
    __is->read(reduceTaskNum);
    __is->read(doLocalCombine);
    __is->read(doGroupBySort);
    __is->read(doConcatOutputs);
    __is->read(mapperClass);
    __is->read(reducerClass);
    __is->read(mapperOutKeyClass);
    __is->read(mapperOutValueClass);
    __is->read(mapperInKeyClass);
    __is->read(mapperInValueClass);
    __is->read(mapperRecordReaderClass);
    __is->read(reducerOutKeyClass);
    __is->read(reducerOutValueClass);
    __is->read(reducerRecordWriterClass);
}
