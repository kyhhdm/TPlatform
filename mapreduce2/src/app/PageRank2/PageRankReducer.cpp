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
        if(pValue->urlNumber > 0){
            if(value.linkoutURLs != NULL && value.urlNumber > 0){
                char** temp = new char*[value.urlNumber + pValue->urlNumber];
                memcpy(temp, value.linkoutURLs, value.urlNumber * sizeof(char*) );
                memcpy(temp + value.urlNumber, pValue->linkoutURLs, pValue->urlNumber * sizeof(char*) );
                value.urlNumber += pValue->urlNumber;
                delete[] value.linkoutURLs;
                value.linkoutURLs = temp;
            }
            else{
                value.urlNumber = pValue->urlNumber;
                value.linkoutURLs = pValue->linkoutURLs;
            }
        }
        count ++;
    }
    
    collector.collect(key, &value);
    
    return true;
}
