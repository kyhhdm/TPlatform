
#include <cxxtest/TestSuite.h>
#include "datatransfer/XConnector.hpp"
#include "datatransfer/SocketMsg.hpp"
#include "datatransfer/ChunkTransfer.hpp"
//#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

//Logger pLogger = Logger::getInstance("chunkserver");

class TestLocalAppend : public CxxTest::TestSuite
{
public:
    void testAppend()
    {
        ChunkTransfer transfer;
        vector<ChunkServerAddr> vec;
        vec.push_back(ChunkServerAddr("127.0.0.1",9005));
        vec.push_back(ChunkServerAddr("127.0.0.1",9006));
        vec.push_back(ChunkServerAddr("127.0.0.1",9007));
        if (transfer.initConnect(vec) < 0){
            cout<<" init failed"<<endl;
        }
        TS_ASSERT(transfer.addChunk(12345) > 0);
        ifstream infile("/data/film/CD2.avi");
        if (!infile){
            cout<<" no input data"<<endl;
            return;
        }
        char * buf = new char[1024*1024*5];
        for (int i=0; i < 5; ++i){
            memset(buf,0,1024*1024*5);
            infile.read(buf,1024*1024*5);
            TS_ASSERT(transfer.appendData(buf,1024*1024*5) > 0);
        }
        TS_ASSERT(transfer.finishAppend() > 0);
        delete [] buf;            

        char buf2[500];
        memset(buf2,0,500);
        for (int i = 0; i< 100; ++i){
            TS_ASSERT(transfer.addChunk(1000+i) > 0);

            for (int k = 0; k < 10 ; ++k){
                memset(buf2,0,500);
                infile.read(buf2,500);
                TS_ASSERT(transfer.appendData(buf2,500) > 0);
            }
            TS_ASSERT(transfer.finishAppend() > 0)
        }        

    }
};
