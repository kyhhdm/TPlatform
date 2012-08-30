/**
 * @file Archive.hpp
 * @description:
 *  Archive is in charge of serialization.
 *  
 *  Important design decision:
 *	<Key,Value> pair are present by void*, which are pointers to memeory actually. 
 *	It's very fast, and give best performance for primitive data types.
 *  the crons is it's weak type safty, but it may be unresolvable in non-dynamical 
 *	language, such as c++.
 *	Archiver is build upon archiveBuffer and FileStream, it's serialzable record I/O.
 *  RecordReader and RecordWriter can build on top of Achive, and it does not create
 *  new record object for better performance. Because primitive data types need not 
 *  to be created, pointer to them in the archiveBuffer is just ok. For class object,
 *  it's user's responsibility to mange object creation and deletion. Archive just use
 *	pointer to feed in the object, refer to next().
 *
 *  #TODO:
 *  20080417: svn version $1153$
 *      Use uniform static reallocable data structure image in searialization.
 *      The key point is to save all pointers into archive, load and reallocate them
 *      when read in.
 *      This provides a uniform concept for all data types, including primitvies and 
 *      user defines, and deprecates all memory copies and all memeory frees.
 *      The crons are expands of pointers saved in archive file, which seems large for 
 *      some pointer intensive data structure, just like char*.
 *          primitive types: [data...]
 *          pointers and user defined types: [object][data...]
 *
 *
 *
 * @date 2008-01-07
 * */

#ifndef TPLATFORM_MAPREDUCE_ARCHIVE
#define TPLATFORM_MAPREDUCE_ARCHIVE

#include <string>
#include <map>

namespace mapreduce{
    class FileStream;
    class ArchiveBuffer;

    class Archive{
        ArchiveBuffer *m_buffer;

        std::string m_keyTypeName;
        std::string m_valueTypeName;
        bool m_initFlag;

    public:
        /**
         * Constructor
         *
		 * @param bufferSize : buffer size for underneath buffers.
		 * @param autoClearBuffer : auto free read buffer when true, otherwise hold all read data
         *
         **/     
        Archive(int bufferSize = 0, bool autoClearBuffer = false);
        ~Archive();

        /**
        * Open a stream. 
		* @throws FSError : under fstream error, like open mode mismatch
        */
        void open(FileStream* stream);

        /**
         * Close the stream. 
		 * @throws FSError : under fstream error, like open mode mismatch
         */
        void close();

        /**
         * Init archiver
         *
         * @param filename
         * @param mode
         * @throws FSError
         *
         **/                 
        void initialize(const std::string& keyTypeName, const std::string& valueTypeName);

        /**
         * Accessors
         *
         **/                 
        inline ArchiveBuffer* getBuffer();
        inline std::string getKeyTypeName();
        inline std::string getValueTypeName();
        inline bool isInitialized();

    };

    //implementation of inline functions
    ArchiveBuffer* Archive::getBuffer() {return m_buffer;}
    std::string Archive::getKeyTypeName(){return m_keyTypeName;}
    std::string Archive::getValueTypeName(){return m_valueTypeName;}
    bool Archive::isInitialized(){return m_initFlag;}

    /**
     * Serialization
     * Global operator overloading.
     * #TODO May use template<typename type> be better
     **/                 
     Archive& operator<<(Archive& ar, char* data);
     Archive& operator<<(Archive& ar, char data);
     Archive& operator<<(Archive& ar, short data);
     Archive& operator<<(Archive& ar, int data);
     Archive& operator<<(Archive& ar, long data);
     Archive& operator<<(Archive& ar, long long& data);
     Archive& operator<<(Archive& ar, unsigned char data);
     Archive& operator<<(Archive& ar, unsigned short data);
     Archive& operator<<(Archive& ar, unsigned int data);
     Archive& operator<<(Archive& ar, unsigned long data);
     Archive& operator<<(Archive& ar, unsigned long long& data);
     Archive& operator<<(Archive& ar, float data);
     Archive& operator<<(Archive& ar, double data);
     Archive& operator<<(Archive& ar, long double& data);

     Archive& operator>>(Archive& ar, char*& data);
     Archive& operator>>(Archive& ar, short*& data);
     Archive& operator>>(Archive& ar, int*& data);
     Archive& operator>>(Archive& ar, long*& data);
     Archive& operator>>(Archive& ar, long long*& data);
     Archive& operator>>(Archive& ar, unsigned char*& data);
     Archive& operator>>(Archive& ar, unsigned short*& data);
     Archive& operator>>(Archive& ar, unsigned int*& data);
     Archive& operator>>(Archive& ar, unsigned long*& data);
     Archive& operator>>(Archive& ar, unsigned long long*& data);
     Archive& operator>>(Archive& ar, float*& data);
     Archive& operator>>(Archive& ar, double*& data);
     Archive& operator>>(Archive& ar, long double*& data);
     
     Archive& operator>>(Archive& ar, char**& data);

	 Archive& operator<<(Archive& ar, std::string& data);
	 Archive& operator>>(Archive& ar, std::string*& data);

}

#endif
