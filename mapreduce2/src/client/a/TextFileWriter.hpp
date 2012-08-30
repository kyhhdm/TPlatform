/**
 * @file TextFileWriter.hpp
 * @description:
 *  TextFileWriter is a template of text file writer
 *  It builds on Archive.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_TextFileWriter
#define TPLATFORM_MAPREDUCE_TextFileWriter

#include "FileStream.hpp"
#include "RecordWriter.hpp"
#include "boost/lexical_cast.hpp"
#include <string>

namespace mapreduce{
    class FileStream;

    template<typename KeyType, typename ValueType>
    class TextFileWriter : public  RecordWriter{
        public:
            /**
             * Construct from FileStream object 
             */
            TextFileWriter(){;}
            
            ~TextFileWriter(){;}

            /**
            * Initialize the writer, this is necessary for dynamically created objects,
            * which only runs default constructor.
            */
            virtual void initialize(int bufferSize = 0, bool autoClearBuffer = false){;}

            /**
            * Open a stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void open(FileStream* stream){
                //cout <<"TextFileWriter: append" <<endl;
                m_stream = stream;
            }

            /**
            * Close the stream. 
            * @throws FSError : under fstream error, like open mode mismatch
            */
            virtual void close(){ 
                if(m_stream){ m_stream->close(); m_stream = NULL;}
            }

            /**
             * Append a record.
             * @param key , key to append
             * @param value , value to append
             * @return : true if success
             *           false if fail, for example, reading reach the end.
             */
            bool append(const void* key, const void* value);

            /**
            * Append a record.
            * This call append a memory block as a record directly.
            * This method is design for in memory sorting.
            * @param iter, records memory regions 
            * @return : true if success
            *           false if fail, for example, reading reach the end.
            */
            virtual bool append(RegionIterator& iter){return false;}

    private:
        FileStream *m_stream;
    };

    //
    template<typename KeyType, typename ValueType>
    bool TextFileWriter<KeyType,ValueType>::append(const void* key, const void* value){
        std::string keyString, valueString;

        //cout <<"TextFileWriter: append" <<endl;
        try{
            keyString = boost::lexical_cast<std::string>(*(KeyType*)key);
        }catch(boost::bad_lexical_cast &){
            //keyString = *(KeyType*)key.toString();
        }

        try{
            valueString = boost::lexical_cast<std::string>(*(ValueType*)value);
        }catch(boost::bad_lexical_cast &){
            //valueString = *(ValueType*)value.toString();
        }

        keyString += '\t';
        m_stream->append(keyString.c_str(), keyString.length());

        valueString += '\n';
        m_stream->append(valueString.c_str(), valueString.length());

        return true;
    }
}

#endif
