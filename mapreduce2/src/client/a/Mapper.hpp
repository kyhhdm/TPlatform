#ifndef TPLATFORM_MAPREDUCE_IMAPPER
#define TPLATFORM_MAPREDUCE_IMAPPER 

namespace mapreduce{
	class Collector;

    class Mapper{
        public:

            /**
             * Map input (Key, Value) pair to output (Key',Value') pairs
             *
             * @param key  :
			 * @param value :
             * @param collector :
             * @return : success/error code
             * @throws 
             *
             */
            virtual bool map(const void* key, const void* value, Collector& collector) const = 0;

            virtual ~Mapper() {;}
    };
}

#endif /* _MAPPER_HPP */
