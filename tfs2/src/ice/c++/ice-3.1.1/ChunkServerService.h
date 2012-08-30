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

#ifndef _____c___ice_3_1_1_ChunkServerService_h__
#define _____c___ice_3_1_1_ChunkServerService_h__

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
#include <Exceptions.h>
#include <MasterCommand.h>
#include <Heartbeat.h>
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

class ChunkServerService;
bool operator==(const ChunkServerService&, const ChunkServerService&);
bool operator!=(const ChunkServerService&, const ChunkServerService&);
bool operator<(const ChunkServerService&, const ChunkServerService&);
bool operator<=(const ChunkServerService&, const ChunkServerService&);
bool operator>(const ChunkServerService&, const ChunkServerService&);
bool operator>=(const ChunkServerService&, const ChunkServerService&);

}

}

}

namespace tfs
{

namespace slice
{

class ChunkServerService;
bool operator==(const ChunkServerService&, const ChunkServerService&);
bool operator!=(const ChunkServerService&, const ChunkServerService&);
bool operator<(const ChunkServerService&, const ChunkServerService&);
bool operator<=(const ChunkServerService&, const ChunkServerService&);
bool operator>(const ChunkServerService&, const ChunkServerService&);
bool operator>=(const ChunkServerService&, const ChunkServerService&);

}

}

namespace IceInternal
{

void incRef(::tfs::slice::ChunkServerService*);
void decRef(::tfs::slice::ChunkServerService*);

void incRef(::IceProxy::tfs::slice::ChunkServerService*);
void decRef(::IceProxy::tfs::slice::ChunkServerService*);

}

namespace tfs
{

namespace slice
{

typedef ::IceInternal::Handle< ::tfs::slice::ChunkServerService> ChunkServerServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::tfs::slice::ChunkServerService> ChunkServerServicePrx;

void __write(::IceInternal::BasicStream*, const ChunkServerServicePrx&);
void __read(::IceInternal::BasicStream*, ChunkServerServicePrx&);
void __write(::IceInternal::BasicStream*, const ChunkServerServicePtr&);
void __patch__ChunkServerServicePtr(void*, ::Ice::ObjectPtr&);

}

}

namespace tfs
{

namespace slice
{

}

}

namespace IceProxy
{

namespace tfs
{

namespace slice
{

class ChunkServerService : virtual public ::IceProxy::Ice::Object
{
public:

    void enroll(const ::tfs::slice::Address& chunkServerAddress)
    {
	enroll(chunkServerAddress, __defaultContext());
    }
    void enroll(const ::tfs::slice::Address&, const ::Ice::Context&);

    ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Heartbeat& info)
    {
	return sendHeartbeat(chunkServerAddress, info, __defaultContext());
    }
    ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address&, const ::tfs::slice::Heartbeat&, const ::Ice::Context&);

    void chunkReport(const ::tfs::slice::Address& chunkServerAddress, const ::tfs::slice::Chunks& chks)
    {
	chunkReport(chunkServerAddress, chks, __defaultContext());
    }
    void chunkReport(const ::tfs::slice::Address&, const ::tfs::slice::Chunks&, const ::Ice::Context&);

    void completeMigrateChunk(const ::tfs::slice::LocatedChunk& lchk)
    {
	completeMigrateChunk(lchk, __defaultContext());
    }
    void completeMigrateChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);
    
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

class ChunkServerService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void enroll(const ::tfs::slice::Address&, const ::Ice::Context&) = 0;

    virtual ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address&, const ::tfs::slice::Heartbeat&, const ::Ice::Context&) = 0;

    virtual void chunkReport(const ::tfs::slice::Address&, const ::tfs::slice::Chunks&, const ::Ice::Context&) = 0;

    virtual void completeMigrateChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&) = 0;
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

class ChunkServerService : virtual public ::IceDelegate::tfs::slice::ChunkServerService,
			   virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void enroll(const ::tfs::slice::Address&, const ::Ice::Context&);

    virtual ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address&, const ::tfs::slice::Heartbeat&, const ::Ice::Context&);

    virtual void chunkReport(const ::tfs::slice::Address&, const ::tfs::slice::Chunks&, const ::Ice::Context&);

    virtual void completeMigrateChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);
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

class ChunkServerService : virtual public ::IceDelegate::tfs::slice::ChunkServerService,
			   virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void enroll(const ::tfs::slice::Address&, const ::Ice::Context&);

    virtual ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address&, const ::tfs::slice::Heartbeat&, const ::Ice::Context&);

    virtual void chunkReport(const ::tfs::slice::Address&, const ::tfs::slice::Chunks&, const ::Ice::Context&);

    virtual void completeMigrateChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);
};

}

}

}

namespace tfs
{

namespace slice
{

class ChunkServerService : virtual public ::Ice::Object
{
public:

    typedef ChunkServerServicePrx ProxyType;
    typedef ChunkServerServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void enroll(const ::tfs::slice::Address&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___enroll(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::MasterCommand sendHeartbeat(const ::tfs::slice::Address&, const ::tfs::slice::Heartbeat&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___sendHeartbeat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void chunkReport(const ::tfs::slice::Address&, const ::tfs::slice::Chunks&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___chunkReport(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void completeMigrateChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___completeMigrateChunk(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ChunkServerServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
