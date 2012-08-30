/**
 * @file WordFrequencyFeeder.cpp
 * the implementation of WordFrequencyFeeder.hpp
 *
 * @author Chen Rishan, PengBo
 * @date 2007-12-09
 * */

#include "WordFrequencyFeeder.hpp"
#include "KeyValue.hpp"
#include <TWReader.h>
#include <iostream>

using namespace std;
using namespace mapreduce;
using namespace boost;


IMPLEMENT_FACTORY(IFeeder, WordFrequencyFeeder);

//===============================================
int WordFrequencyFeeder::open(string fileName)
{
    if(m_reader = new TWReader(fileName.c_str())){
        return 1;
    }
    else return -1;
}

int WordFrequencyFeeder::close()
{
    delete m_reader;
    m_reader = NULL;
    return 1;
}

shared_ptr<KeyValue> WordFrequencyFeeder::next()
{
    KeyValueField key;
    KeyValueField value;
    
    try{
        const TWReader::T_PageRecord* record =  m_reader->nextRecord();
        
        if(record){
            key.appendStr(record->url);
            value.appendStr(record->body);

            KeyValue* nextKeyValue = new KeyValue(1);
            nextKeyValue->setKey(key);
            nextKeyValue->setValue(0,value);
            shared_ptr<KeyValue> pNextKeyValue(nextKeyValue);
            return pNextKeyValue;
        }

    }catch (TWReaderException &E) {
        cout << E.what() << endl;
    } catch (exception &E) {
        cout << E.what() << endl;
    }
    
    //return a nul object, it sucks.
//    key.appendStr("");
//    value.appendStr("");
//    KeyValue* nextKeyValue = new KeyValue(1);
//    nextKeyValue->setKey(key);
//    nextKeyValue->setValue(0,value);
//    shared_ptr<KeyValue> pNextKeyValue(nextKeyValue);
    KeyValue* nextKeyValue = NULL;
    shared_ptr<KeyValue> pNextKeyValue(nextKeyValue);
    return pNextKeyValue;
}

