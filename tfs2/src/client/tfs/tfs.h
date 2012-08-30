/**
 * @file    tfs.h
 *  Interface of tplatform file system.
 * 
 * @author  Fan Kai(fk), Peking University    
 * @date    08/22/2007 09:04:35 AM CST
 *
 */

#ifndef TFS_H
#define TFS_H

#include <string>
#include <vector>
#include <exception>

namespace tfs {

class FileSystem;
class InputStream;
class OutputStream;
class AppendStream;

namespace api {

/** 
 * Base exception type for all exceptions that could be thrown out by tfs. 
 * Instances of this class won't be thrown out, only instances of its 
 * subclasses will be thrown out.
 */
struct TFSException : public std::exception {
public:
    TFSException() throw() { reason = NULL; }
    ~TFSException() throw() { }
    TFSException(const char *str) { reason = str; }
    const char *what() const throw() { return reason; }
private:
    const char *reason;
};

/**
 * Base exception type for exceptions indicating that system has encountered 
 * severe problems and can not recover. 
 * Instances of this class won't be thrown out, only instances of its 
 * subclasses will be thrown out.
 * Possible reasons:
 *  1.Connection error, usually occurs when not be able to connect master.
 *  2.Can not load configuration file(tfs_client.ini).
 *  3.Can not parse configuration file(tfs_client.ini).
 *  4.Fatal internal error. 
 */
struct FatalError : public TFSException {
    FatalError(const char *str) : TFSException(str) { }
};

/**
 * Base exception type for exceptions that would be thrown out if user 
 * specifies improper parameters.
 * Instances of this class won't be thrown out, only instances of its 
 * subclasses will be thrown out.
 * Possible reasons:
 *  1.Replication out of range: the allowed range is 1 - 5
 *  2.Chunk size out of range: the allowed range is 1024*1024 - 128*1024*1024
 *  3.Buffer size out of range: the buffer size should not exceed chunk size
 *  4.Invalid file or directory name: file name should not be ended with '/'
 *  5.Unknown seek option: seek option must be SEEK_SET, SEEK_CUR or SEEK_END
 *  6.Append size exceeds chunk size: in a single append operation, the appended
 *      size must not exceed chunk size.
 */
struct ParameterError : public TFSException { 
    ParameterError(const char *str) : TFSException(str) { }
};

/** 
 * Base exception type for exceptions that would be thrown out if certain 
 * file system operations failed.
 * Instances of this class won't be thrown out, only instances of its 
 * subclasses will be thrown out.
 * Possible reasons:
 *  1.No such file or directory.
 *  2.File or directory already exists.
 *  3.No file is opened for this stream.
 *  4.Can not lock file or directory: when a file is opened, itself and all its
 *      parent directories can not be removed or renamed. 
 *  5.Can not transfer from or to chunkservers: error occurs when transfering 
 *      data with chunkservers.
 *  6.Can not allocate new chunk: there is no space to allocate a new chunk.
 */
class FSError : public TFSException {
public:
    FSError(const char *str) : TFSException(str) { }
};

/* Following is the exceptions that are actually thrown out. */

struct ConnectionError : public FatalError {
    ConnectionError() : FatalError("Connection Error.") { }
};

struct LoadConfigurationError : public FatalError {
    LoadConfigurationError() : FatalError("Cannot load Configuration file.") { }
};

struct ParseConfigurationError : public FatalError {
    ParseConfigurationError() : FatalError("Cannot parse Configuration file.") { }
};

struct InternalError : public FatalError {
    InternalError() : FatalError("Fatal internal Error.") { }
};

struct ReplicationOutOfRange : public ParameterError {
    ReplicationOutOfRange() : ParameterError("Replication out of range.") { }
};

struct ChunkSizeOutOfRange : public ParameterError {
    ChunkSizeOutOfRange() : ParameterError("Chunk size out of range.") { }
};

struct BufferSizeOutOfRange : public ParameterError {
    BufferSizeOutOfRange() : ParameterError("Buffer size out of range.") { }
};

struct InvalidFileOrDirName : public ParameterError {
    InvalidFileOrDirName() : ParameterError("Invalid file or directory name.") { }
};

struct UnknownSeekOption : public ParameterError {
    UnknownSeekOption() : ParameterError("Unknown seek option.") { }
};

struct AppendSizeTooLarge : public ParameterError {
    AppendSizeTooLarge() : ParameterError("Append size too large."){ }
};

struct AuthenticationFail: public FSError {
    AuthenticationFail() : FSError("Authentication fail.") { }
};

struct NoSuchFileOrDir: public FSError {
    NoSuchFileOrDir() : FSError("No such file or directory.") { }
};

struct FileOrDirAlreadyExists: public FSError {
    FileOrDirAlreadyExists() : FSError("File or directory already exists.") { }
};

struct NoFileOpened: public FSError {
    NoFileOpened() : FSError("No file is opened for this stream.") { }
};

struct LockFail: public FSError {
    LockFail() : FSError("Can not lock file or directory.") { }
};

struct TransferFail : public FSError {
    TransferFail() : FSError("Failed to transfer data.") { }
};

struct AllocateFail : public FSError {
    AllocateFail() : FSError("Failed to allocate new chunk.") { }
};

/** Flag constants in FileInfo structure */
const short FileModeTypeDir = 512;
const short FileModeOwnerRead = 256;
const short FileModeOwnerWrite = 128;
const short FileModeOwnerExec = 64;
const short FileModeGroupRead = 32;
const short FileModeGroupWrite = 16;
const short FileModeGroupExec = 8;
const short FileModeOtherRead = 4;
const short FileModeOtherWrite = 2;
const short FileModeOtherExec = 1;

/** Struct to store the basic information of a file or directory. */
struct FileInfo {
    /// Indicate the mode of a file or dir, must be "bit of" of the above constants.
    short flag;
    /// The name of the file or directory.
    std::string name;
    /// Created time of the file or directory.
    int createTime;
    /// Size of the file, invalid for direcotry.
    int64_t size;
    /// Replication of the file, invalid for direcotry.
    short replication;
    /// Chunk size of the file, invalid for direcotry.
    int64_t chunkSize;
};

typedef std::vector<FileInfo> FilesInfo;

/**
 * This class declares input stream which we could use to read data 
 * from a tfs file.
 */
class InputStream {
public:
    /**
     * Construct stream, start a client instance if necessary.
     * @throw   ConnectionError, LoadConfigurationError, ParseConfigurationError
     */
    InputStream();

    /**
     * Construct stream and open a file, start a client instance if necessary.
     * @see     ::tfs::api::InputStream::open
     * @throw   ConnectionError, LoadConfigurationError, ParseConfigurationError
     *          NoSuchFileOrDir, BufferSizeOutOfRange, ConnectionError
     */
    InputStream(const std::string &path, int bufferSize);

    /**
     * Destruct stream, close currently opened file if there is any.
     * @throw   ConnectionError
     */
    ~InputStream();

    /**
     * Open a file as the source of this input stream.
     *
     * @param path          Path of the file to be opened.
     * @param bufferSize    The size of buffer in this stream.
     *                      If this number is 0, client default is used.
     *                      The default value can be set in tfs_client.ini.
     * @throw   NoSuchFileOrDir, BufferSizeOutOfRange, ConnectionError
     */
    void open(const std::string &path, int bufferSize);

    /**
     * Close the current opened file.
     * If no file is opened, nothing happens.
     *
     * @param   void
     * @return  void
     * @throw   ConnectionError
     */
    void close();

    /**
     * Read from current position.
     *
     * @param buf       Storage location for data.
     * @param nbytes    Maximum bytes to read.
     * @return      Number of bytes really read.
     * @throw       NoFileOpened, TransferFail 
     */
    int64_t read(char *buf, int64_t nbytes);

    /**
     * Seek to certain position in a file. 
     * If the result is less than 0, it will be set to 0. 
     * If the result is larger than file size, it will be set to file size.
     *
     * @param offset    Position relative to whence, can be positive or negative
     * @param whence    The way to interpret offset, must be SEEK_SET, SEEK_CUR 
     *                  or SEEK_END
     * @return      The offset from the beginning of file after seek operation.
     * @throw       NoFileOpened, UnknownSeekOption
     */
    int64_t seek(int64_t offset, int whence);

private:
    InputStream(const InputStream &) { }
    InputStream &operator=(const InputStream &is) { return *this; }
    tfs::InputStream *m_istream;
};  // class InputStream

/**
 * This class decalres append stream which we could
 * use to append data to a tfs file.
 */
class AppendStream {
public:
    /** 
     * Constructor stream, start a client instance if necessary.
     * @throw   ConnectionError, LoadConfigurationError, ParseConfigurationError
     */
    AppendStream();

    /**
     * Construct and open a file, start a client instance if necessary.
     * @see     ::tfs::api::AppendStream::open
     * @throw   ConnectionError, LoadConfigurationError, ParseConfigurationError
     *          NoSuchFileOrDir, BufferSizeOutOfRange
     */
    AppendStream(const std::string &path, int bufferSize);

    /**
     * Destructor, close currently opened file if there is any.
     * @throw   ConnectionError
     */
    ~AppendStream();

    /**
     * Open a file as the destination of this append stream.
     *
     * @param path      Path of the file to be opened.
     * @param bufferSize    The size of buffer in this stream.
     *                      If this number is 0, client default is used.
     *                      The default value can be set in tfs_client.ini.
     * @throw   NoSuchFileOrDir, BufferSizeOutOfRange, ConnectionError
     */
    void open(const std::string &path, int bufferSize);

    /**
     * Close the current opened file.
     * If there is still untransfered data in buffer, it will be flushed.
     * If no file is opened, nothing happens.
     *
     * @param   void
     * @return  void
     * @throw   ConnectionError
     */
    void close();

    /**
     * Append to current position.
     * TFS guarantee that all data in a single append operation will be stored
     * in the same chunk, thus the append size must not exceed chunk size.
     * When several clients is appending simultaneously, the order of appended 
     * chunks is not guaranteed.
     *
     * @param buf       Storage location for data.
     * @param nbytes    Number of bytes to append, must be no more than chunk size.
     * @return      void
     * @throw       ConnectionError, NoFileOpened, AppendSizeExceedChunkSize,
     *              AllocateFail, TransferFail
     */
    void append(const char *buf, int nbytes);

    /**
     * Flush output. 
     * Untransfered data in buffer will be transfered and form a new chunk, 
     * however large it is. If there is currently no data in buffer, nothing 
     * happenes.
     *
     * @param   void
     * @return  void
     * @throw   ConnectionError, NoFileOpened, AppendSizeExceedChunkSize, 
     *          AllocateFail, TransferFail
     */
    void flush();

private:
    AppendStream &operator=(const AppendStream &is);
    tfs::AppendStream *m_astream;
};  // class AppendStream

/**
 * This class speicies the configuration of the tfs.
 */ 
struct TFSConfiguration {
    /// The ip address of master, "127.0.0.1" for default
    std::string masterIP;
    /// The listening port of master, "10000" for default
    std::string masterPort;
    /// The default buffer size of tfs in KB, "1024" for default
    int bufferSize;
    /// Specify log level, including DEBUG, INFO, WARNING, ERROR, FATAL, 
    /// "DEBUG" for default
    std::string logLevel;
    /// Speicify the logger file, "tfs_client.log"" for default
    std::string logFile;
    /// Specify user name and key
    std::string username;
    std::string userkey;

    /// Default constructor, do nothing.
    TFSConfiguration(): masterIP("127.0.0.1"),
                        masterPort("10000"),
                        bufferSize(1024),
                        logLevel("DEBUG"),
                        logFile("tfs_client.log") {}

    /// Full constructor.
    TFSConfiguration(const std::string &ip, const std::string port, int size, 
                     const std::string &level, const std::string &file) : 
             masterIP(ip), 
             masterPort(port),
             bufferSize(size),
             logLevel(level),
             logFile(file) {}

    /**
     * Set global configuration.
     * @param conf  The TFSConfiguration to apply.
     * @return      true if set successfully, false if the tfs has been configured.
     * @throw       void
     */
    static bool set(const TFSConfiguration &conf);

    /**
     * Set global configuration file.
     * @param path  The path of TFSConfiguration file.
     * @return      true if set successfully, false if the tfs has been configured.
     * @throw       void
     */
    static bool setFile(const std::string &path);

};  // class TFSConfiguration

/**
 * This class specifies operations we could carry out on tfs system.
 */
class FileSystem {
public:
    /**
     * Constructor.
     * Start a client instance if necessary.
     *
     * @throw ConnectionError, LoadConfigurationError, ParseConfigurationError
     */
    FileSystem();

    ~FileSystem();

    /**
     * Test whether a directory exist.
     *
     * @param path      The path of the directory to be tested.
     * @return      True if path exists, False else.
     */
    bool existDirectory(const std::string &path);

    /**
     * List a directory.
     *
     * @param path      The directory to list.
     *                  The slash '/' in the end of path can be ommitted or not.
     * @return      FilesInfo contains information for all files under path.
     * @throw       NoSuchFileOrDir
     */
    FilesInfo listDirectory(const std::string &path);

    /**
     * Create a directory.
     *
     * @param path  The directory to create.
     * @return      void
     * @throw       FileOrDirAlreadyExists, InvalidFileOrDirName
     */
    void createDirectory(const std::string &path);

    /**
     * Remove a directory.
     * By default the recursive parameter is false and this method can only
     * remove a empty directory. If the recursive paramter is true, this method
     * will remove directory and all contents in the directory as well.
     * If there is opened file in this directory, a LockFail exception will
     * be thrown out.
     *
     * @param path          The directory to delete.
     * @param recursive     Whether remove recursively.
     * @return      void
     * @throw       NoSuchFileOrDir, LockFail
     */
    void removeDirectory(const std::string &path, bool recursive = false);

    /**
     * Rename a directory.
     * If there is opened file in this directory, a LockFail exception will
     * be thrown out.
     *
     * @param src   The directory to be renamed.
     * @param dst   The disired name.
     * @return      void
     * @throw       NoSuchFileOrDir, FileOrDirAlreadyExists, 
     *              LockFail, InvalidFileOrDirName
     */
    void renameDirectory(const std::string &src, const std::string &dst);

    /**
     * Test whether a file exists.
     *
     * @param path      The path of the file to be tested
     * @return      True if path exists, False else
     */
    bool existFile(const std::string &path);

    /**
     * Create a new file.
     *
     * @param path          Path of the file that is to be created.
     * @param replication   Number of chunk replication of this file.
     *                      System support the range of 1-5.
     *                      If the number is 0, use the system default.
     * @param chunkSize     The max chunk size of this file.
     *                      System support the range of 1M-64M.
     *                      If the number is 0, use system default.
     * @return  void
     * @throw   FileOrDirAlreadyExists, ReplicationOutOfRange,
     *          ChunkSizeOutOfRange, InvalidFileOrDirName
     */
    void createFile(const std::string &path, int replication, int chunkSize);

    /**
     * Remove a file.
     *
     * @param path      The file to be removed
     * @return          void
     * @throw           NoSuchFileOrDir, LockFail
     */
    void removeFile(const std::string &path);

    /**
     * Set replication of a file.
     *
     * @param path          The path of the file.
     * @param replication   Number of republications of this file.
     *                      System support the range of 1-5.
     *                      If this number is 0, use the system default. 
     * @return      void
     * @throw       NoSuchFileOrDir, ReplicationOutOfRange
     */
    void setReplication(const std::string &path, int replication);

    /**
     * Rename a file.
     *
     * @param src   The file to be renamed.
     * @param dst   The desired name.
     * @return      void
     * @throw       NoSuchFileOrDir, FileOrDirAlreadyExists,
     *              LockFail, InvalidFileOrDirName
     */
    void renameFile(const std::string &src, const std::string &dst);

    /**
     * Get information of a file.
     *
     * @param path  The path of the file
     * @return  FileInfo representing the info of this file
     * @throw   NoSuchFileOrDir
     */
    FileInfo getFileInfo(const std::string &path);

private:
    tfs::FileSystem *m_fs;
};  // class FileSystem

}   // namespace api

}   // namespace tfs

#endif // TFS_H
