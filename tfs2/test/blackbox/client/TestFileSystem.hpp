/**
 * @file    TestFileSystem.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    10/18/2007 10:28:33 PM CST
 *
 */

#ifndef  TESTFILESYSTEM_FILE_HEADER_INC
#define  TESTFILESYSTEM_FILE_HEADER_INC

#include <cxxtest/TestSuite.h>
#include <tfs/tfs.h>
#include <tfs/FileSystem.hpp>
#include <iostream>

namespace {

using namespace tfs::api;
using namespace std;

class TestFileSystem : public CxxTest::TestSuite {
public:
    void testSimpleDirectory() {
        try {
            FileSystem tfs;
            if(tfs.existDirectory("/test/dir")) {
                tfs.removeDirectory("/test/dir", true);
            }
            TS_ASSERT(!tfs.existDirectory("/test/dir"));
            tfs.createDirectory("/test/dir");
            TS_ASSERT(tfs.existDirectory("/test/dir"));
            tfs.removeDirectory("/test/dir");
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        } catch (...) {
            TS_FAIL("EXC");
        }
    }

    void testSimpleFile() {
        try {
            FileSystem tfs;
            if (tfs.existFile("/test/file")) {
                tfs.removeFile("/test/file");
            }
            if (tfs.existFile("/test/file2")) {
                tfs.removeFile("/test/file2");
            }
            TS_ASSERT(!tfs.existFile("/test/file"));
            TS_ASSERT(!tfs.existFile("/test/file2"));
            
            tfs.createFile("/test/file", 3, 0);
            TS_ASSERT(tfs.existFile("/test/file"));

            tfs.renameFile("/test/file", "/test/file2");
            TS_ASSERT(!tfs.existFile("/test/file"));
            TS_ASSERT(tfs.existFile("/test/file2"));

            tfs.removeFile("/test/file2");
            TS_ASSERT(!tfs.existFile("/test/file2"));
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }

    void testDirectory() {
        try {
            FileSystem tfs;
            if (tfs.existDirectory("/test"))
                tfs.removeDirectory("/test", true);
            tfs.createDirectory("/test/dir/dir1");
            TS_ASSERT(tfs.existDirectory("/test/dir"));
            TS_ASSERT(tfs.existDirectory("/test/dir/dir1"));

            FilesInfo infos = tfs.listDirectory("/test");
            TS_ASSERT_EQUALS(infos.size(), 1);

            tfs.renameDirectory("/test/dir", "/test/dir2");
            TS_ASSERT(tfs.existDirectory("/test/dir2/dir1"));
            TS_ASSERT(!tfs.existDirectory("/test/dir/dir1"));

            // test getFileInfo
            FileInfo info = tfs.getFileInfo("/test/dir2/");
            TS_ASSERT((info.flag & FileModeTypeDir) != 0);
            TS_ASSERT_SAME_DATA(info.name.c_str(), "dir2/", 4);

            tfs.createFile("/test/dir2/file", 3, 0);
            infos = tfs.listDirectory("/test/dir2");
            TS_ASSERT_EQUALS(infos.size(), 2);

            TS_ASSERT(!tfs.existDirectory("/test/dir2/dir3/dir4"));
            tfs.createDirectory("/test/dir2/dir3/dir4");
            TS_ASSERT(tfs.existDirectory("/test/dir2/dir3"));
            TS_ASSERT(tfs.existDirectory("/test/dir2/dir3/dir4"));

            tfs.renameDirectory("/test/dir2/dir3", "/test/dir");
            TS_ASSERT(!tfs.existDirectory("/test/dir2/dir3/dir4"));
            TS_ASSERT(tfs.existDirectory("/test/dir/dir4"));

            infos = tfs.listDirectory("/test");
            TS_ASSERT_EQUALS(infos.size(), 2);

            tfs.removeDirectory("/test", true);
            TS_ASSERT(!tfs.existFile("/test/dir2/dir1"));
            TS_ASSERT(!tfs.existFile("/test/dir2/testfile"));
            TS_ASSERT(!tfs.existFile("/test/dir2"));
            TS_ASSERT(!tfs.existFile("/test/dir"));
            TS_ASSERT(!tfs.existFile("/test"));
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }

    void testFile() {
        try {
            FileSystem tfs;
            if (tfs.existDirectory("/test")) {
                tfs.removeDirectory("/test");
            }
            TS_ASSERT(!tfs.existFile("/test/file"));
            TS_ASSERT(!tfs.existFile("/test/file2"));
            
            tfs.createFile("/test/file", 3, 0);
            TS_ASSERT(tfs.existFile("/test/file"));

            FileInfo info = tfs.getFileInfo("/test/file");
            TS_ASSERT_EQUALS(info.replication, 3);
            TS_ASSERT_EQUALS(info.size, 0);
            TS_ASSERT_EQUALS(info.chunkSize, 64*1024*1024);
            TS_ASSERT_EQUALS(info.flag & FileModeTypeDir , 0);
            TS_ASSERT_EQUALS(info.flag & FileModeTypeDir , 0);
            TS_ASSERT_SAME_DATA(info.name.c_str(), "file", 4);

            tfs.setReplication("/test/file", 5);
            AppendStream as("/test/file", 1024);
            for (int i = 0; i < 1024; ++i)
                as.append("helloworld", 10);
            as.close();

            info = tfs.getFileInfo("/test/file");
            TS_ASSERT_EQUALS(info.replication, 5);
            TS_ASSERT_EQUALS(info.size, 10240);
            TS_ASSERT_EQUALS(info.chunkSize, 64*1024*1024);
            TS_ASSERT_EQUALS(info.flag & FileModeTypeDir , 0);
            TS_ASSERT_EQUALS(info.flag & FileModeTypeDir , 0);
            TS_ASSERT_SAME_DATA(info.name.c_str(), "file", 4);

            tfs.renameFile("/test/file", "/test/file2");
            TS_ASSERT(!tfs.existFile("/test/file"));
            TS_ASSERT(tfs.existFile("/test/file2"));

            tfs.renameFile("/test/file2", "/test/dir/file2");
            TS_ASSERT(!tfs.existFile("/test/file2"));
            TS_ASSERT(tfs.existFile("/test/dir/file2"));

            tfs.renameFile("/test/dir/file2", "/test/file2");
            TS_ASSERT(!tfs.existFile("/test/file"));
            TS_ASSERT(tfs.existFile("/test/file2"));
            TS_ASSERT(tfs.existDirectory("/test/dir"));

            tfs.removeFile("/test/file2");
            TS_ASSERT(!tfs.existFile("/test/file2"));

            tfs.removeDirectory("/test", true);
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }

    void testDirectoryException() {
        try {
            // TODO all following comments are tests that have not passed
            FileSystem tfs;

            tfs.createDirectory("/test/dir1");
            tfs.createDirectory("/test/dir2");

            TS_ASSERT_THROWS(tfs.createDirectory("/test"), FileOrDirAlreadyExists);

            TS_ASSERT_THROWS(tfs.createDirectory("te"), InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.removeDirectory("/test/unexist"), NoSuchFileOrDir);

            TS_ASSERT_THROWS(tfs.removeDirectory("test"), InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.listDirectory("/test/unexist"), NoSuchFileOrDir);

            TS_ASSERT_THROWS(tfs.listDirectory("test"), InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.renameDirectory("/test/dir1", "/test/dir2"),
                    FileOrDirAlreadyExists);

            TS_ASSERT_THROWS(tfs.renameDirectory("/test/unexist", "/test/unexist2"),
                    NoSuchFileOrDir);

            TS_ASSERT_THROWS(tfs.renameDirectory("/test/dir1", "test/unexist2"),
                    InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.renameDirectory("/test", "/test/dir1"),
                    InvalidFileOrDirName);

            //tfs.createFile("/test/file", 0, 0);
            //AppendStream as("/test/file", 1024);
            //TS_ASSERT_THROWS(tfs.removeFile("/test/file"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.renameFile("/test/file", "/test/file2"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.renameDirectory("/test", "/test2"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.removeDirectory("/test"),
            //        LockFail);
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }

    void testFileException() {
        try {
            // TODO all following comments are tests that have not passed
            FileSystem tfs;
            tfs.createFile("/test/file", 0, 0);
            tfs.createFile("/test/file2", 0, 0);

            TS_ASSERT_THROWS(tfs.createFile("/test/file", 0, 0), 
                    FileOrDirAlreadyExists);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", -1, 0), 
                    ReplicationOutOfRange);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 10, 0), 
                    ReplicationOutOfRange);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist2/", 0, 0), 
                    InvalidFileOrDirName);
            TS_ASSERT_THROWS(tfs.createFile("test/unexist2", 0, 0), 
                    InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 0, - 1), 
                    ChunkSizeOutOfRange);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 0, 1000), 
                    ChunkSizeOutOfRange);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 0, 1024*1024 - 1), 
                    ChunkSizeOutOfRange);
            TS_ASSERT_THROWS_NOTHING(tfs.createFile("/test/unexist", 0, 1024*1024))
            TS_ASSERT_THROWS_NOTHING(tfs.removeFile("/test/unexist"));
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 0, 1000*1000*1000), 
                    ChunkSizeOutOfRange);
            TS_ASSERT_THROWS(tfs.createFile("/test/unexist", 0, 128*1024*1024 + 1), 
                    ChunkSizeOutOfRange);
            TS_ASSERT_THROWS_NOTHING(tfs.createFile("/test/unexist", 0, 128*1024*1024));
            TS_ASSERT_THROWS_NOTHING(tfs.removeFile("/test/unexist"));

            TS_ASSERT_THROWS(tfs.setReplication("/test/file", -1), 
                    ReplicationOutOfRange);
            TS_ASSERT_THROWS(tfs.setReplication("/test/file", 6), 
                    ReplicationOutOfRange);
            TS_ASSERT_THROWS_NOTHING(tfs.setReplication("/test/file", 5));
            TS_ASSERT_THROWS_NOTHING(tfs.setReplication("/test/file", 0)); 

            TS_ASSERT_THROWS(tfs.renameFile("/test/file", "/test/file2"), 
                    FileOrDirAlreadyExists);
            TS_ASSERT_THROWS(tfs.renameFile("/test/unexist", "/test/unexist2"), 
                    NoSuchFileOrDir);
            TS_ASSERT_THROWS(tfs.renameFile("/test/file", "/test/unexsit/"), 
                    InvalidFileOrDirName);

            TS_ASSERT_THROWS(tfs.getFileInfo("/test/unexist"),
                    NoSuchFileOrDir);

            TS_ASSERT_THROWS(tfs.removeFile("/test/unexist"),
                    NoSuchFileOrDir);

            //AppendStream as("/test/file", 1024);
            //TS_ASSERT_THROWS(tfs.removeFile("/test/file"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.renameFile("/test/file", "/test/file2"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.renameDirectory("/test", "/test2"),
            //        LockFail);
            //TS_ASSERT_THROWS(tfs.remove("/test"),
            //        LockFail);

            tfs.removeDirectory("/test", true);
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }
};

}

#endif   /* ----- #ifndef TESTFILESYSTEM_FILE_HEADER_INC  ----- */

