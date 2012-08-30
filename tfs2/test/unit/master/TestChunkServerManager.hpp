/** 
 * @file TestChunkServerManager.hpp
 * test of ChunkServerManager.
 * 
 * @author Zhifeng YANG
 * @date 2007-07-11
 */
#ifndef _TESTCHUNKSERVERMANAGER_HPP
#define _TESTCHUNKSERVERMANAGER_HPP 1
#include "master/ChunkServerManager.hpp"
#include "common/IceGenerated.hpp"

class TestChunkServerManager: public CxxTest::TestSuite
{
public:
    void testException()
        {
            ::tfs::ChunkServerManager csm(32);
            ::tfs::Address address;
            address.name = "local";
            address.port = 255;
            TS_ASSERT_THROWS(csm.remove(address), ::tfs::UnknownChunkServer);
            csm.enroll(address);
            TS_ASSERT_THROWS_NOTHING(csm.remove(address));
        }
    void testAddRemove()
        {
            ::tfs::ChunkServerManager csm(32);
            ::tfs::Address address;
            address.name = "local";
            address.port = 255;
            tfs::Chunk chk;
            tfs::Chunks chks;
            for (int i = 0; i < 256; i++){
                chk.id = i;
                chk.size = i*1024;
                chks.push_back(chk);
            }
            csm.enroll(address);
            TS_ASSERT(csm.isEnrolled(address));
            
            csm.add(address, chks);
            csm.remove(address, chk);
            tfs::ChunksPtr pChunks = csm.get(address);

            TS_ASSERT_EQUALS(pChunks->size(), 255);
        }
    
};
#endif /* _TESTCHUNKSERVERMANAGER_HPP */
