
#include "util/Logger.hpp"
#include "MasterDaemon.hpp"
#include "ChunkServerConf.hpp"
#include "common/Types.hpp"
#include "common/IceGenerated.hpp"
#include "common/Exception.hpp"
#include "ChunkServerService.h"
#include "MasterCommand.h"
#include "TaskMgr.hpp"
#include <Ice/Ice.h>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <cassert>
#include <unistd.h>
#include <time.h>
#include "String.hpp"


using namespace std;
using namespace ::tfs::slice;
using namespace Ice;
using namespace tfs;

extern ::log4cplus::Logger pLogger;

MasterDaemon::MasterDaemon(ChunkManager * chunk_manager)
{
    assert(chunk_manager!=NULL);
    m_pManager=chunk_manager;
    m_pConf=ChunkServerConf::getInstance();
}

//thread run
void MasterDaemon::operator()()
{
    while(!enroll()){
        sleepCurThread(5);
        //        sleep(5);
    }
    try{
        chunkReport();
    }catch(const UnknownChunkServer &ex){
        cout<<ex<<endl;
    }
    
    MasterCommand master_cmd;
    while(1){
        try{
            master_cmd=sendHeartbeat();
        }catch(const UnknownChunkServer &ex){
            cout<<ex<<endl;
            try{
                while(!enroll()){
                    continue;
                }
                chunkReport();
            }catch(const UnknownChunkServer &ex){
                continue;
            }
        } catch (const Ice::Exception & ex) {
            cerr << ex << endl;
        }catch(...){
            cerr << ".";
            //if send heartbeat error
            srandom(time(NULL));
            int rt = random() % 30;
            assert(rt >= 0 && rt < 30);
            sleepCurThread(30 + rt);
            continue;
        }
        //@todo process master_cmd        
        //        sleep(5);
        sleepCurThread(5);
    }
}


//chunkserver enroll
int MasterDaemon::enroll()
{
    static int init = 0;


    try{
    if (init==0){
    Ice::CommunicatorPtr ic = Ice::initialize();
    Ice::ObjectPrx base	= ic->stringToProxy(((m_pConf->MASTER_PROXY_INFO).c_str()));
    m_pServicePrx = ChunkServerServicePrx::checkedCast(base);
    }

    }catch(const Ice::Exception &ex){
        cout<<"ice enroll failed"<<endl;
        return -1;
    }

    init = 1;

    Address addr;
    addr.name=m_pConf->LOCALE_IP;
    addr.port=m_pConf->DATA_SOCKET_PORT;
    m_pServicePrx->enroll(addr);
    return 1;
}

MasterCommand MasterDaemon::sendHeartbeat()
{
    Heartbeat heart_beat;
    heart_beat.capacity=(Long)m_pManager->getCapacity();
    heart_beat.free=(Long)m_pManager->getFreespace();
    heart_beat.workload=m_pManager->getWorkload();

    Address addr;
    addr.name=m_pConf->LOCALE_IP;
    addr.port=m_pConf->DATA_SOCKET_PORT;

    MasterCommand cmd;
    try{
        cmd = m_pServicePrx->sendHeartbeat(addr,heart_beat);
        dealMasterCmd(cmd);
        
    }catch(const UnknownChunkServer &ex){
        cout<<"in sendHeartbeat:"<<ex<<endl;
        throw ex;
    }catch(...){
        throw "send heartbeat error!";
    }
    return cmd;
}

int MasterDaemon::chunkReport()
{
    Address addr;
    addr.name=m_pConf->LOCALE_IP;
    addr.port=m_pConf->DATA_SOCKET_PORT;

    map<int64_t,ChunkInfo> map_chunks=m_pManager->getChunks();
    map<int64_t,ChunkInfo>::iterator it = map_chunks.begin();
    vector<Chunk> vec_chunks;
    for(;it!=map_chunks.end();++it){
        ChunkInfo achunkinfo=it->second;
        Chunk achunk;
        achunk.id=(Long)(achunkinfo.mID);
        achunk.size=(achunkinfo.mSize);
        achunk.version=(achunkinfo.mVersion);
        vec_chunks.push_back(achunk);
    }
    try{
        m_pServicePrx->chunkReport(addr,vec_chunks);
    }catch(const UnknownChunkServer &ex){
        cout<<"in chunkReport:"<<ex<<endl;
        throw ex;
    }
    return 1;
}

bool MasterDaemon::dealMasterCmd(const MasterCommand & master_cmd)
{
    //    LOG4CPLUS_DEBUG(pLogger,"Enter MasterDaemon::dealMasterCmd");
    
    TaskMgr * p_task_mgr = TaskMgr::getInstance();
    if (master_cmd.command == McRemoveChunks)
    {
        SysTask task;
        task.m_action = Del_Chunk_Task;

        string str_log = "";
        
        vector<int64_t> dest_chunks;
        vector<Chunk>::const_iterator vec_it = (master_cmd.chks).begin();
        for (;vec_it != master_cmd.chks.end(); ++vec_it){
            dest_chunks.push_back(vec_it->id);
            str_log += string(ts("%d; ",vec_it->id));
        }
        
        task.m_chunks = dest_chunks;

//         vector<ChunkServerAddr> server_addr;
        
//         vector<Address>::const_iterator it = master_cmd.targets.begin();
//         for (;it != master_cmd.targets.end(); ++it){
//             server_addr.push_back(ChunkServerAddr((it->name).c_str(),it->port));
//         }

//         task.m_chunkservers = server_addr;

        p_task_mgr->addSysTask(task);
        
        LOG4CPLUS_DEBUG(pLogger,"Add new systask: Delete_chunk_task! id:" << str_log);
        //        task.m_chunkservers = master_cmd.        
    }
    return true;
}
