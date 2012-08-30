#ifndef TPLATFORM_MAPREDUCE_EXCEPTION
#define TPLATFORM_MAPREDUCE_EXCEPTION

#include <exception>
#include <string>

namespace mapreduce{

    /** 
     * Base exception type for all exceptions that could be thrown out by mapreduce client. 
     * Instances of this class won't be thrown out, only instances of its 
     * subclasses will be thrown out.
     */
    class MapReduceException : public std::exception {
        //const char* m_error;
        std::string m_error;
    public:
        //MapReduceException(const char* str):std::exception(str){}
        MapReduceException(const char* str):m_error(str){}
        ~MapReduceException() throw(){}
        const char* what() const throw(){return m_error.c_str();}
        //MapReduceException(const std::string& errormsg):std::exception(errormsg.c_str()){}
    };


    /** 
     * Base exception type for exceptions that would be thrown out if certain 
     * file system operations failed.
     * Instances of this class won't be thrown out, only instances of its 
     * subclasses will be thrown out.
     * Possible reasons:
     *  1.No such file or directory.
     *  2.File or directory already exists.
     *  3.No file is opened for this stream.
     */
    class FSError : public MapReduceException {
    public:
        FSError(const char *str) : MapReduceException(str) { }
        FSError(const std::string& str) : MapReduceException(str.c_str()) { }
    };

    /** 
     * Possible reasons:
     *  1.Record too large and exceed buffer boundary.
     *  2.eof
     *  3.
     */
    class BufferError : public MapReduceException {
    public:
        BufferError(const char *str) : MapReduceException(str) { }
    };

    /** 
    * Base exception type for all exceptions that could be thrown out by ClassLoader. 
    * Instances of this class won't be thrown out, only instances of its 
    * subclasses will be thrown out.
    */
    class ClassLoaderError: public MapReduceException {
    public:
        ClassLoaderError(const char *str) : MapReduceException(str) { }
        ClassLoaderError(const std::string& str) : MapReduceException(str.c_str()) { }
    };
}

#endif
