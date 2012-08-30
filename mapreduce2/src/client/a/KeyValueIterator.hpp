#ifndef TPLATFORM_MAPREDUCE_KEYVALUEITERATOR
#define TPLATFORM_MAPREDUCE_KEYVALUEITERATOR

#include <vector>

namespace mapreduce{
    /**
     * class KeyValueIterator supplies an forward only iterator interface 
     * to access a set of key value records
     *
     **/
    class KeyValueIterator{
        public:
            /**
             * Test if there are more items left
             *
             *
             */
            virtual bool hasMore() = 0;

            /**
            * Get next record
            *
            * @return : void*
            *
            */
            virtual void* next() = 0;

            virtual ~KeyValueIterator() {};
    };

    class VectorKeyValueIterator: public KeyValueIterator{
        std::vector<void*>::iterator m_iter;
        std::vector<void*>::iterator m_end;
    public:
        VectorKeyValueIterator(std::vector<void*>& vec){
            m_iter = vec.begin();
            m_end = vec.end();
        }

        virtual bool hasMore(){ 
            return ( m_iter != m_end );
        }

        virtual void* next(){
            void *ret = *m_iter;
            ++m_iter;
            return ret;
        }

        virtual ~VectorKeyValueIterator() {};
    };
}

#endif
