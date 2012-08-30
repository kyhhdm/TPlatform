// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `AdminService.ice'

#include <AdminService.h>
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

static const ::std::string __tfs__slice__AdminService__getStartTime_name = "getStartTime";

static const ::std::string __tfs__slice__AdminService__getChunkServers_name = "getChunkServers";

static const ::std::string __tfs__slice__AdminService__getClients_name = "getClients";

static const ::std::string __tfs__slice__AdminService__getOperationsCount_name = "getOperationsCount";

void
IceInternal::incRef(::tfs::slice::AdminService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::tfs::slice::AdminService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::tfs::slice::AdminService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::tfs::slice::AdminService* p)
{
    p->__decRef();
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::AdminServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::AdminServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::tfs::slice::AdminService;
	v->__copyFrom(proxy);
    }
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::AdminServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

::std::string
IceProxy::tfs::slice::AdminService::getStartTime(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__AdminService__getStartTime_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::AdminService* __del = dynamic_cast< ::IceDelegate::tfs::slice::AdminService*>(__delBase.get());
	    return __del->getStartTime(__ctx);
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

::tfs::slice::Addresses
IceProxy::tfs::slice::AdminService::getChunkServers(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__AdminService__getChunkServers_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::AdminService* __del = dynamic_cast< ::IceDelegate::tfs::slice::AdminService*>(__delBase.get());
	    return __del->getChunkServers(__ctx);
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

::tfs::slice::Addresses
IceProxy::tfs::slice::AdminService::getClients(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__AdminService__getClients_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::AdminService* __del = dynamic_cast< ::IceDelegate::tfs::slice::AdminService*>(__delBase.get());
	    return __del->getClients(__ctx);
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

::tfs::slice::OperationsCount
IceProxy::tfs::slice::AdminService::getOperationsCount(const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__AdminService__getOperationsCount_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::AdminService* __del = dynamic_cast< ::IceDelegate::tfs::slice::AdminService*>(__delBase.get());
	    return __del->getOperationsCount(__ctx);
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
IceProxy::tfs::slice::AdminService::ice_staticId()
{
    return ::tfs::slice::AdminService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::tfs::slice::AdminService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::tfs::slice::AdminService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::tfs::slice::AdminService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::tfs::slice::AdminService);
}

bool
IceProxy::tfs::slice::operator==(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator!=(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<=(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return l < r || l == r;
}

bool
IceProxy::tfs::slice::operator>(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::tfs::slice::operator>=(const ::IceProxy::tfs::slice::AdminService& l, const ::IceProxy::tfs::slice::AdminService& r)
{
    return !(l < r);
}

::std::string
IceDelegateM::tfs::slice::AdminService::getStartTime(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__AdminService__getStartTime_name, ::Ice::Idempotent, __context, __compress);
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
	::std::string __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::tfs::slice::Addresses
IceDelegateM::tfs::slice::AdminService::getChunkServers(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__AdminService__getChunkServers_name, ::Ice::Idempotent, __context, __compress);
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
	::tfs::slice::Addresses __ret;
	::tfs::slice::__read(__is, __ret, ::tfs::slice::__U__Addresses());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::tfs::slice::Addresses
IceDelegateM::tfs::slice::AdminService::getClients(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__AdminService__getClients_name, ::Ice::Idempotent, __context, __compress);
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
	::tfs::slice::Addresses __ret;
	::tfs::slice::__read(__is, __ret, ::tfs::slice::__U__Addresses());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::tfs::slice::OperationsCount
IceDelegateM::tfs::slice::AdminService::getOperationsCount(const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__AdminService__getOperationsCount_name, ::Ice::Idempotent, __context, __compress);
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
	::tfs::slice::OperationsCount __ret;
	__is->read(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::std::string
IceDelegateD::tfs::slice::AdminService::getStartTime(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__AdminService__getStartTime_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::AdminService* __servant = dynamic_cast< ::tfs::slice::AdminService*>(__direct.servant().get());
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

::tfs::slice::Addresses
IceDelegateD::tfs::slice::AdminService::getChunkServers(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__AdminService__getChunkServers_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::AdminService* __servant = dynamic_cast< ::tfs::slice::AdminService*>(__direct.servant().get());
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
	    return __servant->getChunkServers(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::Addresses
IceDelegateD::tfs::slice::AdminService::getClients(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__AdminService__getClients_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::AdminService* __servant = dynamic_cast< ::tfs::slice::AdminService*>(__direct.servant().get());
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
	    return __servant->getClients(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::OperationsCount
IceDelegateD::tfs::slice::AdminService::getOperationsCount(const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__AdminService__getOperationsCount_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::AdminService* __servant = dynamic_cast< ::tfs::slice::AdminService*>(__direct.servant().get());
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
	    return __servant->getOperationsCount(__current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
tfs::slice::AdminService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __tfs__slice__AdminService_ids[2] =
{
    "::Ice::Object",
    "::tfs::slice::AdminService"
};

bool
tfs::slice::AdminService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__tfs__slice__AdminService_ids, __tfs__slice__AdminService_ids + 2, _s);
}

::std::vector< ::std::string>
tfs::slice::AdminService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__tfs__slice__AdminService_ids[0], &__tfs__slice__AdminService_ids[2]);
}

const ::std::string&
tfs::slice::AdminService::ice_id(const ::Ice::Current&) const
{
    return __tfs__slice__AdminService_ids[1];
}

const ::std::string&
tfs::slice::AdminService::ice_staticId()
{
    return __tfs__slice__AdminService_ids[1];
}

::IceInternal::DispatchStatus
tfs::slice::AdminService::___getStartTime(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = getStartTime(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::AdminService::___getChunkServers(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Addresses __ret = getChunkServers(__current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::tfs::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::tfs::slice::__U__Addresses());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::AdminService::___getClients(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Addresses __ret = getClients(__current);
    if(__ret.size() == 0)
    {
	__os->writeSize(0);
    }
    else
    {
	::tfs::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::tfs::slice::__U__Addresses());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::AdminService::___getOperationsCount(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::OperationsCount __ret = getOperationsCount(__current);
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

static ::std::string __tfs__slice__AdminService_all[] =
{
    "getChunkServers",
    "getClients",
    "getOperationsCount",
    "getStartTime",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
tfs::slice::AdminService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__tfs__slice__AdminService_all, __tfs__slice__AdminService_all + 8, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __tfs__slice__AdminService_all)
    {
	case 0:
	{
	    return ___getChunkServers(in, current);
	}
	case 1:
	{
	    return ___getClients(in, current);
	}
	case 2:
	{
	    return ___getOperationsCount(in, current);
	}
	case 3:
	{
	    return ___getStartTime(in, current);
	}
	case 4:
	{
	    return ___ice_id(in, current);
	}
	case 5:
	{
	    return ___ice_ids(in, current);
	}
	case 6:
	{
	    return ___ice_isA(in, current);
	}
	case 7:
	{
	    return ___ice_ping(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
tfs::slice::AdminService::__write(::IceInternal::BasicStream* __os) const
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
tfs::slice::AdminService::__read(::IceInternal::BasicStream* __is, bool __rid)
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
tfs::slice::AdminService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::AdminService was not generated with stream support";
    throw ex;
}

void
tfs::slice::AdminService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::AdminService was not generated with stream support";
    throw ex;
}

void 
tfs::slice::__patch__AdminServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::tfs::slice::AdminServicePtr* p = static_cast< ::tfs::slice::AdminServicePtr*>(__addr);
    assert(p);
    *p = ::tfs::slice::AdminServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::tfs::slice::AdminService::ice_staticId();
	throw e;
    }
}

bool
tfs::slice::operator==(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator!=(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<=(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return l < r || l == r;
}

bool
tfs::slice::operator>(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return !(l < r) && !(l == r);
}

bool
tfs::slice::operator>=(const ::tfs::slice::AdminService& l, const ::tfs::slice::AdminService& r)
{
    return !(l < r);
}
