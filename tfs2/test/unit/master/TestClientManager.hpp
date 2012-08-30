/** 
 * @file TestClientManager.hpp
 * test of ClientManager.
 * 
 * @author Zhifeng YANG
 * @date 2007-07-11
 */
#ifndef _TESTCLIENTMANAGER_HPP
#define _TESTCLIENTMANAGER_HPP 1

#include <cxxtest/TestSuite.h>
#include "master/ClientManager.hpp"
#include <unistd.h>

class TestClientManager: public CxxTest::TestSuite
{
public:
    void testAll()
        {
            tfs::ClientManager cm(5);
            tfs::Address client1;
            client1.name = "local";
            client1.port = 25;
            
            cm.renewHeartbeat(client1);
            tfs::Addresses expiredClients;

            cm.removeExpired(expiredClients);
            TS_ASSERT_EQUALS(expiredClients.size(), 0);

            sleep(6);
            
            cm.removeExpired(expiredClients);
            TS_ASSERT_EQUALS(expiredClients.size(), 1);
            
        }
};


#endif /* _TESTCLIENTMANAGER_HPP */
