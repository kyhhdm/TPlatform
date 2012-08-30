/** 
 * @file JobServiceImpl.hpp
 * The implementation class of ClientService interface.
 * 
 * @author Zhifeng YANG
 * @date 2007-11-28
 */
#ifndef _JOBSERVICEIMPL_HPP
#define _JOBSERVICEIMPL_HPP 1

#include "master/MasterDB.hpp"
#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "util/Logger.hpp"

namespace mapreduce{
    class JobServiceImpl: public JobService
    {
        MasterDB *m_db;
        Logger m_logger;
    public:
        /// constructor
        JobServiceImpl();
        /// @{ RPC interface, @see WorkerService.ice
        int32_t create(const ::mapreduce::slice::MapReduceJob& job, const Ice::Current&);
        //int32_t wait(int32_t jobId, const Ice::Current&);
        JobDetail getJobDetail(int32_t jobId, const ::Ice::Current&);
        //void detach(int32_t jobId, const Ice::Current&);
        int kill(int32_t jobId, const Ice::Current&);
        /// @}
    };

    inline JobServiceImpl::JobServiceImpl()
        :m_logger(Logger::getInstance("master"))
    {
        m_db = MasterDB::instance();
    }

}


#endif /* _JOBSERVICEIMPL_HPP */
