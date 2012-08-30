/**
 * @file TestPath.hpp
 *
 * @author PengBo
 * @date 2007-09-19
 */
#ifndef _TEST_PATH_HPP
#define _TEST_PATH_HPP 

#include "fsdirectory/Path.hpp"
#include <cxxtest/TestSuite.h>
#include <ostream>
#include <iostream>
#include <fstream>


using namespace tfs;
using namespace std;

//
// This test suite shows what to do when your test case
// class cannot be instantiated statically.
// As an example, this test suite requires a non-default constructor.
//

class TestPath: public CxxTest::TestSuite
{

    void printPath(Path &path)
    {
        cout << "path.isPureDir() = " << path.isPureDir() << endl
             << "path.getFileName() = " << path.getFileName() << endl
             << "path.getDirName() = " << path.getDirName() << endl
             << "path.getFullPathName() = " << path.getFullPathName() << endl;
        cout << endl;
    }

public:

    void testBoostPath(void)
    {
        boost::filesystem::path path("//home/tfs//haha/do.doc");
        cout << endl << "test boost path on : //home/tfs//haha/do.doc" << endl;

        boost::filesystem::path::iterator iter = path.begin();
        for ( ; iter != path.end(); ++iter ){
            cout << " " << *iter ;
        }

        iter = path.begin();
        TS_ASSERT(*iter == "//home");
        ++iter;
        TS_ASSERT(*iter == "/" );
        ++iter;
        TS_ASSERT(*iter == "tfs" );
        ++iter;
        TS_ASSERT(*iter == "haha" );
        ++iter;
        TS_ASSERT(*iter == "do.doc" );


        cout << endl;

    }

    void testNullPath(void)
    {
        Path path("");
        
	cout << "test Path: <null>" << endl;
	TS_ASSERT(path.isPureDir() == false);
        TS_ASSERT(path.getFileName() == "");
        TS_ASSERT(path.getDirName() == "");

        printPath(path);
    }

    void testRootPath(void)
    {
        //#BUGTEST Bugs item #6
        Path path("/");
	cout << "test Path: /" << endl;
        TS_ASSERT(path.isPureDir() == true);
        TS_ASSERT(path.getFileName() == "");
        TS_ASSERT(path.getDirName() == "/");

        printPath(path);
    }

    void testRootPath2(void)
    {
        //#BUGTEST Bugs item #6
        Path path("//");
	    cout << "test Path: //" << endl;
        TS_ASSERT(path.isPureDir() == true);
        TS_ASSERT(path.getFileName() == "");
        TS_ASSERT(path.getDirName() == "/");

        printPath(path);
    }


    void testDoubleRoot(void)
    {
        Path path("//home/tfs/ok.doc");
	    cout << "test Path: //home/tfs/ok.doc" << endl;

        TS_ASSERT(path.isPureDir() == false);
        TS_ASSERT(path.getFileName() == "ok.doc");
        TS_ASSERT(path.getDirName() == "/home/tfs/");

        printPath(path);
    }

    void testNormalize(void)
    {
        Path path("/home/../home/ok.doc");
	    cout << "test Path: /home/../home/ok.doc" << endl;

        TS_ASSERT(path.isPureDir() == false);
        TS_ASSERT(path.getFileName() == "ok.doc");
        TS_ASSERT(path.getDirName() == "/home/");

        printPath(path);
    }

    void testGetDirName(void)
    {
        Path path("/home/subdir/");
	    cout << "test Path: /home/subdir/" << endl;

        TS_ASSERT(path.isPureDir() == true);
        TS_ASSERT(path.getFileName() == "");
        TS_ASSERT(path.getDirName() == "/home/subdir/");

        printPath(path);
    }

    void testGetFileName(void)
    {
        Path path("/home/file");
	    cout << "test Path: /home/file" << endl;

        TS_ASSERT(path.isPureDir() == false);
        TS_ASSERT(path.getFileName() == "file");
        TS_ASSERT(path.getDirName() == "/home/");

        printPath(path);
    }


    void testIter()
    {
        Path path("");

        Path::PathIterator iter = path.begin();

        TS_ASSERT(iter == path.end());
        TS_ASSERT(*iter == "");
        
        int unused;
        #define UNUSED(a) ((void*)a == NULL)
        UNUSED(unused);


    }
};

#endif /* _TEST_PATH_HPP */
