// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `MonitorService.ice'

#ifndef _____c___ice_3_1_1_MonitorService_h__
#define _____c___ice_3_1_1_MonitorService_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Address.h>
#include <JobDetail.h>
#include <TaskDetail.h>
#include <WorkerDetail.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace mapreduce
{

namespace slice
{

class MonitorService;
bool operator==(const MonitorService&, const MonitorService&);
bool operator!=(const MonitorService&, const MonitorService&);
bool operator<(const MonitorService&, const MonitorService&);
bool operator<=(const MonitorService&, const MonitorService&);
bool operator>(const MonitorService&, const MonitorService&);
bool operator>=(const MonitorService&, const MonitorService&);

}

}

}

namespace mapreduce
{

namespace slice
{

class MonitorService;
bool operator==(const MonitorService&, const MonitorService&);
bool operator!=(const MonitorService&, const MonitorService&);
bool operator<(const MonitorService&, const MonitorService&);
bool operator<=(const MonitorService&, const MonitorService&);
bool operator>(const MonitorService&, const MonitorService&);
bool operator>=(const MonitorService&, const MonitorService&);

}

}

namespace IceInternal
{

void incRef(::mapreduce::slice::MonitorService*);
void decRef(::mapreduce::slice::MonitorService*);

void incRef(::IceProxy::mapreduce::slice::MonitorService*);
void decRef(::IceProxy::mapreduce::slice::MonitorService*);

}

namespace mapreduce
{

namespace slice
{

typedef ::IceInternal::Handle< ::mapreduce::slice::MonitorService> MonitorServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::mapreduce::slice::MonitorService> MonitorServicePrx;

void __write(::IceInternal::BasicStream*, const MonitorServicePrx&);
void __read(::IceInternal::BasicStream*, MonitorServicePrx&);
void __write(::IceInternal::BasicStream*, const MonitorServicePtr&);
void __patch__MonitorServicePtr(void*, ::Ice::ObjectPtr&);

}

}

namespace mapreduce
{

namespace slice
{

typedef ::std::vector< ::Ice::Int> TasksStatistics;

class __U__TasksStatistics { };

}

}

namespace IceProxy
{

namespace mapreduce
{

namespace slice
{

class MonitorService : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int getStartTime()
    {
	return getStartTime(__defaultContext());
    }
    ::Ice::Int getStartTime(const ::Ice::Context&);

    ::Ice::Int getCompletedJobs()
    {
	return getCompletedJobs(__defaultContext());
    }
    ::Ice::Int getCompletedJobs(const ::Ice::Context&);

    ::Ice::Int getCompletedTasks()
    {
	return getCompletedTasks(__defaultContext());
    }
    ::Ice::Int getCompletedTasks(const ::Ice::Context&);

    ::mapreduce::slice::WorkersDetail getWorkers()
    {
	return getWorkers(__defaultContext());
    }
    ::mapreduce::slice::WorkersDetail getWorkers(const ::Ice::Context&);

    ::mapreduce::slice::JobsDetail getJobs()
    {
	return getJobs(__defaultContext());
    }
    ::mapreduce::slice::JobsDetail getJobs(const ::Ice::Context&);

    ::mapreduce::slice::TasksDetail getTasks(::Ice::Int jobId)
    {
	return getTasks(jobId, __defaultContext());
    }
    ::mapreduce::slice::TasksDetail getTasks(::Ice::Int, const ::Ice::Context&);

    ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int jobId)
    {
	return getTasksStat(jobId, __defaultContext());
    }
    ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

}

namespace IceDelegate
{

namespace mapreduce
{

namespace slice
{

class MonitorService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int getStartTime(const ::Ice::Context&) = 0;

    virtual ::Ice::Int getCompletedJobs(const ::Ice::Context&) = 0;

    virtual ::Ice::Int getCompletedTasks(const ::Ice::Context&) = 0;

    virtual ::mapreduce::slice::WorkersDetail getWorkers(const ::Ice::Context&) = 0;

    virtual ::mapreduce::slice::JobsDetail getJobs(const ::Ice::Context&) = 0;

    virtual ::mapreduce::slice::TasksDetail getTasks(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int, const ::Ice::Context&) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace mapreduce
{

namespace slice
{

class MonitorService : virtual public ::IceDelegate::mapreduce::slice::MonitorService,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int getStartTime(const ::Ice::Context&);

    virtual ::Ice::Int getCompletedJobs(const ::Ice::Context&);

    virtual ::Ice::Int getCompletedTasks(const ::Ice::Context&);

    virtual ::mapreduce::slice::WorkersDetail getWorkers(const ::Ice::Context&);

    virtual ::mapreduce::slice::JobsDetail getJobs(const ::Ice::Context&);

    virtual ::mapreduce::slice::TasksDetail getTasks(::Ice::Int, const ::Ice::Context&);

    virtual ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int, const ::Ice::Context&);
};

}

}

}

namespace IceDelegateD
{

namespace mapreduce
{

namespace slice
{

class MonitorService : virtual public ::IceDelegate::mapreduce::slice::MonitorService,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int getStartTime(const ::Ice::Context&);

    virtual ::Ice::Int getCompletedJobs(const ::Ice::Context&);

    virtual ::Ice::Int getCompletedTasks(const ::Ice::Context&);

    virtual ::mapreduce::slice::WorkersDetail getWorkers(const ::Ice::Context&);

    virtual ::mapreduce::slice::JobsDetail getJobs(const ::Ice::Context&);

    virtual ::mapreduce::slice::TasksDetail getTasks(::Ice::Int, const ::Ice::Context&);

    virtual ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int, const ::Ice::Context&);
};

}

}

}

namespace mapreduce
{

namespace slice
{

class MonitorService : virtual public ::Ice::Object
{
public:

    typedef MonitorServicePrx ProxyType;
    typedef MonitorServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int getStartTime(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getStartTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getCompletedJobs(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getCompletedJobs(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getCompletedTasks(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getCompletedTasks(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::mapreduce::slice::WorkersDetail getWorkers(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getWorkers(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::mapreduce::slice::JobsDetail getJobs(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getJobs(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::mapreduce::slice::TasksDetail getTasks(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getTasks(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::mapreduce::slice::TasksStatistics getTasksStat(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getTasksStat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__MonitorServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
