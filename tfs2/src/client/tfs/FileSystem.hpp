/**
 * @file    FileSystem.hpp
 *   Header file of FileSystem class.
 *
 * @author  Fan Kai(FK), Peking University    
 * @date    05/30/2007 11:59:12 PM CST
 */

#ifndef  FILESYSTEM_FILE_HEADER_INC
#define  FILESYSTEM_FILE_HEADER_INC

#include <common/IceGenerated.hpp>
#include <util/Logger.hpp>
#include <string>

namespace tfs {

using std::string;
    
/** @see ::tfs::api::FileSystem  */
class FileSystem {
public:
    FileSystem();

    FilesInfo listDirectory(const string &path);

    bool existDirectory(const string &path);

    void createDirectory(const string &path);

    void removeDirectory(const string &path, bool recursive);

    void renameDirectory(const string &src, const string &dst);

    bool existFile(const string &path);

    void createFile(const string &path, int replication, int chunkSize);

    void removeFile(const string &path);

    void renameFile(const string &src, const string &dst);

    void setReplication(const string &path, int replication);

    FileInfo getFileInfo(const string &path);

};  // class FileSystem

}   // namespace tfs
#endif   /* ----- #ifndef FILESYSTEM_FILE_HEADER_INC  ----- */
