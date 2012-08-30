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
//#include "PageRankMapper.hpp"
#include "TianwangRawFileFeeder.hpp"
#include "FileStream.hpp"
#include "FileStreamLocal.hpp"
#include "PageRank/PageRankValue.hpp"
#include "TKeyValueFeeder.hpp"
#include <tianwang/TWReader.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace mapreduce;

class TestPageRank: public CxxTest::TestSuite 
{
public:
    void testConvert(){
        //PageRankMapper mapper;
        char* key = "http://www.pku.edu.cn";
        char* value = "<a href=\"http://safari.awprofessional.com/?XmlId=0321113586\" class=\"external\">";
        
    }
    void testTianwangRawFileFeeder(){
        TianwangRawFileFeeder feeder;
        feeder.initialize(0, true);
        feeder.open(new FileStreamLocal("testpage.dat", FileStream::ReadOnly, false) );
        void* key = feeder.createKeys();
        void* value = feeder.createValues();
        void* doKey = key;
        void* doValue = value;
        int count = 0;
        while(feeder.next(doKey, doValue) ){
            
            //cout << "url: " << *(string*)doKey << endl;
            //cout << "body: " << *(string*)doValue << endl;
            
            feeder.flush();
            count ++;
        }
        cout << count << endl;
    }
    void testTWReader()
    {
        TWReader reader("testpage.dat");
        const TWReader::T_PageRecord * record;
        int count = 0;
        while((record = reader.nextRecord()) ){
            //cout << record->url << " " << record->body << endl;
            //cout << record->url << " " << record->date << endl;
            count ++;
        }
        cout << count << endl;
    }
    void testTKeyValueFeeder(){
        TKeyValueFeeder<char*, PageRankValue> feeder;
        feeder.initialize(0, true);
        feeder.open(new FileStreamLocal("sorted.dat", FileStream::ReadOnly, false));
        //feeder.open(new FileStreamLocal("result.dat.bak", FileStream::ReadOnly, false));
        
        void* key = feeder.createKeys();
        void* value = feeder.createValues();
        void* doKey = key;
        void* doValue = value;
        int count = 0;
        vector<string> test;
        /*
        int* p = (int*)(&test);
        int i;
        cout << "-----------" << endl;
        for(i = 0; i < sizeof(test)/sizeof(int); i ++){
            cout << *p << " ";
            p ++;
        }
        cout << endl << sizeof(test) << endl;
        cout << "-----------" << endl;
       
        test.push_back("setste\n");
        test.push_back("sesdftste\n");
        test.push_back("sdf12sesdftste\n");
        p = (int*)(&test);
        cout << "-----------" << endl;
        for(i = 0; i < sizeof(test)/sizeof(int); i ++){
            cout << *p << " ";
            p ++;
        }
        cout << endl << sizeof(test) << endl;
        cout << "-----------" << endl;
        */
        
        while(feeder.next(doKey, doValue) ){
            //cout << sizeof(PageRankValue) << " " << sizeof(vector<string>) << " "<< sizeof(double) << " " << sizeof(string) << endl;
            cout << "url" << *(char**)doKey << " "<< ((PageRankValue*)doValue)->pagerank << " " << ((PageRankValue*)doValue)->linkoutURLs.size() << endl;
            for(int i = 0; i < ((PageRankValue*)doValue)->linkoutURLs.size(); i ++){
                //cout << "it's z! " << ((PageRankValue*)doValue)->linkoutURLs[i] << endl;
            }
            feeder.flush();
            count ++;
        }
        
        cout << count << endl;

    }
};


#endif /* _TESTPAGERANKMAPPER_HPP */
