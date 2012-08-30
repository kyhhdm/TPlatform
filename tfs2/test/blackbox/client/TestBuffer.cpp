/**
 * @file	TestBuffer.cpp
 *  This file test for suitable buffer size.	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	11/14/2007 06:01:59 PM CST
 *
 */

#include "tfs/tfs.h"
#include "tfs/Client.hpp"
#include "tfs/File.hpp"
#include <sstream>
#include <ctime>
#include <sys/time.h>
using namespace std;
using namespace tfs::api;
const int FILE_SIZE = 1024 * 1024 * 1024;
const int CHUNK_SIZE = 64 * 1024 * 1024;
const int MIN_BUF = 8 * 1024;
const int MAX_BUF = 8 * 1024 * 1024;
const string testfile = "/test/testbuffer";
char tmp[MAX_BUF];
vector<int> bufsize;
struct timeval tstart, tend;
double tused;

void create() {
    FileSystem tfs;
    tfs.createFile(testfile, 0, CHUNK_SIZE);
    AppendStream as(testfile, 0);
    for (int i = 0; i < FILE_SIZE / 1024 / 1024; ++i) {
        as.append(tmp, 1024 * 1024);
        cout <<"\rCreating " <<testfile <<" ... " << i * 1024 * 1024 <<flush;
    }
    cout <<" ... over" <<endl;
    as.close();
}

void test_read_buffer() {
    FileSystem tfs;

    cout <<"Testing read buffer ..." <<endl;
    cout <<"Test file size : " <<FILE_SIZE/1024/1024 <<" M" <<endl;

    if (tfs.existFile(testfile)) {
        FileInfo info = tfs.getFileInfo(testfile);
        if (info.size != FILE_SIZE) {
            tfs.removeFile(testfile);
            create();
        }
    } else
        create();

    InputStream is;
    tfs::File fin;
    for (int i = 0; i < bufsize.size(); ++i) {
        cout <<"Test read with buffer " <<bufsize[i]/1024 <<" K ... " <<flush;
        is.open(testfile, bufsize[i]);
        //fin.open(testfile, tfs::FileOpenRead);
        gettimeofday(&tstart, NULL);
        while(is.read(tmp, bufsize[i]) > 0);
        gettimeofday(&tend, NULL);
        is.close();
        //fin.close();
        tused = 1000000*(tend.tv_sec - tstart.tv_sec)
            + tend.tv_usec - tstart.tv_usec;
        tused /= 1000000;
        cout <<" cost " <<tused <<" seconds" <<endl;
    }
    cout <<"Test read buffer over" <<endl;
}

void test_append_buffer() {
    FileSystem tfs;

    cout <<"Testing append buffer ..." <<endl;
    cout <<"Test file size : " <<FILE_SIZE/1024/1024 <<" M" <<endl;

    AppendStream as;
    tfs::File fout;
    for (int i = 0; i < bufsize.size(); ++i) {
        if (tfs.existFile(testfile))
            tfs.removeFile(testfile);
        tfs.createFile(testfile, 0, CHUNK_SIZE);
        cout <<"Test append with buffer " <<bufsize[i]/1024 <<" K ... " <<flush;
        as.open(testfile, bufsize[i]);
        gettimeofday(&tstart, NULL);
        for (int i = 0; i < FILE_SIZE/1024; ++i)
            as.append(tmp, 1024);
        as.flush();
        gettimeofday(&tend, NULL);
        as.close();
        tused = 1000000*(tend.tv_sec - tstart.tv_sec)
            + tend.tv_usec - tstart.tv_usec;
        tused /= 1000000;
        cout <<" cost " <<tused <<" seconds" <<endl;
    }
    cout <<"Test append buffer over" <<endl;
}

int main() {
    FileSystem tfs;

    bufsize.push_back(8 * 1024);
    bufsize.push_back(16 * 1024);
    bufsize.push_back(32 * 1024);
    bufsize.push_back(64 * 1024);
    bufsize.push_back(128 * 1024);
    bufsize.push_back(256 * 1024);
    bufsize.push_back(512 * 1024);
    bufsize.push_back(1024 * 1024);
    bufsize.push_back(2 * 1024 * 1024);
    bufsize.push_back(4 * 1024 * 1024);
    bufsize.push_back(8 * 1024 * 1024);

    test_append_buffer();
    test_read_buffer();

    return 0;
}
