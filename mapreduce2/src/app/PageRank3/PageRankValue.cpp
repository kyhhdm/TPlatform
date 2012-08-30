/**
 * @file PageRankValue.cpp
 *
 * */

#include "PageRankValue.hpp"
#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;
using namespace mapreduce;


PageRankValue::PageRankValue()
{
    pagerank = 0;
    linkoutNumber = 0;
    linkoutURLs = NULL;
    totalNumber = 0;
}

PageRankValue::~PageRankValue()
{
    if(linkoutURLs != NULL){
        for(int i = 0; i < linkoutNumber; i ++){
            //if(linkoutURLs[i] != NULL)
                //delete[] linkoutURLs[i];
        }
        //delete[] linkoutURLs;
        //TODO: memory leak here
        linkoutURLs = NULL;
        linkoutNumber = 0;
        totalNumber = 0;
    }
}

namespace mapreduce{

std::ostream& operator << (std::ostream& out, const PageRankValue& value)
{
    out << value.pagerank;
    out << value.linkoutNumber;
    out << value.totalNumber;
    int length = 0;
    for(int i = 0; i < value.linkoutNumber; i ++){
        length = strlen(value.linkoutURLs[i]);
        out << length;
        out << value.linkoutURLs[i];
    }
                                                 
    return out;
}                                                          
 
std::istream& operator >> (std::istream& in, PageRankValue& value)
{
    if(value.linkoutURLs != NULL){
        for(int i = 0; i < value.linkoutNumber; i ++){
            delete[] value.linkoutURLs[i];
        }
        delete[] value.linkoutURLs;
        value.linkoutURLs = NULL;
        value.linkoutNumber = 0;
    }
    in >> value.pagerank >> value.linkoutNumber >> value.totalNumber;
    int length = 0;
    value.linkoutURLs = new char*[value.linkoutNumber];
    for(int i = 0; i < value.linkoutNumber; i ++){
        in >> length;
        value.linkoutURLs[i] = new char[length+1];
        in >> value.linkoutURLs[i];
        value.linkoutURLs[length] = 0;
    }
    return in;
}
    
Archive& operator << (Archive& archive, const PageRankValue& value)
{
    archive.getBuffer()->appendData(&value, sizeof(PageRankValue) );
    for(int i = 0; i < value.linkoutNumber; i ++){
        archive.getBuffer()->appendZString(value.linkoutURLs[i]);
    }
    return archive;
}

Archive& operator >> (Archive& archive, PageRankValue*& value)
{
    PageRankValue* tmp = (PageRankValue*)archive.getBuffer()->readData(sizeof(PageRankValue) );
    if(tmp == NULL){
        value->pagerank = 0;
        value->linkoutNumber = 0;
        return archive;
    }
    value->pagerank = tmp->pagerank;
    value->linkoutNumber = tmp->linkoutNumber;
    value->totalNumber = tmp->totalNumber;
    
    assert(value->linkoutNumber >= 0);
    
    if(value->linkoutURLs != NULL){
        delete[] value->linkoutURLs;
        value->linkoutURLs = NULL;
    }
    
    if(value->linkoutNumber > 0){
        value->linkoutURLs = new char*[value->linkoutNumber];
        for(int i = 0; i < value->linkoutNumber; i ++){
            value->linkoutURLs[i] = archive.getBuffer()->readZString();
        }
    }
    return archive;
}


}
