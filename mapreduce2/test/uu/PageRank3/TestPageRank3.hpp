/** 
 * @file TestPageRank.hpp
 * .
 * 
 * @author Chen Rishan
 * @date 2008-06-24
 */
#ifndef _TESTPAGERANK_HPP
#define _TESTPAGERANK_HPP 1

#include <cxxtest/TestSuite.h>
#include "TianwangRawFileFeeder.hpp"
#include "FileStream.hpp"
#include "FileStreamLocal.hpp"
#include "PageRank3/PageRankValue.hpp"
#include "TKeyValueFeeder.hpp"
#include "TKeyValueWriter.hpp"
#include <tianwang/TWReader.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace mapreduce;

class TestPageRank: public CxxTest::TestSuite 
{
public:
    
    void testTKeyValueFeeder(){
    
        TKeyValueFeeder<char*, PageRankValue> feeder;
        feeder.initialize(0, true);
        feeder.open(new FileStreamLocal("hollins.dat", FileStream::ReadOnly, false));
        //feeder.open(new FileStreamLocal("test.par", FileStream::ReadOnly, false));
        
        void* key = feeder.createKeys();
        void* value = feeder.createValues();
        void* doKey = key;
        void* doValue = value;
        int count = 0;
        vector<string> test;
     
        while(feeder.next(doKey, doValue) ){
            cout << "url " << *(char**)doKey << " "<< ((PageRankValue*)doValue)->pagerank << " " << ((PageRankValue*)doValue)->linkoutNumber << " " << ((PageRankValue*)doValue)->totalNumber << endl;
            for(int i = 0; i < ((PageRankValue*)doValue)->linkoutNumber; i ++){
                cout << "it's z! " << ((PageRankValue*)doValue)->linkoutURLs[i] << endl;
            }
            feeder.flush();
            count ++;
        }
        
        cout << count << endl;

    }
    void testArchive(){
        PageRankValue value1;
        value1.pagerank = 0.88;
        value1.linkoutNumber = 3;
        value1.linkoutURLs = new char*[3];
        char* temp = "asfd12345";
        char* temp2 = "sfasfd1234512943==123";
        char* temp3 = "asfffsfdasfsdf45";
        value1.linkoutURLs[0] = new char[strlen(temp)+1];
        value1.linkoutURLs[1] = new char[strlen(temp2)+1];
        value1.linkoutURLs[2] = new char[strlen(temp3)+1];
        memcpy(value1.linkoutURLs[0], temp, strlen(temp));
        memcpy(value1.linkoutURLs[1], temp2, strlen(temp2));
        memcpy(value1.linkoutURLs[2], temp3, strlen(temp3) );
        value1.linkoutURLs[0][strlen(temp)] = 0;
        value1.linkoutURLs[1][strlen(temp2)] = 0;
        value1.linkoutURLs[2][strlen(temp3)] = 0;
        
        char* pkey = "werwesdfsdfr";

        TKeyValueWriter<char*, PageRankValue> writer;
        writer.initialize(8*1024, true);
        writer.open(new FileStreamLocal("test.par", FileStream::Append, false));
        writer.append(&pkey, &value1);
        writer.close();
        
        TKeyValueFeeder<char*, PageRankValue> feeder;
        feeder.initialize(0, true);
        feeder.open(new FileStreamLocal("test.par", FileStream::ReadOnly, false));
        
        void* key = feeder.createKeys();
        void* value = feeder.createValues();
        void* doKey = key;
        void* doValue = value;
        feeder.next(doKey, doValue);
        TS_ASSERT_SAME_DATA(*(char**)doKey, pkey, strlen(pkey) );
        TS_ASSERT_EQUALS(((PageRankValue*)doValue)->pagerank, value1.pagerank);
        TS_ASSERT_EQUALS(((PageRankValue*)doValue)->linkoutNumber, value1.linkoutNumber);
        for(int i = 0; i < value1.linkoutNumber; i ++){
            TS_ASSERT_SAME_DATA(((PageRankValue*)doValue)->linkoutURLs[i], value1.linkoutURLs[i], strlen(value1.linkoutURLs[i]));
        }
        feeder.releaseKeys(key);
        feeder.releaseValues(value);
        feeder.close();
    }
};


#endif /* _TESTPAGERANKMAPPER_HPP */
