/**
 * @file TianwangRawFileFeeder.hpp
 * @description 
 *  RecordReader for Tianwang Raw Web Page File
 *  <url, body> is output record, type is <char*, char*>
 * @add by Chen Rishan
 * type turns to <string*, string*> maybe more careful, but isnot efficient
 **/

#ifndef TIANWANGRAWFILEFEEDER_HPP
#define TIANWANGRAWFILEFEEDER_HPP

#include "RecordReader.hpp"
#include <fstream>

class TWReader;

namespace mapreduce{
    class RegionIterator;
    class FileStream;

    class TianwangRawFileFeeder : public RecordReader {
        public:
            virtual ~TianwangRawFileFeeder(){}

            /**
            * Initialize the reader, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false) {}

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream);

            /**
            * flush the stream buffers. 
            * @return : -1 means the operation was failed;
            *            1 means it was success.
            */
            virtual void flush() {}

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close() ;

            /**
            * Create Key Class object. 
            * @return : 
            *           
            */
            virtual void* createKeys(int number = 0){
                if (number <= 0){
                    return new char*[1];
                }
                else{
                    return new char*[number];
                }
            }

            /**
            * Get Key Class size. 
            * @return : 
            *           
            */
            virtual int getKeySize(){return sizeof(char*);}

            /**
            * Create Value Class object. 
            * @return : 
            *           
            */
            virtual void* createValues(int number = 0){
                if (number <= 0){
                    return new char*[1];
                }
                else{
                    return new char*[number];
                }
            }

            /**
            * Get Value Class size. 
            * @return : 
            *           
            */
            virtual int getValueSize(){return sizeof(char*);}

            /**
            * Access the next record.
            * User must provide key and value object, send their address in.
            * @param key [out], key read in
            * @param value [out], value read in
            * @return : true if success
            *           false if fail, for example, reading reach the end.
            */
            virtual bool next(void*& key, void*& value);

            /**
            * Access the next record.
            * This call create new key object by createKey call.
            * This method is design for in memory sorting.
            * Read in <key pointer, recordLen> pairs as index and sort on them.
            * @param key [out], key read in
            * @param iter [out], record regions
            * @return : true if success
            *           false if fail, for example, reading reach the end.
            */
            virtual bool next(void*& key, RegionIterator& iter){return false;}
            
            /**
             * release the pointer or pointers allocated when create keys
             * */
            virtual bool releaseKeys(void*& keys);
            
            /**
             * release the pointer or pointers allocated when create values
             * */
            virtual bool releaseValues(void*& values);


        private:
            TWReader    *m_reader;
    };
}
#endif
