/** @file DirTreePath.cpp
 *
 * @author PengBo
 * @date 20070803
 *
 *
 */

#include "fsdirectory/INode.hpp"
#include "fsdirectory/DirNode.hpp"
#include "fsdirectory/DirTree.hpp"
#include "fsdirectory/DirTreePath.hpp"

using namespace std;
using namespace tfs;

DirTreePath::DirTreePath(const DirTree* pDirTree, const std::string& pathName):m_path(pathName)
{
    this->m_pTree = (DirTree*)pDirTree;
}

DirTreePath::~DirTreePath()
{

}

DirTreePath::iterator DirTreePath::begin()
{   
    DirTreePath::iterator iter;

    iter.m_pDirNode = m_pTree->getRoot();
    iter.m_pathIter = m_path.begin();
    iter.m_matchFlag = ( iter.m_pDirNode->getName() == *iter.m_pathIter);

    return iter;
}

DirTreePath::iterator DirTreePath::end()
{
    DirTreePath::iterator iter;
    iter.m_pDirNode = m_pTree->getRoot();
    iter.m_pathIter = m_path.end();
    iter.m_matchFlag = true;
    return iter;
}

