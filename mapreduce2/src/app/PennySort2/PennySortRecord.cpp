/**
 * @file PennySortRecord.cpp
 *
 * */
#include "PennySortRecord.hpp"
#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include <boost/functional/hash.hpp>
#include <ext/hash_map>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace mapreduce;


bool PennyRecordKeyHelper::operator()(const void* key1, const void* key2) const
{
    return (memcmp(key1, key2, sizeof(PennyRecordKey) + sizeof(PennyRecordValue)) <= 0);
}

bool PennyRecordKeyHelper::equal(const void* key1, const void* key2) const
{
    return (memcmp(key1, key2, sizeof(PennyRecordKey) + sizeof(PennyRecordValue)) == 0);
}

unsigned int PennyRecordKeyHelper::hash(const void* key, int partitionNumber) const
{
    /* this hash function can't provide sorted result
    char* pEnd = ((PennyRecordKey*)key)->key + sizeof(PennyRecordKey);
    char save = *pEnd;

    //it's ok to set end of key as zero, atomic record gurantee memory writable
    *pEnd = 0;
    //boost::hash<char*> keyHash;
    
    __gnu_cxx::hash<const char*> keyHash;
    unsigned int ret = (unsigned int)keyHash(((PennyRecordKey*)key)->key);
    *pEnd = save;

    return ret;
    */

    //test on high 4bits, it means 16 reducers should be there
//     int  n = 0, minus = 1;
//     unsigned int val = partitionNumber;
//     while(val){
//         val = val >> 1;
//         n++;
//         minus = minus << 1;
//     }
//     minus = minus >> 2;
 
//     //cout << n << ".." << minus << endl;   
    
//     unsigned int theKey = *(unsigned int*)((PennyRecordKey*)key)->key;
//     return (theKey >> (32 - n -1)) - minus;
    char * theChar = (char* )((PennyRecordKey*)key)->key;
    double num = 0;
    int num1 = *theChar - ' ';  // key[0]
    num = num * 95 + num1;
    theChar += 4;
    int num2 = *theChar - ' ';  // key[4]
    num = num * 95 + num2;
    theChar += 4;
    int num3 = *theChar++ - ' '; // key[8]
    num = num * 95 + num3;

    unsigned partition = (unsigned) (num * partitionNumber / (95*95*95)); // [0, partitionNumber)
    //cout << num1 << ":" <<num2 << ":" <<num3  << ":" << num << ":" << partition << endl;
    return partition;
}

namespace mapreduce{

Archive& operator>>(Archive& ar, PennyRecordKey*& data)
{
    void* tmp = (void*)(ar.getBuffer()->readData(sizeof(PennyRecordKey)));
    if (tmp == NULL) data = NULL;
    else data = (PennyRecordKey*)tmp;
    return ar;
}

Archive& operator<<(Archive& ar, PennyRecordKey& data)
{
    ar.getBuffer()->appendData( (const void*)data.key, sizeof(PennyRecordKey));
    return ar;
}

Archive& operator>>(Archive& ar, PennyRecordValue*& data)
{
    PennyRecordValue* tmp = (PennyRecordValue*)(ar.getBuffer()->readData(sizeof(PennyRecordValue)));
    if (tmp == NULL) data = NULL;
    else data = tmp;
    return ar;
}

Archive& operator<<(Archive& ar, PennyRecordValue& data)
{
    ar.getBuffer()->appendData( (const void*)data.value, sizeof(PennyRecordValue));
    return ar;
}

}
