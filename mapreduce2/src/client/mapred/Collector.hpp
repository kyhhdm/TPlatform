#ifndef TPLATFORM_MAPREDUCE_ICOLLECTOR
#define TPLATFORM_MAPREDUCE_ICOLLECTOR 

namespace mapreduce{

    class Collector{
        public:

            /**
             * Collect a <Key, Value> pair
             * 
             * @param key  :
             * @param value :
             * @return : success/error code
             * @throws 
             *
             */
            virtual int collect(const void* key, const void* value) = 0;

            virtual ~Collector() {;}
    };
}

#endif /* _COLLECTOR_HPP */
