/**
 * @file WordFrequencyKeyHasher.cpp
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#include "WordFrequencyKeyHasher.hpp"
#include "Buffer.hpp"
#include <iostream>

using namespace std;
using namespace mapreduce;

IMPLEMENT_FACTORY(IKeyHasher, WordFrequencyKeyHasher);

int WordFrequencyKeyHasher::hash(const KeyValueField& key) const
{
    string word;
    key.getStr(word);
    int h = 0, g;
    for(int i = 0; i < word.size(); i ++){
        h = (h << 4) + word[i];
        if(g = h & 0xf0000000){
            h = h ^ (g >> 24);
        }
        h = h ^ g;
    }
    return h;
}

