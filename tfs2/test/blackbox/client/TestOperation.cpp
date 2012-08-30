/**
 * @file    TestOperation.cpp
 *  This file test for master operation efficiency. 
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    11/12/2007 12:50:07 AM CST
 *
 */

#include <tfs/tfs.h>
#include <tfs/Client.hpp>
#include <ctime>
#include <iostream>
#include <sys/time.h>
#include <sstream>
using namespace std;
using namespace tfs::api;

FileSystem fs;
string testdir;
string testfile;

// Mock the real situation.
void testMock() {
    stringstream ss;
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
        fs.createFile(testfile, 0, 0);
        infos = fs.listDirectory(testdir);
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
            for (int k = 0; k < 100; ++k) {
                is.open(testfile, 0);
                is.close();
            }
        }
        fs.removeFile(testfile);
    }
    fs.removeDirectory(testdir);
}

int main() {
    FileSystem fs;
    const int NUM = 10000;
    string name[NUM + 1];
    assert(NUM >= 100);
    struct timeval tstart, tend;
    double tused;
    stringstream ss;
    for (int i = 0; i < NUM + 1; ++i) {
        ss <<"/test_" <<tfs::Client::address().name 
           <<tfs::Client::address().port <<"/" << i;
        ss >>name[i];
        ss.clear();
    }

    // Test when mock the real situation.
    ss <<"/test/op_" <<tfs::Client::address().name <<tfs::Client::address().port;
    ss >>testdir;
    if (fs.existDirectory(testdir))
        fs.removeDirectory(testdir, true);
    gettimeofday(&tstart, NULL);
    testMock();
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<"Mock finished in " <<tused <<" seconds" <<endl <<endl;

    return 0;

    // Test mkdir
    if (fs.existDirectory("/test/testop"))
        fs.removeDirectory("/test/testop", true);
    gettimeofday(&tstart, NULL);
    for (int i = 1; i < NUM + 1; ++i) {
        tfs::Client::service()->mkdir(name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" mkdir finished in " <<tused <<" seconds" <<endl;

    // Test renamedir
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->renamedir(name[i+1], name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" renamedir finished in " <<tused <<" seconds" <<endl;

    // Test rmdir
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->rmdir(name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" rmdir finished in " <<tused <<" seconds" <<endl;

    return 0;

    // Test create
    gettimeofday(&tstart, NULL);
    for (int i = 1; i < NUM + 1; ++i) {
        tfs::Client::service()->create(name[i], 3, 10000000 );
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" create finished in " <<tused <<" seconds" <<endl;

    // Test rename
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->rename(name[i+1], name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" rename finished in " <<tused <<" seconds" <<endl;

    // Test getFileInfo 
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->getFileInfo(name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getFileInfo finished in " <<tused <<" seconds" <<endl;

    // Test addChunk
    tfs::LocatedChunk lc[NUM];
    AppendStream as(name[0], 0);
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[0]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" addChunk finished in " <<tused <<" seconds" <<endl;

    // Test completeWrittenChunk
    for (int i = 0; i < NUM; ++i)
        lc[i].chk.size = 64 * 1024 * 1024;
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" completeWrittenChunk finished in " <<tused <<" seconds" <<endl;
    as.close();

    // Test abandonAddChunk
    as.open(name[0], 0);
    for (int i = 0; i < NUM; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[0]);
    }
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->abandonAddChunk(lc[i].chk);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" abandonAddChunk finished in " <<tused <<" seconds" <<endl;
    as.close();

    // Test getChunksInfo (0 chunk)
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[1]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(0 chunk) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (20 chunk)
    as.open(name[2], 0);
    for (int i = 0; i < 20; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[2]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[2]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(20 chunks) finished in " <<tused <<" seconds" <<endl;

 
    // Test getChunksInfo (50 chunk)
    as.open(name[3], 0);
    for (int i = 0; i < 50; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[3]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[3]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(50 chunks) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (100 chunk)
    as.open(name[4], 0);
    for (int i = 0; i < 100; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[4]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[4]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(100 chunks) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (150 chunk)
    as.open(name[5], 0);
    for (int i = 0; i < 150; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[5]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[5]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(150 chunks) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (200 chunk)
    as.open(name[6], 0);
    for (int i = 0; i < 200; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[6]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[6]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(200 chunks) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (300 chunk)
    as.open(name[7], 0);
    for (int i = 0; i < 300; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[7]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[7]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(300 chunks) finished in " <<tused <<" seconds" <<endl;

    // Test getChunksInfo (500 chunk)
    as.open(name[8], 0);
    for (int i = 0; i < 500; ++i) {
        lc[i] = tfs::Client::service()->addChunk(tfs::Client::address(),
                                              name[8]);
        lc[i].chk.size = 64 * 1024 * 1024;
        tfs::Client::service()->completeWrittenChunk(lc[i]);
    }
    as.close();
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::LocatedChunks lcs = tfs::Client::service()->getChunksInfo(
                tfs::Client::address(), name[8]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" getChunksInfo(500 chunks) finished in " <<tused <<" seconds" <<endl;



    // Test open
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->open(tfs::Client::address(),
                                     name[i], tfs::FileOpenRead);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" open finished in " <<tused <<" seconds" <<endl;

    // Test close
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        tfs::Client::service()->close(tfs::Client::address(),
                                     name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" close finished in " <<tused <<" seconds" <<endl;
    // Test removeFile
    gettimeofday(&tstart, NULL);
    for (int i = 0; i < NUM; ++i) {
        fs.removeFile(name[i]);
    }
    gettimeofday(&tend, NULL);
    tused = 1000000*(tend.tv_sec - tstart.tv_sec)
        + tend.tv_usec - tstart.tv_usec;
    tused /= 1000000;
    cout <<NUM <<" removeFile finished in " <<tused <<" seconds" <<endl;
}

