

#include <cxxtest/TestSuite.h>
#include "datatransfer/XConnector.hpp"
#include "datatransfer/SocketMsg.hpp"
//#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

//Logger pLogger = Logger::getInstance("chunkserver");

class TestRemoteDealer : public CxxTest::TestSuite
{
public:
    void testListChunk()
    {
        const string strip = "127.0.0.1";
        int port = 9018;
        XConnector conn;
        if (!conn.init(strip,port)){
            cout<<"Connect to "<< strip <<":"<< port <<" failed"<<endl;
            return;
        }
        vector<ChunkStatus> vec = conn.getChunks();
        vector<ChunkStatus>::iterator it = vec.begin();
        for (; it != vec.end(); ++it){
            cout<< it->m_id <<" "<< it->m_size <<endl;
        }
        cout<<"Sum:"<<vec.size()<<endl;
    }
};
