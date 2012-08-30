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
            string url = *(iter);
            linkoutUrl.push_back(url);
            iter ++;
        }
        int linkoutNum = linkoutUrl.size();
        //assign average weight for each out-node
        double dividedPretreat = 0;
        if(linkoutNum > 0)
            dividedPretreat = 1/(double)linkoutNum;
        
        int i = 0;

        for(i = 0; i < linkoutNum; i ++){
            PageRankValue linkoutValue;
            linkoutValue.pagerank = dividedPretreat;
            const char* purl = linkoutUrl[i].c_str();
            collector.collect(&purl, &linkoutValue);
        }
            
        //send the linkout list
        newValue.linkoutURLs = new char*[linkoutNum];
        newValue.urlNumber = linkoutNum;
        for(i = 0; i < linkoutNum; i ++){
            const char* purl = linkoutUrl[i].c_str();
            newValue.linkoutURLs[i] = const_cast<char*>(purl);
        }
        collector.collect(key, &newValue);
        delete[] newValue.linkoutURLs;
        newValue.linkoutURLs = NULL;
    }
    
    return true;
}

