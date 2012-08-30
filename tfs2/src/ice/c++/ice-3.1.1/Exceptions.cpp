// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Exceptions.ice'

#include <Exceptions.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <Ice/LocalException.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

tfs::slice::GenericException::GenericException(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    UserException(),
#else
    ::Ice::UserException(),
#endif
    reason(__ice_reason)
{
}

static const char* __tfs__slice__GenericException_name = "tfs::slice::GenericException";

const ::std::string
tfs::slice::GenericException::ice_name() const
{
    return __tfs__slice__GenericException_name;
}

::Ice::Exception*
tfs::slice::GenericException::ice_clone() const
{
    return new GenericException(*this);
}

void
tfs::slice::GenericException::ice_throw() const
{
    throw *this;
}

void
tfs::slice::GenericException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::GenericException"), false);
    __os->startWriteSlice();
    __os->write(reason);
    __os->endWriteSlice();
}

void
tfs::slice::GenericException::__read(::IceInternal::BasicStream* __is, bool __rid)
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
tfs::slice::GenericException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::GenericException was not generated with stream support";
    throw ex;
}

void
tfs::slice::GenericException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::GenericException was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__GenericException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::GenericException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__GenericException__Ptr = new __F__tfs__slice__GenericException;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::GenericException::ice_factory()
{
    return __F__tfs__slice__GenericException__Ptr;
}

class __F__tfs__slice__GenericException__Init
{
public:

    __F__tfs__slice__GenericException__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::GenericException", ::tfs::slice::GenericException::ice_factory());
    }

    ~__F__tfs__slice__GenericException__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::GenericException");
    }
};

static __F__tfs__slice__GenericException__Init __F__tfs__slice__GenericException__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__GenericException__initializer() {} }
#endif

tfs::slice::NoSuchFileOrDir::NoSuchFileOrDir(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__NoSuchFileOrDir_name = "tfs::slice::NoSuchFileOrDir";

const ::std::string
tfs::slice::NoSuchFileOrDir::ice_name() const
{
    return __tfs__slice__NoSuchFileOrDir_name;
}

::Ice::Exception*
tfs::slice::NoSuchFileOrDir::ice_clone() const
{
    return new NoSuchFileOrDir(*this);
}

void
tfs::slice::NoSuchFileOrDir::ice_throw() const
{
    throw *this;
}

void
tfs::slice::NoSuchFileOrDir::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::NoSuchFileOrDir"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::NoSuchFileOrDir::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::NoSuchFileOrDir::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoSuchFileOrDir was not generated with stream support";
    throw ex;
}

void
tfs::slice::NoSuchFileOrDir::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoSuchFileOrDir was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__NoSuchFileOrDir : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::NoSuchFileOrDir();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__NoSuchFileOrDir__Ptr = new __F__tfs__slice__NoSuchFileOrDir;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::NoSuchFileOrDir::ice_factory()
{
    return __F__tfs__slice__NoSuchFileOrDir__Ptr;
}

class __F__tfs__slice__NoSuchFileOrDir__Init
{
public:

    __F__tfs__slice__NoSuchFileOrDir__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::NoSuchFileOrDir", ::tfs::slice::NoSuchFileOrDir::ice_factory());
    }

    ~__F__tfs__slice__NoSuchFileOrDir__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::NoSuchFileOrDir");
    }
};

static __F__tfs__slice__NoSuchFileOrDir__Init __F__tfs__slice__NoSuchFileOrDir__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__NoSuchFileOrDir__initializer() {} }
#endif

tfs::slice::IOError::IOError(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__IOError_name = "tfs::slice::IOError";

const ::std::string
tfs::slice::IOError::ice_name() const
{
    return __tfs__slice__IOError_name;
}

::Ice::Exception*
tfs::slice::IOError::ice_clone() const
{
    return new IOError(*this);
}

void
tfs::slice::IOError::ice_throw() const
{
    throw *this;
}

void
tfs::slice::IOError::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::IOError"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::IOError::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::IOError::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::IOError was not generated with stream support";
    throw ex;
}

void
tfs::slice::IOError::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::IOError was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__IOError : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::IOError();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__IOError__Ptr = new __F__tfs__slice__IOError;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::IOError::ice_factory()
{
    return __F__tfs__slice__IOError__Ptr;
}

class __F__tfs__slice__IOError__Init
{
public:

    __F__tfs__slice__IOError__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::IOError", ::tfs::slice::IOError::ice_factory());
    }

    ~__F__tfs__slice__IOError__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::IOError");
    }
};

static __F__tfs__slice__IOError__Init __F__tfs__slice__IOError__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__IOError__initializer() {} }
#endif

tfs::slice::LockFail::LockFail(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__LockFail_name = "tfs::slice::LockFail";

const ::std::string
tfs::slice::LockFail::ice_name() const
{
    return __tfs__slice__LockFail_name;
}

::Ice::Exception*
tfs::slice::LockFail::ice_clone() const
{
    return new LockFail(*this);
}

void
tfs::slice::LockFail::ice_throw() const
{
    throw *this;
}

void
tfs::slice::LockFail::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::LockFail"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::LockFail::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::LockFail::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::LockFail was not generated with stream support";
    throw ex;
}

void
tfs::slice::LockFail::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::LockFail was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__LockFail : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::LockFail();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__LockFail__Ptr = new __F__tfs__slice__LockFail;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::LockFail::ice_factory()
{
    return __F__tfs__slice__LockFail__Ptr;
}

class __F__tfs__slice__LockFail__Init
{
public:

    __F__tfs__slice__LockFail__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::LockFail", ::tfs::slice::LockFail::ice_factory());
    }

    ~__F__tfs__slice__LockFail__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::LockFail");
    }
};

static __F__tfs__slice__LockFail__Init __F__tfs__slice__LockFail__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__LockFail__initializer() {} }
#endif

tfs::slice::OffsetOutOfRange::OffsetOutOfRange(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__OffsetOutOfRange_name = "tfs::slice::OffsetOutOfRange";

const ::std::string
tfs::slice::OffsetOutOfRange::ice_name() const
{
    return __tfs__slice__OffsetOutOfRange_name;
}

::Ice::Exception*
tfs::slice::OffsetOutOfRange::ice_clone() const
{
    return new OffsetOutOfRange(*this);
}

void
tfs::slice::OffsetOutOfRange::ice_throw() const
{
    throw *this;
}

void
tfs::slice::OffsetOutOfRange::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::OffsetOutOfRange"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::OffsetOutOfRange::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::OffsetOutOfRange::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::OffsetOutOfRange was not generated with stream support";
    throw ex;
}

void
tfs::slice::OffsetOutOfRange::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::OffsetOutOfRange was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__OffsetOutOfRange : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::OffsetOutOfRange();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__OffsetOutOfRange__Ptr = new __F__tfs__slice__OffsetOutOfRange;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::OffsetOutOfRange::ice_factory()
{
    return __F__tfs__slice__OffsetOutOfRange__Ptr;
}

class __F__tfs__slice__OffsetOutOfRange__Init
{
public:

    __F__tfs__slice__OffsetOutOfRange__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::OffsetOutOfRange", ::tfs::slice::OffsetOutOfRange::ice_factory());
    }

    ~__F__tfs__slice__OffsetOutOfRange__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::OffsetOutOfRange");
    }
};

static __F__tfs__slice__OffsetOutOfRange__Init __F__tfs__slice__OffsetOutOfRange__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__OffsetOutOfRange__initializer() {} }
#endif

tfs::slice::NoChunkAllocated::NoChunkAllocated(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__NoChunkAllocated_name = "tfs::slice::NoChunkAllocated";

const ::std::string
tfs::slice::NoChunkAllocated::ice_name() const
{
    return __tfs__slice__NoChunkAllocated_name;
}

::Ice::Exception*
tfs::slice::NoChunkAllocated::ice_clone() const
{
    return new NoChunkAllocated(*this);
}

void
tfs::slice::NoChunkAllocated::ice_throw() const
{
    throw *this;
}

void
tfs::slice::NoChunkAllocated::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::NoChunkAllocated"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::NoChunkAllocated::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::NoChunkAllocated::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoChunkAllocated was not generated with stream support";
    throw ex;
}

void
tfs::slice::NoChunkAllocated::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoChunkAllocated was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__NoChunkAllocated : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::NoChunkAllocated();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__NoChunkAllocated__Ptr = new __F__tfs__slice__NoChunkAllocated;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::NoChunkAllocated::ice_factory()
{
    return __F__tfs__slice__NoChunkAllocated__Ptr;
}

class __F__tfs__slice__NoChunkAllocated__Init
{
public:

    __F__tfs__slice__NoChunkAllocated__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::NoChunkAllocated", ::tfs::slice::NoChunkAllocated::ice_factory());
    }

    ~__F__tfs__slice__NoChunkAllocated__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::NoChunkAllocated");
    }
};

static __F__tfs__slice__NoChunkAllocated__Init __F__tfs__slice__NoChunkAllocated__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__NoChunkAllocated__initializer() {} }
#endif

tfs::slice::NoSuchChunk::NoSuchChunk(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__NoSuchChunk_name = "tfs::slice::NoSuchChunk";

const ::std::string
tfs::slice::NoSuchChunk::ice_name() const
{
    return __tfs__slice__NoSuchChunk_name;
}

::Ice::Exception*
tfs::slice::NoSuchChunk::ice_clone() const
{
    return new NoSuchChunk(*this);
}

void
tfs::slice::NoSuchChunk::ice_throw() const
{
    throw *this;
}

void
tfs::slice::NoSuchChunk::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::NoSuchChunk"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::NoSuchChunk::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::NoSuchChunk::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoSuchChunk was not generated with stream support";
    throw ex;
}

void
tfs::slice::NoSuchChunk::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::NoSuchChunk was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__NoSuchChunk : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::NoSuchChunk();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__NoSuchChunk__Ptr = new __F__tfs__slice__NoSuchChunk;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::NoSuchChunk::ice_factory()
{
    return __F__tfs__slice__NoSuchChunk__Ptr;
}

class __F__tfs__slice__NoSuchChunk__Init
{
public:

    __F__tfs__slice__NoSuchChunk__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::NoSuchChunk", ::tfs::slice::NoSuchChunk::ice_factory());
    }

    ~__F__tfs__slice__NoSuchChunk__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::NoSuchChunk");
    }
};

static __F__tfs__slice__NoSuchChunk__Init __F__tfs__slice__NoSuchChunk__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__NoSuchChunk__initializer() {} }
#endif

tfs::slice::FileOrDirAlreadyExists::FileOrDirAlreadyExists(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__FileOrDirAlreadyExists_name = "tfs::slice::FileOrDirAlreadyExists";

const ::std::string
tfs::slice::FileOrDirAlreadyExists::ice_name() const
{
    return __tfs__slice__FileOrDirAlreadyExists_name;
}

::Ice::Exception*
tfs::slice::FileOrDirAlreadyExists::ice_clone() const
{
    return new FileOrDirAlreadyExists(*this);
}

void
tfs::slice::FileOrDirAlreadyExists::ice_throw() const
{
    throw *this;
}

void
tfs::slice::FileOrDirAlreadyExists::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::FileOrDirAlreadyExists"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::FileOrDirAlreadyExists::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::FileOrDirAlreadyExists::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::FileOrDirAlreadyExists was not generated with stream support";
    throw ex;
}

void
tfs::slice::FileOrDirAlreadyExists::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::FileOrDirAlreadyExists was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__FileOrDirAlreadyExists : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::FileOrDirAlreadyExists();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__FileOrDirAlreadyExists__Ptr = new __F__tfs__slice__FileOrDirAlreadyExists;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::FileOrDirAlreadyExists::ice_factory()
{
    return __F__tfs__slice__FileOrDirAlreadyExists__Ptr;
}

class __F__tfs__slice__FileOrDirAlreadyExists__Init
{
public:

    __F__tfs__slice__FileOrDirAlreadyExists__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::FileOrDirAlreadyExists", ::tfs::slice::FileOrDirAlreadyExists::ice_factory());
    }

    ~__F__tfs__slice__FileOrDirAlreadyExists__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::FileOrDirAlreadyExists");
    }
};

static __F__tfs__slice__FileOrDirAlreadyExists__Init __F__tfs__slice__FileOrDirAlreadyExists__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__FileOrDirAlreadyExists__initializer() {} }
#endif

tfs::slice::UnknownChunkServer::UnknownChunkServer(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__UnknownChunkServer_name = "tfs::slice::UnknownChunkServer";

const ::std::string
tfs::slice::UnknownChunkServer::ice_name() const
{
    return __tfs__slice__UnknownChunkServer_name;
}

::Ice::Exception*
tfs::slice::UnknownChunkServer::ice_clone() const
{
    return new UnknownChunkServer(*this);
}

void
tfs::slice::UnknownChunkServer::ice_throw() const
{
    throw *this;
}

void
tfs::slice::UnknownChunkServer::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::UnknownChunkServer"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::UnknownChunkServer::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::UnknownChunkServer::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::UnknownChunkServer was not generated with stream support";
    throw ex;
}

void
tfs::slice::UnknownChunkServer::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::UnknownChunkServer was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__UnknownChunkServer : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::UnknownChunkServer();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__UnknownChunkServer__Ptr = new __F__tfs__slice__UnknownChunkServer;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::UnknownChunkServer::ice_factory()
{
    return __F__tfs__slice__UnknownChunkServer__Ptr;
}

class __F__tfs__slice__UnknownChunkServer__Init
{
public:

    __F__tfs__slice__UnknownChunkServer__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::UnknownChunkServer", ::tfs::slice::UnknownChunkServer::ice_factory());
    }

    ~__F__tfs__slice__UnknownChunkServer__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::UnknownChunkServer");
    }
};

static __F__tfs__slice__UnknownChunkServer__Init __F__tfs__slice__UnknownChunkServer__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__UnknownChunkServer__initializer() {} }
#endif

tfs::slice::ReplicationOutOfRange::ReplicationOutOfRange(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__ReplicationOutOfRange_name = "tfs::slice::ReplicationOutOfRange";

const ::std::string
tfs::slice::ReplicationOutOfRange::ice_name() const
{
    return __tfs__slice__ReplicationOutOfRange_name;
}

::Ice::Exception*
tfs::slice::ReplicationOutOfRange::ice_clone() const
{
    return new ReplicationOutOfRange(*this);
}

void
tfs::slice::ReplicationOutOfRange::ice_throw() const
{
    throw *this;
}

void
tfs::slice::ReplicationOutOfRange::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::ReplicationOutOfRange"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::ReplicationOutOfRange::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::ReplicationOutOfRange::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ReplicationOutOfRange was not generated with stream support";
    throw ex;
}

void
tfs::slice::ReplicationOutOfRange::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ReplicationOutOfRange was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__ReplicationOutOfRange : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::ReplicationOutOfRange();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__ReplicationOutOfRange__Ptr = new __F__tfs__slice__ReplicationOutOfRange;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::ReplicationOutOfRange::ice_factory()
{
    return __F__tfs__slice__ReplicationOutOfRange__Ptr;
}

class __F__tfs__slice__ReplicationOutOfRange__Init
{
public:

    __F__tfs__slice__ReplicationOutOfRange__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::ReplicationOutOfRange", ::tfs::slice::ReplicationOutOfRange::ice_factory());
    }

    ~__F__tfs__slice__ReplicationOutOfRange__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::ReplicationOutOfRange");
    }
};

static __F__tfs__slice__ReplicationOutOfRange__Init __F__tfs__slice__ReplicationOutOfRange__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__ReplicationOutOfRange__initializer() {} }
#endif

tfs::slice::ChunkSizeOutOfRange::ChunkSizeOutOfRange(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__ChunkSizeOutOfRange_name = "tfs::slice::ChunkSizeOutOfRange";

const ::std::string
tfs::slice::ChunkSizeOutOfRange::ice_name() const
{
    return __tfs__slice__ChunkSizeOutOfRange_name;
}

::Ice::Exception*
tfs::slice::ChunkSizeOutOfRange::ice_clone() const
{
    return new ChunkSizeOutOfRange(*this);
}

void
tfs::slice::ChunkSizeOutOfRange::ice_throw() const
{
    throw *this;
}

void
tfs::slice::ChunkSizeOutOfRange::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::ChunkSizeOutOfRange"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::ChunkSizeOutOfRange::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::ChunkSizeOutOfRange::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkSizeOutOfRange was not generated with stream support";
    throw ex;
}

void
tfs::slice::ChunkSizeOutOfRange::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::ChunkSizeOutOfRange was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__ChunkSizeOutOfRange : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::ChunkSizeOutOfRange();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__ChunkSizeOutOfRange__Ptr = new __F__tfs__slice__ChunkSizeOutOfRange;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::ChunkSizeOutOfRange::ice_factory()
{
    return __F__tfs__slice__ChunkSizeOutOfRange__Ptr;
}

class __F__tfs__slice__ChunkSizeOutOfRange__Init
{
public:

    __F__tfs__slice__ChunkSizeOutOfRange__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::ChunkSizeOutOfRange", ::tfs::slice::ChunkSizeOutOfRange::ice_factory());
    }

    ~__F__tfs__slice__ChunkSizeOutOfRange__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::ChunkSizeOutOfRange");
    }
};

static __F__tfs__slice__ChunkSizeOutOfRange__Init __F__tfs__slice__ChunkSizeOutOfRange__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__ChunkSizeOutOfRange__initializer() {} }
#endif

tfs::slice::InvalidFileOrDirName::InvalidFileOrDirName(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__InvalidFileOrDirName_name = "tfs::slice::InvalidFileOrDirName";

const ::std::string
tfs::slice::InvalidFileOrDirName::ice_name() const
{
    return __tfs__slice__InvalidFileOrDirName_name;
}

::Ice::Exception*
tfs::slice::InvalidFileOrDirName::ice_clone() const
{
    return new InvalidFileOrDirName(*this);
}

void
tfs::slice::InvalidFileOrDirName::ice_throw() const
{
    throw *this;
}

void
tfs::slice::InvalidFileOrDirName::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::InvalidFileOrDirName"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::InvalidFileOrDirName::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::InvalidFileOrDirName::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::InvalidFileOrDirName was not generated with stream support";
    throw ex;
}

void
tfs::slice::InvalidFileOrDirName::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::InvalidFileOrDirName was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__InvalidFileOrDirName : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::InvalidFileOrDirName();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__InvalidFileOrDirName__Ptr = new __F__tfs__slice__InvalidFileOrDirName;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::InvalidFileOrDirName::ice_factory()
{
    return __F__tfs__slice__InvalidFileOrDirName__Ptr;
}

class __F__tfs__slice__InvalidFileOrDirName__Init
{
public:

    __F__tfs__slice__InvalidFileOrDirName__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::InvalidFileOrDirName", ::tfs::slice::InvalidFileOrDirName::ice_factory());
    }

    ~__F__tfs__slice__InvalidFileOrDirName__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::InvalidFileOrDirName");
    }
};

static __F__tfs__slice__InvalidFileOrDirName__Init __F__tfs__slice__InvalidFileOrDirName__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__InvalidFileOrDirName__initializer() {} }
#endif

tfs::slice::JournalException::JournalException(const ::std::string& __ice_reason) :
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException(__ice_reason)
#else
    ::tfs::slice::GenericException(__ice_reason)
#endif
{
}

static const char* __tfs__slice__JournalException_name = "tfs::slice::JournalException";

const ::std::string
tfs::slice::JournalException::ice_name() const
{
    return __tfs__slice__JournalException_name;
}

::Ice::Exception*
tfs::slice::JournalException::ice_clone() const
{
    return new JournalException(*this);
}

void
tfs::slice::JournalException::ice_throw() const
{
    throw *this;
}

void
tfs::slice::JournalException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::tfs::slice::JournalException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__write(__os);
#else
    ::tfs::slice::GenericException::__write(__os);
#endif
}

void
tfs::slice::JournalException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
	::std::string myId;
	__is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if (defined(_MSC_VER) && (_MSC_VER < 1300)) // VC++ 6 compiler bug
    GenericException::__read(__is, true);
#else
    ::tfs::slice::GenericException::__read(__is, true);
#endif
}

void
tfs::slice::JournalException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::JournalException was not generated with stream support";
    throw ex;
}

void
tfs::slice::JournalException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception tfs::slice::JournalException was not generated with stream support";
    throw ex;
}

struct __F__tfs__slice__JournalException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
	throw ::tfs::slice::JournalException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__tfs__slice__JournalException__Ptr = new __F__tfs__slice__JournalException;

const ::IceInternal::UserExceptionFactoryPtr&
tfs::slice::JournalException::ice_factory()
{
    return __F__tfs__slice__JournalException__Ptr;
}

class __F__tfs__slice__JournalException__Init
{
public:

    __F__tfs__slice__JournalException__Init()
    {
	::IceInternal::factoryTable->addExceptionFactory("::tfs::slice::JournalException", ::tfs::slice::JournalException::ice_factory());
    }

    ~__F__tfs__slice__JournalException__Init()
    {
	::IceInternal::factoryTable->removeExceptionFactory("::tfs::slice::JournalException");
    }
};

static __F__tfs__slice__JournalException__Init __F__tfs__slice__JournalException__i;

#ifdef __APPLE__
extern "C" { void __F__tfs__slice__JournalException__initializer() {} }
#endif
