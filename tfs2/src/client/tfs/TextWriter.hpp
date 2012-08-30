/**
 * @file    TextWriter.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    2008年05月20日 21时40分52秒 CST
 *
 */

#ifndef  TEXTWRITER_FILE_HEADER_INC
#define  TEXTWRITER_FILE_HEADER_INC

#include "tfs/tfs.h"

namespace tfs {
namespace api {

class TextWriter {
public:
    TextWriter(const std::string &path, bool create = true) { 
        open(path, create); 
    }
    ~TextWriter() { close(); }

    void open(const std::string &path, bool create) { 
        if (create) {
            FileSystem tfs;
            if (!tfs.existFile(path))
                tfs.createFile(path, 0, 0);
        }
        m_as.open(path, 0); }

    void close() { m_as.close(); }

    void clear() { m_status = 0; }

    bool good() const { return m_status == 0; }

    bool eof() const { return m_status & eofbit == eofbit; }

    bool fail() const { return m_status & failbit == failbit; }

    bool bad() const { return m_status & badbit == badbit; }

    void exceptions(unsigned char e) {
        m_status = e;
    }

    TextWriter & operator <<(const std::string &s) {
        write(s.c_str(), s.size());
        return *this;
    }

    TextWriter & operator <<(char c) {
        return (*this) <<boost::lexical_cast<std::string>(c);
    }

    TextWriter & operator <<(short i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(int i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(long i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(double i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(float i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(long long i) {
        return (*this) <<boost::lexical_cast<std::string>(i);
    }

    TextWriter & operator <<(const char *s) {
        write(s, strlen(s));
        return *this;
    }

    void write(const char *s, int len) {
        if (bad()) return;
        try {
            m_as.append(s, len);
        } catch (TFSException &ex) {
            setbad();
            if (m_exceptions & badbit)
                throw;
        }
    }

    TextWriter put(char c) {
        write(&c, 1);
        return *this;
    }

    operator bool const () {
        return good();
    }


private:
    void seteof(){ 
        m_status |= eofbit;
        if (m_exceptions & eofbit) 
            throw TFSException("End of file reached.");
    }
    void setfail(){ 
        m_status |= failbit;
        if (m_exceptions & failbit)
            throw TFSException("Read failure.");
    }
    void setbad(){ 
        m_status |= badbit; 
    }

    std::deque<char> buf;
    AppendStream m_as;
    unsigned char m_status;
    unsigned char m_exceptions;

};  //class TextWriter   

}
}

#endif   /* ----- #ifndef TEXTWRITER_FILE_HEADER_INC  ----- */

