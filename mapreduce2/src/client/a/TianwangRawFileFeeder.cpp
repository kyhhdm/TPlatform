/**
* @file TianwangRawFileFeeder.cpp
* @description 
*  RecordReader for Tianwang Raw Web Page File
*  <char*,char*> is the key value type, while use void*
*  it turns to <char**, char**>, be careful
* @add by Chen Rishan
*  it turns to <string*, string*> can work too
**/

#include "TianwangRawFileFeeder.hpp"
#include "FileStream.hpp"
#include "MapReduceException.hpp"
#include <TWReader.h>
#include <iostream>

using namespace std;
using namespace mapreduce;
//using namespace boost;

void TianwangRawFileFeeder::open(FileStream* stream)
{
    if((m_reader = new TWReader(stream->getFilename().c_str())) != NULL){
        return;
    }
    else throw FSError("TianwangRawFileFeeder::open failed.");
}

void TianwangRawFileFeeder::close()
{
    if(m_reader) delete m_reader;
    m_reader = NULL;
}

bool TianwangRawFileFeeder::next(void*& key, void*& value)
{
    try{
        const TWReader::T_PageRecord* record =  m_reader->nextRecord();
        
        if(record){
            *(char**)key = (char*)record->url.c_str();
            *(char**)value = (char*)record->body.c_str();

            return true;
        }

    }catch (TWReaderException &E) {
        cout << E.what() << endl;
    } catch (exception &E) {
        cout << E.what() << endl;
    }
    
    //return a nul object
    key = value = NULL;
    return false;

}

bool TianwangRawFileFeeder::releaseKeys(void*& keys)
{
    if(keys != NULL){
        char** pkeys = (char**)keys;
        delete[] pkeys;
    }
    return true;
}

bool TianwangRawFileFeeder::releaseValues(void*& values)
{
    if(values != NULL){
        char** pvalues = (char**)values;
        delete[] pvalues;
    }
    return true;
}
