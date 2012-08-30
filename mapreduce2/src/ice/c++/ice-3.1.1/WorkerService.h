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

#ifndef _____c___ice_3_1_1_WorkerService_h__
#define _____c___ice_3_1_1_WorkerService_h__

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

namespace mapreduce
{

namespace slice
{

class WorkerService;
bool operator==(const WorkerService&, const WorkerService&);
bool operator!=(const WorkerService&, const WorkerService&);
bool operator<(const WorkerService&, const WorkerService&);
bool operator<=(const WorkerService&, const WorkerService&);
bool operator>(const WorkerService&, const WorkerService&);
bool operator>=(const WorkerService&, const WorkerService&);

}

}

}

namespace mapreduce
{

namespace slice
{

class WorkerService;
bool operator==(const WorkerService&, const WorkerService&);
bool operator!=(const WorkerService&, const WorkerService&);
bool operator<(const WorkerService&, const WorkerService&);
bool operator<=(const WorkerService&, const WorkerService&);
bool operator>(const WorkerService&, const WorkerService&);
bool operator>=(const WorkerService&, const WorkerService&);

}

}

namespace IceInternal
{

void incRef(::mapreduce::slice::WorkerService*);
void decRef(::mapreduce::slice::WorkerService*);

void incRef(::IceProxy::mapreduce::slice::WorkerService*);
void decRef(::IceProxy::mapreduce::slice::WorkerService*);

}

namespace mapreduce
{

namespace slice
{

typedef ::IceInternal::Handle< ::mapreduce::slice::WorkerService> WorkerServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::mapreduce::slice::WorkerService> WorkerServicePrx;

void __write(::IceInternal::BasicStream*, const WorkerServicePrx&);
void __read(::IceInternal::BasicStream*, WorkerServicePrx&);
void __write(::IceInternal::BasicStream*, const WorkerServicePtr&);
void __patch__WorkerServicePtr(void*, ::Ice::ObjectPtr&);

}

}

namespace mapreduce
{

namespace slice
{

}

}

namespace IceProxy
{

namespace mapreduce
{

namespace slice
{

class WorkerService : virtual public ::IceProxy::Ice::Object
{
public:

    ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address& workerAddress, const ::mapreduce::slice::Heartbeat& info)
    {
	return sendHeartbeat(workerAddress, info, __defaultContext());
    }
    ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address&, const ::mapreduce::slice::Heartbeat&, const ::Ice::Context&);

    void completeTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskID)
    {
	completeTask(workerAddress, taskID, __defaultContext());
    }
    void completeTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);

    void abandonTask(const ::mapreduce::slice::Address& workerAddress, ::Ice::Int taskId)
    {
	abandonTask(workerAddress, taskId, __defaultContext());
    }
    void abandonTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);
    
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

namespace mapreduce
{

namespace slice
{

class WorkerService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address&, const ::mapreduce::slice::Heartbeat&, const ::Ice::Context&) = 0;

    virtual void completeTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual void abandonTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace mapreduce
{

namespace slice
{

class WorkerService : virtual public ::IceDelegate::mapreduce::slice::WorkerService,
		      virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address&, const ::mapreduce::slice::Heartbeat&, const ::Ice::Context&);

    virtual void completeTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);

    virtual void abandonTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);
};

}

}

}

namespace IceDelegateD
{

namespace mapreduce
{

namespace slice
{

class WorkerService : virtual public ::IceDelegate::mapreduce::slice::WorkerService,
		      virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address&, const ::mapreduce::slice::Heartbeat&, const ::Ice::Context&);

    virtual void completeTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);

    virtual void abandonTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Context&);
};

}

}

}

namespace mapreduce
{

namespace slice
{

class WorkerService : virtual public ::Ice::Object
{
public:

    typedef WorkerServicePrx ProxyType;
    typedef WorkerServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::mapreduce::slice::MasterCommands sendHeartbeat(const ::mapreduce::slice::Address&, const ::mapreduce::slice::Heartbeat&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___sendHeartbeat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void completeTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___completeTask(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void abandonTask(const ::mapreduce::slice::Address&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___abandonTask(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__WorkerServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
