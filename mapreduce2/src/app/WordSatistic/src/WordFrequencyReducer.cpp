/**
 * @file WordFrequencyReducer.cpp
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#include "WordFrequencyReducer.hpp"
#include "KeyValue.hpp"
#include "Buffer.hpp"
#include <iostream>

using namespace std;
using namespace mapreduce;
using namespace boost;


IMPLEMENT_FACTORY(IReducer, WordFrequencyReducer);


int WordFrequencyReducer::reduce(const vector<shared_ptr<KeyValue> >& inKeyValues, 
                                 vector<shared_ptr<KeyValue> >& outKeyValues) const
{
    int sum = 0;
    int freq;

    Buffer key;
    Buffer value;

    KeyValue* temp = inKeyValues[0].get();
    temp->getKey(key);
    
    for(int i = 0 ; i < inKeyValues.size() ; i++){
        inKeyValues[i]->getValue(0,value);
        value.getInt(freq);
        sum += freq;
    }

    value.clear();
    value.appendInt(sum);

    KeyValue* outKeyValue = new KeyValue(1);
    outKeyValue->setKey(key);
    outKeyValue->setValue(0,value);

    shared_ptr<KeyValue> pKeyValue(outKeyValue);
    outKeyValues.push_back(pKeyValue);
    return 1;
}
