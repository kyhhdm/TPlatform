/**
 * @file TestNewChunkTable.hpp
 * test of NewChunkTable
 *
 * @author Chenr Rishan
 * @date 2007-08-06
 */

#ifndef _TESTNEWCHUNKTABLE_HPP
#define _TESTNEWCHUNKTABLE_HPP 1

#include "fsdirectory/NewChunkTable.hpp"
#include "fsdirectory/INode.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <cxxtest/TestSuite.h>
using namespace tfs;
using namespace std;

class TestNewChunkTable: public CxxTest::TestSuite
{
public:
    NewChunkTable table;
    Long id, id2, id3;
    string holder;
    string holder2;
    bool judge;
    const INode* p1 ;
    const INode* p2 ;
    const INode* p3 ;
    //--------------------Constructor------------------------
    TestNewChunkTable()
    {
        p1 = new INode("peter");
        p2 = new INode("tsunami");
        p3 = new INode("jack");
        id = 1,id2 = 2,id3=3;
        holder.append("jackson");
        holder2.append("jacksaaon");
    }
    ~TestNewChunkTable()
    {
        delete p1;
        delete p2;
        delete p3;
    }
    //---------------------test---------------------------

    void testAddItem(void)
    {  
        //TS_ASSERT_EQUALS(p3->getName(),"jack");
        
        judge = table.addItem(id,holder,p1);
        TS_ASSERT_EQUALS(judge,true);
        
        judge = table.addItem(id,holder,p1);
        TS_ASSERT_EQUALS(judge,false);

        judge = table.addItem(id2,holder2,p2);
        TS_ASSERT_EQUALS(judge,true);
    }

    
    void testDeleteId(void){
        judge = table.deleteItem(id);
        TS_ASSERT_EQUALS(judge,true);
 
        judge = table.deleteItem(id);
        TS_ASSERT_EQUALS(judge,false);
        
        judge = table.deleteItem(id2);
        TS_ASSERT_EQUALS(judge,true);
        
        judge = table.deleteItem(id3);
        TS_ASSERT_EQUALS(judge,false);
    }
    void testDeleteHolder(void){
        int count = 0;
        vector<Long> deleteNewChunkIds;
        count = table.deleteItem(holder, deleteNewChunkIds);
        TS_ASSERT_EQUALS(count,0);
        
        table.addItem(id,holder,p1);
        table.addItem(id2,holder,p2);
        table.addItem(id3,holder,p3);

        deleteNewChunkIds.clear();
        count = table.deleteItem(holder, deleteNewChunkIds);
        TS_ASSERT_EQUALS(count,3);
        judge = table.deleteItem(id);
        TS_ASSERT_EQUALS(judge,false);
    }
    void testFindItem(void){
        const INode* inode;
        inode = table.findItem(id);
        TS_ASSERT(inode == NULL);

        table.addItem(id,holder,p1);
        inode = table.findItem(id);
        TS_ASSERT(inode != NULL);
        TS_ASSERT_SAME_DATA(inode,p1,sizeof(*p1));
        //inode->getName();
        table.addItem(id2,holder2,p3);
        inode = table.findItem(id2);
        TS_ASSERT_SAME_DATA(inode,p3,sizeof(*p3) );
    
    }
    
};
#endif /* _TESTNEWCHUNKTABLE_HPP */
