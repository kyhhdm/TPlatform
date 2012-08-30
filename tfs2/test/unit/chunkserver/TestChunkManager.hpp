
/**
 * @file   TestChunkManager.cpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Thu Oct 11 11:28:20 2007
 * 
 * @brief  
 * 
 * 
 */

#include <cxxtest/TestSuite.h>
#include "chunkserver/ChunkManager.hpp"
#include "chunkserver/ChunkServerConf.hpp"
#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

Logger pLogger = Logger::getInstance("chunkserver");


class TestChunkManager : public CxxTest::TestSuite
{
public:
    void testCommit()
    {

        ChunkServerConf::setConfPath("tfs_chunkserver_test.ini");


        ChunkServerConf * pConf=ChunkServerConf::getInstance();
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(new RollingFileAppender((pConf->LOG_PATH).c_str(), 5*1024, 5));

        //@todo if the LOG_PATH don't exsist, return -1
        //     if(append_1==NULL){
        //         return -1;
        //     }
        append_1->setName("appender1");
        append_1->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
        Logger::getRoot().addAppender(append_1);

        
        ChunkManager *pManager=new ChunkManager;
        TS_ASSERT(pManager->init());

        ofstream outfile;
        int64_t chunk_id=123456789123LL;
        TS_ASSERT(pManager->getNewChunkOutStream(outfile,chunk_id));

        int i = 0;
        for(int k = 0;k < 64000;k ++){
			outfile << char(i%10);
			i ++;  
		}

        TS_ASSERT(pManager->commitChunk(chunk_id));
                          
    }
};
