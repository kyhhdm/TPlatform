/** 
 * @file AdminServiceImpl.hpp
 * implementation class of interface AdminService.
 * 
 * @author Zhifeng YANG
 * @date 2007-08-29
 */
#ifndef _ADMINSERVICEIMPL_HPP
#define _ADMINSERVICEIMPL_HPP 1
#include "common/IceGenerated.hpp"
#include "master/MasterDB.hpp"
#include "AdminService.h"

namespace tfs
{
    class AdminServiceImpl:public tfs::slice::AdminService
    {
    public:
        // constructor
        AdminServiceImpl();

        // interface
        std::string getStartTime(const ::Ice::Current& = ::Ice::Current());
        Addresses getChunkServers(const ::Ice::Current& = ::Ice::Current());
        Addresses getClients(const ::Ice::Current& = ::Ice::Current());
        tfs::slice::OperationsCount getOperationsCount(const ::Ice::Current& = ::Ice::Current());
    private:
        MasterDB* m_db;
    };

    inline AdminServiceImpl::AdminServiceImpl()
    {
        m_db = MasterDB::instance();
    }

}

#endif /* _ADMINSERVICEIMPL_HPP */
