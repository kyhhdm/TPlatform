#ifndef TPLATFORM_MAPREDUCE_IREDUCER
#define TPLATFORM_MAPREDUCE_IREDUCER

#include "Collector.hpp"
#include "KeyValueIterator.hpp"

namespace mapreduce{

    /**
     * class Reduce supplies an interface to reduce a set of keyvalue records with 
     * same key to other set of keyvalue records
     *
     **/
    class Reducer{
        public:
            /**
             * Reduce input <Key, Values> pairs to output (Key',Value') pair
             *
             * @param key :
			 * @param values: 
             * @param collector :
             * @return : success/error code
             * @throws 
             *
             */
            virtual bool reduce(const void* key,KeyValueIterator& values,Collector& collector) const = 0;

            virtual ~Reducer() {};
    };
}

#endif
