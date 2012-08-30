/**
 * @file FileStreamLocal.hpp
 * @description:
 *  FileStreamLocal is local file system implementation for FileStream interface.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_FILESTREAMLOCAL
#define TPLATFORM_MAPREDUCE_FILESTREAMLOCAL

#include "FileStream.hpp"
#include <fstream>

namespace mapreduce{
    class FileStreamLocal: public FileStream{
        std::ifstream *m_fin;
        std::ofstream *m_fout;

    public:
        /**
        * Constructor 
        * FileStream opens a read stream or an append stream.
        *
        * @param filename :
        * @param mode : ReadOnly or Append
        * @param OpenOnDemand : 
        *          false by default if stream always open, 
        *          true if stream open only when append or read call, and close automatically after that call
        *
        * @throws : FSError
        * */
        FileStreamLocal(const std::string& filename, OpenMode mode = ReadOnly, bool OpenOnDemand = false);

        ~FileStreamLocal();

        /**
        * Open file
        * @throws: FSError
        * */
        void open();

        /**
        * Close file
        * */
        void close();

        /**
         * read data
         * @param buffer : buffer to hold read in data
         * @param len : read data length
         * @return: data length actually read
         * */
        int read(char* buffer, int len);

        /**
         * append data
         *
         * @param buffer : buffer to hold data to append
         * @param len : data length
         * @return: data length actually appended
         * */
        int append(const char* buffer, int len);

        /**
         * Get meta-data by name
         * @param propertyName : meta-data name
         * @return: meta-data content for the name
         * */
        std::string getMetaData(const std::string& propertyName);

        /**
         * Set meta-data by name
         * @param propertyName : meta-data name
         * @return: meta-data content for the name
         * */
        bool setMetaData(const std::string& propertyName, const std::string& data);

    };
}

#endif


