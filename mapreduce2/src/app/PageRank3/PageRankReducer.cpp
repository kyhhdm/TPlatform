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
    //more info about the formula of pagerank:
    //http://www.limfinity.com/ir/kristen_thesis.pdf
    
    PageRankValue value;
    const double damping = 0.85;
    while(values.hasMore()){
        PageRankValue* pValue = (PageRankValue*)(values.next());
        value.pagerank += pValue->pagerank;
        if(pValue->linkoutNumber > 0){
            value.linkoutNumber = pValue->linkoutNumber;
            value.linkoutURLs = pValue->linkoutURLs;
            value.totalNumber = pValue->totalNumber;
        }
    }
    
    //cout << "reducer: " << *(char**)key << " " << value.pagerank << endl;
    value.pagerank += (1 - damping)/(double)value.totalNumber;
    collector.collect(key, &value);
    value.linkoutURLs = NULL;
    
    return true;
}
