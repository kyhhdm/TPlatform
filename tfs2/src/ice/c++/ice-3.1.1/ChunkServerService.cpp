// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `ChunkServerService.ice'

#include <ChunkServerService.h>
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

static const ::std::string __tfs__slice__ChunkServerService__enroll_name = "enroll";

static const ::std::string __tfs__slice__ChunkServerService__sendHeartbeat_name = "sendHeartbeat";

static const ::std::string __tfs__slice__ChunkServerService__chunkReport_name = "chunkReport";

static const ::std::string __tfs__slice__ChunkServerService__completeMigrateChunk_name = "completeMigrateChunk";

void
IceInternal::incRef(::tfs::slice::ChunkServerService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::tfs::slice::ChunkServerService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::tfs::slice::ChunkServerService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::tfs::slice::ChunkServerService* p)
{
    p->__decRef();
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::ChunkServerServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::ChunkServerServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::tfs::slice::ChunkServerService;
	v->__copyFrom(proxy);
    }
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::ChunkServerServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
IceProxy::tfs::slice::ChunkServerService::enroll(const ::tfs::slice::Address& chunkServerAddress, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ChunkServerService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ChunkServerService*>(__delBase.get());
	    __del->enroll(chunkServerAddress, __ctx);
	    return;
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

::tfs::slice::MasterCommand
IceProxy::tfs::slice::ChunkServerService::sendHeartbeat(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Heartbeat& info, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ChunkServerService__sendHeartbeat_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ChunkServerService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ChunkServerService*>(__delBase.get());
	    return __del->sendHeartbeat(chunkServerAddress, info, __ctx);
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

void
IceProxy::tfs::slice::ChunkServerService::chunkReport(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Chunks& chks, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ChunkServerService__chunkReport_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ChunkServerService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ChunkServerService*>(__delBase.get());
	    __del->chunkReport(chunkServerAddress, chks, __ctx);
	    return;
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

void
IceProxy::tfs::slice::ChunkServerService::completeMigrateChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ChunkServerService__completeMigrateChunk_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ChunkServerService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ChunkServerService*>(__delBase.get());
	    __del->completeMigrateChunk(lchk, __ctx);
	    return;
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
IceProxy::tfs::slice::ChunkServerService::ice_staticId()
{
    return ::tfs::slice::ChunkServerService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::tfs::slice::ChunkServerService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::tfs::slice::ChunkServerService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::tfs::slice::ChunkServerService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::tfs::slice::ChunkServerService);
}

bool
IceProxy::tfs::slice::operator==(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator!=(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<=(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return l < r || l == r;
}

bool
IceProxy::tfs::slice::operator>(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::tfs::slice::operator>=(const ::IceProxy::tfs::slice::ChunkServerService& l, const ::IceProxy::tfs::slice::ChunkServerService& r)
{
    return !(l < r);
}

void
IceDelegateM::tfs::slice::ChunkServerService::enroll(const ::tfs::slice::Address& chunkServerAddress, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ChunkServerService__enroll_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	chunkServerAddress.__write(__os);
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

::tfs::slice::MasterCommand
IceDelegateM::tfs::slice::ChunkServerService::sendHeartbeat(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Heartbeat& info, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ChunkServerService__sendHeartbeat_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	chunkServerAddress.__write(__os);
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
	    catch(const ::tfs::slice::UnknownChunkServer&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::MasterCommand __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::tfs::slice::ChunkServerService::chunkReport(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Chunks& chks, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ChunkServerService__chunkReport_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	chunkServerAddress.__write(__os);
	if(chks.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    ::tfs::slice::__write(__os, &chks[0], &chks[0] + chks.size(), ::tfs::slice::__U__Chunks());
	}
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
	    catch(const ::tfs::slice::UnknownChunkServer&)
	    {
		throw;
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
IceDelegateM::tfs::slice::ChunkServerService::completeMigrateChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ChunkServerService__completeMigrateChunk_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	lchk.__write(__os);
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
	    catch(const ::tfs::slice::NoSuchChunk&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::UnknownChunkServer&)
	    {
		throw;
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
IceDelegateD::tfs::slice::ChunkServerService::enroll(const ::tfs::slice::Address& chunkServerAddress, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ChunkServerService__enroll_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ChunkServerService* __servant = dynamic_cast< ::tfs::slice::ChunkServerService*>(__direct.servant().get());
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
	    __servant->enroll(chunkServerAddress, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::MasterCommand
IceDelegateD::tfs::slice::ChunkServerService::sendHeartbeat(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Heartbeat& info, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ChunkServerService__sendHeartbeat_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ChunkServerService* __servant = dynamic_cast< ::tfs::slice::ChunkServerService*>(__direct.servant().get());
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
	    return __servant->sendHeartbeat(chunkServerAddress, info, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ChunkServerService::chunkReport(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Chunks& chks, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ChunkServerService__chunkReport_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ChunkServerService* __servant = dynamic_cast< ::tfs::slice::ChunkServerService*>(__direct.servant().get());
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
	    __servant->chunkReport(chunkServerAddress, chks, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ChunkServerService::completeMigrateChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ChunkServerService__completeMigrateChunk_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ChunkServerService* __servant = dynamic_cast< ::tfs::slice::ChunkServerService*>(__direct.servant().get());
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
	    __servant->completeMigrateChunk(lchk, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
tfs::slice::ChunkServerService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __tfs__slice__ChunkServerService_ids[2] =
{
    "::Ice::Object",
    "::tfs::slice::ChunkServerService"
};

bool
tfs::slice::ChunkServerService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__tfs__slice__ChunkServerService_ids, __tfs__slice__ChunkServerService_ids + 2, _s);
}

::std::vector< ::std::string>
tfs::slice::ChunkServerService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__tfs__slice__ChunkServerService_ids[0], &__tfs__slice__ChunkServerService_ids[2]);
}

const ::std::string&
tfs::slice::ChunkServerService::ice_id(const ::Ice::Current&) const
{
    return __tfs__slice__ChunkServerService_ids[1];
}

const ::std::string&
tfs::slice::ChunkServerService::ice_staticId()
{
    return __tfs__slice__ChunkServerService_ids[1];
}

::IceInternal::DispatchStatus
tfs::slice::ChunkServerService::___enroll(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::tfs::slice::Address chunkServerAddress;
    chunkServerAddress.__read(__is);
    enroll(chunkServerAddress, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ChunkServerService::___sendHeartbeat(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Address chunkServerAddress;
    ::tfs::slice::Heartbeat info;
    chunkServerAddress.__read(__is);
    info.__read(__is);
    try
    {
	::tfs::slice::MasterCommand __ret = sendHeartbeat(chunkServerAddress, info, __current);
	__ret.__write(__os);
    }
    catch(const ::tfs::slice::UnknownChunkServer& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ChunkServerService::___chunkReport(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Address chunkServerAddress;
    ::tfs::slice::Chunks chks;
    chunkServerAddress.__read(__is);
    ::tfs::slice::__read(__is, chks, ::tfs::slice::__U__Chunks());
    try
    {
	chunkReport(chunkServerAddress, chks, __current);
    }
    catch(const ::tfs::slice::UnknownChunkServer& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ChunkServerService::___completeMigrateChunk(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::LocatedChunk lchk;
    lchk.__read(__is);
    try
    {
	completeMigrateChunk(lchk, __current);
    }
    catch(const ::tfs::slice::NoSuchChunk& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::UnknownChunkServer& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

static ::std::string __tfs__slice__ChunkServerService_all[] =
{
    "chunkReport",
    "completeMigrateChunk",
    "enroll",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "sendHeartbeat"
};

::IceInternal::DispatchStatus
tfs::slice::ChunkServerService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__tfs__slice__ChunkServerService_all, __tfs__slice__ChunkServerService_all + 8, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __tfs__slice__ChunkServerService_all)
    {
	case 0:
	{
	    return ___chunkReport(in, current);
	}
	case 1:
	{
	    return ___completeMigrateChunk(in, current);
	}
	case 2:
	{
	    return ___enroll(in, current);
	}
	case 3:
	{
	    return ___ice_id(in, current);
	}
	case 4:
	{
	    return ___ice_ids(in, current);
	}
	case 5:
	{
	    return ___ice_isA(in, current);
	}
	case 6:
	{
	    return ___ice_ping(in, current);
	}
	case 7:
	{
	    return ___sendHeartbeat(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
tfs::slice::ChunkServerService::__write(::IceInternal::BasicStream* __os) const
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
tfs::slice::ChunkServerService::__read(::IceInternal::BasicStream* __is, bool __rid)
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
tfs::slice::ChunkServerService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::ChunkServerService was not generated with stream support";
    throw ex;
}

void
tfs::slice::ChunkServerService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::ChunkServerService was not generated with stream support";
    throw ex;
}

void 
tfs::slice::__patch__ChunkServerServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::tfs::slice::ChunkServerServicePtr* p = static_cast< ::tfs::slice::ChunkServerServicePtr*>(__addr);
    assert(p);
    *p = ::tfs::slice::ChunkServerServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::tfs::slice::ChunkServerService::ice_staticId();
	throw e;
    }
}

bool
tfs::slice::operator==(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator!=(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<=(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return l < r || l == r;
}

bool
tfs::slice::operator>(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return !(l < r) && !(l == r);
}

bool
tfs::slice::operator>=(const ::tfs::slice::ChunkServerService& l, const ::tfs::slice::ChunkServerService& r)
{
    return !(l < r);
}
