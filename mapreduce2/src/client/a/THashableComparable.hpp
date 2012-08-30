/**
* @file THashableComparable.hpp
* @description:
*    THashableComparable is a template class implements HashableComparable interface.
*
* @date 2008-04-20
* */

#ifndef TPLATFORM_MAPREDUCE_THASHABLECOMPARABLE
#define TPLATFORM_MAPREDUCE_THASHABLECOMPARABLE

#include "HashableComparable.hpp"
#include <boost/functional/hash.hpp>

namespace mapreduce{

    template<typename KeyType> 
    class THashableComparable: public HashableComparable{
        public:

            /**
            * binary predicator for sort algorithm
            * 
            * @param key1,key2  :
            * @return : 
            *      true larger
            *      false otherwise
            *
            */
            virtual bool operator()(const void* key1, const void* key2) const{
                return (*(KeyType*)key1 > *(KeyType*)key2);
            };

            /**
             * compare two keys
             * 
             * @param key1,key2  :
             * @return : 
             *    true equal
             *    false otherwise
             *
             */
            virtual bool equal(const void* key1, const void* key2) const{
                return (*(KeyType*)key1 == *(KeyType*)key2);
            };

            /**
             * get hash code from a key
             * 
             * @param key:
             * @return : 
             * @throws 
             *
             */
            virtual unsigned int hash(const void* key, int partitionNumber) const{
                boost::hash<KeyType> keyHash;
                return (unsigned int)keyHash(*(KeyType*)key) % partitionNumber;
            };

            ~THashableComparable() {;}
    };
}

//Globe operator overloading for char*
//bool operator>(char* key1, char* key2)
//{
//    return (strcmp(key1,key2)>0);
//}
//
//bool operator==(char* key1, char* key2)
//{
//    return (strcmp(key1,key2)==0);
//}

#endif /* _THASHABLECOMPARABLE_HPP */
