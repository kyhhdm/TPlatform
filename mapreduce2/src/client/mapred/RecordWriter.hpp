#ifndef TPLATFORM_MAPREDUCE_IRECORDWRITER
#define TPLATFORM_MAPREDUCE_IRECORDWRITER

#include <string>

namespace mapreduce{
    class RegionIterator;
    class FileStream;

    /**
     * RecordWriter supplies a interface to append record to a record set file
	 * Define no open method, for normally constructor is better place to initialize.
     * */
    class RecordWriter {
        public:
            virtual ~RecordWriter(){}

            /**
            * Initialize the writer, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false) = 0;

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream) = 0;

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close() = 0;


            /**
             * Append a record.
			 * @param key , key to append
			 * @param value , value to append
             * @return : true if success
             *           false if fail.
             */
            virtual bool append(const void* key, const void* value) = 0;

            /**
            * Append a record.
            * This call append a memory block as a record directly.
            * This method is design for in memory sorting.
            * @param iter, records memory regions 
            * @return : true if success
            *           false if fail, for example, reading reach the end.
            */
            virtual bool append(RegionIterator& iter) = 0;

    };
}

#endif
