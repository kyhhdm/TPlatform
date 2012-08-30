/** 
 * @file TestGarbageCollection.hpp
 * unit test of GarbageCollection.
 * 
 * @author Zhifeng YANG
 * @date 2007-08-06
 */
#ifndef _TESTGARBAGECOLLECTION_HPP
#define _TESTGARBAGECOLLECTION_HPP 1

#include <cxxtest/TestSuite.h>
#include "master/GarbageCollection.hpp"
#include "common/IceGenerated.hpp"
using namespace tfs;

class TestActiveChunkManager: public CxxTest::TestSuite
{
    GarbageCollection m_gc;
public:
    void testAll(void){
        Chunk chk;
        chk.version = 0;
        chk.id = 123;
        chk.size = 456;
        Address address;
        address.name = "127.0.0.1";
        address.port = 80;
        
        m_gc.add(address, chk);
        ChunksPtr pChunks = m_gc.get(address);
        Chunk chk2;
        chk2 = (*pChunks)[0];
        TS_ASSERT_SAME_DATA(&chk2, &chk, sizeof(chk));
    }
};

#endif /* _TESTGARBAGECOLLECTION_HPP */
