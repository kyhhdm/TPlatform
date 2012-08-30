#ifndef TPLATFORM_MAPREDUCE_DIRECTCOLLECTOR
#define TPLATFORM_MAPREDUCE_DIRECTCOLLECTOR 

#include "Collector.hpp"

namespace mapreduce{
    class RecordWriter;

    class DirectCollector : public Collector{
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
        int collect(const void* key, const void* value);

        /**
        * Constructor
        * 
        */
        DirectCollector(RecordWriter* writer);

        /**
        * Destructor
        * 
        */
        ~DirectCollector() {;}
    private:
        RecordWriter* m_writer;
    };
}

#endif /* _DIRECTCOLLECTOR_HPP */
