/**
 * @file PageLenDll.cpp
 * @description 
 *  test simple map reduce task
 *
 * @author Peng Bo
 * @date 2008-4-22
 * */

#include "PageLenMapper.hpp"
#include "PageLenReducer.hpp"
#include "mapred/MapReduceLib.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

REGISTER_CLASS_BEGIN();
REGISTER_FEEDER_CLASS(int,char*);
REGISTER_WRITER_CLASS(int,char*);
REGISTER_TEXTFILEWRITER_CLASS(int,char*);
REGISTER_CLASS(THashableComparable<int>);
REGISTER_CLASS(TianwangRawFileFeeder);
REGISTER_CLASS(PageLenMapper);
REGISTER_CLASS(PageLenReducer);
REGISTER_CLASS_END(); 

