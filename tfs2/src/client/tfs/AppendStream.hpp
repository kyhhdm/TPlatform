/**
 * @file	AppendStream.hpp
 *  TFS append stream provided to user
 * @author	Fan Kai(FK), Peking University	
 * @date	07/11/2007 11:36:45 PM CST
 *
 */

#ifndef  APPENDSTREAM_FILE_HEADER_INC
#define  APPENDSTREAM_FILE_HEADER_INC

#include "File.hpp"

namespace tfs {

/**
 * This class decalres append stream which we could
 * use to append one or more chunks to a tfs file.
 */
class AppendStream {
public:
    AppendStream();

    ~AppendStream();

    void open(const string &path, int bufSize);

    void close();
    
    void append(const char * buf, int64_t nbytes);

    void flush();

private:
    /// Pointer to a File class.
    File *m_pfile;

    /// Max chunk size.
    int m_chunkSize;

    /// Size of the opened file.
    int64_t m_fileSize;

    /// Pointer to buffer
    char *m_buffer;

    /// Size of buffer
    int m_bufferSize;

    /// Filled bytes in buffet
    int m_nfilled;

    /// Offset in current stream
    int64_t m_offset;

    /// Indicate whether any file is opened.
    bool m_opened;

};  // class AppendStream

}	// namespace tfs

#endif   /* ----- #ifndef APPENDSTREAM_FILE_HEADER_INC  ----- */

