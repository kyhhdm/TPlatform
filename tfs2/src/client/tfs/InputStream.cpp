/**
 * @file	InputStream.cpp
 * 	Implementation of InputStream
 * 
 * @author	Fan Kai(FK), Peking University	
 * @date	07/09/2007 06:01:26 PM CST
 *
 */

#include "InputStream.hpp"
#include "Client.hpp"

namespace tfs{

InputStream::InputStream() {
    m_file = new File();
    LOG_INFO("InputStream: Construct.")
    m_opened = false;
    m_buffer = NULL;
}

InputStream::~InputStream() {
    LOG_INFO("InputStream: Destruct.")
    close();
    delete m_file;
}

void InputStream::open(const string &path, int bufSize) {
    LOG_INFO("InputStream: Open " <<path
                   <<" buffer size: " <<bufSize)
    m_file->open(path, FileOpenRead);
    if (bufSize == 0)
        bufSize = Client::defaultBufferSize();
    if (bufSize < 1024 || bufSize > m_file->info().chunkSize) {
        LOG_ERROR("InputStream: Throw api::BufferSizeOutOfRange")
        throw api::BufferSizeOutOfRange();
    }
    if (m_buffer == NULL || m_bufferSize != bufSize) {
        if (m_buffer != NULL) delete m_buffer;
        m_bufferSize = bufSize;
        m_buffer = new char[m_bufferSize];
    }
    m_offset = 0;
    m_available = 0;
    m_used = 0;
    m_opened = true;
}

void InputStream::close() {
    LOG_INFO("InputStream: Close file.")
    if (!m_opened) return;
    m_file->close();
    m_opened = false;
}

void InputStream::fillBuffer() {
    m_file->seek(m_offset, SEEK_SET);
    assert(m_buffer != NULL);
    m_available = m_file->read(m_buffer, m_bufferSize);
    m_used = 0;
}

int64_t InputStream::read(char *buf, int64_t nbytes) {
    LOG_INFO("InputStream: Read " << nbytes <<" bytes");
    if (!m_opened) {
        LOG_ERROR("InputStream: Throw api::NoFileOpened")
        throw api::NoFileOpened();
    }

    if (nbytes <= 0) return 0;

    int64_t nread = 0;

    if (m_available >= nbytes){
        // have enough cache
        memcpy(buf, m_buffer + m_used, nbytes);
        m_available -= nbytes;
        m_used += nbytes;
        m_offset += nbytes;
        nread = nbytes;
    } else {
        // read the current cache first
        if (m_available > 0) {
            memcpy(buf, m_buffer + m_used, m_available);
            nbytes -= m_available;
            m_offset += m_available;
            nread = m_available;
        }
        if (m_bufferSize > nbytes) {
            // if buffer size is bigger, fill the buffer
            fillBuffer();
            m_used = m_available > nbytes ? nbytes : m_available;
            memcpy(buf + nread, m_buffer, m_used);
            m_available -= m_used;
            m_offset += m_used;
            nread += m_used;
        } else {
            // direct read without buffer
            m_file->seek(m_offset, SEEK_SET);
            nread += m_file->read(buf + nread, nbytes);
            m_offset += nread;
            m_used = 0;
            m_available = 0;
        }
    }
    return nread;	
}

int64_t InputStream::seek(int64_t offset, int whence) {
    if (!m_opened) {
        LOG_ERROR("InputStream: Throw api::NoFileOpened")
        throw api::NoFileOpened();
    }
    int64_t newoff;
    if (whence == SEEK_SET) {
        LOG_INFO("InputStream: Seek from start: " << offset);
        newoff = offset;
    } else if (whence == SEEK_CUR) {
        LOG_INFO("InputStream: Seek from current: " <<offset);
        newoff = m_offset + offset;
    } else if (whence == SEEK_END) {
        LOG_INFO("InputStream: Seek from end: " <<offset);
        newoff = m_file->info().size + offset;
    } else {
        LOG_ERROR("InputStream: Throw api::UnknownSeekOption")
        throw api::UnknownSeekOption();
    }

    if (newoff < 0)
        newoff = 0;
    else if (newoff > m_file->info().size)
        newoff = m_file->info().size;

	if (whence == SEEK_CUR)
		m_file->seek(m_offset, SEEK_SET);
    newoff = m_file->seek(offset, whence);

    if (m_offset - m_used  <= newoff && 
            newoff < m_offset + m_available){
        // new offset within buffer range
        m_used += (newoff - m_offset);
        m_available -= (newoff - m_offset);
    } else {
        m_available = 0;
        m_used = 0;
    }
    m_offset = newoff;
    return m_offset;
}

char InputStream::get() {
    if (m_available == 0)
        fillBuffer();
    if (m_available == 0)
        return EOF;
    --m_available;
    ++m_offset;
    return m_buffer[m_used++];
}

void InputStream::getLine(char *str, int count, char delim) {
    int nread = 0;
    int i = 0;
    while (count > 0) {
        if (m_available == 0)
            fillBuffer();
        if (m_available == 0) {
            str[nread ] = '\0';
            return;
        }
        i = 0;
        while (i < count && i < m_available && m_buffer[m_used + i] != delim)
            ++i;
        memcpy(str + nread, m_buffer + m_used, i);
        nread += i;
        m_used -= i;
        m_available -= i;
    }

}

}   // namespace tfs

