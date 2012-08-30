/** 
 * @file IceGenerated.hpp
 * convert ::tfs::slice namespace into ::tfs.
 * 
 * @author Zhifeng YANG
 * @date 2007-06-17
 */
#ifndef _ICE_HPP
#define _ICE_HPP 1

// headers generated by ice
#include "ChunkServerService.h"
#include "ClientService.h"
#include "Chunk.h"
#include "FileInfo.h"
#include "Address.h"
#include "MasterCommand.h"
#include "Heartbeat.h"

#include <boost/shared_ptr.hpp>


//this macro should be palced somewhere else
//it bypass the compile warning: unused variable/argument
#define UNUSED(a) do{/*NULL*/}while((void*)&a == NULL);

namespace tfs
{
    using tfs::slice::Chunk;
    using tfs::slice::Chunks;

    using tfs::slice::Address;
    using tfs::slice::Addresses;

    using tfs::slice::LocatedChunk;
    using tfs::slice::LocatedChunks;
    
    using tfs::slice::FileInfo;
    using tfs::slice::FilesInfo;
    using tfs::slice::FileOpenMode;
    using tfs::slice::ClientService;
    using tfs::slice::ClientServicePrx;

    using tfs::slice::ChunkServerService;
    using tfs::slice::MasterCommand;
    using tfs::slice::Heartbeat;

    using tfs::slice::McDoNothing;
    using tfs::slice::McRegister;
    using tfs::slice::McRemoveChunks;
    using tfs::slice::McTransferChunks;
    using tfs::slice::McShutdown;

    
    using tfs::slice::FileModeTypeDir;
    using tfs::slice::FileModeOwnerRead;
    using tfs::slice::FileModeOwnerWrite;
    using tfs::slice::FileModeOwnerExec;
    using tfs::slice::FileModeGroupRead;
    using tfs::slice::FileModeGroupWrite;
    using tfs::slice::FileModeGroupExec;
    using tfs::slice::FileModeOtherRead;
    using tfs::slice::FileModeOtherWrite;
    using tfs::slice::FileModeOtherExec;

    using tfs::slice::FileOpenRead;
    using tfs::slice::FileOpenAppend;
    using tfs::slice::FileOpenWrite;

    using tfs::slice::Strings;
    
    // pb: common pointer type
    typedef boost::shared_ptr<Chunks> ChunksPtr;
    typedef boost::shared_ptr<FileInfo> FileInfoPtr;
    typedef boost::shared_ptr<FilesInfo> FilesInfoPtr;

    enum LockType {ReadLock, WriteLock};
}



#endif /* _ICE_HPP */
