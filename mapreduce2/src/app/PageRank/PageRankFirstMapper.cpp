/**
 * @file PageRankFirstMapper.cpp
 *
 * */
#include "PageRankFirstMapper.hpp"
#include "Collector.hpp"
#include "PageRankValue.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <tianwang/TWReader.h>
#include <boost/regex.hpp>


using namespace std;
using namespace mapreduce;

PageRankFirstMapper::PageRankFirstMapper()
{
}

PageRankFirstMapper::~PageRankFirstMapper()
{
}

bool PageRankFirstMapper::map(const void* key, const void* value, Collector& collector) const
{
    if(key && value){
        string content;
        content.erase();
        char c;
        char** pvalue = (char**)value;
        while((c = **pvalue)){
            if(content.capacity() == content.size() )
                content.reserve(content.capacity() * 3);
            content.append(1, c);
            (*pvalue) ++;
        }

        vector<string> linkoutUrl;
        boost::regex e("<\\s*[aA]\\s+[^>]*href\\s*=\\s*\"(http[^\"]*)\"", boost::regex::normal | boost::regbase::icase);
            
        boost::sregex_token_iterator iter(content.begin(), content.end(), e, 1);
        boost::sregex_token_iterator j;
            
        //url<\n>url<\n>url-...
        PageRankValue newValue;
        //initial weight is 1
        newValue.pagerank = 1;
        while(iter != j){
            string linkoutUrl = *(iter);
            newValue.linkoutURLs.push_back(linkoutUrl);
            iter ++;
        }
        int linkoutNum = newValue.linkoutURLs.size();
        //assign average weight for each out-node
        double dividedPretreat = 0;
        if(linkoutNum > 0)
            dividedPretreat = 1/(double)linkoutNum;
            
        for(int i = 0; i < linkoutNum; i ++){
            PageRankValue linkoutValue;
            linkoutValue.pagerank = dividedPretreat;
            const char* url = newValue.linkoutURLs[i].c_str();
            collector.collect(&url, &linkoutValue);
        }
            
        //send the linkout list
        collector.collect(key, &newValue);
    }
    
    return true;
}

