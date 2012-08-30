/**
 * @file PennySortDll.cpp
 * @description 
 *  test simple map reduce task
 *
 * @author Peng Bo
 * @date 2008-5-16
 * */
#include "PennySortRecord.hpp"
#include "PennySortMapper.hpp"
#include "PennySortReducer.hpp"
#include "mapred/MapReduceLib.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

REGISTER_CLASS_BEGIN();
REGISTER_FEEDER_CLASS(PennyRecordKey,PennyRecordValue);
REGISTER_WRITER_CLASS(PennyRecordKey,PennyRecordValue);
REGISTER_CLASS(PennyRecordKeyHelper);
REGISTER_CLASS(PennySortMapper);
REGISTER_CLASS(PennySortReducer);
REGISTER_CLASS_END(); 

