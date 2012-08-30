/**
 * @file PageRankLatterMapper.cpp
 *
 * */
#include "PageRankLatterMapper.hpp"
#include "Collector.hpp"
#include "PageRankValue.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <tianwang/TWReader.h>
#include <boost/regex.hpp>


using namespace std;
using namespace mapreduce;


PageRankLatterMapper::PageRankLatterMapper()
{
}

PageRankLatterMapper::~PageRankLatterMapper()
{
}

bool PageRankLatterMapper::map(const void* key, const void* value, Collector& collector) const
{
    
    //the latter iteration, the input is the same as before
        
    PageRankValue* pvalue = (PageRankValue*)value;
    double newPagerank = 0;
        
    if(pvalue->urlNumber > 0){
        newPagerank = pvalue->pagerank/(double)(pvalue->urlNumber );
        for(int i = 0;i < pvalue->urlNumber; i ++){
            char* purl = pvalue->linkoutURLs[i];
            PageRankValue newValue;
            newValue.pagerank = newPagerank;
            collector.collect(&purl, &newValue);
        }
    }
    collector.collect(key, pvalue);
               
    return true;
}

