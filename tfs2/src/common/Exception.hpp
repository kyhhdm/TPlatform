/** 
 * @file Exception.hpp
 * Our exception architecture.
 * 
 * @author Zhifeng YANG
 * @date 2007-06-19
 */
#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP 1

#include "ice/c++/ice-3.1.1/Exceptions.h"
namespace tfs
{
    // root of all the exceptions
    using ::tfs::slice::GenericException;

    using ::tfs::slice::NoSuchFileOrDir;
    using ::tfs::slice::IOError;
    using ::tfs::slice::LockFail;
    using ::tfs::slice::OffsetOutOfRange;
    using ::tfs::slice::NoChunkAllocated;
    using ::tfs::slice::NoSuchChunk;
    using ::tfs::slice::FileOrDirAlreadyExists;
    using ::tfs::slice::UnknownChunkServer;
    using ::tfs::slice::ReplicationOutOfRange;
    using ::tfs::slice::InvalidFileOrDirName;
    using ::tfs::slice::JournalException;
    using ::tfs::slice::ChunkSizeOutOfRange;
    
}
    
#endif /* _EXCEPTION_HPP */
