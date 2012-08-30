/**
 * @file WordFrequencyKeyComparison.cpp
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#include "WordFrequencyKeyComparison.hpp"
#include "KeyValue.hpp"
#include <iostream>

using namespace std;
using namespace mapreduce;

IMPLEMENT_FACTORY(IKeyComparison, WordFrequencyKeyComparison);

int WordFrequencyKeyComparison::compare(const KeyValueField& key1, const KeyValueField& key2) const
{
    string word1;
    string word2;
    key1.getStr(word1);
    key2.getStr(word2);
    if(word1 < word2){
        return -1;
    }
    if(word1 == word2){
        return 0;
    }
    if(word1 > word2){
        return 1;
    }
    return 0;
}
