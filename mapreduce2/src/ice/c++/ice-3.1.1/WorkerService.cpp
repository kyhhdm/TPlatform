// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `WorkerService.ice'

#include <WorkerService.h>
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

static const ::std::string __mapreduce__slice__WorkerService__sendHeartbeat_name = "sendHeartbeat";

static const ::std::string __mapreduce__slice__WorkerService__completeTask_name = "completeTask";

static const ::std::string __mapreduce__slice__WorkerService__abandonTask_name = "abandonTask";

void
IceInternal::incRef(::mapreduce::slice::WorkerService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::mapreduce::slice::WorkerService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::mapreduce::slice::WorkerService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::mapreduce::slice::WorkerService* p)
{
    p->__decRef();
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::WorkerServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
mapreduce::slice::__read(::IceInternal::BasicStream* __is, ::mapreduce::slice::WorkerServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::mapreduce::slice::WorkerService;
	v->__copyFrom(proxy);
    }
}

void
mapreduce::slice::__write(::IceInternal::BasicStream* __os, const ::mapreduce::slice::WorkerServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

::mapreduce::slice::MasterCommands
IceProxy::mapreduce::slice::WorkerService::sendHeartbeat(const ::mapreduce::slice::Address& workerAddress, const ::mapreduce::slice::Heartbeat& info, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__mapreduce__slice__WorkerService__sendHeartbeat_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::WorkerService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::WorkerService*>(__delBase.get());
	    return __del->sendHeartbeat(workerAddress, info, __ctx);
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapperRelaxed(__ex, __cnt);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

void
IceProxy::mapreduce::slice::WorkerService::completeTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskID, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::WorkerService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::WorkerService*>(__delBase.get());
	    __del->completeTask(workerAddress, taskID, __ctx);
	    return;
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapperRelaxed(__ex, __cnt);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

void
IceProxy::mapreduce::slice::WorkerService::abandonTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskId, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::mapreduce::slice::WorkerService* __del = dynamic_cast< ::IceDelegate::mapreduce::slice::WorkerService*>(__delBase.get());
	    __del->abandonTask(workerAddress, taskId, __ctx);
	    return;
	}
	catch(const ::IceInternal::LocalExceptionWrapper& __ex)
	{
	    __handleExceptionWrapperRelaxed(__ex, __cnt);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    __handleException(__ex, __cnt);
	}
    }
}

const ::std::string&
IceProxy::mapreduce::slice::WorkerService::ice_staticId()
{
    return ::mapreduce::slice::WorkerService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::mapreduce::slice::WorkerService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::mapreduce::slice::WorkerService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::mapreduce::slice::WorkerService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::mapreduce::slice::WorkerService);
}

bool
IceProxy::mapreduce::slice::operator==(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator!=(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::mapreduce::slice::operator<=(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return l < r || l == r;
}

bool
IceProxy::mapreduce::slice::operator>(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::mapreduce::slice::operator>=(const ::IceProxy::mapreduce::slice::WorkerService& l, const ::IceProxy::mapreduce::slice::WorkerService& r)
{
    return !(l < r);
}

::mapreduce::slice::MasterCommands
IceDelegateM::mapreduce::slice::WorkerService::sendHeartbeat(const ::mapreduce::slice::Address& workerAddress, const ::mapreduce::slice::Heartbeat& info, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__WorkerService__sendHeartbeat_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	workerAddress.__write(__os);
	info.__write(__os);
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
	::mapreduce::slice::MasterCommands __ret;
	::mapreduce::slice::__read(__is, __ret, ::mapreduce::slice::__U__MasterCommands());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::mapreduce::slice::WorkerService::completeTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskID, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__WorkerService__completeTask_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	workerAddress.__write(__os);
	__os->write(taskID);
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
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::mapreduce::slice::WorkerService::abandonTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskId, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __mapreduce__slice__WorkerService__abandonTask_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	workerAddress.__write(__os);
	__os->write(taskId);
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
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::mapreduce::slice::MasterCommands
IceDelegateD::mapreduce::slice::WorkerService::sendHeartbeat(const ::mapreduce::slice::Address& workerAddress, const ::mapreduce::slice::Heartbeat& info, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__WorkerService__sendHeartbeat_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::WorkerService* __servant = dynamic_cast< ::mapreduce::slice::WorkerService*>(__direct.servant().get());
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
	    return __servant->sendHeartbeat(workerAddress, info, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::mapreduce::slice::WorkerService::completeTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskID, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__WorkerService__completeTask_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::WorkerService* __servant = dynamic_cast< ::mapreduce::slice::WorkerService*>(__direct.servant().get());
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
	    __servant->completeTask(workerAddress, taskID, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::mapreduce::slice::WorkerService::abandonTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskId, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __mapreduce__slice__WorkerService__abandonTask_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::mapreduce::slice::WorkerService* __servant = dynamic_cast< ::mapreduce::slice::WorkerService*>(__direct.servant().get());
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
	    __servant->abandonTask(workerAddress, taskId, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
mapreduce::slice::WorkerService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __mapreduce__slice__WorkerService_ids[2] =
{
    "::Ice::Object",
    "::mapreduce::slice::WorkerService"
};

bool
mapreduce::slice::WorkerService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__mapreduce__slice__WorkerService_ids, __mapreduce__slice__WorkerService_ids + 2, _s);
}

::std::vector< ::std::string>
mapreduce::slice::WorkerService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__mapreduce__slice__WorkerService_ids[0], &__mapreduce__slice__WorkerService_ids[2]);
}

const ::std::string&
mapreduce::slice::WorkerService::ice_id(const ::Ice::Current&) const
{
    return __mapreduce__slice__WorkerService_ids[1];
}

const ::std::string&
mapreduce::slice::WorkerService::ice_staticId()
{
    return __mapreduce__slice__WorkerService_ids[1];
}

::IceInternal::DispatchStatus
mapreduce::slice::WorkerService::___sendHeartbeat(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::mapreduce::slice::Address workerAddress;
    ::mapreduce::slice::Heartbeat info;
    workerAddress.__read(__is);
    info.__read(__is);
    ::mapreduce::slice::MasterCommands __ret = sendHeartbeat(workerAddress, info, __current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::mapreduce::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::mapreduce::slice::__U__MasterCommands());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::WorkerService::___completeTask(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::mapreduce::slice::Address workerAddress;
    ::Ice::Int taskID;
    workerAddress.__read(__is);
    __is->read(taskID);
    completeTask(workerAddress, taskID, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
mapreduce::slice::WorkerService::___abandonTask(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::mapreduce::slice::Address workerAddress;
    ::Ice::Int taskId;
    workerAddress.__read(__is);
    __is->read(taskId);
    abandonTask(workerAddress, taskId, __current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __mapreduce__slice__WorkerService_all[] =
{
    "abandonTask",
    "completeTask",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "sendHeartbeat"
};

::IceInternal::DispatchStatus
mapreduce::slice::WorkerService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__mapreduce__slice__WorkerService_all, __mapreduce__slice__WorkerService_all + 7, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __mapreduce__slice__WorkerService_all)
    {
	case 0:
	{
	    return ___abandonTask(in, current);
	}
	case 1:
	{
	    return ___completeTask(in, current);
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
	    return ___sendHeartbeat(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
mapreduce::slice::WorkerService::__write(::IceInternal::BasicStream* __os) const
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
mapreduce::slice::WorkerService::__read(::IceInternal::BasicStream* __is, bool __rid)
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
mapreduce::slice::WorkerService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::WorkerService was not generated with stream support";
    throw ex;
}

void
mapreduce::slice::WorkerService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type mapreduce::slice::WorkerService was not generated with stream support";
    throw ex;
}

void 
mapreduce::slice::__patch__WorkerServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::mapreduce::slice::WorkerServicePtr* p = static_cast< ::mapreduce::slice::WorkerServicePtr*>(__addr);
    assert(p);
    *p = ::mapreduce::slice::WorkerServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::mapreduce::slice::WorkerService::ice_staticId();
	throw e;
    }
}

bool
mapreduce::slice::operator==(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator!=(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
mapreduce::slice::operator<=(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return l < r || l == r;
}

bool
mapreduce::slice::operator>(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return !(l < r) && !(l == r);
}

bool
mapreduce::slice::operator>=(const ::mapreduce::slice::WorkerService& l, const ::mapreduce::slice::WorkerService& r)
{
    return !(l < r);
}
