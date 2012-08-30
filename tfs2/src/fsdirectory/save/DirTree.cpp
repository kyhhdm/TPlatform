/** @file DirTree.cpp
 *
 * @author PengBo
 * @date 18 7 2007
 *
 *
 */

#include "fsdirectory/INode.hpp"
#include "fsdirectory/DirNode.hpp"
#include "fsdirectory/DirTree.hpp"
#include "fsdirectory/DirTreePath.hpp"

using namespace std;
using namespace tfs;

DirTree::DirTree(const std::string imageFileName)
{
    UNUSED(imageFileName);

}

DirTree::DirTree(DirNode *pDirNode) 
{
    if(!pDirNode){
        //build a default Tree with "/" root node 
        pDirNode = new DirNode(Path::RootString, NULL);
        pDirNode->setParent(pDirNode);
        m_pRoot = pDirNode;
    }
    else{
        m_pRoot = pDirNode;
    }
}

DirTree::DirTree()
{
    m_pRoot = NULL;
}

DirTree::~DirTree()
{
    if (m_pRoot) delete m_pRoot;
}

DirNode* DirTree::findDirNode(const std::string &pathName) const
{
    DirTreePath treePath(this,pathName);

    DirTreePath::iterator iter;
    
    //#BUGFIX, item 16, when readDir("a") it will fail the treePath walk
    iter = treePath.begin();
    if(!iter.match()) return NULL;
    //for (iter = treePath.begin();  iter != treePath.end() ; ++iter) {
    
    for (;  iter != treePath.end() ; ++iter) {
        if( !iter.match() ){
            return NULL;
        }
    }

    return *iter;
}

INode* DirTree::findINode(const std::string &name) const
{
    DirNode *pNode;
    INode   *pInode;
    Path    path(name);

    if ( (pNode = findDirNode(name)) ) {
        if (path.isPureDir()) {
            return pNode->getINode();
        }
        else {
            //try file node first
            pInode = pNode->findFile(path.getFileName());
            if(pInode) return pInode;
            
            //try dir node then
            DirNode *pDirNode = pNode->findChild(path.getFileName());
            if(pDirNode) return pDirNode->getINode();
            else return NULL;
        }
    }

    return NULL;
}

DirNode* DirTree::createDirNodes(const std::string& pathName)
{
    DirTreePath treePath(this, pathName);

    DirTreePath::iterator iter = treePath.begin();

    if(!iter.match()) {
        //not match from Root, failed
        //return true if empty
        //#BUGFIX-20080810, createRootFile failed bug
        //if(iter != treePath.end()) return NULL;
        //else return *iter;
        
        //#deprecated BUGFIX-20080810
        return NULL;
    }

    for ( ;  iter != treePath.end() ; ++iter) {
        if( !iter.match() ){

            //create new node if it doesn't exist
            DirNode *pCurNode = *iter;
            DirNode *pNewNode = new DirNode(iter.getNodeName(), pCurNode);
            pCurNode->addChild(pNewNode);

            //march the iterator to the new child node, and goon iteration there
            iter.setDirNode(pNewNode);

            iter.clear();
        }
    }

    return *iter;

}

bool DirTree::moveDirNode(const DirNode* src, const DirNode* dst)
{
    UNUSED(src);
    UNUSED(dst);

    return false;
}

bool DirTree::deleteDirNode(DirNode* node)
{
    UNUSED(node);
    return false;
}

bool DirTree::lockPath(const std::string& pathName)
{
    //TODO,pb,20070803, should be Synchronized call here
    DirTreePath treePath(this,pathName);

    DirTreePath::iterator iter;

    for (iter = treePath.begin();  iter != treePath.end() ; ++iter) {
        if( !iter.match() ){
            return false;
        }

        (*iter)->incLock();

    }
    return true;
}

bool DirTree::unlockPath(const std::string& pathName)
{
    //TODO,pb,20070803, should be Synchronized call here
    DirTreePath treePath(this,pathName);

    DirTreePath::iterator iter;

    for (iter = treePath.begin();  iter != treePath.end() ; ++iter) {
        if( !iter.match() ){
            return false;
        }

        (*iter)->decLock();

    }
    return true;
}

