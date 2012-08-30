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

#ifndef __Transfer_h__
#define __Transfer_h__

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
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
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

namespace tfs
{

namespace slice
{

class Transfer;
bool operator==(const Transfer&, const Transfer&);
bool operator!=(const Transfer&, const Transfer&);
bool operator<(const Transfer&, const Transfer&);
bool operator<=(const Transfer&, const Transfer&);
bool operator>(const Transfer&, const Transfer&);
bool operator>=(const Transfer&, const Transfer&);

}

}

}

namespace tfs
{

namespace slice
{

class Transfer;
bool operator==(const Transfer&, const Transfer&);
bool operator!=(const Transfer&, const Transfer&);
bool operator<(const Transfer&, const Transfer&);
bool operator<=(const Transfer&, const Transfer&);
bool operator>(const Transfer&, const Transfer&);
bool operator>=(const Transfer&, const Transfer&);

}

}

namespace IceInternal
{

void incRef(::tfs::slice::Transfer*);
void decRef(::tfs::slice::Transfer*);

void incRef(::IceProxy::tfs::slice::Transfer*);
void decRef(::IceProxy::tfs::slice::Transfer*);

}

namespace tfs
{

namespace slice
{

typedef ::IceInternal::Handle< ::tfs::slice::Transfer> TransferPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::tfs::slice::Transfer> TransferPrx;

void __write(::IceInternal::BasicStream*, const TransferPrx&);
void __read(::IceInternal::BasicStream*, TransferPrx&);
void __write(::IceInternal::BasicStream*, const TransferPtr&);
void __patch__TransferPtr(void*, ::Ice::ObjectPtr&);

}

}

namespace tfs
{

namespace slice
{

class ErrorBase : public ::Ice::UserException
{
public:

    ErrorBase() {}
    explicit ErrorBase(const ::std::string&);

    virtual const ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string reason;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static ErrorBase __ErrorBase_init;

class DataError : public ::tfs::slice::ErrorBase
{
public:

    DataError() {}
    explicit DataError(const ::std::string&);

    virtual const ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ChunkError : public ::tfs::slice::ErrorBase
{
public:

    ChunkError() {}
    explicit ChunkError(const ::std::string&);

    virtual const ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ChunkNotExist : public ::tfs::slice::ErrorBase
{
public:

    ChunkNotExist() {}
    explicit ChunkNotExist(const ::std::string&);

    virtual const ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

typedef ::std::vector< ::Ice::Byte> ByteSeq;

class __U__ByteSeq { };

}

}

namespace IceProxy
{

namespace tfs
{

namespace slice
{

class Transfer : virtual public ::IceProxy::Ice::Object
{
public:

    ::tfs::slice::ByteSeq read(::Ice::Long chunkid, ::Ice::Int offset, ::Ice::Int len)
    {
	return read(chunkid, offset, len, __defaultContext());
    }
    ::tfs::slice::ByteSeq read(::Ice::Long, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    ::Ice::Int write(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int offset, ::Ice::Int len)
    {
	return write(chunkid, bytes, offset, len, __defaultContext());
    }
    ::Ice::Int write(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    void addChunk(::Ice::Long chunkid)
    {
	addChunk(chunkid, __defaultContext());
    }
    void addChunk(::Ice::Long, const ::Ice::Context&);

    ::Ice::Int append(::Ice::Long chunkid, const ::tfs::slice::ByteSeq& bytes, ::Ice::Int len)
    {
	return append(chunkid, bytes, len, __defaultContext());
    }
    ::Ice::Int append(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, const ::Ice::Context&);

    void rollback(::Ice::Long opid)
    {
	rollback(opid, __defaultContext());
    }
    void rollback(::Ice::Long, const ::Ice::Context&);

    ::std::string getLocalPath(::Ice::Long chunkid)
    {
	return getLocalPath(chunkid, __defaultContext());
    }
    ::std::string getLocalPath(::Ice::Long, const ::Ice::Context&);
    
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

namespace tfs
{

namespace slice
{

class Transfer : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::tfs::slice::ByteSeq read(::Ice::Long, ::Ice::Int, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int write(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual void addChunk(::Ice::Long, const ::Ice::Context&) = 0;

    virtual ::Ice::Int append(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual void rollback(::Ice::Long, const ::Ice::Context&) = 0;

    virtual ::std::string getLocalPath(::Ice::Long, const ::Ice::Context&) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace tfs
{

namespace slice
{

class Transfer : virtual public ::IceDelegate::tfs::slice::Transfer,
		 virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::tfs::slice::ByteSeq read(::Ice::Long, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int write(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual void addChunk(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int append(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, const ::Ice::Context&);

    virtual void rollback(::Ice::Long, const ::Ice::Context&);

    virtual ::std::string getLocalPath(::Ice::Long, const ::Ice::Context&);
};

}

}

}

namespace IceDelegateD
{

namespace tfs
{

namespace slice
{

class Transfer : virtual public ::IceDelegate::tfs::slice::Transfer,
		 virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::tfs::slice::ByteSeq read(::Ice::Long, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int write(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual void addChunk(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int append(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, const ::Ice::Context&);

    virtual void rollback(::Ice::Long, const ::Ice::Context&);

    virtual ::std::string getLocalPath(::Ice::Long, const ::Ice::Context&);
};

}

}

}

namespace tfs
{

namespace slice
{

class Transfer : virtual public ::Ice::Object
{
public:

    typedef TransferPrx ProxyType;
    typedef TransferPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::tfs::slice::ByteSeq read(::Ice::Long, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___read(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int write(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___write(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void addChunk(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___addChunk(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int append(::Ice::Long, const ::tfs::slice::ByteSeq&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___append(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void rollback(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___rollback(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string getLocalPath(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getLocalPath(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__TransferPtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
