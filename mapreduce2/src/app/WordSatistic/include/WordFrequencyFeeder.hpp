/**
 * @file WordFrequencyFeeder.hpp
 * @description convert the data in the chunk into <key,value> pairs which store in the temporay local files
 *
 **/

#ifndef WORDFREQUENCYFEEDER_HPP
#define WORDFREQUENCYFEEDER_HPP

#include "IFeeder.hpp"
#include "IMapReduce.hpp"
#include <fstream>


DECLARE_FACTORY(IFeeder);

class TWReader;

namespace mapreduce{

    class WordFrequencyFeeder : public IFeeder {
        public:
            /**
             * open the file in current directory
             *
             */
            int open(std::string fileName) ;

            /**
             * return value: -1 means the operation was failed;
             *                1 means it was success.
             */
            int close() ;

            /**
             * return value: the next pointer to the KeyValue object
             *               if the pointer is NULL, means the it feeds all the data
             */
            boost::shared_ptr<KeyValue> next() ;

        private:
            TWReader    *m_reader;

    };

}
#endif
