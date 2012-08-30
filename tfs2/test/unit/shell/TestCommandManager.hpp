/** 
 * @file TestCommandManager.hpp
 * test of CommandManager.
 * 
 * @author Chen Rishan
 * @date 2007-09-29
 */
#ifndef _TESTCOMMANDMANAGER_HPP
#define _TESTCOMMANDMANAGER_HPP 1

#include <cxxtest/TestSuite.h>
#include <string>
#include "app/shell/include/CommandManager.hpp"

using namespace terminal;

class TestCommandManager: public CxxTest::TestSuite
{
    CommandManager m_manager;
public:
    void testcore()
    {
        std::string result = m_manager.back();
        TS_ASSERT_EQUALS(result, "");
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, "");
    }
    void testBackandForward()
    {
        std::string c1("mkdir test/dir/test/");
        std::string c2("rm /root/*");
        std::string c3("ls -a /root/");
        std::string empty;
        m_manager.insert(c1);
        std::string result = m_manager.back();
        TS_ASSERT_EQUALS(result, c1);
        m_manager.insert(c2);
        m_manager.insert(c3);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c3);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c2);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c1);
        
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, c2);
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, c3);
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, empty);
    }
    void testBackAndForward2()
    {   
        std::string c1("put Makefile ./");
        std::string c2("ls");
        std::string c3("get Makefile ./");
        std::string c4("cd /root/");
        std::string c5("ls");
        std::string result;
        m_manager.insert(c5);
        m_manager.insert(c4);
        m_manager.insert(c3);
        m_manager.insert(c2);
        m_manager.insert(c1);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c1);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c2);
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, c2);
        result = m_manager.forward();
        TS_ASSERT_EQUALS(result, c1);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c1);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c2);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c3);
        result = m_manager.back();
        TS_ASSERT_EQUALS(result, c4);
    }
    void testDepart()
    {
        std::string c0("ls");
        std::string c1(" mkdir test/test");
        std::string c2("       rm        -rf /root/test");
        std::string para;
        m_manager.commandDepart(c1, para);
        TS_ASSERT_EQUALS(para, " test/test");
        m_manager.commandDepart(c0, para);
        TS_ASSERT_EQUALS(para, "");
        m_manager.commandDepart(c2, para);
        TS_ASSERT_EQUALS(para, "        -rf /root/test");
    }
};

#endif
