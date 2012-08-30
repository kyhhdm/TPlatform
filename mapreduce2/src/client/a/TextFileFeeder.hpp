/**
 * @file TextFileFeeder.hpp
 * @description 
 *  RecordReader for Text File
 *  <lineno, line> is input record, type is <int, char*>
 *
 **/

#ifndef TEXTFILEFEEDER_HPP
#define TEXTFILEFEEDER_HPP

#include "RecordReader.hpp"
#include <fstream>


namespace mapreduce{
    class RegionIterator;
    class FileStream;
    class Archive;

    class TextFileFeeder : public RecordReader {
        public:
             TextFileFeeder();
             ~TextFileFeeder();

            /**
            * Initialize the reader, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
             void initialize(int bufferSize = 0, bool autoClearBuffer = false);

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
             void flush();

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
             void close();

            /**
            * Create Key Class object. 
            * @return : 
            *           
            */
            virtual void* createKeys(int number = 1){return new int[number];}

            /**
            * Get Key Class size. 
            * @return : 
            *           
            */
            virtual int getKeySize(){return sizeof(int);}

            /**
            * Create Value Class object. 
            * @return : 
            *           
            */
            virtual void* createValues(int number = 1){return new char*[number];}

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
             bool next(void*& key, void*& value);

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
            Archive* m_archive;
    };
  
}
#endif
