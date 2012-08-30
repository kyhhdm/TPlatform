/**
 * @file MapReduceDll.cpp
 * @description 
 *  test simple map reduce task
 *
 * @author Peng Bo
 * @date 2008-4-21
 * */


#include "Mapper.hpp"
#include "Collector.hpp"
#include "Reducer.hpp"
#include "KeyValueIterator.hpp"
#include "TKeyValueFeeder.hpp"
#include "TKeyValueWriter.hpp"
#include "THashableComparable.hpp"
#include "TStringHashableComparable.hpp"
#include "ClassLoader.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

//=================MapReduceDll.hpp==============
class CharCountMapper: public Mapper{
    ~CharCountMapper() {;}
    bool map(const void* key, const void* value, Collector& collector) const{
        //<int, char*> as mapper intput
        //<char, int> as mapper output
        int outValue = 1;
        
        char* pData = *(char**)value;    

        while(*pData){
            collector.collect( pData, &outValue);
            ++pData;
        }

        return true;
    }
};


class CharCountReducer: public Reducer{
    ~CharCountReducer(){}
    bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const{
        //<char, int> as reducer intput
        //<char, int> as reducer output
        int outValue = 0;

        while(values.hasMore()){
            outValue += *(int*)values.next();
        }
        collector.collect( key, &outValue);

        return true;
    }
};


//======================================


//REGISTER_CLASS(CharCountMapper);
//REGISTER_CLASS(CharCountReducer);

REGISTER_CLASS_BEGIN();
//REGISTER_CLASS(TKeyValueFeeder<int\x02c char*>);
//REGISTER_CLASS(TKeyValueWriter<int\,char*>);
//REGISTER_CLASS(TKeyValueFeeder<char\,int>);
//REGISTER_CLASS(TKeyValueWriter<char\,int>);
REGISTER_FEEDER_CLASS(int,char*);
REGISTER_FEEDER_CLASS(char,int);
REGISTER_FEEDER_CLASS(char*,int);
REGISTER_WRITER_CLASS(int,char*);
REGISTER_WRITER_CLASS(char,int);
REGISTER_WRITER_CLASS(char*,int);
REGISTER_CLASS(THashableComparable<char>);
REGISTER_CLASS(THashableComparable<int>);
REGISTER_CLASS(TStringHashableComparable<char*>);
REGISTER_CLASS(CharCountMapper);
REGISTER_CLASS(CharCountReducer);
REGISTER_CLASS_END(); 

