/**
 * @file    TextReader.hpp
 *  
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    2008年05月20日 20时24分55秒 CST
 *
 */

#ifndef  TEXTREADER_FILE_HEADER_INC
#define  TEXTREADER_FILE_HEADER_INC

#include "tfs/tfs.h"
#include <deque>
#include <boost/lexical_cast.hpp>

namespace tfs {
namespace api {

const unsigned char eofbit = 1;
const unsigned char failbit = 2; 
const unsigned char badbit = 2; 

class TextReader {
public:
    TextReader(const std::string &path) { 
        m_exceptions = 0;
        clear();
        open(path); 
    }
    ~TextReader() { close(); }

    void open(const std::string &path) { m_is.open(path, 0); }

    void close() { m_is.close(); buf.clear(); }

    void clear() { m_status = 0; }

    bool good() const { return m_status == 0; }

    bool eof() const { return (m_status & eofbit) == eofbit; }

    bool fail() const { return (m_status & failbit) == failbit; }

    bool bad() const { return (m_status & badbit) == badbit; }

    void exceptions(unsigned char e) {
        m_exceptions = e;
    }

    char get() {
        char c = EOF;
        if (!good()) return c;
        try {
            if (buf.empty()) fill();
        } catch (TFSException &ex) {
            setbad();
            if (m_exceptions & badbit)
                throw;
        }
        if (buf.empty()) 
            seteof();
        else {
            c = buf.front();
            buf.pop_front();
        }
        return c;
    }

    const std::string getline() {
        std::string tmp;
        char c;
        while(peek() != EOF) {
            c = get();
            if (c == '\n') break;
            else tmp.push_back(c);
        }
        return tmp;
    }

    char peek() {
        if (!good()) return EOF;
        if (buf.empty()) fill();
        if (buf.empty()) return EOF;
        char c = get();
        buf.push_front(c);
        return c;
    }

    TextReader & operator >> (double &i) {
        std::string tmp;
        while(isspace(peek())) get();
        while(isdigit(peek()) || peek() == '.')
            tmp.push_back(get());
        if (tmp.empty()) setfail();    
        else i = boost::lexical_cast<double>(tmp);
        return *this;
    }

    TextReader & operator >> (long &i) {
        std::string tmp;
        while(isspace(peek())) get();
        while(isdigit(peek()) || peek() == '.')
            tmp.push_back(get());
        if (tmp.empty()) setfail();    
        else i = boost::lexical_cast<long>(tmp);
        return *this;
    }

    TextReader & operator >> (bool &i) {
        std::string tmp;
        while(isspace(peek())) get();
        while(isdigit(peek()) || peek() == '.')
            tmp.push_back(get());
        if (tmp.empty()) setfail();    
        else i = boost::lexical_cast<bool>(tmp);
        return *this;
    }

    TextReader & operator >> (int &i) {
        std::string tmp;
        while(isspace(peek())) get();
        while(isdigit(peek()) || peek() == '.')
            tmp.push_back(get());
        if (tmp.empty()) setfail();    
        else i = boost::lexical_cast<int>(tmp);
        return *this;
    }

    TextReader & operator >> (short &i) {
        std::string tmp;
        while(isspace(peek())) get();
        while(isdigit(peek()) || peek() == '.')
            tmp.push_back(get());
        if (tmp.empty()) setfail();    
        else i = boost::lexical_cast<short>(tmp);
        return *this;
    }

    TextReader & operator >> (char &c) {
        c = get();
        return *this;
    }

    TextReader & operator >> (char* s) {
        std::string tmp;
        while(isspace(peek())) get();
        while(!isspace(peek()))
            tmp.push_back(get());
        memcpy(s, tmp.c_str(), tmp.size());
        return *this;
    }

    TextReader & operator >> (std::string &tmp) {
        tmp.clear();
        while(isspace(peek())) get();
        while(!isspace(peek()))
            tmp.push_back(get());
        return *this;
    }

    int read(char *s, int len) {
        int n = 0;
        for (int i = 0; !buf.empty() && i < len; ++i) {
            s[i]=buf.front();
            buf.pop_front();
            ++n;
        }
        if (len > 0)
            n += m_is.read(s + n, len - n);
        return n;
    }

    TextReader& ignore(unsigned num = 1, int delim = EOF) {
        for (int i = 0; i < num && peek() != delim; ++i) 
            get();
        return *this;
    }

    TextReader& putback(char c) {
        buf.push_front(c);
        return *this;
    }

    operator bool() const { return good(); }

private:
    void fill() {
        static char s[100];
        int n = m_is.read(s, 100);
        buf.insert(buf.end(), s, s+n);
    }
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
    InputStream m_is;
    unsigned char m_status;
    unsigned char m_exceptions;
};  //class TextReader

}   // namespace api
}   // namespace tfs

#endif   /* ----- #ifndef TEXTREADER_FILE_HEADER_INC  ----- */

