/**
 * @file TKeyValueFeeder.hpp
 * @description:
 *  TKeyValueFeeder is a template class implements RecordReader interface.
 *  It builds on Archive.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_KEYVALUEFEEDER
#define TPLATFORM_MAPREDUCE_KEYVALUEFEEDER

#include <mapred/Archive.hpp>
#include <mapred/ArchiveBuffer.hpp>
#include <mapred/FileStream.hpp>
#include <mapred/RecordReader.hpp>
#include <string>
#include <iostream>

namespace mapreduce{
    class FileStream;
    class Archive;

    template<typename KeyType, typename ValueType> 
    class TKeyValueFeeder : public  RecordReader{
        public:
	    /**
             * Construct from FileStream object 
             */
            TKeyValueFeeder();
            ~TKeyValueFeeder();

            /**
            * Initialize the reader, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false);

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream);

            /**
            * flush the stream buffers. 
            */
            virtual void flush();

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close();

            /**
            * Create Key Class object. 
            * @return : 
            *           
            */
            virtual void* createKeys(int number = 0);


            /**
            * Get Key Class size. 
            * @return : 
            *           
            */
            virtual int getKeySize();

            /**
            * Create Value Class object. 
            * @return : 
            *           
            */
            virtual void* createValues(int number = 0);

            /**
            * Get Value Class size. 
            * @return : 
            *           
            */
            virtual int getValueSize();

            /**
             * Access the next record.
			 * @param key [out], key readed in
			 * @param value [out], value readed in
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
            virtual bool next(void*& key, RegionIterator& iter);
            
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

    //template definitions
    template<typename KeyType, typename ValueType> 
    TKeyValueFeeder<KeyType,ValueType>::~TKeyValueFeeder()
    {
        if(m_archive){
			close();
            delete m_archive;
            m_archive = NULL;
        }
    }

    template<typename KeyType, typename ValueType> 
    TKeyValueFeeder<KeyType,ValueType>::TKeyValueFeeder()
    {
        m_archive = NULL;
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueFeeder<KeyType,ValueType>::initialize(int bufferSize, bool autoClearBuffer)
    {
        m_archive = new Archive(bufferSize, autoClearBuffer);
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueFeeder<KeyType,ValueType>::open(FileStream* stream)
    {
        if(m_archive){
            m_archive->open(stream);
        }
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueFeeder<KeyType,ValueType>::flush()
    {
        m_archive->getBuffer()->commitReadRecord();
    }

    template<typename KeyType, typename ValueType> 
    void TKeyValueFeeder<KeyType,ValueType>::close()
    {
		if(m_archive) m_archive->close();
    }

    template<typename KeyType, typename ValueType> 
    bool TKeyValueFeeder<KeyType,ValueType>::next(void*& key, void*& value)
    {
        KeyType *tmpKey = (KeyType*)key;
        ValueType *tmpValue = (ValueType*)value;

        *m_archive >> tmpKey >> tmpValue;

        if((tmpKey == NULL) || (tmpValue == NULL)) return false;
        else{
            key = tmpKey;
            value = tmpValue;
            return true;
        }
    }

    template<typename KeyType, typename ValueType> 
    void* TKeyValueFeeder<KeyType,ValueType>::createKeys(int number)
    {
        if(number <=1){
            KeyType *key =new KeyType[1]();
            return (void*)key;
        }
        else{
            KeyType *key =new KeyType[number]();
            return (void*)key;
        }
    }

    template<typename KeyType, typename ValueType>
    bool TKeyValueFeeder<KeyType,ValueType>::releaseKeys(void*& keys)
    {
        if(keys != NULL){
            KeyType* pkeys = (KeyType*)keys;
            delete[] pkeys;
        }
        return true;
    }

    template<typename KeyType, typename ValueType>
    bool TKeyValueFeeder<KeyType,ValueType>::releaseValues(void*& values)
    {
        if(values != NULL){
            ValueType* pvalues = (ValueType*)values;
            delete[] pvalues;
        }
        return true;
    }
    
    template<typename KeyType, typename ValueType> 
    int TKeyValueFeeder<KeyType,ValueType>::getKeySize()
    {
        return sizeof(KeyType);
    }

    template<typename KeyType, typename ValueType> 
    int TKeyValueFeeder<KeyType,ValueType>::getValueSize()
    {
        return sizeof(ValueType);
    }

    template<typename KeyType, typename ValueType> 
    void* TKeyValueFeeder<KeyType,ValueType>::createValues(int number)
    {
        if(number <= 1) {
            ValueType *value = new ValueType[1]();
            return (void*)value;
        }
        else{
            ValueType *value = new ValueType[number]();
            return (void*)value;
        }
    }

    template<typename KeyType, typename ValueType> 
    bool TKeyValueFeeder<KeyType,ValueType>::next(void*& key, RegionIterator& iter)
    {
        //#TODO, should be reset when clearBuffer
        static int startPos = 0;

        int endPos;
        KeyType *tmpKey = (KeyType*)key;
        static ValueType *tmpValue = (ValueType *)createValues(1);

        *m_archive >> tmpKey >> tmpValue;
        endPos = m_archive->getBuffer()->commitReadRecord();

        if((tmpKey == NULL) || (tmpValue == NULL)) return false;
        else{
            key = tmpKey;
            iter = m_archive->getBuffer()->getRecord(startPos, endPos);
            startPos = endPos;
            return true;
        }
    }

}

#endif
