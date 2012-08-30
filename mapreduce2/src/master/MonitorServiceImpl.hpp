/** 
 * @file MonitorServiceImpl.hpp
 * implemantation class for interface MonitorService.
 * @see MonitorService.ice
 * @author Zhifeng YANG
 * @date 2007-12-05
 */
#ifndef _MONITORSERVICEIMPL_HPP
#define _MONITORSERVICEIMPL_HPP 1
#include "common/IceGenerated.hpp"
#include "master/MasterDB.hpp"
namespace mapreduce{
    class MonitorServiceImpl: public MonitorService
    {
        MasterDB *m_db;
    public:
        /// constructor
        MonitorServiceImpl();
        /// RPC interface
        int32_t getStartTime(const ::Ice::Current&);
	    int32_t getCompletedJobs(const ::Ice::Current&);
	    int32_t getCompletedTasks(const ::Ice::Current&);
        WorkersDetail getWorkers(const ::Ice::Current&);
        JobsDetail getJobs(const ::Ice::Current&);
        TasksDetail getTasks(int32_t jobId, const ::Ice::Current&);
        TasksStatistics getTasksStat(int32_t jobId, const ::Ice::Current&);
        
    };
    inline MonitorServiceImpl::MonitorServiceImpl()
    {
        m_db = MasterDB::instance();
    }
}


#endif /* _MONITORSERVICEIMPL_HPP */
