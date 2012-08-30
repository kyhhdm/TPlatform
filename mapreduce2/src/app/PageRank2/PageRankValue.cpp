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
    urlNumber = 0;
    linkoutURLs = NULL;
}

PageRankValue::~PageRankValue()
{
    if(linkoutURLs != NULL){
        for(int i = 0; i < urlNumber; i ++){
            //if(linkoutURLs[i] != NULL)
                //delete[] linkoutURLs[i];
        }
        //cout << "come here" << endl;
        //delete[] linkoutURLs;
        //cout << "come here2" << endl;
        linkoutURLs = NULL;
        urlNumber = 0;
    }
}

namespace mapreduce{

std::ostream& operator << (std::ostream& out, const PageRankValue& value)
{
    out << value.pagerank;
    out << value.urlNumber;
    int length = 0;
    for(int i = 0; i < value.urlNumber; i ++){
        length = strlen(value.linkoutURLs[i]);
        out << length;
        out << value.linkoutURLs[i]; 
    }
                                                 
    return out;
}                                                          
 
std::istream& operator >> (std::istream& in, PageRankValue& value)
{
    if(value.linkoutURLs != NULL){
        for(int i = 0; i < value.urlNumber; i ++){
            delete[] value.linkoutURLs[i];
        }
        delete[] value.linkoutURLs;
        value.linkoutURLs = NULL;
        value.urlNumber = 0;
    }
    in >> value.pagerank >> value.urlNumber;
    int length = 0;
    value.linkoutURLs = new char*[value.urlNumber];
    for(int i = 0; i < value.urlNumber; i ++){
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
    for(int i = 0; i < value.urlNumber; i ++){
        archive.getBuffer()->appendZString(value.linkoutURLs[i]);
    }
    return archive;
}

Archive& operator >> (Archive& archive, PageRankValue*& value)
{
    PageRankValue* tmp = (PageRankValue*)archive.getBuffer()->readData(sizeof(PageRankValue) );
    if(tmp == NULL){
        value = NULL;
        return archive;
    }
    value->pagerank = tmp->pagerank;
    value->urlNumber = tmp->urlNumber;
    assert(value->urlNumber >= 0);
    
    if(value->linkoutURLs != NULL){
        delete[] value->linkoutURLs;
        value->linkoutURLs = NULL;
    }
    if(value->urlNumber > 0){
        value->linkoutURLs = new char*[value->urlNumber];
        for(int i = 0; i < value->urlNumber; i ++){
            value->linkoutURLs[i] = archive.getBuffer()->readZString();
        }
    }
    return archive;
}


}
