/* 
 * @(#)MasterDB.cpp
 * AUTHOR: YangZhifeng
 * CREATED DATE: 11  5ÔÂ 2007
 * DESCRIPTION: 
 */

#include "master/MasterDB.hpp"
#include "master/MasterConfig.hpp"
using namespace tfs;

MasterDB::MasterDB()
    :m_chunkServers(MasterConfig::ChunkServerExpiredSeconds), m_activeClients(MasterConfig::ClientExpiredSeconds), m_fsJournal(MasterConfig::JournalFilePathName), m_dir(&m_fsJournal)
{
    m_statistics.m_startTime = time((time_t*)NULL);
}

MasterDB* MasterDB::instance()
{
    if (_instance == NULL){
        _instance = new MasterDB;
    }
    return _instance;
}


MasterDB* MasterDB::_instance = NULL;
