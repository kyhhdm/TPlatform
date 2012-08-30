
#include <cxxtest/TestSuite.h>
#include "chunkserver/FileSystemUtil.hpp"
#include "util/Logger.hpp"
#include "common/Types.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tfs;

Logger pLogger = Logger::getInstance("chunkserver");

class TestFileSystemUtil : public CxxTest::TestSuite
{
public:
    void testGetFiles(){
        vector<string> vec;
        cout << FileSystemUtil::getFiles(vec,".")<<endl;
        vec.clear();
        cout << FileSystemUtil::getFiles(vec,".",".cpp")<<endl;
        vec.clear();
        cout << FileSystemUtil::getFiles(vec,".",".hpp")<<endl;
    }
    void testGetAllFiles(){
        vector<string> vec;
        cout << FileSystemUtil::getAllFiles(vec,".")<<endl;
        vec.clear();
        cout << FileSystemUtil::getAllFiles(vec,"./",".cpp")<<endl;
        vector<string>::iterator it = vec.begin();
//         for(;it!=vec.end();++it)
//             cout << *it<<endl;
        vec.clear();
        cout << FileSystemUtil::getAllFiles(vec,".",".hpp")<<endl;        
    }

    void testGetDirs()
    {
        vector<string> vec;
        cout << "Dirs: "<<FileSystemUtil::getDirs(vec,"/home/tqc/")<<endl;
        vec.clear();
        cout << "Dirs: "<<FileSystemUtil::getDirs(vec,"/home/tqc/",false)<<endl;
    }
    void testBase(){
        TS_ASSERT(FileSystemUtil::getExtension("/af/asf/a.txt") == ".txt");
        TS_ASSERT(FileSystemUtil::getExtension("/af/asf/a.hpp") == ".hpp");
        TS_ASSERT(FileSystemUtil::getExtension(".a.cpp") == ".cpp");
        TS_ASSERT(FileSystemUtil::getExtension(".abc") == ".abc");
        TS_ASSERT(FileSystemUtil::getExtension("abc") == "");

        TS_ASSERT(FileSystemUtil::getBasename("/a/af/abc.cpp") == "abc");
        TS_ASSERT(FileSystemUtil::getBasename("abc.cpp") == "abc");
        TS_ASSERT(FileSystemUtil::getBasename("/a/af/.abc.cpp") == ".abc");

        //        TS_ASSERT(FileSystemUtil::createDir("mydir"));

        cout<<endl<<FileSystemUtil::getBranchPath("/a/abc")<<endl;
        cout<<endl<<FileSystemUtil::getBranchPath("/a//abc/")<<endl;
        TS_ASSERT(FileSystemUtil::getBranchPath("/abc") == "/");
        TS_ASSERT(FileSystemUtil::getBranchPath("/a/abc") == "/a");
        TS_ASSERT(FileSystemUtil::getBranchPath("/a//abc") == "/a");
        TS_ASSERT(FileSystemUtil::getBranchPath("/a//abc/") == "/a//abc");

        TS_ASSERT(FileSystemUtil::isDir("./CMakeFiles"));
        TS_ASSERT(FileSystemUtil::isDir("./CMakeFiles/"));
        TS_ASSERT(FileSystemUtil::isDir("./0"));
        TS_ASSERT(!FileSystemUtil::isDir("./afsasfas"));

        TS_ASSERT(FileSystemUtil::isExists("./0"));
        TS_ASSERT(!FileSystemUtil::isExists("./xxxxx"));

        TS_ASSERT(FileSystemUtil::createDir("./xxxxx"));
        TS_ASSERT(!FileSystemUtil::createDir("./xxxxx"));
        TS_ASSERT(FileSystemUtil::isExists("./xxxxx"));

        TS_ASSERT(FileSystemUtil::renameFile("./xxxxx","./yyyyy"));
        TS_ASSERT(FileSystemUtil::isExists("./yyyyy"));
        TS_ASSERT(FileSystemUtil::removeFile("./yyyyy"));

        TS_ASSERT(FileSystemUtil::renameFile("./testFileSystemUtil","./mydir/testFileSystemUtil.2"));
        //        TS_ASSERT(FileSystemUtil::removeFile("./testFileSystemUtil.2"));
            
            
        //        cout<<FileSystemUtil::getFileSize("testFileUtil1","K")<<endl;

    
        
        //        cout <<endl <<FileSystemUtil::normalize("/a//abc")<<endl;
        //        TS_ASSERT(FileSystemUtil::getBranchPath("/a//abc/") == "/a//abc");
        //        TS_ASSERT();
    }
        
};
