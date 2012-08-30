/**
 * @file FileStream.hpp
 * @description:
 *  FileStream is interface of input and output stream, which integrate local file system stream and 
 *  tfs stream.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_FILESTREAM
#define TPLATFORM_MAPREDUCE_FILESTREAM

#include <string>

namespace mapreduce{
    class FileStream{

    public:
        enum OpenMode{
            Unkown,
            ReadOnly,
            Append
        };

        virtual ~FileStream(){}
        
        /**
         * Open file
         * @throws: FSError
         * */
        virtual void open() = 0;

        /**
         * Close file
         * */
        virtual void close() = 0;

        /**
         * Read data
         * @param buffer : buffer to hold read data
         * @param len : read data length
         * @return: data length actually read, 
         *        : return 0 at eof
		 * @throws FSError
         * */
        virtual int read(char* buffer, int len) = 0;

        /**
         * Append data
         *
         * @param buffer : buffer to hold data to append
         * @param len : data length
         * @return: data length actually appended
		 * @throws FSError
         * */
        virtual int append(const char* buffer, int len) = 0;

        /**
         * Get meta data by name
         * @param propertyName : meta data name
         * @return: meta data content for the name
		 * @throws FSError
         * */
        virtual std::string getMetaData(const std::string& propertyName) = 0;

        /**
         * Set meta data by name
         * @param propertyName : meta data name
         * @return: meta data content for the name
		 * @throws FSError
         * */
        virtual bool setMetaData(const std::string& propertyName, const std::string& data) = 0;

        /**
         *  Accessors
         */
        inline OpenMode getOpenMode();
        inline std::string getFilename();

    protected:
        OpenMode    m_openMode;
        std::string m_filename;
    };

    //implementation of inline functions
    FileStream::OpenMode FileStream::getOpenMode(){
        return m_openMode;
    }

    std::string FileStream::getFilename(){
        return m_filename;
    }
}

#endif


