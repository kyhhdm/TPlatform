/**
* @file HashableComparable.hpp
* @description:
*	HashableComparable is interface for operations on Key .
*
* @date 2008-04-2
* */

#ifndef TPLATFORM_MAPREDUCE_IHASHABLECOMPARABLE
#define TPLATFORM_MAPREDUCE_IHASHABLECOMPARABLE

namespace mapreduce{

    class HashableComparable{
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
            virtual bool operator()(const void* key1, const void* key2) const = 0;

            /**
             * compare two keys
             * 
             * @param key1,key2  :
             * @return : 
			 *		true equal
             *		false otherwise
             *
             */
            virtual bool equal(const void* key1, const void* key2) const = 0;

            /**
             * get hash code from a key
             * 
             * @param key:
             * @return : 
             * @throws 
             *
             */
            virtual unsigned int hash(const void* key, int partitionNumber) const = 0;

            virtual ~HashableComparable(){}
    };
}

#endif /* _HASHABLECOMPARABLE_HPP */
