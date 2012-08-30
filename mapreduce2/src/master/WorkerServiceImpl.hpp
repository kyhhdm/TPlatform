/** 
 * @file WorkerServiceImpl.hpp
 * Implementation class of WorkerService interface.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _WORKERSERVICEIMPL_HPP
#define _WORKERSERVICEIMPL_HPP 1

#include "master/MasterDB.hpp"
#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "util/Logger.hpp"

namespace mapreduce{
    class WorkerServiceImpl: public WorkerService
    {
        MasterDB *m_db;
        Logger m_logger;
    public:
        /// constructor
        WorkerServiceImpl();

        /// @{ RPC interface, @see WorkerService.ice
        MasterCommands sendHeartbeat(const Address& worker, const Heartbeat& heartbeat, const Ice::Current& = Ice::Current());
        void completeTask(const Address& worker, int32_t taskID, const Ice::Current& = Ice::Current());
        /// abandon the task and re-schedule the tasks
        void abandonTask(const Address& worker, int32_t taskID, const Ice::Current& = Ice::Current());
        /// @}
    };

    inline WorkerServiceImpl::WorkerServiceImpl()
        :m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }

}


#endif /* _WORKERSERVICEIMPL_HPP */
