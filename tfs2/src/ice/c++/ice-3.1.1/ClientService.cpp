// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `ClientService.ice'

#include <ClientService.h>
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

static const ::std::string __tfs__slice__ClientService__open_name = "open";

static const ::std::string __tfs__slice__ClientService__close_name = "close";

static const ::std::string __tfs__slice__ClientService__getChunksInfo_name = "getChunksInfo";

static const ::std::string __tfs__slice__ClientService__completeWrittenChunk_name = "completeWrittenChunk";

static const ::std::string __tfs__slice__ClientService__updateChunkInfo_name = "updateChunkInfo";

static const ::std::string __tfs__slice__ClientService__addChunk_name = "addChunk";

static const ::std::string __tfs__slice__ClientService__abandonAddChunk_name = "abandonAddChunk";

static const ::std::string __tfs__slice__ClientService__reportBadChunks_name = "reportBadChunks";

static const ::std::string __tfs__slice__ClientService__setReplication_name = "setReplication";

static const ::std::string __tfs__slice__ClientService__getFileInfo_name = "getFileInfo";

static const ::std::string __tfs__slice__ClientService__create_name = "create";

static const ::std::string __tfs__slice__ClientService__rename_name = "rename";

static const ::std::string __tfs__slice__ClientService__remove_name = "remove";

static const ::std::string __tfs__slice__ClientService__mkdir_name = "mkdir";

static const ::std::string __tfs__slice__ClientService__renamedir_name = "renamedir";

static const ::std::string __tfs__slice__ClientService__rmdir_name = "rmdir";

static const ::std::string __tfs__slice__ClientService__lsdir_name = "lsdir";

static const ::std::string __tfs__slice__ClientService__concatFiles_name = "concatFiles";

static const ::std::string __tfs__slice__ClientService__reportHeartbeat_name = "reportHeartbeat";

void
IceInternal::incRef(::tfs::slice::ClientService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::tfs::slice::ClientService* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::tfs::slice::ClientService* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::tfs::slice::ClientService* p)
{
    p->__decRef();
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::ClientServicePrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::ClientServicePrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
	v = 0;
    }
    else
    {
	v = new ::IceProxy::tfs::slice::ClientService;
	v->__copyFrom(proxy);
    }
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, const ::tfs::slice::ClientServicePtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
tfs::slice::__write(::IceInternal::BasicStream* __os, ::tfs::slice::FileOpenMode v)
{
    __os->write(static_cast< ::Ice::Byte>(v));
}

void
tfs::slice::__read(::IceInternal::BasicStream* __is, ::tfs::slice::FileOpenMode& v)
{
    ::Ice::Byte val;
    __is->read(val);
    v = static_cast< ::tfs::slice::FileOpenMode>(val);
}

void
IceProxy::tfs::slice::ClientService::open(const ::tfs::slice::Address& client, const ::std::string& filename, ::Ice::Int mode, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__open_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->open(client, filename, mode, __ctx);
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
IceProxy::tfs::slice::ClientService::close(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->close(client, filename, __ctx);
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

::tfs::slice::LocatedChunks
IceProxy::tfs::slice::ClientService::getChunksInfo(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__getChunksInfo_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    return __del->getChunksInfo(client, filename, __ctx);
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
IceProxy::tfs::slice::ClientService::completeWrittenChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__completeWrittenChunk_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->completeWrittenChunk(lchk, __ctx);
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
IceProxy::tfs::slice::ClientService::updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__updateChunkInfo_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->updateChunkInfo(lchk, __ctx);
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

::tfs::slice::LocatedChunk
IceProxy::tfs::slice::ClientService::addChunk(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__addChunk_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    return __del->addChunk(client, filename, __ctx);
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
IceProxy::tfs::slice::ClientService::abandonAddChunk(const ::tfs::slice::Chunk& chk, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__abandonAddChunk_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->abandonAddChunk(chk, __ctx);
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
IceProxy::tfs::slice::ClientService::reportBadChunks(const ::tfs::slice::LocatedChunks& chunks, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->reportBadChunks(chunks, __ctx);
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
IceProxy::tfs::slice::ClientService::setReplication(const ::std::string& filename, ::Ice::Short replication, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__setReplication_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->setReplication(filename, replication, __ctx);
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

::tfs::slice::FileInfo
IceProxy::tfs::slice::ClientService::getFileInfo(const ::std::string& filename, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__getFileInfo_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    return __del->getFileInfo(filename, __ctx);
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
IceProxy::tfs::slice::ClientService::create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__create_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->create(filename, replication, chunkSize, __ctx);
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
IceProxy::tfs::slice::ClientService::rename(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__rename_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->rename(src, dst, __ctx);
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
IceProxy::tfs::slice::ClientService::remove(const ::std::string& src, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__remove_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->remove(src, __ctx);
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
IceProxy::tfs::slice::ClientService::mkdir(const ::std::string& src, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__mkdir_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->mkdir(src, __ctx);
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
IceProxy::tfs::slice::ClientService::renamedir(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__renamedir_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->renamedir(src, dst, __ctx);
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
IceProxy::tfs::slice::ClientService::rmdir(const ::std::string& src, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__rmdir_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->rmdir(src, __ctx);
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

::tfs::slice::FilesInfo
IceProxy::tfs::slice::ClientService::lsdir(const ::std::string& src, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__lsdir_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    return __del->lsdir(src, __ctx);
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
IceProxy::tfs::slice::ClientService::concatFiles(const ::tfs::slice::Strings& srcFiles, const ::std::string& dst, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    __checkTwowayOnly(__tfs__slice__ClientService__concatFiles_name);
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->concatFiles(srcFiles, dst, __ctx);
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
IceProxy::tfs::slice::ClientService::reportHeartbeat(const ::tfs::slice::Address& clientAddress, const ::Ice::Context& __ctx)
{
    int __cnt = 0;
    while(true)
    {
	try
	{
	    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase = __getDelegate();
	    ::IceDelegate::tfs::slice::ClientService* __del = dynamic_cast< ::IceDelegate::tfs::slice::ClientService*>(__delBase.get());
	    __del->reportHeartbeat(clientAddress, __ctx);
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
IceProxy::tfs::slice::ClientService::ice_staticId()
{
    return ::tfs::slice::ClientService::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::tfs::slice::ClientService::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::tfs::slice::ClientService);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::tfs::slice::ClientService::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::tfs::slice::ClientService);
}

bool
IceProxy::tfs::slice::operator==(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator!=(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::tfs::slice::operator<=(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return l < r || l == r;
}

bool
IceProxy::tfs::slice::operator>(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::tfs::slice::operator>=(const ::IceProxy::tfs::slice::ClientService& l, const ::IceProxy::tfs::slice::ClientService& r)
{
    return !(l < r);
}

void
IceDelegateM::tfs::slice::ClientService::open(const ::tfs::slice::Address& client, const ::std::string& filename, ::Ice::Int mode, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__open_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	client.__write(__os);
	__os->write(filename);
	__os->write(mode);
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
	    catch(const ::tfs::slice::LockFail&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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
IceDelegateM::tfs::slice::ClientService::close(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__close_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	client.__write(__os);
	__os->write(filename);
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

::tfs::slice::LocatedChunks
IceDelegateM::tfs::slice::ClientService::getChunksInfo(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__getChunksInfo_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	client.__write(__os);
	__os->write(filename);
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
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::LocatedChunks __ret;
	::tfs::slice::__read(__is, __ret, ::tfs::slice::__U__LocatedChunks());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::tfs::slice::ClientService::completeWrittenChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__completeWrittenChunk_name, ::Ice::Normal, __context, __compress);
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
IceDelegateM::tfs::slice::ClientService::updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__updateChunkInfo_name, ::Ice::Normal, __context, __compress);
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

::tfs::slice::LocatedChunk
IceDelegateM::tfs::slice::ClientService::addChunk(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__addChunk_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	client.__write(__os);
	__os->write(filename);
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
	    catch(const ::tfs::slice::NoChunkAllocated&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::LocatedChunk __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::tfs::slice::ClientService::abandonAddChunk(const ::tfs::slice::Chunk& chk, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__abandonAddChunk_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	chk.__write(__os);
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
	    catch(const ::tfs::slice::NoChunkAllocated&)
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
IceDelegateM::tfs::slice::ClientService::reportBadChunks(const ::tfs::slice::LocatedChunks& chunks, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__reportBadChunks_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	if(chunks.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    ::tfs::slice::__write(__os, &chunks[0], &chunks[0] + chunks.size(), ::tfs::slice::__U__LocatedChunks());
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
IceDelegateM::tfs::slice::ClientService::setReplication(const ::std::string& filename, ::Ice::Short replication, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__setReplication_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(filename);
	__os->write(replication);
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
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::ReplicationOutOfRange&)
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

::tfs::slice::FileInfo
IceDelegateM::tfs::slice::ClientService::getFileInfo(const ::std::string& filename, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__getFileInfo_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(filename);
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
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::FileInfo __ret;
	__ret.__read(__is);
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::tfs::slice::ClientService::create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__create_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(filename);
	__os->write(replication);
	__os->write(chunkSize);
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
	    catch(const ::tfs::slice::ChunkSizeOutOfRange&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::FileOrDirAlreadyExists&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::ReplicationOutOfRange&)
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
IceDelegateM::tfs::slice::ClientService::rename(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__rename_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
	__os->write(dst);
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
	    catch(const ::tfs::slice::FileOrDirAlreadyExists&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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
IceDelegateM::tfs::slice::ClientService::remove(const ::std::string& src, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__remove_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
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
	    catch(const ::tfs::slice::LockFail&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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
IceDelegateM::tfs::slice::ClientService::mkdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__mkdir_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
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
	    catch(const ::tfs::slice::FileOrDirAlreadyExists&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
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
IceDelegateM::tfs::slice::ClientService::renamedir(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__renamedir_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
	__os->write(dst);
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
	    catch(const ::tfs::slice::FileOrDirAlreadyExists&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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
IceDelegateM::tfs::slice::ClientService::rmdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__rmdir_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
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
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::LockFail&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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

::tfs::slice::FilesInfo
IceDelegateM::tfs::slice::ClientService::lsdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__lsdir_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	__os->write(src);
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
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
	    {
		throw;
	    }
	    catch(const ::Ice::UserException& __ex)
	    {
		throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
	    }
	}
	::tfs::slice::FilesInfo __ret;
	::tfs::slice::__read(__is, __ret, ::tfs::slice::__U__FilesInfo());
	return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
	throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::tfs::slice::ClientService::concatFiles(const ::tfs::slice::Strings& srcFiles, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__concatFiles_name, ::Ice::Normal, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	if(srcFiles.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    __os->write(&srcFiles[0], &srcFiles[0] + srcFiles.size());
	}
	__os->write(dst);
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
	    catch(const ::tfs::slice::FileOrDirAlreadyExists&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::InvalidFileOrDirName&)
	    {
		throw;
	    }
	    catch(const ::tfs::slice::NoSuchFileOrDir&)
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
IceDelegateM::tfs::slice::ClientService::reportHeartbeat(const ::tfs::slice::Address& clientAddress, const ::Ice::Context& __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __tfs__slice__ClientService__reportHeartbeat_name, ::Ice::Idempotent, __context, __compress);
    try
    {
	::IceInternal::BasicStream* __os = __og.os();
	clientAddress.__write(__os);
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
IceDelegateD::tfs::slice::ClientService::open(const ::tfs::slice::Address& client, const ::std::string& filename, ::Ice::Int mode, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__open_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->open(client, filename, mode, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::close(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__close_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->close(client, filename, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::LocatedChunks
IceDelegateD::tfs::slice::ClientService::getChunksInfo(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__getChunksInfo_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    return __servant->getChunksInfo(client, filename, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::completeWrittenChunk(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__completeWrittenChunk_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->completeWrittenChunk(lchk, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__updateChunkInfo_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->updateChunkInfo(lchk, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::LocatedChunk
IceDelegateD::tfs::slice::ClientService::addChunk(const ::tfs::slice::Address& client, const ::std::string& filename, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__addChunk_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    return __servant->addChunk(client, filename, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::abandonAddChunk(const ::tfs::slice::Chunk& chk, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__abandonAddChunk_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->abandonAddChunk(chk, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::reportBadChunks(const ::tfs::slice::LocatedChunks& chunks, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__reportBadChunks_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->reportBadChunks(chunks, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::setReplication(const ::std::string& filename, ::Ice::Short replication, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__setReplication_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->setReplication(filename, replication, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::FileInfo
IceDelegateD::tfs::slice::ClientService::getFileInfo(const ::std::string& filename, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__getFileInfo_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    return __servant->getFileInfo(filename, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__create_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->create(filename, replication, chunkSize, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::rename(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__rename_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->rename(src, dst, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::remove(const ::std::string& src, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__remove_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->remove(src, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::mkdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__mkdir_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->mkdir(src, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::renamedir(const ::std::string& src, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__renamedir_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->renamedir(src, dst, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::rmdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__rmdir_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->rmdir(src, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::tfs::slice::FilesInfo
IceDelegateD::tfs::slice::ClientService::lsdir(const ::std::string& src, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__lsdir_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    return __servant->lsdir(src, __current);
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::concatFiles(const ::tfs::slice::Strings& srcFiles, const ::std::string& dst, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__concatFiles_name, ::Ice::Normal, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->concatFiles(srcFiles, dst, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

void
IceDelegateD::tfs::slice::ClientService::reportHeartbeat(const ::tfs::slice::Address& clientAddress, const ::Ice::Context& __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __tfs__slice__ClientService__reportHeartbeat_name, ::Ice::Idempotent, __context);
    while(true)
    {
	::IceInternal::Direct __direct(__current);
	::tfs::slice::ClientService* __servant = dynamic_cast< ::tfs::slice::ClientService*>(__direct.servant().get());
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
	    __servant->reportHeartbeat(clientAddress, __current);
	    return;
	}
	catch(const ::Ice::LocalException& __ex)
	{
	    throw ::IceInternal::LocalExceptionWrapper(__ex, false);
	}
    }
}

::Ice::ObjectPtr
tfs::slice::ClientService::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __tfs__slice__ClientService_ids[2] =
{
    "::Ice::Object",
    "::tfs::slice::ClientService"
};

bool
tfs::slice::ClientService::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__tfs__slice__ClientService_ids, __tfs__slice__ClientService_ids + 2, _s);
}

::std::vector< ::std::string>
tfs::slice::ClientService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__tfs__slice__ClientService_ids[0], &__tfs__slice__ClientService_ids[2]);
}

const ::std::string&
tfs::slice::ClientService::ice_id(const ::Ice::Current&) const
{
    return __tfs__slice__ClientService_ids[1];
}

const ::std::string&
tfs::slice::ClientService::ice_staticId()
{
    return __tfs__slice__ClientService_ids[1];
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___open(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Address client;
    ::std::string filename;
    ::Ice::Int mode;
    client.__read(__is);
    __is->read(filename);
    __is->read(mode);
    try
    {
	open(client, filename, mode, __current);
    }
    catch(const ::tfs::slice::LockFail& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___close(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::tfs::slice::Address client;
    ::std::string filename;
    client.__read(__is);
    __is->read(filename);
    close(client, filename, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___getChunksInfo(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Address client;
    ::std::string filename;
    client.__read(__is);
    __is->read(filename);
    try
    {
	::tfs::slice::LocatedChunks __ret = getChunksInfo(client, filename, __current);
	if(__ret.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    ::tfs::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::tfs::slice::__U__LocatedChunks());
	}
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___completeWrittenChunk(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::LocatedChunk lchk;
    lchk.__read(__is);
    try
    {
	completeWrittenChunk(lchk, __current);
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

::IceInternal::DispatchStatus
tfs::slice::ClientService::___updateChunkInfo(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::LocatedChunk lchk;
    lchk.__read(__is);
    try
    {
	updateChunkInfo(lchk, __current);
    }
    catch(const ::tfs::slice::NoSuchChunk& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___addChunk(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Address client;
    ::std::string filename;
    client.__read(__is);
    __is->read(filename);
    try
    {
	::tfs::slice::LocatedChunk __ret = addChunk(client, filename, __current);
	__ret.__write(__os);
    }
    catch(const ::tfs::slice::NoChunkAllocated& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___abandonAddChunk(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Chunk chk;
    chk.__read(__is);
    try
    {
	abandonAddChunk(chk, __current);
    }
    catch(const ::tfs::slice::NoChunkAllocated& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___reportBadChunks(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::tfs::slice::LocatedChunks chunks;
    ::tfs::slice::__read(__is, chunks, ::tfs::slice::__U__LocatedChunks());
    reportBadChunks(chunks, __current);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___setReplication(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string filename;
    ::Ice::Short replication;
    __is->read(filename);
    __is->read(replication);
    try
    {
	setReplication(filename, replication, __current);
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::ReplicationOutOfRange& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___getFileInfo(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string filename;
    __is->read(filename);
    try
    {
	::tfs::slice::FileInfo __ret = getFileInfo(filename, __current);
	__ret.__write(__os);
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___create(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string filename;
    ::Ice::Short replication;
    ::Ice::Long chunkSize;
    __is->read(filename);
    __is->read(replication);
    __is->read(chunkSize);
    try
    {
	create(filename, replication, chunkSize, __current);
    }
    catch(const ::tfs::slice::ChunkSizeOutOfRange& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::FileOrDirAlreadyExists& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::ReplicationOutOfRange& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___rename(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    ::std::string dst;
    __is->read(src);
    __is->read(dst);
    try
    {
	rename(src, dst, __current);
    }
    catch(const ::tfs::slice::FileOrDirAlreadyExists& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___remove(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    __is->read(src);
    try
    {
	remove(src, __current);
    }
    catch(const ::tfs::slice::LockFail& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___mkdir(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    __is->read(src);
    try
    {
	mkdir(src, __current);
    }
    catch(const ::tfs::slice::FileOrDirAlreadyExists& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___renamedir(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    ::std::string dst;
    __is->read(src);
    __is->read(dst);
    try
    {
	renamedir(src, dst, __current);
    }
    catch(const ::tfs::slice::FileOrDirAlreadyExists& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___rmdir(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    __is->read(src);
    try
    {
	rmdir(src, __current);
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::LockFail& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___lsdir(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string src;
    __is->read(src);
    try
    {
	::tfs::slice::FilesInfo __ret = lsdir(src, __current);
	if(__ret.size() == 0)
	{
	    __os->writeSize(0);
	}
	else
	{
	    ::tfs::slice::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::tfs::slice::__U__FilesInfo());
	}
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___concatFiles(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::tfs::slice::Strings srcFiles;
    ::std::string dst;
    __is->read(srcFiles);
    __is->read(dst);
    try
    {
	concatFiles(srcFiles, dst, __current);
    }
    catch(const ::tfs::slice::FileOrDirAlreadyExists& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::InvalidFileOrDirName& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    catch(const ::tfs::slice::NoSuchFileOrDir& __ex)
    {
	__os->write(__ex);
	return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
tfs::slice::ClientService::___reportHeartbeat(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::tfs::slice::Address clientAddress;
    clientAddress.__read(__is);
    reportHeartbeat(clientAddress, __current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __tfs__slice__ClientService_all[] =
{
    "abandonAddChunk",
    "addChunk",
    "close",
    "completeWrittenChunk",
    "concatFiles",
    "create",
    "getChunksInfo",
    "getFileInfo",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "lsdir",
    "mkdir",
    "open",
    "remove",
    "rename",
    "renamedir",
    "reportBadChunks",
    "reportHeartbeat",
    "rmdir",
    "setReplication",
    "updateChunkInfo"
};

::IceInternal::DispatchStatus
tfs::slice::ClientService::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__tfs__slice__ClientService_all, __tfs__slice__ClientService_all + 23, current.operation);
    if(r.first == r.second)
    {
	return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __tfs__slice__ClientService_all)
    {
	case 0:
	{
	    return ___abandonAddChunk(in, current);
	}
	case 1:
	{
	    return ___addChunk(in, current);
	}
	case 2:
	{
	    return ___close(in, current);
	}
	case 3:
	{
	    return ___completeWrittenChunk(in, current);
	}
	case 4:
	{
	    return ___concatFiles(in, current);
	}
	case 5:
	{
	    return ___create(in, current);
	}
	case 6:
	{
	    return ___getChunksInfo(in, current);
	}
	case 7:
	{
	    return ___getFileInfo(in, current);
	}
	case 8:
	{
	    return ___ice_id(in, current);
	}
	case 9:
	{
	    return ___ice_ids(in, current);
	}
	case 10:
	{
	    return ___ice_isA(in, current);
	}
	case 11:
	{
	    return ___ice_ping(in, current);
	}
	case 12:
	{
	    return ___lsdir(in, current);
	}
	case 13:
	{
	    return ___mkdir(in, current);
	}
	case 14:
	{
	    return ___open(in, current);
	}
	case 15:
	{
	    return ___remove(in, current);
	}
	case 16:
	{
	    return ___rename(in, current);
	}
	case 17:
	{
	    return ___renamedir(in, current);
	}
	case 18:
	{
	    return ___reportBadChunks(in, current);
	}
	case 19:
	{
	    return ___reportHeartbeat(in, current);
	}
	case 20:
	{
	    return ___rmdir(in, current);
	}
	case 21:
	{
	    return ___setReplication(in, current);
	}
	case 22:
	{
	    return ___updateChunkInfo(in, current);
	}
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
tfs::slice::ClientService::__write(::IceInternal::BasicStream* __os) const
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
tfs::slice::ClientService::__read(::IceInternal::BasicStream* __is, bool __rid)
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
tfs::slice::ClientService::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::ClientService was not generated with stream support";
    throw ex;
}

void
tfs::slice::ClientService::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type tfs::slice::ClientService was not generated with stream support";
    throw ex;
}

void 
tfs::slice::__patch__ClientServicePtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::tfs::slice::ClientServicePtr* p = static_cast< ::tfs::slice::ClientServicePtr*>(__addr);
    assert(p);
    *p = ::tfs::slice::ClientServicePtr::dynamicCast(v);
    if(v && !*p)
    {
	::Ice::NoObjectFactoryException e(__FILE__, __LINE__);
	e.type = ::tfs::slice::ClientService::ice_staticId();
	throw e;
    }
}

bool
tfs::slice::operator==(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator!=(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
tfs::slice::operator<=(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return l < r || l == r;
}

bool
tfs::slice::operator>(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return !(l < r) && !(l == r);
}

bool
tfs::slice::operator>=(const ::tfs::slice::ClientService& l, const ::tfs::slice::ClientService& r)
{
    return !(l < r);
}
