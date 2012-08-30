/**
* @file Serializable.hpp
* @description:
*    Serializable is an interface to do object serialization/deserialization to/from string.
*
* @date 2008-07-7
* */

#ifndef TPLATFORM_MAPREDUCE_SERIALIZABLE
#define TPLATFORM_MAPREDUCE_SERIALIZABLE

#include <string>

namespace mapreduce{

    class Serializable{
        public:
        /**
        * Write object into a string by serialization
        * 
        * @param output: output string
        * @return : 
        *      true 
        *      false 
        *
        */
        virtual bool writeToString(std::string& output) const = 0;

        /**
         * Read in object from a string by deserialization
         * 
         * @param input:
         * @return : 
         *    true 
         *    false
         *
         */
        virtual bool readFromString(const std::string& input) = 0;
        
    };

}

#endif /* _SERIALIZABLE_HPP */
