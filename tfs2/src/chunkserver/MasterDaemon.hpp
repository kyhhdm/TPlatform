
/**
 * @file   MasterDaemon.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Sat Jul 14 22:36:54 2007
 * 
 * @brief  
 * 
 * 
 */


#ifndef  _MASTER_DAEMON_HPP
#define  _MASTER_DAEMON_HPP

#include "ChunkManager.hpp"
#include "common/Types.hpp"
#include "common/IceGenerated.hpp"
#include "common/Exception.hpp"
#include "Daemon.hpp"
#include "ChunkServerService.h"
#include "MasterCommand.h"
#include "ChunkServerConf.hpp"
#include <Ice/Ice.h>
#include <stdint.h>
#include <string>
#include <vector>


namespace tfs
{
    class MasterDaemon: public Daemon
    {
    public:
        MasterDaemon(ChunkManager * chunk_manager);
        void operator()();
    private:
        int enroll();
        slice::MasterCommand sendHeartbeat();
        int chunkReport();
        int delChunk(const std::vector<int64_t> &);

        bool dealMasterCmd(const MasterCommand & master_cmd);
    private:        
        ChunkManager * m_pManager;
        slice::ChunkServerServicePrx m_pServicePrx;
        ChunkServerConf * m_pConf;
    };
}

#endif
