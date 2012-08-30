/**
 * @file TestDirTreePath.hpp
 *
 * @author PengBo
 * @date 2007-08-07
 */
#ifndef _TEST_DIRTREEPATH_HPP
#define _TEST_DIRTREEPATH_HPP 

#include "fsdirectory/INode.hpp"
#include "fsdirectory/DirNode.hpp"
#include "fsdirectory/DirTree.hpp"
#include "fsdirectory/DirTreePath.hpp"
#include <cxxtest/TestSuite.h>
#include <ostream>

using namespace std;
using namespace tfs;

//
// This test suite shows what to do when your test case
// class cannot be instantiated statically.
// As an example, this test suite requires a non-default constructor.
//

class TestDirTreePath: public CxxTest::TestSuite
{
    tfs::DirTree* m_pTree;

public:
    TestDirTreePath( int noUse ){
        UNUSED(noUse);
        //build a test Tree 
        m_pTree = new DirTree(NULL);
    }

    virtual ~TestDirTreePath(){
        delete m_pTree;
    }

    static TestDirTreePath *createSuite() {
        return new TestDirTreePath( 1 ); 
    }
    
    static void destroySuite( TestDirTreePath *suite ) { 
        delete suite; 
    }
  
    //=============test goes here ===============================
    void setUpWorld() 
    {


    }
    
    void tearDownWorld()
    {

    }

    void printIter(DirTreePath::iterator /*iter*/)
    {
        #if 0
        if(*iter){
            cout << "pDirNode->name = " << (*iter)->getName() << "  "
                 << "Node name = " << iter.getNodeName() << endl;
        }
        else{
            cout << "pDirNode->name = NULL    "
                 << "Node name = " << iter.getNodeName() << endl;

        }
        #endif
    }

    void testIteration(void)
    {
      
        //DirNode* pDirNode = NULL;
        DirTreePath treePath(m_pTree, "/home/tfs/src/DirTree.cpp");
        DirTreePath::iterator iter,iterEnd;

        //test begin
        iter = treePath.begin();
        printIter(iter);
        iterEnd = treePath.end();
        printIter(iterEnd);
        
        TS_ASSERT_EQUALS(iter.getNodeName(), "/");
        TS_ASSERT(iter.match());
        TS_ASSERT( iter != treePath.end() );

        ++iter;
        printIter(iter);
        TS_ASSERT(!iter.match());
        TS_ASSERT_EQUALS(iter.getNodeName(), "home");
        TS_ASSERT( iter != treePath.end() );

        ++iter;
        printIter(iter);
        TS_ASSERT(!iter.match());
        TS_ASSERT_EQUALS(iter.getNodeName(), "tfs");
        TS_ASSERT( iter != treePath.end() );

        ++iter;
        printIter(iter);
        TS_ASSERT(!iter.match());
        TS_ASSERT_EQUALS(iter.getNodeName(), "src");
        TS_ASSERT( iter != treePath.end() );

        ++iter;
        printIter(iter);
        TS_ASSERT(!iter.match());
        TS_ASSERT_EQUALS(iter.getNodeName(), ".");

        //cout << "-->" << endl;

        ++iter;
        printIter(iter);
        TS_ASSERT(!iter.match());
        TS_ASSERT( !(iter != treePath.end()) );

    }

};

#endif /* _TEST_DIRTREEPATH_HPP */
