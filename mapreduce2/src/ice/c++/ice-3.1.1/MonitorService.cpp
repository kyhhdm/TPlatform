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

#include <MonitorService.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
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

static const ::std::string __mapreduce__slice__MonitorService__getStartTime_name = "getStartTime";

static const ::std::string __mapreduce__slice__MonitorService__getCompletedJobs_name = "getCompletedJobs";

static const ::std::string __mapreduce__slice__MonitorService__getCompletedTasks_name = "getCompletedTasks";

static const ::std::string __mapreduce__slice__MonitorService__getWorkers_name = "getWorkers";

static const ::std::string __mapreduce__slice__MonitorService__getJobs_name = "getJobs";

static const ::std::string __mapreduce__slice__MonitorService__getTasks_name = "getTasks";

static const ::std::string __mapreduce__slice__MonitorService__getTasksStat_name = "getTasksStat";

void
IceInternal::incRef(::mapreduce::slice::MonitorService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::mapreduce::slice::MonitorService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::mapreduce::slice::MonitorService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::mapreduce::slice::MonitorService* p)
{
    p->__decRef();
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::MonitorServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::MonitorServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::mapreduce::slice::MonitorService;
	v->__copyFrom(proxy);
    }
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::MonitorServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

::Ice::Int
IceProxy::mapreduce::slice::MonitorService::getStartTime(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getStartTime_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getStartTime(__ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::Ice::Int
IceProxy::mapreduce::slice::MonitorService::getCompletedJobs(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getCompletedJobs_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getCompletedJobs(__ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::Ice::Int
IceProxy::mapreduce::slice::MonitorService::getCompletedTasks(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getCompletedTasks_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getCompletedTasks(__ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::mapreduce::slice::WorkersDetail
IceProxy::mapreduce::slice::MonitorService::getWorkers(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getWorkers_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getWorkers(__ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::mapreduce::slice::JobsDetail
IceProxy::mapreduce::slice::MonitorService::getJobs(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getJobs_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getJobs(__ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::mapreduce::slice::TasksDetail
IceProxy::mapreduce::slice::MonitorService::getTasks(::Ice::Int jobId, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getTasks_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getTasks(jobId, __ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

::mapreduce::slice::TasksStatistics
IceProxy::mapreduce::slice::MonitorService::getTasksStat(::Ice::Int jobId, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__MonitorService__getTasksStat_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::MonitorService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::MonitorService*>(__delBase.get());
	    return __del->getTasksStat(jobId, __ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapper(__ex);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

const ::std::string&
IceProxy::mapreduce::slice::MonitorService::ice_staticId()
{
    return ::mapreduce::slice::MonitorService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::mapreduce::slice::MonitorService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::mapreduce::slice::MonitorService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::mapreduce::slice::MonitorService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::mapreduce::slice::MonitorService);
}

bool
IceProxy::mapreduce::slice::operator==(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator!=(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<=(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return l < r || l == r;
}

bool
IceProxy::mapreduce::slice::operator>(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::mapreduce::slice::operator>=(const ::IceProxy::mapreduce::slice::MonitorService& l, const ::IceProxy::mapreduce::slice::MonitorService& r)
{
    return !(l < r);
}

::Ice::Int
IceDelegateM::mapreduce::slice::MonitorService::getStartTime(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getStartTime_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::Ice::Int __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::mapreduce::slice::MonitorService::getCompletedJobs(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getCompletedJobs_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::Ice::Int __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::mapreduce::slice::MonitorService::getCompletedTasks(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getCompletedTasks_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::Ice::Int __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::WorkersDetail
IceDelegateM::mapreduce::slice::MonitorService::getWorkers(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getWorkers_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::mapreduce::slice::WorkersDetail __ret;
	::mapreduce::slice::__read(__is, __ret, ::mapreduce::slice::__U__WorkersDetail());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::JobsDetail
IceDelegateM::mapreduce::slice::MonitorService::getJobs(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getJobs_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::mapreduce::slice::JobsDetail __ret;
	::mapreduce::slice::__read(__is, __ret, ::mapreduce::slice::__U__JobsDetail());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::TasksDetail
IceDelegateM::mapreduce::slice::MonitorService::getTasks(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getTasks_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(jobId);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::mapreduce::slice::TasksDetail __ret;
	::mapreduce::slice::__read(__is, __ret, ::mapreduce::slice::__U__TasksDetail());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::TasksStatistics
IceDelegateM::mapreduce::slice::MonitorService::getTasksStat(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__MonitorService__getTasksStat_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(jobId);
    }
    catch(const ::Ice::LocalException& __ex)
    {
	__og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
	::IceInternal::BasicStream* __is = __og.is();
	if(!__ok)
	{
	    try
	    {
		__is->throwException();
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::mapreduce::slice::TasksStatistics __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateD::mapreduce::slice::MonitorService::getStartTime(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getStartTime_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getStartTime(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::Int
IceDelegateD::mapreduce::slice::MonitorService::getCompletedJobs(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getCompletedJobs_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getCompletedJobs(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::Int
IceDelegateD::mapreduce::slice::MonitorService::getCompletedTasks(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getCompletedTasks_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getCompletedTasks(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::mapreduce::slice::WorkersDetail
IceDelegateD::mapreduce::slice::MonitorService::getWorkers(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getWorkers_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getWorkers(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::mapreduce::slice::JobsDetail
IceDelegateD::mapreduce::slice::MonitorService::getJobs(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getJobs_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getJobs(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::mapreduce::slice::TasksDetail
IceDelegateD::mapreduce::slice::MonitorService::getTasks(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getTasks_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getTasks(jobId, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::mapreduce::slice::TasksStatistics
IceDelegateD::mapreduce::slice::MonitorService::getTasksStat(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__MonitorService__getTasksStat_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::MonitorService* __servant = dynamic_cast< ::mapreduce::slice::MonitorService*>(__direct.servant().get());
	if(!__servant)
	{
	    ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
	    __opEx.id = __current.id;
	    __opEx.facet = __current.facet;
	    __opEx.operation = __current.operation;
	    throw __opEx;
	}
	try
	{
	    return __servant->getTasksStat(jobId, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
mapreduce::slice::MonitorService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __mapreduce__slice__MonitorService_ids[2] =
{
    "::Ice::Object",
    "::mapreduce::slice::MonitorService"
};

bool
mapreduce::slice::MonitorService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__mapreduce__slice__MonitorService_ids, __mapreduce__slice__MonitorService_ids + 2, _s);
}

::std::vector< ::std::string>
mapreduce::slice::MonitorService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__mapreduce__slice__MonitorService_ids[0], &__mapreduce__slice__MonitorService_ids[2]);
}

const ::std::string&
mapreduce::slice::MonitorService::ice_id(const ::Ice::Current&) const
{
    return __mapreduce__slice__MonitorService_ids[1];
}

const ::std::string&
mapreduce::slice::MonitorService::ice_staticId()
{
    return __mapreduce__slice__MonitorService_ids[1];
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getStartTime(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = getStartTime(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getCompletedJobs(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = getCompletedJobs(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getCompletedTasks(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = getCompletedTasks(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getWorkers(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::mapreduce::slice::WorkersDetail __ret = getWorkers(__current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::mapreduce::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::mapreduce::slice::__U__WorkersDetail());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getJobs(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::mapreduce::slice::JobsDetail __ret = getJobs(__current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::mapreduce::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::mapreduce::slice::__U__JobsDetail());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getTasks(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int jobId;
    __is->read(jobId);
    ::mapreduce::slice::TasksDetail __ret = getTasks(jobId, __current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::mapreduce::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::mapreduce::slice::__U__TasksDetail());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::___getTasksStat(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int jobId;
    __is->read(jobId);
    ::mapreduce::slice::TasksStatistics __ret = getTasksStat(jobId, __current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	__os->write(&__ret[0], &__ret[0] + __ret.size());
    }
    return ::IceInternal::DispatchOK;
}

static ::std::string __mapreduce__slice__MonitorService_all[] =
{
    "getCompletedJobs",
    "getCompletedTasks",
    "getJobs",
    "getStartTime",
    "getTasks",
    "getTasksStat",
    "getWorkers",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
mapreduce::slice::MonitorService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__mapreduce__slice__MonitorService_all, __mapreduce__slice__MonitorService_all + 11, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __mapreduce__slice__MonitorService_all)
    {
	case 0:
	{
	    return ___getCompletedJobs(in, current);
	}
	case 1:
	{
	    return ___getCompletedTasks(in, current);
	}
	case 2:
	{
	    return ___getJobs(in, current);
	}
	case 3:
	{
	    return ___getStartTime(in, current);
	}
	case 4:
	{
	    return ___getTasks(in, current);
	}
	case 5:
	{
	    return ___getTasksStat(in, current);
	}
	case 6:
	{
	    return ___getWorkers(in, current);
	}
	case 7:
	{
	    return ___ice_id(in, current);
	}
	case 8:
	{
	    return ___ice_ids(in, current);
	}
	case 9:
	{
	    return ___ice_isA(in, current);
	}
	case 10:
	{
	    return ___ice_ping(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
mapreduce::slice::MonitorService::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
mapreduce::slice::MonitorService::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
mapreduce::slice::MonitorService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::MonitorService was not generated with stream support";
    throw ex;
}

void
mapreduce::slice::MonitorService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::MonitorService was not generated with stream support";
    throw ex;
}

void 
mapreduce::slice::__patch__MonitorServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::mapreduce::slice::MonitorServicePtr* p = static_cast< ::mapreduce::slice::MonitorServicePtr*>(__addr);
    assert(p);
    *p = ::mapreduce::slice::MonitorServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::mapreduce::slice::MonitorService::ice_staticId();
	throw e;
    }
}

bool
mapreduce::slice::operator==(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator!=(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<=(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return l < r || l == r;
}

bool
mapreduce::slice::operator>(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return !(l < r) && !(l == r);
}

bool
mapreduce::slice::operator>=(const ::mapreduce::slice::MonitorService& l, const ::mapreduce::slice::MonitorService& r)
{
    return !(l < r);
}
