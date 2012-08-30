/** 
 * @file TestChunkTable.hpp
 * test of ChunkTable.
 *
 * @author Chen Rishan
 * @date 2007-08-01
 */

#ifndef _TESTCHUNKTABLE_HPP
#define _TESTCHUNKTABLE_HPP
#include "fsdirectory/ChunkTable.hpp"
#include "fsdirectory/INode.hpp"
#include "common/Types.hpp"
#include <cxxtest/TestSuite.h>
using namespace tfs;
class TestChunkTable: public CxxTest::TestSuite
{
public:
    void testALL(void)
	{
	    ::tfs::ChunkTable table;
	    const Long id1=1,id2=2;
	    INode node1,node2;
	    //const INode* p1 = &node1;
	    //const INode* p2 = &node2;
	    node1.setName(std::string("peter") );
	    node2.setName(std::string("jay") );
	    const INode* p1 = &node1;
	    const INode* p2 = &node2;
	    bool judge = table.addItem(id1,p1);
	    
	    TS_ASSERT_EQUALS(judge ,true);
	    judge = table.deleteItem(id2);
	    TS_ASSERT_EQUALS(judge,true);
	    TS_ASSERT_EQUALS(table.deleteItem(id1),true);
	    table.addItem(id2,p2);
	    TS_ASSERT_EQUALS(table.findItem(id2),p2);
	
	}

    void testNullTable()
    {
        ChunkTable *pTable = new ChunkTable;

        const INode* pInode = pTable->findItem(0);
        TS_ASSERT(pInode==NULL);
        
        delete pTable;
    }
};

#endif /* _TESTCHUNKTABLE_HPP */ 
