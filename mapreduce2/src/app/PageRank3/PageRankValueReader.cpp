/**
 * @file	PageRankValueReader.cpp
 * read the raw data(take from http://www.limfinity.com/ir/) into the PageRankValue archive stream	
 * 
 * @author	Chen Rishan, 	
 * @date	07/09/2008 04:33:51 PM CST
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "PageRankValue.hpp"
#include "TKeyValueWriter.hpp"
#include "FileStreamLocal.hpp"

using namespace std;
using namespace mapreduce;

int main(int argc, char** argv)
{
    if(argc != 3){
        cout << "Usage: pagerankReader <inputfilename> <outputfilename>" << endl;
        return -1;
    }
    ifstream fin(argv[1], ios::in);
    vector<string> urls;
    PageRankValue* pValue;
    string url;
    int urlNumber, linkoutNumber, temp;
    fin >> urlNumber >> linkoutNumber;
    int i = 0;
    for(i = 0; i < urlNumber; i ++){
        fin >> temp >> url;
        urls.push_back(url);
    }
    pValue = new PageRankValue[urlNumber];
    vector<int> *pRecords = new vector<int>[urlNumber];
    int index, linkout;
    double pagerank = 1/(double)urlNumber;
    for(i = 0; i < linkoutNumber; i ++){
        fin >> index >> linkout;
        index --;
        linkout --;
        pValue[index].linkoutNumber ++;
        pRecords[index].push_back(linkout);
    }
    for(i = 0; i < urlNumber; i ++){
        pValue[i].pagerank = pagerank;
        pValue[i].totalNumber = urlNumber;
        pValue[i].linkoutURLs = new char*[pValue[i].linkoutNumber];
        for(int j = 0; j < pValue[i].linkoutNumber; j ++){
            int length = urls[ pRecords[i][j] ].size();
            pValue[i].linkoutURLs[j] = new char[length + 1];
            memcpy(pValue[i].linkoutURLs[j], urls[ pRecords[i][j] ].c_str(), length * sizeof(char) );
            pValue[i].linkoutURLs[j][length] = 0;
        }
    }
    
    TKeyValueWriter<char*,PageRankValue> writer;
    writer.initialize(8*1024*1024, true);
    writer.open(new FileStreamLocal(argv[2], FileStream::Append, false));
    
    for(i = 0; i < urlNumber; i ++){
        const char* url = urls[i].c_str();
        writer.append(&url, &pValue[i]);
    }

    //release source
    writer.close();
    for(i = 0; i < urlNumber; i ++){
        if(pValue[i].linkoutNumber > 0){
            for(int j = 0;j < pValue[i].linkoutNumber; j ++){
                delete[]pValue[i].linkoutURLs[j];
            }
            delete[] pValue[i].linkoutURLs;
        }
    }
    delete[]pValue;
    delete[]pRecords;
    cout << "read raw data and convert into TKeyValue data successfully" << endl;
    return 0;
}

