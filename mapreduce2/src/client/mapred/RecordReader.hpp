/**
 * @file RecordReader.hpp
 * @description:
 *	RecordReader is interface for record I/O.
 *
 *  Important design decision here: 
 *	<Key,Value> pair are present by void*, which are pointers to memeory actually. 
 *	It's very fast, and give best performance for primitive data types.
 *  the crons is it's weak type safty, but it may be unresolvable in non-dynamical 
 *	language, such as c++.
 *
 * @date 2008-03-31
 * */

 
#ifndef TPLATFORM_MAPREDUCE_IRECORDREADER
#define TPLATFORM_MAPREDUCE_IRECORDREADER

#include <string>

namespace mapreduce{
    class RegionIterator;
    class FileStream;

    /**
     * RecordReader supplies a interface to extract record one by one a record set file
	 * Define no open method, for normally constructor is better place to initialize.
	 * 
     * */
    class RecordReader {
        public:

            virtual ~RecordReader(){}

            /**
            * Initialize the reader, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false) = 0;

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream) = 0;

            /**
            * flush the stream buffers. 
            * @return : -1 means the operation was failed;
            *            1 means it was success.
            */
            virtual void flush() = 0;

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close() = 0;

            /**
            * Create Key Class object. 
            * @return : 
            *           
            */
            virtual void* createKeys(int number = 0) = 0;

            /**
            * Get Key Class size. 
            * @return : 
            *           
            */
            virtual int getKeySize() = 0;

            /**
            * Create Value Class object. 
            * @return : 
            *           
            */
            virtual void* createValues(int number = 0) = 0;

            /**
            * Get Value Class size. 
            * @return : 
            *           
            */
            virtual int getValueSize() = 0;

            /**
             * Access the next record.
             * User must provide key and value object, send their address in.
			 * @param key [out], key read in
			 * @param value [out], value read in
             * @return : true if success
             *           false if fail, for example, reading reach the end.
             */
            virtual bool next(void*& key, void*& value) = 0;

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
            virtual bool next(void*& key, RegionIterator& iter) = 0;
            
            /**
             * release the pointer or pointers allocated when create keys
             * */
            virtual bool releaseKeys(void*& keys) = 0;
            
            /**
             * release the pointer or pointers allocated when create values
             * */
            virtual bool releaseValues(void*& values) = 0;


    };
}

#endif
