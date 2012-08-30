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

#ifndef _____c___ice_3_1_1_AdminService_h__
#define _____c___ice_3_1_1_AdminService_h__

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

class AdminService;
bool operator==(const AdminService&, const AdminService&);
bool operator!=(const AdminService&, const AdminService&);
bool operator<(const AdminService&, const AdminService&);
bool operator<=(const AdminService&, const AdminService&);
bool operator>(const AdminService&, const AdminService&);
bool operator>=(const AdminService&, const AdminService&);

}

}

}

namespace tfs
{

namespace slice
{

class AdminService;
bool operator==(const AdminService&, const AdminService&);
bool operator!=(const AdminService&, const AdminService&);
bool operator<(const AdminService&, const AdminService&);
bool operator<=(const AdminService&, const AdminService&);
bool operator>(const AdminService&, const AdminService&);
bool operator>=(const AdminService&, const AdminService&);

}

}

namespace IceInternal
{

void incRef(::tfs::slice::AdminService*);
void decRef(::tfs::slice::AdminService*);

void incRef(::IceProxy::tfs::slice::AdminService*);
void decRef(::IceProxy::tfs::slice::AdminService*);

}

namespace tfs
{

namespace slice
{

typedef ::IceInternal::Handle< ::tfs::slice::AdminService> AdminServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::tfs::slice::AdminService> AdminServicePrx;

void __write(::IceInternal::BasicStream*, const AdminServicePrx&);
void __read(::IceInternal::BasicStream*, AdminServicePrx&);
void __write(::IceInternal::BasicStream*, const AdminServicePtr&);
void __patch__AdminServicePtr(void*, ::Ice::ObjectPtr&);

}

}

namespace tfs
{

namespace slice
{

typedef ::std::vector< ::Ice::Int> OperationsCount;

class __U__OperationsCount { };

}

}

namespace IceProxy
{

namespace tfs
{

namespace slice
{

class AdminService : virtual public ::IceProxy::Ice::Object
{
public:

    ::std::string getStartTime()
    {
	return getStartTime(__defaultContext());
    }
    ::std::string getStartTime(const ::Ice::Context&);

    ::tfs::slice::Addresses getChunkServers()
    {
	return getChunkServers(__defaultContext());
    }
    ::tfs::slice::Addresses getChunkServers(const ::Ice::Context&);

    ::tfs::slice::Addresses getClients()
    {
	return getClients(__defaultContext());
    }
    ::tfs::slice::Addresses getClients(const ::Ice::Context&);

    ::tfs::slice::OperationsCount getOperationsCount()
    {
	return getOperationsCount(__defaultContext());
    }
    ::tfs::slice::OperationsCount getOperationsCount(const ::Ice::Context&);
    
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

class AdminService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::std::string getStartTime(const ::Ice::Context&) = 0;

    virtual ::tfs::slice::Addresses getChunkServers(const ::Ice::Context&) = 0;

    virtual ::tfs::slice::Addresses getClients(const ::Ice::Context&) = 0;

    virtual ::tfs::slice::OperationsCount getOperationsCount(const ::Ice::Context&) = 0;
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

class AdminService : virtual public ::IceDelegate::tfs::slice::AdminService,
		     virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::std::string getStartTime(const ::Ice::Context&);

    virtual ::tfs::slice::Addresses getChunkServers(const ::Ice::Context&);

    virtual ::tfs::slice::Addresses getClients(const ::Ice::Context&);

    virtual ::tfs::slice::OperationsCount getOperationsCount(const ::Ice::Context&);
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

class AdminService : virtual public ::IceDelegate::tfs::slice::AdminService,
		     virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::std::string getStartTime(const ::Ice::Context&);

    virtual ::tfs::slice::Addresses getChunkServers(const ::Ice::Context&);

    virtual ::tfs::slice::Addresses getClients(const ::Ice::Context&);

    virtual ::tfs::slice::OperationsCount getOperationsCount(const ::Ice::Context&);
};

}

}

}

namespace tfs
{

namespace slice
{

class AdminService : virtual public ::Ice::Object
{
public:

    typedef AdminServicePrx ProxyType;
    typedef AdminServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::std::string getStartTime(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getStartTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::Addresses getChunkServers(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getChunkServers(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::Addresses getClients(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getClients(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::OperationsCount getOperationsCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getOperationsCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__AdminServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
