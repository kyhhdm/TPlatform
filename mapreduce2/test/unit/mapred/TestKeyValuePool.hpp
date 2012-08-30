/** 
 * @file TestKeyValuePool.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-21
 */
#ifndef _TEST_MAPREDUCE_KEYVALUEPOOL_HPP
#define _TEST_MAPREDUCE_KEYVALUEPOOL_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "TaskConfigure.hpp"
#include "KeyValuePool.hpp"
#include "FileStream.hpp"
#include "RecordReader.hpp"
#include "TKeyValueFeeder.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;

class KeyValuePoolFixture : public CxxTest::GlobalFixture{
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


static KeyValuePoolFixture KeyValuePoolFixture;



class TestKeyValuePool: public CxxTest::TestSuite
{


    void doKeyValuePool()
    {
        RecordReader* reader = new TKeyValueFeeder<int,char*>();
        KeyValuePool keyPool(reader, true, 4);

        TS_ASSERT(keyPool.itemSize() == sizeof(int));

        void *key, *keyNext;

        keyPool.next(key);
        keyPool.next(keyNext);
        TS_ASSERT( (char*)key + keyPool.itemSize() == (char*)keyNext);
        keyPool.next(keyNext);
        TS_ASSERT( (char*)key + 2 * keyPool.itemSize() == (char*)keyNext);
        keyPool.next(keyNext);
        TS_ASSERT( (char*)key + 3 * keyPool.itemSize() == (char*)keyNext);

        //exceed block boundary, and new block allocated
        keyPool.next(keyNext);
        TS_ASSERT( (char*)key + 4 * keyPool.itemSize() != (char*)keyNext);

        keyPool.clear();
        keyPool.next(key);
        TS_ASSERT( (char*)keyNext + keyPool.itemSize() == (char*)key);
        
    }

    void doKeyValuePoolIter()
    {
        RecordReader* reader = new TKeyValueFeeder<int,char*>();
        KeyValuePool keyPool(reader, true, 10);

        TS_ASSERT(keyPool.itemSize() == sizeof(int));

        void *key;

        keyPool.next(key);
        int* pKey = (int*)key;
        for (int i =0 ;i < 10 ;i++) {
            pKey[i] = i;
        }


        keyPool.next(key);
        keyPool.next(key);
        keyPool.next(key);
        PoolKeyValueIterator iter = keyPool.iter(); 

        int val = 0;
        while(iter.hasMore()){
            TS_ASSERT(*(int*)iter.next() == val);
            val ++;
        }
        TS_ASSERT(val == 4);

        keyPool.clear();
        keyPool.next(key);
        keyPool.next(key);        
        PoolKeyValueIterator iter2 = keyPool.iter(); 

        while(iter2.hasMore()){
            TS_ASSERT(*(int*)iter2.next() == val);
            val ++;
        }
        TS_ASSERT(val == 6);
        
        keyPool.clear();
        PoolKeyValueIterator iter3 = keyPool.iter(); 

        TS_ASSERT(iter3.hasMore() == false);

    }

public:

    //==============test goes here =====================

    void testKeyValuePool(void)	{
        doKeyValuePool();
    }

    void testKeyValuePoolIter(void)	{
        doKeyValuePoolIter();
    }
    
};


#endif /* _TEST_MAPREDUCE_KEYVALUEPOOL_HPP */

