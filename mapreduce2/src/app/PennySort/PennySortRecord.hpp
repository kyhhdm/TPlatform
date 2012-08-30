/**
 * @file PennySortMapper.hpp
 * @description it is implementation of the interface mapper 
 *
 * */
#ifndef PennySortRecord_HPP
#define PennySortRecord_HPP

#include "mapred/HashableComparable.hpp"


namespace mapreduce{

    class Archive;

#pragma pack(push)
#pragma pack(1)
    class PennyRecordKey{
    public:
        char key[10];

        friend class Archive;
    };

    class PennyRecordValue{
    public:
        char value[90];

        friend class Archive;
    };

#pragma pack(pop)

    class PennyRecordKeyHelper: public HashableComparable{
    public:
        friend class PennyRecordKey;

        virtual bool operator()(const void* key1, const void* key2) const;
        virtual bool equal(const void* key1, const void* key2) const;
        virtual unsigned int hash(const void* key, int partitionNumber) const;
    };

    Archive& operator>>(Archive& ar, PennyRecordKey*& data);
    Archive& operator<<(Archive& ar, PennyRecordKey& data);

    Archive& operator>>(Archive& ar, PennyRecordValue*& data);
    Archive& operator<<(Archive& ar, PennyRecordValue& data);

}


#endif /* PennySortMAPPER_HPP:*/
