/**
 * @file WordCountMapper.cpp
 *
 * */
#include "WordCountMapper.hpp"
#include "Collector.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace mapreduce;


WordCountMapper::WordCountMapper()
{
}

WordCountMapper::~WordCountMapper()
{
}

bool WordCountMapper::map(const void* key, const void* value, Collector& collector) const
{
    int num = 1;
    collector.collect(value, &num);
        return true;
}

