

#include <cxxtest/TestSuite.h>
#include "chunkserver/DiskManager.hpp"
#include "chunkserver/ChunkManager.hpp"
#include "chunkserver/FileUtil.hpp"
#include "chunkserver/ChunkServerConf.hpp"
#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

class TestDiskManager : public CxxTest::TestSuite
{
public:
    void testDiskMgr()
    {
//         DiskManager * pMgr = new DiskManager("./chunk_store");
//         vector<ChunkInfo> v_info;
//         pMgr->getChunks(v_info);

//         vector<string> v_dir;
//         FileUtil::getDirs("./chunk_store",v_dir,0);
//         vector<string>::iterator it = v_dir.begin();
//         for (;it!=v_dir.end();++it){
//             cout<<*it<<endl;
//         }
        
    }
};
