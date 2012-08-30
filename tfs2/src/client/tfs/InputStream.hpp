/**
 * @file     InputStream.hpp
 *         TFS InputStream provided to user
 * @author    fk
 * @date    2007-05-23
 */

#ifndef  INPUTSTREAM_FILE_HEADER_INC
#define  INPUTSTREAM_FILE_HEADER_INC

#include "File.hpp"

namespace tfs {

/**
 * This class declares input stream which we could 
 * use to get data from a tfs file.
 */
class InputStream {
public:
    InputStream();

    ~InputStream();

    void open(const string &path, int bufSize);

    void close();

    int64_t read(char *buf, int64_t nbytes);

    int64_t seek(int64_t offset, int whence);

    void getLine(char *str, int count, char delim = '\n');

    char get();

    

private:
    /// Fill the buffer.
    void fillBuffer();

    /// Pointer to a File class
    File * m_file;

    /// Pointer to buffer
    char * m_buffer;

    /// Size of buffer
    int64_t m_bufferSize;

    /// Offset in this stream
    int64_t m_offset;

    /// Offset in buffer 
    int64_t m_used;

    /// available bytes in buffer
    int64_t m_available;

    /// Indicate whether any file is opend
    bool m_opened;

};  // class InputStream

}   // namespace tfs

#endif   /* ----- #ifndef INPUTSTREAM_FILE_HEADER_INC  ----- */
