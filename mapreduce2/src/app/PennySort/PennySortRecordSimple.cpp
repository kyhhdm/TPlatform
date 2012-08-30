/**
 * @file PennySortRecord.cpp
 *
 * */
#include "PennySortRecord.hpp"
#include "mapred/Archive.hpp"
#include "mapred/ArchiveBuffer.hpp"
#include <boost/functional/hash.hpp>
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
    return false;
    //return (memcmp(key1, key2, sizeof(PennyRecordKey) + sizeof(PennyRecordValue)) == 0);
}

unsigned int PennyRecordKeyHelper::hash(const void* key, int partitionNumber) const
{
    return 0;

    //char* pEnd = ((PennyRecordKey*)key)->key + sizeof(PennyRecordKey);
    //char save = *pEnd;

    //it's ok to set end of key as zero, atomic record gurantee memory writable
    //*pEnd = 0;
    //boost::hash<char*> keyHash;
    //unsigned int ret = (unsigned int)keyHash(((PennyRecordKey*)key)->key);
    //*pEnd = save;

    //return ret;
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
