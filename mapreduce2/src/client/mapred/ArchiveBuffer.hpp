/**
 * @file ArchiveBuffer.hpp
 * @date 2008-01-07
 * @description:
 *  ArchiveBuffer is a buffer manager for archiver.
 *  It provide record level buffer management, but in fact no guarantee read 
 *  record's data lies continuously in memory. There are holes at the tail of
 *  buffers occasionally. To defeat this ugly discreate space access difficulty
 *  a set of acccessing method are provided.
 *
 *	For ReadOnly Buffer:
 *      Fill whole buffer with one read call to stream.
 *      Malloc new buffer when reading exceed the tail of the last buffer.
 *      It's difficult to decide when to release buffers, so provide a 
 *      commitReadRecord call,and let user decide that.
 *
 *	For Append Buffer:
 *      Use only one buffer, so the maximum record should be smaller than 
 *      buffer size.
 *		To support atomic record I/O, buffer provide commitAppendRecord call
 *      and track record boundary,then it guarantee that every buffer flush 
 *      will be multiple records without spilting.
 *
 * */

#ifndef TPLATFORM_MAPREDUCE_ARCHIVEBUFFER
#define TPLATFORM_MAPREDUCE_ARCHIVEBUFFER

#include <vector>
#include <string>

#include <mapred/FileStream.hpp>
#include <mapred/Region.hpp>

namespace mapreduce{
    class FileStream;

    class ArchiveBuffer{
        class Buffer{
            char* m_buffer;
            int   m_endPos;
            int   m_curPos;
			int	  m_recordEndPos;
            int   m_bufferSize;
        public:
            Buffer(int bufferSize);
            ~Buffer();

            /**
             * Get buffer start pointer
             **/  
            inline char* begin();

            /**
             * Get buffer end pointer
             **/  
            inline char* end();

            /**
             * Get buffer current access pointer
             **/  
            inline char* cur();

            /**
             * Get buffer current record end access pointer
             **/  
            inline char* recordEnd();

            /**
             * Set buffer current access pointer
             **/  
            inline void setCur(int pos);
            
            /**
             * Set buffer end pointer
             **/  
            inline void setTail(int pos);

            /**
             * Set buffer record end pointer
             **/  
			inline void setRecordEnd();
   
			/**
             * Cut all tail data from current access pointer to end
             **/  
            inline void cutTail();

            /**
            * Clear buffer , just for debug purpose
            **/  
            inline void clear();

        };

        static int defaultSize;
        static int defaultRecordSizeThreshold;
        int m_recordSizeThreshold;
        int m_bufferSize;
        std::vector<Buffer*> m_buffers;
        FileStream  *m_stream;
        FileStream::OpenMode m_mode;
		bool m_autoClearBuffer;
        int  m_endBufferId;
        std::vector<Region> m_regions;

        unsigned long long m_bufferOffset;
    public:

        /**
		* Constructor
		*
		* @param bufferSize : buffer size for underneath buffers.
		* @param autoClearBuffer : auto free read buffer when true, otherwise hold all read data
        */
        ArchiveBuffer(int bufferSize = defaultSize, bool autoClearBuffer = false);

        ~ArchiveBuffer();

        /**
        * Open a stream. 
		* @throws FSError : under fstream error, like open mode mismatch
        */
        void openStream(FileStream* stream);

        /**
         * Close the stream. 
		 * @throws FSError : under fstream error, like open mode mismatch
         */
        void closeStream();

		/**
         * Commit record to Append Archive buffer.
         *
         * ArchiveBuffer will take charge to guarantee the record atomicity.
         * So, user should call this to provide record boundary.
         *
         **/  
		void commitAppendRecord();

        /**
        * Set free read data to Read only Archive buffer.
        *
        * ArchiveBuffer will hold all read data in memory, until user tell it to release.
        * AutoClearBuffer is an open flag to indicate system to release buffers used by 
        * committed read operation.
        * AutoClearBuffer can not work on every read call, because there are no record boundary exist
        *
        * It's a good place to return current position here.
        *
        **/  
        int commitReadRecord();

        /**
         * Read in zero C string, <string><\0>
         *
         * @return : pointer to the returned ZString data
         *         : NULL if reach eof 
         * @throws BufferError : reading too large record which exceed buffer boundary
		 * @throws FSError : under fstream error
         **/  
        char* readZString(char endChar = '\0');

        /**
         * Read in Pascal string, <len><string data>
         *
         * @return : pointer to the returned PString data
         *         : NULL if reach eof 
         * @throws BufferError : reading too large record which exceed buffer boundary
		 * @throws FSError : under fstream error
         *
         **/  
        char* readPString(int& stringLen);

        /**
         * Read in data by length
         *
         * @return : pointer to the returned data
         *         : NULL if reach eof 
         * @throws BufferError : reading too large record which exceed buffer boundary
		 * @throws FSError : under fstream error
         *
         **/  
        char* readData(int dataSize);

        /**
         * Append zero C string, <string><\0>
         *
         * @return pointer to the appended ZString data
         * @throws BufferError : reading too large record which exceed buffer boundary
		 * @throws FSError : under fstream error
         *
         **/  
        char* appendZString(const char* data, char endChar = '\0');

        /**
         * Append Pascal string, <len><string data>
         *
         * @return pointer to the appended PString data
         * @throws BufferError : reading too large record wich exceed buffer boundary
		 * @throws FSError : under fstream error
         *
         **/  
        char* appendPString(const char* data, int len);

        /**
         * Append data by length
         *
         * @return pointer to the appended data
         * @throws BufferError : reading too large record wich exceed buffer boundary
		 * @throws FSError : under fstream error
         *
         **/  
        char* appendData(const void* data, int dataSize);

        /**
        * Accessors
        *
        **/
        inline FileStream* getFileStream();
        inline int getBufferSize();

        /**
        * Get current reading position
        * It's used to store record address in buffer space
        * 
        **/  
        int getCurPos();

        /**
        * Get current reading position
        * It's used to store record address in buffer space
        * 
        **/ 
        unsigned long long int getByteOffset();

        /**
        * Mapping buffer position to memory address.
        * It deal with the holes in buffers.
        * It's no thread-safe!
        *  
        * @param startPos, endPos : region define
        * @param recordIter : this is a iterator to access all non-continuous memory blocks
        * @return records number found in this region.
        **/  
        //int getRecord(int startPos, int endPos, RegionIterator& recordIter);
        RegionIterator getRecord(int startPos, int endPos);

    private:
        /**
         * Allocate new buffer and read in more data, 
         * and keep data record boundary integrate in buffer.
         *
         * @return data length read
		 * @throws FSError : under fstream error
         *
         **/  
        int readInNewBuffer();
         
        /**
         * Clear all data has been processed.(Free unused buffers)
         * CAUTION!!!
         *  All the pointers returned by read* functions before 
         *  will be invalided after this call.
         *
         **/  
        void clearBuffer();
    };


    //implementation of inline functions
    char* ArchiveBuffer::Buffer::begin(){
        return m_buffer;
    }

    char* ArchiveBuffer::Buffer::end(){
        return m_buffer + m_endPos;
    }

    char* ArchiveBuffer::Buffer::cur(){
        return m_buffer + m_curPos;
    }

    char* ArchiveBuffer::Buffer::recordEnd(){
        return m_buffer + m_recordEndPos;
    }
    
	void ArchiveBuffer::Buffer::setCur(int pos){
        m_curPos = pos;
    }

 	void ArchiveBuffer::Buffer::setRecordEnd(){
        m_recordEndPos = m_curPos;
    }

    void ArchiveBuffer::Buffer::setTail(int pos){
        m_endPos = pos;
    }

    void ArchiveBuffer::Buffer::cutTail(){
        m_endPos = m_curPos;
    }

    void ArchiveBuffer::Buffer::clear(){
        //memset(m_buffer, 0, m_bufferSize);
        m_buffer[0] = 0;
    }

    FileStream* ArchiveBuffer::getFileStream(){
        return m_stream;
    }
    
    int ArchiveBuffer::getBufferSize(){
        return m_bufferSize;
    }
}

#endif
