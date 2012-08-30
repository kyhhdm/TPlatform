/**
 * @file    tfs.cpp
 *  Implementation for tfs.h
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    09/02/2007 09:04:35 AM CST
 */

#include "tfs.h"
#include "InputStream.hpp"
#include "AppendStream.hpp"
#include "FileSystem.hpp"
#include "Client.hpp"

namespace tfs {

namespace api {

InputStream::InputStream() {
    m_istream = new tfs::InputStream();
}

InputStream::~InputStream() {
    delete m_istream;
}

InputStream::InputStream(const std::string &path, int bufSize) {
    m_istream = new tfs::InputStream();
    open(path, bufSize);
}

void InputStream::open(const string &path, int bufSize) {
    m_istream->open(path, bufSize);
}

void InputStream::close() {
    m_istream->close();
}
        
int64_t InputStream::read(char *buf, int64_t nbytes) {
    return m_istream->read(buf, nbytes);
}

int64_t InputStream::seek(int64_t offset, int whence) {
    return m_istream->seek(offset, whence);
}

AppendStream::AppendStream() {
    m_astream = new tfs::AppendStream(); 
}

AppendStream::~AppendStream() {
    delete m_astream;
}

AppendStream::AppendStream(const std::string &path, int bufSize) {
    m_astream = new tfs::AppendStream(); 
    open(path, bufSize);
}

void AppendStream::open(const string &path, int bufSize) {
    m_astream->open(path, bufSize);
}

void AppendStream::close() {
    m_astream->close();
}

void AppendStream::append(const char *buf, int nbytes) {
    m_astream->append(buf, nbytes);
}

void AppendStream::flush() {
    m_astream->flush();
}

bool TFSConfiguration::set(const TFSConfiguration &conf) {
    return tfs::Client::set(conf);
}

bool TFSConfiguration::setFile(const string &path) {
    return tfs::Client::setFile(path);
}

FileSystem::FileSystem() {
    m_fs = new tfs::FileSystem();
}

FileSystem::~FileSystem() {
}

bool FileSystem::existDirectory(const string &path) {
    return m_fs->existDirectory(path);
}

bool FileSystem::existFile(const string &path) {
    return m_fs->existFile(path);
}

FilesInfo FileSystem::listDirectory(const string &path) {
    // We guarantee that tfs::slice::FileInfo and tfs::api::FileInfo
    // are just the same in byte order.
    tfs::slice::FilesInfo info = m_fs->listDirectory(path);
    return *(FilesInfo *)&info;
}

void FileSystem::createDirectory(const string &path) {
    m_fs->createDirectory(path);
}

void FileSystem::removeDirectory(const string &path, bool recursive) {
    m_fs->removeDirectory(path, recursive);
}

void FileSystem::renameDirectory(const string &src, const string &dst) {
    m_fs->renameDirectory(src, dst);
}

void FileSystem::createFile(const string &path, int replication, 
                            int chunkSize) {
    m_fs->createFile(path, replication, chunkSize);
}

void FileSystem::removeFile(const string &path) {
    m_fs->removeFile(path);
}

void FileSystem::setReplication(const string &path, int replication) {
    m_fs->setReplication(path, replication);
}

void FileSystem::renameFile(const string &src, const string &dst) {
    m_fs->renameFile(src, dst);
}

FileInfo FileSystem::getFileInfo(const string &path) {
    // We guarantee that tfs::slice::FileInfo and tfs::api::FileInfo
    // are just the same in byte order.
    tfs::slice::FileInfo info = m_fs->getFileInfo(path);
    return *(FileInfo *)&info;
}

} // namespace api

} // namespace tfs
