/**
 * @file PageRankValue.cpp
 *
 * */

#include "PageRankValue.hpp"
#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include <iostream>
#include <cassert>

using namespace std;
using namespace mapreduce;


PageRankValue::PageRankValue()
{
    pagerank = 0;
}

PageRankValue::~PageRankValue()
{
}

namespace mapreduce{

std::ostream& operator << (std::ostream& out, const PageRankValue& value)
{
    int number = value.linkoutURLs.size();
    out << value.pagerank;
    out << number;
    for(vector<string>::const_iterator iter = value.linkoutURLs.begin(); iter != value.linkoutURLs.end(); iter ++){
        out << *iter;
    }
    return out;
}
 
std::istream& operator >> (std::istream& in, PageRankValue& value)
{
    int number = 0;
    string url;
    in >> value.pagerank >> number;
    for(int i = 0; i < number; i ++){
        in >> url;
        value.linkoutURLs.push_back(url);
    }
    return in;
}
    
Archive& operator << (Archive& archive, const PageRankValue& value)
{
    int number = value.linkoutURLs.size();
    vector<string> empty;
    archive.getBuffer()->appendData(&value.pagerank, sizeof(double) );
    archive.getBuffer()->appendData(&empty, sizeof(empty) );
    archive.getBuffer()->appendData(&number, sizeof(number) );
    for(vector<string>::const_iterator iter = value.linkoutURLs.begin(); iter != value.linkoutURLs.end(); iter ++ ){
        string url = *iter;
        archive.getBuffer()->appendZString(url.c_str());
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
    int* pNumber = (int*)archive.getBuffer()->readData(sizeof(int) );
    /*
    if(value != NULL){
        //before use the pointer, free it
        //delete value;
        value = NULL;
    }*/
    value = tmp;
    if(pNumber == NULL){
        return archive;
    }
    for(int i = 0; i < *pNumber; i ++){
        char* tmpUrl = archive.getBuffer()->readZString();
        assert(tmpUrl != NULL);
        string url;
        url.assign(tmpUrl);
        //cout << url << endl;
        value->linkoutURLs.push_back(url);
        //cout << "ok" << endl;
    }

    return archive;
}


}
