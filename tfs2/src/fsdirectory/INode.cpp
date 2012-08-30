/** @file INode.cpp
 * INode stores matadata of object in namespace,including file and directory.
 *
 * @author PengBo
 * @date 18 7 2007
 *
 */

#include "fsdirectory/INode.hpp"
#include "FileInfo.h"

using namespace std;
using namespace tfs;

void INode::makeFileInfo(FileInfo& fileInfo)
{
    fileInfo.name = this->m_name;
    fileInfo.createTime = this->m_createTime;
    fileInfo.chunkSize = this->m_chunkSize;
    fileInfo.size = this->m_size;
    fileInfo.replication = this->m_replication;
    fileInfo.flag = this->m_flag;
}


