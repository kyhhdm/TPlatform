/**
 * @file TestDirTree.hpp
 *
 * @author Chen Rishan, PengBo
 * @date 2007-08-03
 */
#ifndef _TEST_DIRTREE_HPP
#define _TEST_DIRTREE_HPP 

#include "fsdirectory/DirNode.hpp"
#include "fsdirectory/DirTree.hpp"
#include <cxxtest/TestSuite.h>
#include <fstream>

using namespace std;
using namespace tfs;

BOOST_CLASS_TRACKING(tfs::DirTree, boost::serialization::track_never)
BOOST_CLASS_TRACKING(tfs::DirNode, boost::serialization::track_never)
BOOST_CLASS_TRACKING(tfs::INode, boost::serialization::track_never)
BOOST_CLASS_TRACKING(tfs::slice::Chunk, boost::serialization::track_never)

class TestDirTree: public CxxTest::TestSuite
{    
    DirTree* m_pTree;

public:
    TestDirTree( int noUse ){
        UNUSED(noUse);
        m_pTree = new DirTree(NULL);
    }

    virtual ~TestDirTree(){
        delete m_pTree;
    }

    static TestDirTree *createSuite() {
        return new TestDirTree( 1 ); 
    }
    
    static void destroySuite( TestDirTree *suite ) { 
        delete suite; 
    }
  
    //=============test goes here ===============================
    void setUpWorld() 
    {


    }
    
    void tearDownWorld()
    {

    }

    //==============helper function ====================
    void printTree(DirTree* /*pTree*/)
    {
        //DirNode* pDirNode = pTree->getRoot();
    }


    //==============test goes here =====================
    void testCreateDirNodes(void)
	{
        string fileName = "xxxx/tfs/src/DirTree.cpp";
        DirNode* pDirNode = m_pTree->createDirNodes(fileName);
        TS_ASSERT(pDirNode == NULL);
        
        fileName = "/home/tfs/src/DirTree.cpp";
        pDirNode = m_pTree->createDirNodes(fileName);
        TS_ASSERT(pDirNode != NULL);
        
        //#BUG, 20070810, createRootFile failed
        pDirNode = m_pTree->createDirNodes("/test");
        TS_ASSERT(pDirNode != NULL);
    }

    void testCreate(void)
	{
        //string fileName = "/home/tfs/src/DirTree.cpp";
        //m_pTree->createDirNodes(fileName);
    
        DirNode* pDirNode = m_pTree->getRoot();
        pDirNode = pDirNode->findChild("home");
        TS_ASSERT(pDirNode != NULL);

        pDirNode = pDirNode->findChild("tfs");
        TS_ASSERT(pDirNode != NULL);

        pDirNode = pDirNode->findChild("src");
        TS_ASSERT(pDirNode != NULL);

        //DirTree doesn't create files, so it's wired here, :)
        INode* pINode = pDirNode->findFile("DirTree.cpp");
        TS_ASSERT(pINode == NULL);
	}

    void testFindChild()
    {
        DirNode* pDirNode;
        INode* pINode;
        
        //find directories
        pDirNode = m_pTree->findDirNode("/home/tfs/src/xxx/");
        TS_ASSERT(pDirNode == NULL);

        pDirNode = m_pTree->findDirNode("/home/tfs/src/");
        TS_ASSERT(pDirNode != NULL);
        TS_ASSERT_EQUALS(pDirNode->getName(), "src");
    
        pDirNode = m_pTree->findDirNode("/home/tfs/");
        TS_ASSERT(pDirNode != NULL);
        TS_ASSERT_EQUALS(pDirNode->getName(), "tfs");
        
        DirNodeIterator iter = pDirNode->getChildrenBegin();
        TS_ASSERT_EQUALS((*iter)->getName(),"src");

        pDirNode = m_pTree->findDirNode("/home/");
        TS_ASSERT(pDirNode != NULL);
        TS_ASSERT_EQUALS(pDirNode->getName(), "home");

        //
        //#findDirNode(pathName), the lookup path must be tailed with "/"
        //
        pDirNode = m_pTree->findDirNode("/home/tfs");
        //cout << "pDirNode->getName() = " << pDirNode->getName() << endl;
        TS_ASSERT(pDirNode != NULL);
        TS_ASSERT_EQUALS(pDirNode->getName(), "home");
        
        pDirNode = m_pTree->findDirNode("/home");
        TS_ASSERT(pDirNode != NULL);
        TS_ASSERT_EQUALS(pDirNode->getName(), "/");
        
        //find INode for dir or file
        pINode = m_pTree->findINode("/home/tfs/src/DirTree.hpp");
        TS_ASSERT(pINode ==NULL);

        pINode = m_pTree->findINode("/home/tfs/src/DirTree.cpp");
        TS_ASSERT(pINode ==NULL);


        pINode = m_pTree->findINode("/home/tfs/src/");
        TS_ASSERT(pINode !=NULL);
        TS_ASSERT_EQUALS(pINode->getName(), "src");

        pINode = m_pTree->findINode("/home/");
        TS_ASSERT(pINode !=NULL);
        TS_ASSERT_EQUALS(pINode->getName(), "home");
        
        pINode = m_pTree->findINode("/home");
        TS_ASSERT(pINode !=NULL);
        TS_ASSERT_EQUALS(pINode->getName(), "home");

        pINode = m_pTree->findINode("/home/xxx/");
        TS_ASSERT(pINode ==NULL);

    }

    //Test 4. serialize
    void vtestSave()
    {
        DirTree tree1(NULL), tree2(NULL);

        //setup
        //if(1){
        DirNode* pDirNode = tree1.createDirNodes("/home/tfs/src/test-a.dat");
        INode inode1("test-a.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode1);
        INode inode2("test-b.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode2);
        INode inode3("test-c.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode3);

        pDirNode = tree1.createDirNodes("/home/tfs/doc/userGuide.doc");
        INode inode4("userGuide.doc", 1, 64*1024*1024);    
        pDirNode->addFile(inode4);
        
        //}

        pDirNode = tree1.getRoot();
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("home");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("tfs");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("src");
        TS_ASSERT(pDirNode != NULL);

        pDirNode = tree1.findDirNode("/home/tfs/src/");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = tree1.findDirNode("/home/tfs/doc/");
        TS_ASSERT(pDirNode != NULL);
        
        INode* pINode = tree1.findINode("/home/tfs/src/test-a.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree1.findINode("/home/tfs/src/test-b.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree1.findINode("/home/tfs/src/test-c.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree1.findINode("/home/tfs/doc/userGuide.doc");
        TS_ASSERT(pINode !=NULL);


        ofstream ofs("tfs.img");
        boost::archive::binary_oarchive oa(ofs);
        //oa << tree1;

    }

    //Test 5. serialize load
    void vtestLoad()
    {
        DirTree tree1(NULL), tree2;

        //setup
        //if(1){
        DirNode* pDirNode = tree1.createDirNodes("/home/tfs/src/test-a.dat");
        INode inode1("test-a.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode1);
        INode inode2("test-b.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode2);
        INode inode3("test-c.dat", 1, 64*1024*1024);    
        pDirNode->addFile(inode3);

        pDirNode = tree1.createDirNodes("/home/tfs/doc/userGuide.doc");
        INode inode4("userGuide.doc", 1, 64*1024*1024);    
        pDirNode->addFile(inode4);
        //}

        ifstream ifs("tfs.img");
        boost::archive::binary_iarchive ia(ifs);
        //ia >> tree2;
    
        //cout << " load up over " << endl;
    
        //check up
        pDirNode = tree2.getRoot();
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("home");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("tfs");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = pDirNode->findChild("src");
        TS_ASSERT(pDirNode != NULL);

        pDirNode = tree2.findDirNode("/home/tfs/src/");
        TS_ASSERT(pDirNode != NULL);
        pDirNode = tree2.findDirNode("/home/tfs/doc/");
        TS_ASSERT(pDirNode != NULL);
        
        INode* pINode = tree2.findINode("/home/tfs/src/test-a.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree2.findINode("/home/tfs/src/test-b.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree2.findINode("/home/tfs/src/test-c.dat");
        TS_ASSERT(pINode !=NULL);
        pINode = tree2.findINode("/home/tfs/doc/userGuide.doc");
        TS_ASSERT(pINode !=NULL);

    }

};

#endif /* _TEST_DIRTREE_HPP */

