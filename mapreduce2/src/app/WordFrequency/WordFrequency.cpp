/**
 * @file WordFrequencyDll.cpp
 * @description 
 *  test simple map reduce task
 *
 * @author Peng Bo
 * @date 2008-4-22
 * */


#include "WordFrequencyMapper.hpp"
#include "WordFrequencyReducer.hpp"
#include "mapred/MapReduceLib.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

REGISTER_CLASS_BEGIN();
REGISTER_FEEDER_CLASS(char*,int);
REGISTER_WRITER_CLASS(char*,int);
REGISTER_TEXTFILEWRITER_CLASS(char*,int);
REGISTER_CLASS(TStringHashableComparable<char*>);
REGISTER_CLASS(TianwangRawFileFeeder);
REGISTER_CLASS(WordFrequencyMapper);
REGISTER_CLASS(WordFrequencyReducer);
REGISTER_CLASS_END(); 

