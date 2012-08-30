// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `JobService.ice'

#include <JobService.h>
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

static const ::std::string __mapreduce__slice__JobService__create_name = "create";

static const ::std::string __mapreduce__slice__JobService__getJobDetail_name = "getJobDetail";

static const ::std::string __mapreduce__slice__JobService__kill_name = "kill";

void
IceInternal::incRef(::mapreduce::slice::JobService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::mapreduce::slice::JobService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::mapreduce::slice::JobService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::mapreduce::slice::JobService* p)
{
    p->__decRef();
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::JobServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::JobServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::mapreduce::slice::JobService;
	v->__copyFrom(proxy);
    }
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::JobServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

::Ice::Int
IceProxy::mapreduce::slice::JobService::create(const ::mapreduce::slice::MapReduceJob& job, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__JobService__create_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::JobService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::JobService*>(__delBase.get());
	    return __del->create(job, __ctx);
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

::mapreduce::slice::JobDetail
IceProxy::mapreduce::slice::JobService::getJobDetail(::Ice::Int jobId, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__JobService__getJobDetail_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::JobService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::JobService*>(__delBase.get());
	    return __del->getJobDetail(jobId, __ctx);
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
IceProxy::mapreduce::slice::JobService::kill(::Ice::Int jobId, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__JobService__kill_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::JobService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::JobService*>(__delBase.get());
	    return __del->kill(jobId, __ctx);
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
IceProxy::mapreduce::slice::JobService::ice_staticId()
{
    return ::mapreduce::slice::JobService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::mapreduce::slice::JobService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::mapreduce::slice::JobService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::mapreduce::slice::JobService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::mapreduce::slice::JobService);
}

bool
IceProxy::mapreduce::slice::operator==(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator!=(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<=(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return l < r || l == r;
}

bool
IceProxy::mapreduce::slice::operator>(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::mapreduce::slice::operator>=(const ::IceProxy::mapreduce::slice::JobService& l, const ::IceProxy::mapreduce::slice::JobService& r)
{
    return !(l < r);
}

::Ice::Int
IceDelegateM::mapreduce::slice::JobService::create(const ::mapreduce::slice::MapReduceJob& job, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__JobService__create_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	job.__write(__os);
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
	::Ice::Int __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::JobDetail
IceDelegateM::mapreduce::slice::JobService::getJobDetail(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__JobService__getJobDetail_name, ::Ice::Normal, __context, __compress);
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
	::mapreduce::slice::JobDetail __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::mapreduce::slice::JobService::kill(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__JobService__kill_name, ::Ice::Normal, __context, __compress);
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
IceDelegateD::mapreduce::slice::JobService::create(const ::mapreduce::slice::MapReduceJob& job, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__JobService__create_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::JobService* __servant = dynamic_cast< ::mapreduce::slice::JobService*>(__direct.servant().get());
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
	    return __servant->create(job, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::mapreduce::slice::JobDetail
IceDelegateD::mapreduce::slice::JobService::getJobDetail(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__JobService__getJobDetail_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::JobService* __servant = dynamic_cast< ::mapreduce::slice::JobService*>(__direct.servant().get());
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
	    return __servant->getJobDetail(jobId, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::Int
IceDelegateD::mapreduce::slice::JobService::kill(::Ice::Int jobId, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__JobService__kill_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::JobService* __servant = dynamic_cast< ::mapreduce::slice::JobService*>(__direct.servant().get());
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
	    return __servant->kill(jobId, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
mapreduce::slice::JobService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __mapreduce__slice__JobService_ids[2] =
{
    "::Ice::Object",
    "::mapreduce::slice::JobService"
};

bool
mapreduce::slice::JobService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__mapreduce__slice__JobService_ids, __mapreduce__slice__JobService_ids + 2, _s);
}

::std::vector< ::std::string>
mapreduce::slice::JobService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__mapreduce__slice__JobService_ids[0], &__mapreduce__slice__JobService_ids[2]);
}

const ::std::string&
mapreduce::slice::JobService::ice_id(const ::Ice::Current&) const
{
    return __mapreduce__slice__JobService_ids[1];
}

const ::std::string&
mapreduce::slice::JobService::ice_staticId()
{
    return __mapreduce__slice__JobService_ids[1];
}

::IceInternal::DispatchStatus
mapreduce::slice::JobService::___create(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::mapreduce::slice::MapReduceJob job;
    job.__read(__is);
    ::Ice::Int __ret = create(job, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::JobService::___getJobDetail(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int jobId;
    __is->read(jobId);
    ::mapreduce::slice::JobDetail __ret = getJobDetail(jobId, __current);
    __ret.__write(__os);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::JobService::___kill(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int jobId;
    __is->read(jobId);
    ::Ice::Int __ret = kill(jobId, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

static ::std::string __mapreduce__slice__JobService_all[] =
{
    "create",
    "getJobDetail",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "kill"
};

::IceInternal::DispatchStatus
mapreduce::slice::JobService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__mapreduce__slice__JobService_all, __mapreduce__slice__JobService_all + 7, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __mapreduce__slice__JobService_all)
    {
	case 0:
	{
	    return ___create(in, current);
	}
	case 1:
	{
	    return ___getJobDetail(in, current);
	}
	case 2:
	{
	    return ___ice_id(in, current);
	}
	case 3:
	{
	    return ___ice_ids(in, current);
	}
	case 4:
	{
	    return ___ice_isA(in, current);
	}
	case 5:
	{
	    return ___ice_ping(in, current);
	}
	case 6:
	{
	    return ___kill(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
mapreduce::slice::JobService::__write(::IceInternal::BasicStream* __os) const
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
mapreduce::slice::JobService::__read(::IceInternal::BasicStream* __is, bool __rid)
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
mapreduce::slice::JobService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::JobService was not generated with stream support";
    throw ex;
}

void
mapreduce::slice::JobService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::JobService was not generated with stream support";
    throw ex;
}

void 
mapreduce::slice::__patch__JobServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::mapreduce::slice::JobServicePtr* p = static_cast< ::mapreduce::slice::JobServicePtr*>(__addr);
    assert(p);
    *p = ::mapreduce::slice::JobServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::mapreduce::slice::JobService::ice_staticId();
	throw e;
    }
}

bool
mapreduce::slice::operator==(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator!=(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<=(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return l < r || l == r;
}

bool
mapreduce::slice::operator>(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return !(l < r) && !(l == r);
}

bool
mapreduce::slice::operator>=(const ::mapreduce::slice::JobService& l, const ::mapreduce::slice::JobService& r)
{
    return !(l < r);
}
