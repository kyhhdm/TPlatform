/** 
 * @file TestClassLoader.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-17
 */
#ifndef _TEST_MAPREDUCE_CLASSLOADER_HPP
#define _TEST_MAPREDUCE_CLASSLOADER_HPP

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "ClassLoader.hpp"
#include "MapReduceException.hpp"
#include <time.h>
#include <string>
#include <iostream>

using namespace std;
using namespace mapreduce;
  
class ClassLoaderFixture : public CxxTest::GlobalFixture{
    public:    
    bool setUpWorld() { 
        return true; 
    }

    bool tearDownWorld() { 
        return true; 
    }

    bool setUp() { 
        return true; 
    }    
    bool tearDown() { 
        return true; 
    }
};


static ClassLoaderFixture ClassLoaderFixture;

class TestInterface{
public:
    virtual void hello()=0;
};

class TestClassLoader: public CxxTest::TestSuite
{

    //==========helper functions=================
    void doTestAll(const char* soFile)
    {
        ClassLoader *loader = new ClassLoader(soFile);

        void *test;
        
        TS_ASSERT_THROWS_NOTHING((TestInterface *)loader->createInstance("TestReader", test));
        TS_ASSERT(test != NULL);
        if(test) ((TestInterface *)test)->hello();
        delete test;

        TS_ASSERT_THROWS_NOTHING((TestInterface *)loader->createInstance("TestWriter", test));
        TS_ASSERT(test != NULL);
        if(test) ((TestInterface *)test)->hello();
        delete test;

        TS_ASSERT_THROWS_NOTHING((TestInterface *)loader->createInstance("TestTemplate<int>", test));
        TS_ASSERT(test != NULL);
        if(test) ((TestInterface *)test)->hello();
        delete test;

        TS_ASSERT_THROWS_NOTHING((TestInterface *)loader->createInstance("TestTemplate<float>", test));
        TS_ASSERT(test != NULL);
        if(test) ((TestInterface *)test)->hello();
        delete test;

        TS_ASSERT_THROWS((TestInterface *)loader->createInstance("TestXXX", test),ClassLoaderError);

        delete loader;
    }

public:

    //==============test goes here =====================

    void testLocalAll(void)	{
       doTestAll("SimpleDll.dll");
    }


};


#endif /* _TEST_TFSMASTER_FileStream_HPP */

