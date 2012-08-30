/**
 * @file    TestStream.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    10/18/2007 08:02:57 PM CST
 *
 */

#ifndef  TESTSTREAM_FILE_HEADER_INC
#define  TESTSTREAM_FILE_HEADER_INC

#include <cxxtest/TestSuite.h>
#include <tfs/tfs.h>
#include <iostream>
using namespace tfs::api;
using namespace std;

namespace {
    const int NUM = 30000000;
    const int CHUNK_SIZE = 4 * 1024 * 1024;
    const int BUF_SIZE = 128 * 1024;
    const int MAX_APPEND_SIZE = 128 * 1024;
}

class TestStream : public CxxTest::TestSuite {
private:
    char data[NUM], tmp[NUM * 2];
public:
    void testSimpleAppendRead() {
		try {
			FileSystem tfs;

			// Initialize data
			for (int i = 0; i < NUM; ++i) 
				data[i] = i*339%7 +'a';

			// create file "/test/file" and append data 
			if (tfs.existFile("/test/file"))
				tfs.removeFile("/test/file");
			TS_ASSERT(!tfs.existFile("/test/file"));
			tfs.createFile("/test/file", 3, CHUNK_SIZE);
			TS_ASSERT(tfs.existFile("/test/file"));
			AppendStream as("/test/file", BUF_SIZE);
            as.append(data, CHUNK_SIZE/4);
			as.close();
            //system("sleep 1");

            bzero(tmp, NUM);
			InputStream is("/test/file", BUF_SIZE);
			int n = is.read(tmp, CHUNK_SIZE/4);
			TS_ASSERT_EQUALS(n, CHUNK_SIZE/4);
			TS_ASSERT(memcmp(data, tmp, n) == 0);
		} catch (TFSException &ex) {
			TS_FAIL(ex.what());
        }
    }

    void testBlankAppendRead() {
        try {
			FileSystem tfs;
			// create file "/test/file" and append data 
			if (tfs.existFile("/test/file"))
				tfs.removeFile("/test/file");
			tfs.createFile("/test/file", 0, CHUNK_SIZE);
			TS_ASSERT(tfs.existFile("/test/file"));
			AppendStream as("/test/file", CHUNK_SIZE);
            as.close();
            InputStream is("/test/file", CHUNK_SIZE);
            int n = is.read(tmp, NUM);
            TS_ASSERT_EQUALS(n, 0);
            is.close();
        } catch (TFSException &ex) {
			TS_FAIL(ex.what());
        }
    }

    void testAppendRead() {
		try {
			FileSystem tfs;

			// create file "/test/file" and append data 
			if (tfs.existFile("/test/file"))
				tfs.removeFile("/test/file");
			TS_ASSERT(!tfs.existFile("/test/file"));
			tfs.createFile("/test/file", 0, CHUNK_SIZE);
			TS_ASSERT(tfs.existFile("/test/file"));
			AppendStream as("/test/file", 0);
			int num = 0, n;
			while (num < NUM - MAX_APPEND_SIZE) {
				n = rand() % MAX_APPEND_SIZE; 
				as.append(data + num, n);
				num += n;
			}
            cout <<"append over" <<endl;

            system("sleep 1");

			InputStream is("/test/file", 0);
			int size = is.seek(0, SEEK_END);
			is.seek(0, SEEK_SET);

			// test 1, read all data
			n = is.read(tmp, size);
			//TS_ASSERT_SAME_DATA(data, tmp, n);
			TS_ASSERT(memcmp(data, tmp, n) == 0);
            cout <<"test 1 ok" <<endl;

			// test 2, read the first half data
			is.seek(0, SEEK_SET);
			n = is.read(tmp, size/2);
			//TS_ASSERT_SAME_DATA(data, tmp, n);
			TS_ASSERT(memcmp(data, tmp, n) == 0);
			cout <<"test 2 ok" <<endl;

			// test3, read the last half data
			n = is.read(tmp, size);
			//TS_ASSERT_SAME_DATA(data + size/2, tmp, n);
			TS_ASSERT(memcmp(data + size/2 , tmp, n) == 0);
			cout <<"test 3 ok" <<endl;

			// test4, read the last 1000 bytes
			is.seek(-1000, SEEK_CUR);
			n = is.read(tmp, NUM);
			//TS_ASSERT_SAME_DATA(data + size - 1000, tmp, n);
			TS_ASSERT(memcmp(data + size -1000, tmp, n) == 0);
			cout <<"test 4 ok" <<endl;

			// test5, seak to middle, and read the last haft data
			is.seek(-NUM/2, SEEK_END);
			n = is.read(tmp, NUM);
			//TS_ASSERT_SAME_DATA(data + size - NUM/2, tmp, n);
			TS_ASSERT(memcmp(data + size -NUM/2, tmp, n) == 0);
			cout <<"test 5 ok" <<endl;

			// test6, read all data with many random read
			n = 0; int t = 0;
			is.seek(0, SEEK_SET);
			while (is.seek(0, SEEK_CUR) < size){
				t = rand() % CHUNK_SIZE * 7;
				is.read(tmp+n, t);
				n += t;
			}
			//TS_ASSERT_SAME_DATA(data, tmp, size);
			TS_ASSERT(memcmp(data, tmp, size) == 0);
			cout <<"test 6 ok" <<endl;

			// test7, test append again
			num = 0;
			while (num < NUM/2 - MAX_APPEND_SIZE) {
				n = rand() % MAX_APPEND_SIZE; 
				as.append(data + num, n);
				num += n;
			}
            as.close();
            system("sleep 1");
			InputStream iss("/test/file", 0);
            size = iss.seek(0, SEEK_END);
			iss.seek(-size, SEEK_END);
			n = iss.read(tmp, size);
			TS_ASSERT_EQUALS(n, size);
			TS_ASSERT(memcmp(data, tmp, size-num) == 0);
			TS_ASSERT(memcmp(data, tmp+size-num, num) == 0);
			 cout <<"test 7 ok" <<endl;
		} catch (TFSException &ex) {
			TS_FAIL(ex.what());
        }
    }

    void xestSeek() {
        try {
            InputStream f;
            f.open("/test/file", 0);
            int len = f.seek(0, SEEK_END);
            f.seek(0, SEEK_SET);

            int p = f.seek(len/2, SEEK_CUR);
            TS_ASSERT_EQUALS(p, len/2);

            p = f.seek(len, SEEK_CUR);
            TS_ASSERT_EQUALS(p, len);

            p = f.seek(len, SEEK_CUR);
            TS_ASSERT_EQUALS(p, len);

            p = f.seek(0 - len/2, SEEK_CUR);
            TS_ASSERT_EQUALS(p, len - len/2);

            p = f.seek(0, SEEK_CUR);
            TS_ASSERT_EQUALS(p, len - len/2);

            p = f.seek(0 - len, SEEK_CUR);
            TS_ASSERT_EQUALS(p, 0);

            p = f.seek(0, SEEK_SET);
            TS_ASSERT_EQUALS(p, 0);

            p = f.seek(-777, SEEK_SET);
            TS_ASSERT_EQUALS(p, 0);

            p = f.seek(len/2, SEEK_SET);
            TS_ASSERT_EQUALS(p, len/2);

            p = f.seek(len, SEEK_SET);
            TS_ASSERT_EQUALS(p, len);

            p = f.seek(len*2, SEEK_SET);
            TS_ASSERT_EQUALS(p, len);

            p = f.seek(0, SEEK_END);
            TS_ASSERT_EQUALS(p, len);

            p = f.seek(-len/2, SEEK_END);
            TS_ASSERT_EQUALS(p, len - len/2);

            p = f.seek(-len, SEEK_END);
            TS_ASSERT_EQUALS(p, 0);

            p = f.seek(999, SEEK_END);
            TS_ASSERT_EQUALS(p, len);

            TS_ASSERT_THROWS( p = f.seek(456, 123), UnknownSeekOption);
        } catch (TFSException &ex) {
            TS_FAIL(ex.what());
        }
    }

};  // class TestStream

#endif   /* ----- #ifndef TESTSTREAM_FILE_HEADER_INC  ----- */

