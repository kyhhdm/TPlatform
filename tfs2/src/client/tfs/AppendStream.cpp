/**
 * @file    AppendStream.cpp
 *  Implementation of TFS append stream
 * 
 * @author  Fan Kai(FK), Peking University
 * @date    07/11/2007 11:37:32 PM CST
 *
 */

#include "AppendStream.hpp"
#include "Client.hpp"

namespace tfs {

AppendStream::AppendStream() {
    m_pfile = new File();
    LOG_INFO("AppendStream: Construct.")
    m_buffer = NULL;
    m_opened = false;
}

AppendStream::~AppendStream() {
    LOG_INFO("AppendStream: Destruct.")
    close();
    delete m_buffer;
    delete m_pfile;
}

void AppendStream::open(const string &path, int bufSize) {
    LOG_INFO("AppendStream: Open " <<path 
                   <<" buffer size: " <<bufSize)
    m_pfile->open(path, FileOpenAppend);
	m_chunkSize = m_pfile->info().chunkSize;
    if (bufSize == 0)
        bufSize = Client::defaultBufferSize();
    if (bufSize < 1024 || bufSize > m_pfile->info().chunkSize) {
        LOG_ERROR("AppendStream: Throw api::BufferSizeOutOfRange")
        throw api::BufferSizeOutOfRange();
    }
    if (m_buffer == NULL || m_bufferSize != bufSize) {
        if (m_buffer != NULL) delete m_buffer;
        m_bufferSize = bufSize;
        m_buffer = new char[m_bufferSize];
    }
    m_offset = 0;
    m_nfilled = 0;
    m_opened = true;
}

void AppendStream::close() {
    LOG_INFO("AppendStream: Close file.")
    if (!m_opened) return;
    flush();
    m_pfile->close();
    m_opened = false;
}

void AppendStream::append(const char *buf, int64_t nbytes) {
    LOG_INFO("AppendStream: Append " <<nbytes <<" bytes.")

    if (!m_opened) {
        LOG_ERROR("AppendStream: Throw api::NoFileOpened")
        throw api::NoFileOpened();
    }
     
    // We ensure that the bytes appended should not exceed the 
    // chunk size.
    if (nbytes <=0 || nbytes > m_chunkSize) {
        LOG_ERROR("AppendStream: Throw api::AppendSizeTooLarge")
        throw api::AppendSizeTooLarge();
    }

    if (nbytes + m_nfilled > m_bufferSize) {
        m_pfile->append(m_buffer, m_nfilled);
        m_nfilled = 0;
    }
    if (nbytes > m_bufferSize){
        // If append bytes is larger than buffer, then directly append
        // these bytes without buffer.
        m_pfile->append(buf, nbytes);
    } else {
        memcpy(m_buffer + m_nfilled, buf, nbytes);
        m_nfilled += nbytes;
    }
}

void AppendStream::flush() {
    LOG_INFO("AppendStream: Flush file.")
    if (!m_opened) {
        LOG_ERROR("AppendStream: Throw api::NoFileOpened")
        throw api::NoFileOpened();
    }
    if (m_nfilled > 0) {
        m_pfile->append(m_buffer, m_nfilled);
        m_nfilled = 0;
    }
    //m_pfile->finishAppend();
}

}   // namespace tfs
