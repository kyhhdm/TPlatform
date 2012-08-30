/**
 * @file FileStreamTfs.hpp
 * @description:
 *  FileStreamTfs is TFS file system implementation for FileStream interface.
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_FILESTREAMTFS
#define TPLATFORM_MAPREDUCE_FILESTREAMTFS

#include <mapred/FileStream.hpp>

namespace tfs{
    namespace api{
        class InputStream;
        class AppendStream;
    }
}

namespace mapreduce{
    class FileStreamTfs: public FileStream{
        tfs::api::InputStream *m_fin;
        tfs::api::AppendStream *m_fout;
    public:
        /**
         * Constructor
         *
         * @param filename
         * @param mode
         * @throws FSError
         *
         **/        
        FileStreamTfs(const std::string& filename, OpenMode mode = ReadOnly, bool OpenOnDemand = false);

        ~FileStreamTfs();

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
         * @param buffer : buffer to hold read data
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
         * Get meta data by name
         * @param propertyName : meta data name
         * @return: meta data content for the name
         * */
        std::string getMetaData(const std::string& propertyName);

        /**
         * Set meta data by name
         * @param propertyName : meta data name
         * @return: meta data content for the name
         * */
        bool setMetaData(const std::string& propertyName, const std::string& data);
    };
}

#endif


