/**
 * @file     File.hpp
 * Header file for File class.
 *
 * @author     fk
 * @date    2007-05-16
 */

#ifndef  FILE_FILE_HEADER_INC
#define  FILE_FILE_HEADER_INC

#include <common/IceGenerated.hpp>
#include <Transfer.h>

namespace tfs {

using std::string;
using std::vector;

/**
 * This class carry out all direct read, write and append operations 
 * with chunkservers.
 */
class File{
public:
    File();

    ~File();    

    /**
     * Open a file with a specific mode.
     *
     * @param path      The path of the file.
     * @param mode      Open mode of the file.
     * @return      void
     * @throw       ::tfs::api::NoSuchFileOrDir
     */
    void open(const string &path, FileOpenMode mode);

    /**
     * Close the currently opened file.
     *
     * @return  void
     */
    void close();

    /**
     * Read directly from current position.
     *
     * @param buf       Memory position to store the bytes.
     * @param nbytes    Maximum bytes to read.
     * @return      Number of bytes actually read.
     */
    int64_t read(char *buf, int64_t nbytes);

    /**
     * Write to current position.
     *
     * @param buf       Memory position where written bytes is stored.
     * @param nbytes    Maximum bytes to write.
     * @return      Number of bytes actually written.
     */
    int64_t write(char *buf, int64_t nbytes);

    /**
     * Append a new chunk.
     *
     * @param buf       Memory position where written bytes is stored.
     * @param nbytes    Maximum bytes to write, must be no more than chunk size.
     * @return      void 
     */
    void append(const char *buf, int nbytes);

    /**
     * Seek to a certain position.
     *
     * @param offset    The wanted position in a file.
     * @param whence    The way to interpret offset.
     * @return      The offset from beginning after this operation.
     */
    int64_t seek(int64_t offset, int whence);

    /**
     * Return the chunk size of currently opened file.
     * This number is only sensible if current open mode is append.
     */
    FileInfo info() { return m_fileInfo; }

private:
    /// Add a new chunk to current file.
    void addChunk();


    /// Initialize ChunkTransfer.
    void initChunkTransfer(LocatedChunk &chk);

    /// Path of opened file. A blank string indicated no file is opened.
    string m_path;

    /// Address of this client.
    Address m_address;

    /// Current offset of this file.
    int64_t m_offset;

    /// Infomation of located chunks.
    LocatedChunks m_locatedChunks;

    /// Store the max offset within a certain chunk.
    vector<int64_t> m_chunkOffset;

    /// Information of this file.
    FileInfo m_fileInfo;

    /// Index of current chunk.
    int m_chunkIndex;

    /// The chunk index that was just transfered, this is used to
    /// avoid unnessary ChunkTransfer initilization.
    int m_lastChunkIndex;

    /// The chunk that is being operated, only meaningful in append mode.
    LocatedChunk m_currentChunk;

    /// Avaiable size in current chunk, only meaningful in append mode.
    int m_availableSize;

    vector<tfs::slice::TransferPrx> m_vt;

};  // class File

}   // namespace tfs

#endif   /* ----- #ifndef FILE_FILE_HEADER_INC  ----- */
