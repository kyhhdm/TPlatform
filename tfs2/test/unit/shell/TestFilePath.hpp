/** 
 * @file TestFilePath.hpp
 * test of FilePath.
 * 
 * @author Chen Rishan
 * @date 2007-10-02
 */
#ifndef _TESTFILEPATH_HPP
#define _TESTFILEPATH_HPP 1

#include <cxxtest/TestSuite.h>
#include <string>
#include "app/shell/include/FilePath.hpp"

using namespace terminal;

class TestCommandManager: public CxxTest::TestSuite
{
    FilePath m_path;
public:
    void testChange()
    {
        std::string c0("/test/dir/test");
        std::string c1("/test/dir/test/");
        std::string c2("/root/temp/.././../.");
        std::string c3("/root/tet/test/./test/../../../");
        std::string c4("/./dd/..");
        std::string c5("/./1/../2/./../3/./././../3/4/5/../../..");
        std::string c6("/test/../test/temp/../../");
        //
        std::string result = m_path.change(c1);
        TS_ASSERT_EQUALS(result, c0);
        result = m_path.change(c2);
        TS_ASSERT_EQUALS(result, "/");
        result = m_path.change(c3);
        TS_ASSERT_EQUALS(result, "/root");
        result = m_path.change(c4);
        TS_ASSERT_EQUALS(result, "/");
        result = m_path.change(c0);
        TS_ASSERT_EQUALS(result, c0);
        result = m_path.change(c5);
        TS_ASSERT_EQUALS(result, "/");
        result = m_path.change("//");
        TS_ASSERT_EQUALS(result, "/");
        result = m_path.change(c6);
        TS_ASSERT_EQUALS(result, "/");
        // @fixbug 19
        std::string c7("/..");
        result = m_path.change(c7);
        TS_ASSERT_EQUALS(result, "/");
        
    }
    void testGetPath()
    {
        std::string c0("test/");
        std::string c1("/dir/test2/");
        std::string result = m_path.getPath(c1,c0);
        TS_ASSERT_EQUALS(result, "/dir/test2/test/");
        result = m_path.getPath(c1,c1);
        TS_ASSERT_EQUALS(result, "/dir/test2/");
    }
//     void testGetLocalPath()
//     {
//         std::string localpath = m_path.getLocalCurrentDir();
//         TS_ASSERT_EQUALS(localpath, "/home/tsunami/tplatform/tfs/build/app/shell/");
//     }
    void testSplit(){
        std::string path = "/";
        bool bAbsolute;
        std::string dir;
        std::string filename;
        
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == true);
        TS_ASSERT(dir == "/");
        TS_ASSERT(filename == "");

        path = ".";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "./");
        TS_ASSERT(filename == "");

        path = "..";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "../");
        TS_ASSERT(filename == "");
        
        path = "/path/to/file1";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == true);
        TS_ASSERT(dir == "/path/to/");
        TS_ASSERT(filename == "file1");

        path = "path/to/file1";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "path/to/");
        TS_ASSERT(filename == "file1");

        path = "file1";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "");
        TS_ASSERT(filename == "file1");

        path = "/path/to/";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == true);
        TS_ASSERT(dir == "/path/to/");
        TS_ASSERT(filename == "");

        path = "path/to/";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "path/to/");
        TS_ASSERT(filename == "");

        path = "";
        FilePath::split(path, bAbsolute, dir, filename);
        TS_ASSERT(bAbsolute == false);
        TS_ASSERT(dir == "");
        TS_ASSERT(filename == "");
    }
    
};


#endif
