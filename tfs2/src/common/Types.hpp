/* 
 * @(#)Types.hpp
 * AUTHOR: YangZhifeng
 * CREATE DATE: 10  5 2007
 * DESCRIPTION: 
 */
/** @file
 * 
 * @author YangZhifeng
 * @date 10  5 2007
 */
#ifndef _TYPES_HPP
#define _TYPES_HPP 1

// use ISO C99: 7.18 Integer types <stdint.h>
#include "common/stdint.h"
// use ice integer types
#include <Ice/Config.h>


namespace tfs
{
    using ::int8_t;             
    using ::int_least8_t;       
    using ::int_fast8_t;        
    using ::uint8_t;            
    using ::uint_least8_t;      
    using ::uint_fast8_t;       
                     
    using ::int16_t;            
    using ::int_least16_t;      
    using ::int_fast16_t;       
    using ::uint16_t;           
    using ::uint_least16_t;     
    using ::uint_fast16_t;      
                     
    using ::int32_t;            
    using ::int_least32_t;      
    using ::int_fast32_t;       
    using ::uint32_t;           
    using ::uint_least32_t;     
    using ::uint_fast32_t;

    using ::int64_t;            
    using ::int_least64_t;      
    using ::int_fast64_t;       
    using ::uint64_t;           
    using ::uint_least64_t;     
    using ::uint_fast64_t;

    using ::intmax_t;      
    using ::uintmax_t;     

    using ::Ice::Byte;          // int8_t
    using ::Ice::Short;         // int16_t
    using ::Ice::Int;           // int32_t
    using ::Ice::Long;          // int64_t
    using ::Ice::Float;
    using ::Ice::Double;

    
}

#endif /* _TYPES_HPP */
