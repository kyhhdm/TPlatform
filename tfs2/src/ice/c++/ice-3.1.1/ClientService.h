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

#ifndef _____c___ice_3_1_1_ClientService_h__
#define _____c___ice_3_1_1_ClientService_h__

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
#include <Chunk.h>
#include <FileInfo.h>
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

class ClientService;
bool operator==(const ClientService&, const ClientService&);
bool operator!=(const ClientService&, const ClientService&);
bool operator<(const ClientService&, const ClientService&);
bool operator<=(const ClientService&, const ClientService&);
bool operator>(const ClientService&, const ClientService&);
bool operator>=(const ClientService&, const ClientService&);

}

}

}

namespace tfs
{

namespace slice
{

class ClientService;
bool operator==(const ClientService&, const ClientService&);
bool operator!=(const ClientService&, const ClientService&);
bool operator<(const ClientService&, const ClientService&);
bool operator<=(const ClientService&, const ClientService&);
bool operator>(const ClientService&, const ClientService&);
bool operator>=(const ClientService&, const ClientService&);

}

}

namespace IceInternal
{

void incRef(::tfs::slice::ClientService*);
void decRef(::tfs::slice::ClientService*);

void incRef(::IceProxy::tfs::slice::ClientService*);
void decRef(::IceProxy::tfs::slice::ClientService*);

}

namespace tfs
{

namespace slice
{

typedef ::IceInternal::Handle< ::tfs::slice::ClientService> ClientServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::tfs::slice::ClientService> ClientServicePrx;

void __write(::IceInternal::BasicStream*, const ClientServicePrx&);
void __read(::IceInternal::BasicStream*, ClientServicePrx&);
void __write(::IceInternal::BasicStream*, const ClientServicePtr&);
void __patch__ClientServicePtr(void*, ::Ice::ObjectPtr&);

}

}

namespace tfs
{

namespace slice
{

enum FileOpenMode
{
    FileOpenWrite,
    FileOpenRead,
    FileOpenAppend
};

void __write(::IceInternal::BasicStream*, FileOpenMode);
void __read(::IceInternal::BasicStream*, FileOpenMode&);

typedef ::std::vector< ::std::string> Strings;

class __U__Strings { };

}

}

namespace IceProxy
{

namespace tfs
{

namespace slice
{

class ClientService : virtual public ::IceProxy::Ice::Object
{
public:

    void open(const ::tfs::slice::Address& client, const ::std::string& filename, ::Ice::Int mode)
    {
	open(client, filename, mode, __defaultContext());
    }
    void open(const ::tfs::slice::Address&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    void close(const ::tfs::slice::Address& client, const ::std::string& filename)
    {
	close(client, filename, __defaultContext());
    }
    void close(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address& client, const ::std::string& filename)
    {
	return getChunksInfo(client, filename, __defaultContext());
    }
    ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    void completeWrittenChunk(const ::tfs::slice::LocatedChunk& lchk)
    {
	completeWrittenChunk(lchk, __defaultContext());
    }
    void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    void updateChunkInfo(const ::tfs::slice::LocatedChunk& lchk)
    {
	updateChunkInfo(lchk, __defaultContext());
    }
    void updateChunkInfo(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address& client, const ::std::string& filename)
    {
	return addChunk(client, filename, __defaultContext());
    }
    ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    void abandonAddChunk(const ::tfs::slice::Chunk& chk)
    {
	abandonAddChunk(chk, __defaultContext());
    }
    void abandonAddChunk(const ::tfs::slice::Chunk&, const ::Ice::Context&);

    void reportBadChunks(const ::tfs::slice::LocatedChunks& chunks)
    {
	reportBadChunks(chunks, __defaultContext());
    }
    void reportBadChunks(const ::tfs::slice::LocatedChunks&, const ::Ice::Context&);

    void setReplication(const ::std::string& filename, ::Ice::Short replication)
    {
	setReplication(filename, replication, __defaultContext());
    }
    void setReplication(const ::std::string&, ::Ice::Short, const ::Ice::Context&);

    ::tfs::slice::FileInfo getFileInfo(const ::std::string& filename)
    {
	return getFileInfo(filename, __defaultContext());
    }
    ::tfs::slice::FileInfo getFileInfo(const ::std::string&, const ::Ice::Context&);

    void create(const ::std::string& filename, ::Ice::Short replication, ::Ice::Long chunkSize)
    {
	create(filename, replication, chunkSize, __defaultContext());
    }
    void create(const ::std::string&, ::Ice::Short, ::Ice::Long, const ::Ice::Context&);

    void rename(const ::std::string& src, const ::std::string& dst)
    {
	rename(src, dst, __defaultContext());
    }
    void rename(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    void remove(const ::std::string& src)
    {
	remove(src, __defaultContext());
    }
    void remove(const ::std::string&, const ::Ice::Context&);

    void mkdir(const ::std::string& src)
    {
	mkdir(src, __defaultContext());
    }
    void mkdir(const ::std::string&, const ::Ice::Context&);

    void renamedir(const ::std::string& src, const ::std::string& dst)
    {
	renamedir(src, dst, __defaultContext());
    }
    void renamedir(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    void rmdir(const ::std::string& src)
    {
	rmdir(src, __defaultContext());
    }
    void rmdir(const ::std::string&, const ::Ice::Context&);

    ::tfs::slice::FilesInfo lsdir(const ::std::string& src)
    {
	return lsdir(src, __defaultContext());
    }
    ::tfs::slice::FilesInfo lsdir(const ::std::string&, const ::Ice::Context&);

    void concatFiles(const ::tfs::slice::Strings& srcFiles, const ::std::string& dst)
    {
	concatFiles(srcFiles, dst, __defaultContext());
    }
    void concatFiles(const ::tfs::slice::Strings&, const ::std::string&, const ::Ice::Context&);

    void reportHeartbeat(const ::tfs::slice::Address& clientAddress)
    {
	reportHeartbeat(clientAddress, __defaultContext());
    }
    void reportHeartbeat(const ::tfs::slice::Address&, const ::Ice::Context&);
    
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

class ClientService : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void open(const ::tfs::slice::Address&, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual void close(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&) = 0;

    virtual void updateChunkInfo(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&) = 0;

    virtual ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void abandonAddChunk(const ::tfs::slice::Chunk&, const ::Ice::Context&) = 0;

    virtual void reportBadChunks(const ::tfs::slice::LocatedChunks&, const ::Ice::Context&) = 0;

    virtual void setReplication(const ::std::string&, ::Ice::Short, const ::Ice::Context&) = 0;

    virtual ::tfs::slice::FileInfo getFileInfo(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void create(const ::std::string&, ::Ice::Short, ::Ice::Long, const ::Ice::Context&) = 0;

    virtual void rename(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void remove(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void mkdir(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void renamedir(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void rmdir(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::tfs::slice::FilesInfo lsdir(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void concatFiles(const ::tfs::slice::Strings&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void reportHeartbeat(const ::tfs::slice::Address&, const ::Ice::Context&) = 0;
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

class ClientService : virtual public ::IceDelegate::tfs::slice::ClientService,
		      virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void open(const ::tfs::slice::Address&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual void close(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    virtual void updateChunkInfo(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    virtual ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual void abandonAddChunk(const ::tfs::slice::Chunk&, const ::Ice::Context&);

    virtual void reportBadChunks(const ::tfs::slice::LocatedChunks&, const ::Ice::Context&);

    virtual void setReplication(const ::std::string&, ::Ice::Short, const ::Ice::Context&);

    virtual ::tfs::slice::FileInfo getFileInfo(const ::std::string&, const ::Ice::Context&);

    virtual void create(const ::std::string&, ::Ice::Short, ::Ice::Long, const ::Ice::Context&);

    virtual void rename(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void remove(const ::std::string&, const ::Ice::Context&);

    virtual void mkdir(const ::std::string&, const ::Ice::Context&);

    virtual void renamedir(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void rmdir(const ::std::string&, const ::Ice::Context&);

    virtual ::tfs::slice::FilesInfo lsdir(const ::std::string&, const ::Ice::Context&);

    virtual void concatFiles(const ::tfs::slice::Strings&, const ::std::string&, const ::Ice::Context&);

    virtual void reportHeartbeat(const ::tfs::slice::Address&, const ::Ice::Context&);
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

class ClientService : virtual public ::IceDelegate::tfs::slice::ClientService,
		      virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void open(const ::tfs::slice::Address&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual void close(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    virtual void updateChunkInfo(const ::tfs::slice::LocatedChunk&, const ::Ice::Context&);

    virtual ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Context&);

    virtual void abandonAddChunk(const ::tfs::slice::Chunk&, const ::Ice::Context&);

    virtual void reportBadChunks(const ::tfs::slice::LocatedChunks&, const ::Ice::Context&);

    virtual void setReplication(const ::std::string&, ::Ice::Short, const ::Ice::Context&);

    virtual ::tfs::slice::FileInfo getFileInfo(const ::std::string&, const ::Ice::Context&);

    virtual void create(const ::std::string&, ::Ice::Short, ::Ice::Long, const ::Ice::Context&);

    virtual void rename(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void remove(const ::std::string&, const ::Ice::Context&);

    virtual void mkdir(const ::std::string&, const ::Ice::Context&);

    virtual void renamedir(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void rmdir(const ::std::string&, const ::Ice::Context&);

    virtual ::tfs::slice::FilesInfo lsdir(const ::std::string&, const ::Ice::Context&);

    virtual void concatFiles(const ::tfs::slice::Strings&, const ::std::string&, const ::Ice::Context&);

    virtual void reportHeartbeat(const ::tfs::slice::Address&, const ::Ice::Context&);
};

}

}

}

namespace tfs
{

namespace slice
{

class ClientService : virtual public ::Ice::Object
{
public:

    typedef ClientServicePrx ProxyType;
    typedef ClientServicePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void open(const ::tfs::slice::Address&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___open(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void close(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::LocatedChunks getChunksInfo(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getChunksInfo(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void completeWrittenChunk(const ::tfs::slice::LocatedChunk&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___completeWrittenChunk(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateChunkInfo(const ::tfs::slice::LocatedChunk&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___updateChunkInfo(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::LocatedChunk addChunk(const ::tfs::slice::Address&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___addChunk(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void abandonAddChunk(const ::tfs::slice::Chunk&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___abandonAddChunk(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void reportBadChunks(const ::tfs::slice::LocatedChunks&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___reportBadChunks(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setReplication(const ::std::string&, ::Ice::Short, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setReplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::FileInfo getFileInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getFileInfo(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void create(const ::std::string&, ::Ice::Short, ::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___create(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void rename(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___rename(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void remove(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remove(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void mkdir(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___mkdir(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void renamedir(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___renamedir(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void rmdir(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___rmdir(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::tfs::slice::FilesInfo lsdir(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___lsdir(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void concatFiles(const ::tfs::slice::Strings&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___concatFiles(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void reportHeartbeat(const ::tfs::slice::Address&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___reportHeartbeat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ClientServicePtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
