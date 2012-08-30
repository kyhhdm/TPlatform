/**
 * @file PageLenMapper.cpp
 *
 * */
#include "PageLenMapper.hpp"
#include "mapred/Collector.hpp"
#include <stdio.h>
#include <SimpleParser/parser.h>
#include <iostream>

using namespace std;
using namespace mapreduce;


PageLenMapper::PageLenMapper()
{
 
}

PageLenMapper::~PageLenMapper()
{
 
}

bool PageLenMapper::map(const void* key, const void* value, Collector& collector) const
{
    //<char*, char*> as mapper intput
    //<int,char*> as mapper output

    int bodyLen = strlen(*(char**)value);

    collector.collect( &bodyLen, key);

    return true;
}

