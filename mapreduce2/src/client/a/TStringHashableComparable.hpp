/**
* @file TStringHashableComparable.hpp
* @description:
*	TStringHashableComparable is a template class implements HashableComparable interface.
*
* @date 2008-04-20
* */

#ifndef TPLATFORM_MAPREDUCE_TSTRINGHASHABLECOMPARABLE
#define TPLATFORM_MAPREDUCE_TSTRINGHASHABLECOMPARABLE

#include "HashableComparable.hpp"
#ifdef _WIN32_
#include <boost/functional/hash.hpp>
#else
#include <ext/hash_map>
#endif

namespace mapreduce{

	template<typename KeyType> 
	class TStringHashableComparable: public HashableComparable{
        public:

            /**
            * binary predicator for sort algorithm
            * 
            * @param key1,key2  :
            * @return : 
            *		true larger
            *		false otherwise
            *
            */
            virtual bool operator()(const void* key1, const void* key2) const{
				return (strcmp(*(KeyType*)key1 , *(KeyType*)key2) < 0);
			};

            /**
             * compare two keys
             * 
             * @param key1,key2  :
             * @return : 
			 *		true equal
             *		false otherwise
             *
             */
            virtual bool equal(const void* key1, const void* key2) const{
				return (strcmp(*(KeyType*)key1 , *(KeyType*)key2) == 0);
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
                #ifdef _WIN32_
                boost::hash<std::string> keyHash;
                return (unsigned int)keyHash(std::string(*(KeyType*)key)) % partitionNumber;
                #else
                __gnu_cxx::hash<const char*> keyHash;
                return (unsigned int)keyHash((char*)(*(KeyType*)key)) % partitionNumber;
                #endif
			};

            ~TStringHashableComparable() {;}
    };
}

#endif /* _HASHABLECOMPARABLE_HPP */
