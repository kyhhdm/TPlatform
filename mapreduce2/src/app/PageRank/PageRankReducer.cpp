/**
 * @file PageRankReducer.cpp
 *
 * */
#include "PageRankReducer.hpp"
#include "KeyValueIterator.hpp"
#include "Collector.hpp"
#include "PageRankValue.hpp"
#include <string> 

using namespace std;
using namespace mapreduce;


bool PageRankReducer::reduce(const void* key, KeyValueIterator& values, Collector& collector) const
{
    //<url, pagerank, linkoutlist> as reducer intput
    //<url, newpagerank, linkoutlist> as reducer output
    
    //the formula of pagerank:
    //pr(a) - (1-d) = d * (pr(b)/l(b) + pr(c)/l(c) + ...)
    //d is the damping factor

    PageRankValue value;
    int count = 0;
    const double damping = 0.85;
    while(values.hasMore()){
        PageRankValue* pValue = (PageRankValue*)(values.next());
        value.pagerank += damping * pValue->pagerank;
        if(pValue->linkoutURLs.size() > 0){
            for(int i = 0; i < pValue->linkoutURLs.size(); i ++){
                value.linkoutURLs.push_back(pValue->linkoutURLs[i]);
            }
        }
        count ++;
    }
    
    collector.collect(key, &value);
    
    return true;
}
