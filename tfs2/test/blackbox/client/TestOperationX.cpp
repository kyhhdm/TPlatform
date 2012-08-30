/**
 * @file    TestOperation.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    11/12/2007 12:50:07 AM CST
 *
 */

#ifndef  TESTOPERATION_FILE_HEADER_INC
#define  TESTOPERATION_FILE_HEADER_INC

#include <tfs/tfs.h>
#include <tfs/Client.hpp>
#include <ctime>
#include <iostream>
#include <sys/time.h>
#include <sstream>
using namespace std;
using namespace tfs::api;

FileSystem fs;

void test() {
    stringstream ss;
    ss <<"/test" <<tfs::Client::address().port;
    string testdir;
    string testfile;
    ss >>testdir;

    if (fs.existDirectory(testdir))
        fs.removeDirectory(testdir, true);
    cout <<"Create dir :" <<testdir <<endl;
    fs.createDirectory(testdir);
    fs.renameDirectory(testdir, testdir + "2");
    fs.renameDirectory(testdir + "2", testdir);
    AppendStream as;
    InputStream is;
    FilesInfo infos;
    for (int i = 0; i < 10; ++i) {
        ss.clear();
        ss <<testdir <<"/file"  <<i;
        ss >>testfile;
        cout <<"Create file :" <<testfile <<endl;
        fs.createFile(testfile, 0, 0);
        infos = fs.listDirectory(testdir);
        cout <<"Have " <<infos.size() <<" files in total" <<endl;
        fs.setReplication(testfile, 5);
        fs.renameFile(testfile, testfile + "2");
        fs.renameFile(testfile + "2", testfile);

        for (int j = 0; j < 10; ++j) {
            as.open(testfile, 0);
            // Chunk operation
            tfs::LocatedChunk lc;
            tfs::LocatedChunks lcs;
            lc = tfs::Client::service()->addChunk(tfs::Client::address(),
                                                  testfile);
            tfs::Client::service()->abandonAddChunk(lc.chk);
            for (int k = 0; k < 10; ++k) {
                lc = tfs::Client::service()->addChunk(tfs::Client::address(),
                                                      testfile);
                lc.chk.size = 60 * 1024 * 1024;
                tfs::Client::service()->completeWrittenChunk(lc);
            }
            as.close();
            lcs = tfs::Client::service()->getChunksInfo(tfs::Client::address(),
                                                        testfile);
            cout <<"Chunk number of " <<testfile <<": " <<lcs.size() <<endl;
            for (int k = 0; k < 100; ++k) {
                is.open(testfile, 0);
                is.close();
            }
        }
        cout <<"Remove file :" <<testfile <<endl;
        fs.removeFile(testfile);
    }
    cout <<"Remove dir :" <<testdir <<endl;
    fs.removeDirectory(testdir);
}

int main() {
    struct timeval tstart, tend;
    double tused;
    gettimeofday(&tstart, NULL);
    test();
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<tused <<endl;


    if (fs.existDirectory("/test/testop"))
        fs.removeDirectory("/test/testop", true);
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < 1000; ++i) {
        fs.createDirectory("/test/testop");
        fs.removeDirectory("/test/testop");
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<tused <<endl;

    fs.createDirectory("/test/testop");
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < 500; ++i) {
    //    fs.renameDirectory("/test/testop", "/test/testop2");
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<tused <<endl;

    gettimeofday(&tstart, NULL);
    for (int i = 0; i < 1000; ++i) {
        fs.createFile("/test/testfile", 0, 0);
        fs.removeFile("/test/testfile");
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<tused <<endl;
}
#endif   /* ----- #ifndef TESTOPERATION_FILE_HEADER_INC  ----- */

