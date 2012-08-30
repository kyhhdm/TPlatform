

#include <cxxtest/TestSuite.h>
#include "chunkserver/FileUtil.hpp"
#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

Logger pLogger = Logger::getInstance("chunkserver");

class TestFileUtil : public CxxTest::TestSuite
{
public:
    void testFun()
    {
        TS_ASSERT(FileUtil::isDir("/home/tqc/") ==  1);
        TS_ASSERT(FileUtil::isDir("/home/tqc") == 1);

        //        cout<<endl<<FileUtil::isDir("/home/tqc")<<endl;
        
        TS_ASSERT(FileUtil::isDir(".") ==  1);
        TS_ASSERT((FileUtil::isDir("./testFileUtil")) == -1);
        TS_ASSERT((FileUtil::isDir("./asfasfa")) == -2);

        //        TS_ASSERT((FileUtil::isDir("/home/tqc/test/linkfile")) == 1);
        

        TS_ASSERT(FileUtil::getFatherDir("/home") == "/");
        TS_ASSERT(FileUtil::getFatherDir("home") == "");
        TS_ASSERT(FileUtil::getFatherDir("home/") == "");        
        TS_ASSERT(FileUtil::getFatherDir("/home///") == "/");
        TS_ASSERT(FileUtil::getFatherDir("/home/abc") == "/home/");
        TS_ASSERT(FileUtil::getFatherDir("/home//abc") == "/home//");
        cout<<FileUtil::getFatherDir("/home//abc")<<endl;
    }
};
