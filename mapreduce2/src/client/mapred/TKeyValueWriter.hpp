/**
 * @file TKeyValueWriter.hpp
 * @description:
 *  TKeyValueWriter is a template class implements RecordWriter interface.
 *  It builds on Archive.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_KEYVALUEWRITER
#define TPLATFORM_MAPREDUCE_KEYVALUEWRITER

#include <mapred/Archive.hpp>
#include <mapred/ArchiveBuffer.hpp>
#include <mapred/FileStream.hpp>
#include <mapred/RecordWriter.hpp>
#include <string>
#include <iostream>
using namespace std;

namespace mapreduce{
    class FileStream;
    class Archive;
    class ArchiveBuffer;

    template<typename KeyType, typename ValueType> 
    class TKeyValueWriter : public  RecordWriter{
        public:
	    /**
             * Construct from FileStream object 
             */
            TKeyValueWriter();
            ~TKeyValueWriter();

            /**
            * Initialize the writer, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false);

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream);

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close();

            /**
             * Append a record.
			 * @param key , key to append
			 * @param value , value to append
             * @return : true if success
             *           false if fail, for example, reading reach the end.
             */
            virtual bool append(const void* key, const void* value);

            /**
            * Append a record.
            * This call append a memory block as a record directly.
            * This method is design for in memory sorting.
            * @param iter, records memory regions 
            * @return : true if success
            *           false if fail, for example, reading reach the end.
            */
            virtual bool append(RegionIterator& iter);

    private:
        Archive* m_archive;
    };

    //template definitions
    template<typename KeyType, typename ValueType> 
    TKeyValueWriter<KeyType,ValueType>::~TKeyValueWriter()
    {
        if(m_archive){
            close();
            delete m_archive;
            m_archive = NULL;
        }
    }

    template<typename KeyType, typename ValueType> 
    TKeyValueWriter<KeyType,ValueType>::TKeyValueWriter()
    {
        m_archive = NULL;
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueWriter<KeyType,ValueType>::initialize(int bufferSize, bool autoClearBuffer)
    {
        //std::cout <<"TKeyValueWriter: initialize" <<std::endl;
        m_archive = new Archive(bufferSize, autoClearBuffer);
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueWriter<KeyType,ValueType>::open(FileStream* stream)
    {
        if(m_archive){
            //std::cout <<"TKeyValueWriter: open" <<std::endl;
            m_archive->open(stream);
        }
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueWriter<KeyType,ValueType>::close()
    {
		if(m_archive) m_archive->close();
    }

    template<typename KeyType, typename ValueType> 
    bool TKeyValueWriter<KeyType,ValueType>::append(const void* key, const void* value)
    {
        //cout <<"TKeyValueWriter : append" <<endl;
        *m_archive << *(KeyType *)key << *(ValueType *)value;
        m_archive->getBuffer()->commitAppendRecord();

        return true;
    }

    template<typename KeyType, typename ValueType> 
    bool TKeyValueWriter<KeyType,ValueType>::append(RegionIterator& iter)
    {
        while(iter.hasMore()){
            Region& region = iter.next();
            m_archive->getBuffer()->appendData(region.pStart, region.len);
        }
        m_archive->getBuffer()->commitAppendRecord();

        return true;
    }


}

#endif
