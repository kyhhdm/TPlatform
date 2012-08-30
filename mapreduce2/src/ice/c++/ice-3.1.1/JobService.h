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

#ifndef _____c___ice_3_1_1_JobService_h__
#define _____c___ice_3_1_1_JobService_h__

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
#include <MapReduceJob.h>
#include <JobDetail.h>
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

class JobService;
bool operator==(const JobService&, const JobService&);
bool operator!=(const JobService&, const JobService&);
bool operator<(const JobService&, const JobService&);
bool operator<=(const JobService&, const JobService&);
bool operator>(const JobService&, const JobService&);
bool operator>=(const JobService&, const JobService&);

}

}

}

namespace mapreduce
{

namespace slice
{

class JobService;
bool operator==(const JobService&, const JobService&);
bool operator!=(const JobService&, const JobService&);
bool operator<(const JobService&, const JobService&);
bool operator<=(const JobService&, const JobService&);
bool operator>(const JobService&, const JobService&);
bool operator>=(const JobService&, const JobService&);

}

}

namespace IceInternal
{

void incRef(::mapreduce::slice::JobService*);
void decRef(::mapreduce::slice::JobService*);

void incRef(::IceProxy::mapreduce::slice::JobService*);
void decRef(::IceProxy::mapreduce::slice::JobService*);

}

namespace mapreduce
{

namespace slice
{

typedef ::IceInternal::Handle< ::mapreduce::slice::JobService> JobServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::mapreduce::slice::JobService> JobServicePrx;

void __write(::IceInternal::BasicStream*, const JobServicePrx&);
void __read(::IceInternal::BasicStream*, JobServicePrx&);
void __write(::IceInternal::BasicStream*, const JobServicePtr&);
void __patch__JobServicePtr(void*, ::Ice::ObjectPtr&);

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

class JobService : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int create(const ::mapreduce::slice::MapReduceJob& job)
    {
	return create(job, __defaultContext());
    }
    ::Ice::Int create(const ::mapreduce::slice::MapReduceJob&, const ::Ice::Context&);

    ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int jobId)
    {
	return getJobDetail(jobId, __defaultContext());
    }
    ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int kill(::Ice::Int jobId)
    {
	return kill(jobId, __defaultContext());
    }
    ::Ice::Int kill(::Ice::Int, const ::Ice::Context&);
    
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

class JobService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int create(const ::mapreduce::slice::MapReduceJob&, const ::Ice::Context&) = 0;

    virtual ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int kill(::Ice::Int, const ::Ice::Context&) = 0;
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

class JobService : virtual public ::IceDelegate::mapreduce::slice::JobService,
		   virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int create(const ::mapreduce::slice::MapReduceJob&, const ::Ice::Context&);

    virtual ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int kill(::Ice::Int, const ::Ice::Context&);
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

class JobService : virtual public ::IceDelegate::mapreduce::slice::JobService,
		   virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int create(const ::mapreduce::slice::MapReduceJob&, const ::Ice::Context&);

    virtual ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int kill(::Ice::Int, const ::Ice::Context&);
};

}

}

}

namespace mapreduce
{

namespace slice
{

class JobService : virtual public ::Ice::Object
{
public:

    typedef JobServicePrx ProxyType;
    typedef JobServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int create(const ::mapreduce::slice::MapReduceJob&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___create(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::mapreduce::slice::JobDetail getJobDetail(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getJobDetail(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int kill(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___kill(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__JobServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
