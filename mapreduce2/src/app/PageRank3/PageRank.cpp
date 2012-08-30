/**
 * @file PageRank.cpp
 * @description 
 *  calculate the web pages' pagerank
 *
 * @author Chen Rishan
 * @date 2008-06-22
 * */


#include "PageRankMapper.hpp"
#include "PageRankReducer.hpp"
#include "TextFileFeeder.hpp"
#include "Mapper.hpp"
#include "Collector.hpp"
#include "Reducer.hpp"
#include "KeyValueIterator.hpp"
#include "TKeyValueFeeder.hpp"
#include "TKeyValueWriter.hpp"
#include "TStringHashableComparable.hpp"
#include "ClassLoader.hpp"
#include "TextFileWriter.hpp"
#include "TianwangRawFileFeeder.hpp"
#include "PageRankValue.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

REGISTER_CLASS_BEGIN();
REGISTER_FEEDER_CLASS(char*,PageRankValue);
REGISTER_FEEDER_CLASS(char*,char*);
REGISTER_WRITER_CLASS(char*,PageRankValue);
REGISTER_WRITER_CLASS(char*,char*);
REGISTER_TEXTFILEWRITER_CLASS(char*,PageRankValue);
REGISTER_CLASS(TStringHashableComparable<char*>);
REGISTER_CLASS(PageRankMapper);
REGISTER_CLASS(PageRankReducer);
REGISTER_CLASS_END(); 

