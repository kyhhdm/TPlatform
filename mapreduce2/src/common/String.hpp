/** 
 * @file String.hpp
 * something about string.
 * 
 * @author YANG Zhifeng
 * @date 23  5 2007
 */
#ifndef _STRING_HPP
#define _STRING_HPP 1
#include <string>

namespace mapreduce
{
    /**
     * A Strict Weak Ordering functor used by some STL containers. 
     * 
     */

    class StringLessThan
    {
    public:
        bool operator()(const std::string& s1, const std::string& s2) const
        {
            return s1 < s2;   
        }
    };
    /**
     * Equal functor used by some STL containers. 
     * 
     */

    class StringEqual
    {
    public:
        bool operator()(const std::string& s1, const std::string& s2) const
        {
            return s1 == s2;   
        }
    };
    /**
     * hash functor for string, from <ext/hash_fun.h>
     * 
     */
    inline size_t hash_string(const char* __s)
    {
        unsigned long __h = 0;
        for ( ; *__s; ++__s)
            __h = 5 * __h + *__s;
        return size_t(__h);
    }
    
    struct StringHash
    {
      size_t operator()(const std::string& s) const
        { 
            return hash_string(s.c_str()); 
        }
    };

}



#endif /* _STRING_HPP */
