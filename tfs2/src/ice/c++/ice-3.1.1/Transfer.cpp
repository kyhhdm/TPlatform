// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Transfer.ice'

#include <Transfer.h>
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

static const ::std::string __tfs__slice__Transfer__read_name = "read";

static const ::std::string __tfs__slice__Transfer__write_name = "write";

static const ::std::string __tfs__slice__Transfer__addChunk_name = "addChunk";

static const ::std::string __tfs__slice__Transfer__append_name = "append";

static const ::std::string __tfs__slice__Transfer__rollback_name = "rollback";

static const ::std::string __tfs__slice__Transfer__getLocalPath_name = "getLocalPath";

void
IceInternal::incRef(::tfs::slice::Transfer* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::tfs::slice::Transfer* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::tfs::slice::Transfer* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::tfs::slice::Transfer* p)
{
    p->__decRef();
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::TransferPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::TransferPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::tfs::slice::Transfer;
	v->__copyFrom(proxy);
    }
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::TransferPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

tfs::slice::ErrorBase::ErrorBase(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    UserException(),
#else
    ::Ice::UserException(),
#endif
    reason(__ice_reason)
{
}

static const char* __tfs__slice__ErrorBase_name = "tfs::slice::ErrorBase";

const ::std::string
tfs::slice::ErrorBase::ice_name() const
{
    return __tfs__slice__ErrorBase_name;
}

::Ice::Exception*
tfs::slice::ErrorBase::ice_clone() const
{
    return new ErrorBase(*this);
}

void
tfs::slice::ErrorBase::ice_throw() const
{
    throw *this;
}

void
tfs::slice::ErrorBase::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::ErrorBase"), false);
    __os->startWriteSlice();
    __os->write(reason);
    __os->endWriteSlice();
}

void
tfs::slice::ErrorBase::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->read(reason);
    __is->endReadSlice();
}

void
tfs::slice::ErrorBase::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ErrorBase was not generated with stream support";
    throw ex;
}

void
tfs::slice::ErrorBase::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ErrorBase was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__ErrorBase : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::ErrorBase();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__ErrorBase__Ptr = new __F__tfs__slice__ErrorBase;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::ErrorBase::ice_factory()
{
    return __F__tfs__slice__ErrorBase__Ptr;
}

class __F__tfs__slice__ErrorBase__Init
{
public:

    __F__tfs__slice__ErrorBase__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::ErrorBase", ::tfs::slice::ErrorBase::ice_factory());
    }

    ~__F__tfs__slice__ErrorBase__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::ErrorBase");
    }
};

static __F__tfs__slice__ErrorBase__Init __F__tfs__slice__ErrorBase__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__ErrorBase__initializer() {} }
#endif

tfs::slice::DataError::DataError(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase(__ice_reason)
#else
    ::tfs::slice::ErrorBase(__ice_reason)
#endif
{
}

static const char* __tfs__slice__DataError_name = "tfs::slice::DataError";

const ::std::string
tfs::slice::DataError::ice_name() const
{
    return __tfs__slice__DataError_name;
}

::Ice::Exception*
tfs::slice::DataError::ice_clone() const
{
    return new DataError(*this);
}

void
tfs::slice::DataError::ice_throw() const
{
    throw *this;
}

void
tfs::slice::DataError::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::DataError"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__write(__os);
#else
    ::tfs::slice::ErrorBase::__write(__os);
#endif
}

void
tfs::slice::DataError::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__read(__is, true);
#else
    ::tfs::slice::ErrorBase::__read(__is, true);
#endif
}

void
tfs::slice::DataError::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::DataError was not generated with stream support";
    throw ex;
}

void
tfs::slice::DataError::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::DataError was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__DataError : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::DataError();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__DataError__Ptr = new __F__tfs__slice__DataError;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::DataError::ice_factory()
{
    return __F__tfs__slice__DataError__Ptr;
}

class __F__tfs__slice__DataError__Init
{
public:

    __F__tfs__slice__DataError__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::DataError", ::tfs::slice::DataError::ice_factory());
    }

    ~__F__tfs__slice__DataError__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::DataError");
    }
};

static __F__tfs__slice__DataError__Init __F__tfs__slice__DataError__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__DataError__initializer() {} }
#endif

tfs::slice::ChunkError::ChunkError(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase(__ice_reason)
#else
    ::tfs::slice::ErrorBase(__ice_reason)
#endif
{
}

static const char* __tfs__slice__ChunkError_name = "tfs::slice::ChunkError";

const ::std::string
tfs::slice::ChunkError::ice_name() const
{
    return __tfs__slice__ChunkError_name;
}

::Ice::Exception*
tfs::slice::ChunkError::ice_clone() const
{
    return new ChunkError(*this);
}

void
tfs::slice::ChunkError::ice_throw() const
{
    throw *this;
}

void
tfs::slice::ChunkError::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::ChunkError"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__write(__os);
#else
    ::tfs::slice::ErrorBase::__write(__os);
#endif
}

void
tfs::slice::ChunkError::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__read(__is, true);
#else
    ::tfs::slice::ErrorBase::__read(__is, true);
#endif
}

void
tfs::slice::ChunkError::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkError was not generated with stream support";
    throw ex;
}

void
tfs::slice::ChunkError::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkError was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__ChunkError : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::ChunkError();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__ChunkError__Ptr = new __F__tfs__slice__ChunkError;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::ChunkError::ice_factory()
{
    return __F__tfs__slice__ChunkError__Ptr;
}

class __F__tfs__slice__ChunkError__Init
{
public:

    __F__tfs__slice__ChunkError__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::ChunkError", ::tfs::slice::ChunkError::ice_factory());
    }

    ~__F__tfs__slice__ChunkError__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::ChunkError");
    }
};

static __F__tfs__slice__ChunkError__Init __F__tfs__slice__ChunkError__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__ChunkError__initializer() {} }
#endif

tfs::slice::ChunkNotExist::ChunkNotExist(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase(__ice_reason)
#else
    ::tfs::slice::ErrorBase(__ice_reason)
#endif
{
}

static const char* __tfs__slice__ChunkNotExist_name = "tfs::slice::ChunkNotExist";

const ::std::string
tfs::slice::ChunkNotExist::ice_name() const
{
    return __tfs__slice__ChunkNotExist_name;
}

::Ice::Exception*
tfs::slice::ChunkNotExist::ice_clone() const
{
    return new ChunkNotExist(*this);
}

void
tfs::slice::ChunkNotExist::ice_throw() const
{
    throw *this;
}

void
tfs::slice::ChunkNotExist::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::ChunkNotExist"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__write(__os);
#else
    ::tfs::slice::ErrorBase::__write(__os);
#endif
}

void
tfs::slice::ChunkNotExist::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    ErrorBase::__read(__is, true);
#else
    ::tfs::slice::ErrorBase::__read(__is, true);
#endif
}

void
tfs::slice::ChunkNotExist::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkNotExist was not generated with stream support";
    throw ex;
}

void
tfs::slice::ChunkNotExist::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkNotExist was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__ChunkNotExist : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::ChunkNotExist();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__ChunkNotExist__Ptr = new __F__tfs__slice__ChunkNotExist;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::ChunkNotExist::ice_factory()
{
    return __F__tfs__slice__ChunkNotExist__Ptr;
}

class __F__tfs__slice__ChunkNotExist__Init
{
public:

    __F__tfs__slice__ChunkNotExist__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::ChunkNotExist", ::tfs::slice::ChunkNotExist::ice_factory());
    }

    ~__F__tfs__slice__ChunkNotExist__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::ChunkNotExist");
    }
};

static __F__tfs__slice__ChunkNotExist__Init __F__tfs__slice__ChunkNotExist__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__ChunkNotExist__initializer() {} }
#endif

::tfs::slice::ByteSeq
IceProxy::tfs::slice::Transfer::read(::Ice::Long chunkid, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__read_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    return __del->read(chunkid, offset, len, __ctx);
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
IceProxy::tfs::slice::Transfer::write(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__write_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    return __del->write(chunkid, bytes, offset, len, __ctx);
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
IceProxy::tfs::slice::Transfer::addChunk(::Ice::Long chunkid, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__addChunk_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    __del->addChunk(chunkid, __ctx);
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

::Ice::Int
IceProxy::tfs::slice::Transfer::append(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int len, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__append_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    return __del->append(chunkid, bytes, len, __ctx);
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
IceProxy::tfs::slice::Transfer::rollback(::Ice::Long opid, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__rollback_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    __del->rollback(opid, __ctx);
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

::std::string
IceProxy::tfs::slice::Transfer::getLocalPath(::Ice::Long chunkid, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__Transfer__getLocalPath_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::Transfer* __del = dynamic_cast< ::IceDelegate::tfs::slice::Transfer*>(__delBase.get());
	    return __del->getLocalPath(chunkid, __ctx);
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
IceProxy::tfs::slice::Transfer::ice_staticId()
{
    return ::tfs::slice::Transfer::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::tfs::slice::Transfer::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::tfs::slice::Transfer);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::tfs::slice::Transfer::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::tfs::slice::Transfer);
}

bool
IceProxy::tfs::slice::operator==(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator!=(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<=(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return l < r || l == r;
}

bool
IceProxy::tfs::slice::operator>(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::tfs::slice::operator>=(const ::IceProxy::tfs::slice::Transfer& l, const ::IceProxy::tfs::slice::Transfer& r)
{
    return !(l < r);
}

::tfs::slice::ByteSeq
IceDelegateM::tfs::slice::Transfer::read(::Ice::Long chunkid, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__read_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(chunkid);
	__os->write(offset);
	__os->write(len);
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
	    catch(const ::tfs::slice::ChunkError&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::ChunkNotExist&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::ByteSeq __ret;
	::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> _____ret;
	__is->read(_____ret);
	::std::vector< ::Ice::Byte>(_____ret.first, _____ret.second).swap(__ret);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::tfs::slice::Transfer::write(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__write_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(chunkid);
	if(bytes.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    __os->write(&bytes[0], &bytes[0] + bytes.size());
	}
	__os->write(offset);
	__os->write(len);
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
	    catch(const ::tfs::slice::ChunkError&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::ChunkNotExist&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::DataError&)
	    {
		throw;
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

void
IceDelegateM::tfs::slice::Transfer::addChunk(::Ice::Long chunkid, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__addChunk_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(chunkid);
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
	    catch(const ::tfs::slice::ChunkError&)
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

::Ice::Int
IceDelegateM::tfs::slice::Transfer::append(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__append_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(chunkid);
	if(bytes.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    __os->write(&bytes[0], &bytes[0] + bytes.size());
	}
	__os->write(len);
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
	    catch(const ::tfs::slice::ChunkError&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::ChunkNotExist&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::DataError&)
	    {
		throw;
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

void
IceDelegateM::tfs::slice::Transfer::rollback(::Ice::Long opid, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__rollback_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(opid);
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
	    catch(const ::tfs::slice::ErrorBase&)
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

::std::string
IceDelegateM::tfs::slice::Transfer::getLocalPath(::Ice::Long chunkid, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__Transfer__getLocalPath_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(chunkid);
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
	    catch(const ::tfs::slice::ChunkError&)
	    {
		throw;
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

::tfs::slice::ByteSeq
IceDelegateD::tfs::slice::Transfer::read(::Ice::Long chunkid, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__read_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    return __servant->read(chunkid, offset, len, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::Int
IceDelegateD::tfs::slice::Transfer::write(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int offset, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__write_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    return __servant->write(chunkid, bytes, offset, len, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::Transfer::addChunk(::Ice::Long chunkid, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__addChunk_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    __servant->addChunk(chunkid, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::Int
IceDelegateD::tfs::slice::Transfer::append(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int len, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__append_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    return __servant->append(chunkid, bytes, len, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::Transfer::rollback(::Ice::Long opid, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__rollback_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    __servant->rollback(opid, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::std::string
IceDelegateD::tfs::slice::Transfer::getLocalPath(::Ice::Long chunkid, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__Transfer__getLocalPath_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::Transfer* __servant = dynamic_cast< ::tfs::slice::Transfer*>(__direct.servant().get());
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
	    return __servant->getLocalPath(chunkid, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
tfs::slice::Transfer::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __tfs__slice__Transfer_ids[2] =
{
    "::Ice::Object",
    "::tfs::slice::Transfer"
};

bool
tfs::slice::Transfer::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__tfs__slice__Transfer_ids, __tfs__slice__Transfer_ids + 2, _s);
}

::std::vector< ::std::string>
tfs::slice::Transfer::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__tfs__slice__Transfer_ids[0], &__tfs__slice__Transfer_ids[2]);
}

const ::std::string&
tfs::slice::Transfer::ice_id(const ::Ice::Current&) const
{
    return __tfs__slice__Transfer_ids[1];
}

const ::std::string&
tfs::slice::Transfer::ice_staticId()
{
    return __tfs__slice__Transfer_ids[1];
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___read(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long chunkid;
    ::Ice::Int offset;
    ::Ice::Int len;
    __is->read(chunkid);
    __is->read(offset);
    __is->read(len);
    try
    {
	::tfs::slice::ByteSeq __ret = read(chunkid, offset, len, __current);
	if(__ret.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    __os->write(&__ret[0], &__ret[0] + __ret.size());
	}
    }
    catch(const ::tfs::slice::ChunkError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::ChunkNotExist& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___write(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long chunkid;
    ::tfs::slice::ByteSeq bytes;
    ::Ice::Int offset;
    ::Ice::Int len;
    __is->read(chunkid);
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___bytes;
    __is->read(___bytes);
    ::std::vector< ::Ice::Byte>(___bytes.first, ___bytes.second).swap(bytes);
    __is->read(offset);
    __is->read(len);
    try
    {
	::Ice::Int __ret = write(chunkid, bytes, offset, len, __current);
	__os->write(__ret);
    }
    catch(const ::tfs::slice::ChunkError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::ChunkNotExist& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::DataError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___addChunk(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long chunkid;
    __is->read(chunkid);
    try
    {
	addChunk(chunkid, __current);
    }
    catch(const ::tfs::slice::ChunkError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___append(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long chunkid;
    ::tfs::slice::ByteSeq bytes;
    ::Ice::Int len;
    __is->read(chunkid);
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___bytes;
    __is->read(___bytes);
    ::std::vector< ::Ice::Byte>(___bytes.first, ___bytes.second).swap(bytes);
    __is->read(len);
    try
    {
	::Ice::Int __ret = append(chunkid, bytes, len, __current);
	__os->write(__ret);
    }
    catch(const ::tfs::slice::ChunkError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::ChunkNotExist& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::DataError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___rollback(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long opid;
    __is->read(opid);
    try
    {
	rollback(opid, __current);
    }
    catch(const ::tfs::slice::ErrorBase& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::Transfer::___getLocalPath(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Long chunkid;
    __is->read(chunkid);
    try
    {
	::std::string __ret = getLocalPath(chunkid, __current);
	__os->write(__ret);
    }
    catch(const ::tfs::slice::ChunkError& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

static ::std::string __tfs__slice__Transfer_all[] =
{
    "addChunk",
    "append",
    "getLocalPath",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "read",
    "rollback",
    "write"
};

::IceInternal::DispatchStatus
tfs::slice::Transfer::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__tfs__slice__Transfer_all, __tfs__slice__Transfer_all + 10, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __tfs__slice__Transfer_all)
    {
	case 0:
	{
	    return ___addChunk(in, current);
	}
	case 1:
	{
	    return ___append(in, current);
	}
	case 2:
	{
	    return ___getLocalPath(in, current);
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
	    return ___read(in, current);
	}
	case 8:
	{
	    return ___rollback(in, current);
	}
	case 9:
	{
	    return ___write(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
tfs::slice::Transfer::__write(::IceInternal::BasicStream* __os) const
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
tfs::slice::Transfer::__read(::IceInternal::BasicStream* __is, bool __rid)
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
tfs::slice::Transfer::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::Transfer was not generated with stream support";
    throw ex;
}

void
tfs::slice::Transfer::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::Transfer was not generated with stream support";
    throw ex;
}

void 
tfs::slice::__patch__TransferPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::tfs::slice::TransferPtr* p = static_cast< ::tfs::slice::TransferPtr*>(__addr);
    assert(p);
    *p = ::tfs::slice::TransferPtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::tfs::slice::Transfer::ice_staticId();
	throw e;
    }
}

bool
tfs::slice::operator==(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator!=(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<=(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return l < r || l == r;
}

bool
tfs::slice::operator>(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return !(l < r) && !(l == r);
}

bool
tfs::slice::operator>=(const ::tfs::slice::Transfer& l, const ::tfs::slice::Transfer& r)
{
    return !(l < r);
}
