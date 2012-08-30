/** 
 * @file TestCxxTest.hpp
 * test cxxtest.
 * 
 * @author Zhifeng YANG
 * @date 2007-06-26
 */
#ifndef _TESTCXXTEST_HPP
#define _TESTCXXTEST_HPP 1

          
#include <cxxtest/TestSuite.h>
          
class MyTestSuite : public CxxTest::TestSuite 
{
public:
    void testAddition( void )
        {
            TS_ASSERT( 1 + 1 > 1 );
            TS_ASSERT_EQUALS( 1 + 1, 2 );
        }
};
          

#endif /* _TESTCXXTEST_HPP */
