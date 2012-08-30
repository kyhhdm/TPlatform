/**
 * @file PageRankMapper.cpp
 *
 * */
#include "PageRankMapper.hpp"
#include "Collector.hpp"
#include "PageRankValue.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <tianwang/TWReader.h>

using namespace std;
using namespace mapreduce;

PageRankMapper::PageRankMapper()
{
}

PageRankMapper::~PageRankMapper()
{
}

bool PageRankMapper::map(const void* key, const void* value, Collector& collector) const
{
    const double damping = 0.85;
    if(key && value){
        PageRankValue* pValue = (PageRankValue*)value; 
        double probability = 0;
        if(pValue->linkoutNumber > 0){
            probability = 1/(double)pValue->linkoutNumber;
            for(int i = 0; i < pValue->linkoutNumber; i ++){
                PageRankValue newValue;
                newValue.linkoutNumber = 0;
                newValue.pagerank = damping * probability * pValue->pagerank;
                newValue.totalNumber = pValue->totalNumber;
                //cout << "map: " << *(char**)key << " " << pValue->linkoutURLs[i] << " " << newValue.pagerank << endl;
                collector.collect(&(pValue->linkoutURLs[i]), &newValue);
            }
        }
        pValue->pagerank = 0;
        collector.collect(key, pValue);
    }
    
    return true;
}

