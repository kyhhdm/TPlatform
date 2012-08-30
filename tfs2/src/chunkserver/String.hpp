#ifndef __STRING_HPP
#define __STRING_HPP

#include <string>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <cstdarg>

class String
{
public:
    static void
    Str2Lower(std::string& rSource)
        {
            transform(rSource.begin(), rSource.end(),
                      rSource.begin(), tolower);
        }

    static bool
    _nocase_compare(char c1, char c2)
        {
            return toupper(c1) == toupper(c2);
        }

    static std::string::size_type
    FindCase(const std::string& haystack,
             const std::string& needle, int From=0)
        {
            if (haystack.empty())
                return std::string::npos;
            if (needle.empty())
                return std::string::npos;

            std::string::const_iterator pos;
            pos = search(haystack.begin() + From, haystack.end(),
                         needle.begin(),needle.end(), _nocase_compare);

            if( pos == haystack.end()){
                return std::string::npos;
            }else{
                return (pos - haystack.begin());
            }
        }

    static void
    EraseStr(std::string& rStr, const std::string& crSubstr)
        {
            if (rStr.size() == 0 || crSubstr.size() == 0){
                return;
            }

            std::string::size_type idx = 0;
            std::string::size_type sub_length = crSubstr.length();
            idx = rStr.find(crSubstr, idx);
            while (idx != std::string::npos) {
                rStr.erase(idx, sub_length);
                idx = rStr.find(crSubstr, idx);
            }
        }
    template<class T>
    static std::string
    Type2String(T arg)
        {
            std::ostringstream sout;
            sout << arg;
            return sout.str();
        }
};



//用法:
//    const char * a=cz("abcd %d %s",12345,p);    
//    string str2(cz("abcd %d %s",12345,p));

class ts
{
public:
    explicit ts(const char * fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        memset(m_buf,0,sizeof(m_buf));
        vsnprintf(m_buf, sizeof(m_buf)-1, fmt, args);
        va_end(args);
    }
    operator const char * () const
    {
        return m_buf;
    }
private:
    char m_buf[1024];
};


#endif
