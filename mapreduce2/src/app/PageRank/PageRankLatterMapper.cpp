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
        
    if(pvalue->linkoutURLs.size() > 0){
        newPagerank = pvalue->pagerank/(double)(pvalue->linkoutURLs.size() );
        for(int i = 0;i < pvalue->linkoutURLs.size(); i ++){
            string url = pvalue->linkoutURLs[i];
            PageRankValue newValue;
            newValue.pagerank = newPagerank;
            const char* purl = url.c_str();
            collector.collect(&purl, &newValue);
        }
    }
    collector.collect(key, pvalue);
               
    return true;
}

