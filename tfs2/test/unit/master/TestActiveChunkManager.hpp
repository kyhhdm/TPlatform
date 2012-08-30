/** 
 * @file TestActiveChunkManager.hpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-06-28
 */
#ifndef _TESTACTIVECHUNKMANAGER_HPP
#define _TESTACTIVECHUNKMANAGER_HPP 1

#include <cxxtest/TestSuite.h>
#include "master/ActiveChunkManager.hpp"

class TestActiveChunkManager: public CxxTest::TestSuite
{
    ::tfs::ActiveChunkManager m_acm;
public:
    void testAddGet(void)
        {
            tfs::Chunk chk;
            tfs::Address location;

            location.name = "162.105.80.1";
            location.port = 1;

            tfs::Chunks chunks;
            
            for (int i = 0; i < 256; i++){
                chk.id = i;
                chk.size = 500*i;
                chk.version = 2*i;
                chunks.push_back(chk);
                
                for (int j = 0; j < 100; j++){
                    location.port = j;
                    m_acm.add(chk, location);
                }
            }

            tfs::LocatedChunks lchks = m_acm.getLocatedChunks(chunks);

            TS_ASSERT_SAME_DATA(&lchks[255].chk, &chk, sizeof(chk));
            TS_ASSERT_EQUALS(lchks[255].locations.size(), 100);
            
            m_acm.remove(chk, location);
            lchks = m_acm.getLocatedChunks(chunks);
            TS_ASSERT_EQUALS(lchks[255].locations.size(), 99);
        }
};


#endif /* _TESTACTIVECHUNKMANAGER_HPP */
