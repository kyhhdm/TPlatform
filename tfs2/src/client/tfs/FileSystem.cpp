/**
 * @file    FileSystem.cpp
 *   Implementation of FileSystem Class
 * 
 * @author  Fan Kai(FK), Peking University    
 * @date    05/30/2007 11:56:12 PM CST
 *
 */

#include "FileSystem.hpp"
#include "Client.hpp"

#include <common/Exception.hpp>
#include <common/stdint.h>

namespace tfs {

FileSystem::FileSystem() {
    Client::init();
}

FilesInfo FileSystem::listDirectory(const string &path) {
    try {
        LOG_INFO("FileSystem: List directory " << path);
        return Client::service()->lsdir(path);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

bool FileSystem::existDirectory(const string &path){ 
    LOG_INFO("FileSystem: Test existDirecotry " << path);
    if (path == "/") return true;
    try {
        FileInfo info = Client::service()->getFileInfo(path + "/");
        return ((info.flag & FileModeTypeDir) != 0);
    } catch (NoSuchFileOrDir &ex) {
        return false;
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::createDirectory(const string &path) {
    try {
        LOG_INFO("FileSystem: Create directory " << path);
        if (!Client::authorized(path)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->mkdir(path);
    } catch (FileOrDirAlreadyExists &ex) {
        LOG_ERROR("FileSystem: Throw api::FileOrDirAlreadyExists")
        throw api::FileOrDirAlreadyExists();
    } catch (InvalidFileOrDirName &ex) {
        LOG_ERROR("FileSystem: Throw api::InvalidFileOrDirName")
        throw api::InvalidFileOrDirName();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::removeDirectory(const string &path, bool recursive) {
    try {
        LOG_INFO("FileSystem: Remove directory " << path);
        if (!Client::authorized(path)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        if (recursive) {
            FilesInfo contents = Client::service()->lsdir(path);
            // We can only delete empty directory, so delete the contents first
            for (int i = 0; i < contents.size(); ++i) {
                LOG_DEBUG("FileSystem: member of " << path <<" :" 
                         <<contents[i].name);
                if (contents[i].flag & FileModeTypeDir) 
                    removeDirectory(path + "/" + contents[i].name, true);
                else
                    removeFile(path + "/" + contents[i].name);
            }
        }
        Client::service()->rmdir(path);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (LockFail &ex) {
        LOG_ERROR("FileSystem: Throw api::LockFail")
        throw api::LockFail();
    } catch (InvalidFileOrDirName &ex) {
        LOG_ERROR("FileSystem: Throw api::InvalidFileOrDirName")
        throw api::InvalidFileOrDirName();
    } catch (GenericException &ex) {
        LOG_FATAL("FileSystem: Get Generic Exception: " <<ex.reason);
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::renameDirectory(const string &src, const string &dst) {
    try {
        LOG_INFO("FileSystem: Rename directory " << src << " -> " <<dst);
        if (!Client::authorized(src) || !Client::authorized(dst)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->renamedir(src, dst);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (FileOrDirAlreadyExists &ex) {
        LOG_ERROR("FileSystem: Throw api::FileOrDirAlreadyExists")
        throw api::FileOrDirAlreadyExists();
    } catch (InvalidFileOrDirName &ex) {
        LOG_ERROR("FileSystem: Throw api::InvalidFileOrDirName")
        throw api::InvalidFileOrDirName();
    } catch (LockFail &ex) {
        LOG_ERROR("FileSystem: Throw api::LockFail")
        throw api::LockFail();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

bool FileSystem::existFile(const string &path)  {
    LOG_INFO("FileSystem: Test existDirecotry: " << path);
    try {
        FileInfo info = Client::service()->getFileInfo(path);
        return ((info.flag & FileModeTypeDir) == 0);
    } catch (NoSuchFileOrDir &ex) {
        return false;
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::createFile(const string &path, 
                            int replication, int chunkSize) {
    try {
        LOG_INFO("FileSystem: Create file :" << path);
        if (!Client::authorized(path)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->create(path, replication, chunkSize);
    } catch (FileOrDirAlreadyExists &ex) {
        LOG_ERROR("FileSystem: Throw api::FileOrDirAlreadyExists")
        throw api::FileOrDirAlreadyExists();
    } catch (InvalidFileOrDirName &ex) {
        LOG_ERROR("FileSystem: Throw api::InvalidFileOrDirName")
        throw api::InvalidFileOrDirName();
    } catch (ReplicationOutOfRange &ex) {
        LOG_ERROR("FileSystem: Throw api::ReplicationOutOfRange")
        throw api::ReplicationOutOfRange();
    } catch (ChunkSizeOutOfRange &ex) {
        LOG_ERROR("FileSystem: Throw api::ChunkSizeOutOfRange")
        throw api::ChunkSizeOutOfRange();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::removeFile(const string &path) {
    try {
        LOG_INFO("FileSystem: Remove file :" << path);
        if (!Client::authorized(path)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->remove(path);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (LockFail &ex) {
        LOG_ERROR("FileSystem: Throw api::LockFail")
        throw api::LockFail();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}
    
void FileSystem::renameFile(const string &src, const string &dst) {
    try {
        LOG_INFO("FileSystem: Rename file " << src << " -> " << dst);
        if (!Client::authorized(src) || !Client::authorized(dst)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->rename(src, dst);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (FileOrDirAlreadyExists &ex) {
        LOG_ERROR("FileSystem: Throw api::FileOrDirAlreadyExists")
        throw api::FileOrDirAlreadyExists();
    } catch (InvalidFileOrDirName &ex) {
        LOG_ERROR("FileSystem: Throw api::InvalidFileOrDirName")
        throw api::InvalidFileOrDirName();
    } catch (LockFail &ex) {
        LOG_ERROR("FileSystem: Throw api::LockFail")
        throw api::LockFail();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

void FileSystem::setReplication(const string &path, int replication){
    try {
        LOG_INFO("FileSystem: Set replictaion of file " << path
                                         <<" to " <<replication);
        if (!Client::authorized(path)) {
            LOG_ERROR("FileSystem: Throw api::AuthenticationFail")
            throw api::AuthenticationFail();
        }
        Client::service()->setReplication(path, replication);
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (ReplicationOutOfRange &ex) {
        LOG_ERROR("FileSystem: Throw api::ReplicationOutOfRange")
        throw api::ReplicationOutOfRange();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

FileInfo FileSystem::getFileInfo(const string &path) {
    try {
        LOG_INFO("FileSystem: Get info of file  " <<path);
        FileInfo info = Client::service()->getFileInfo(path);
        LOG_DEBUG("FileSystem: \tname : " <<info.name);
        LOG_DEBUG("FileSystem: \tsize : " <<info.size);
        LOG_DEBUG("FileSystem: \tchunk size : " <<info.chunkSize);
        LOG_DEBUG("FileSystem: \treplication : " <<info.replication);
        LOG_DEBUG("FileSystem: \tcreated time : " <<info.createTime);
        return info;
    } catch (NoSuchFileOrDir &ex) {
        LOG_ERROR("FileSystem: Throw api::NoSuchFileOrDir")
        throw api::NoSuchFileOrDir();
    } catch (Ice::Exception &ex) {
        LOG_FATAL("FileSystem: Get Ice Exception: " <<ex.ice_name());
        LOG_FATAL("FileSystem: Throw api::ConnectionError");
        throw api::ConnectionError();
    }
}

}   // namespace tfs
