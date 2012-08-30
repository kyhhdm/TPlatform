/** 
 * @file TestWordFreqWriter.hpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2008-03-13
 */
#ifndef _TESTWORDFREQWRITER_HPP
#define _TESTWORDFREQWRITER_HPP 1

#include <cxxtest/TestSuite.h>
#include "WordFrequencyWriter.hpp"
#include "KeyValue.hpp"
#include <string>

using namespace std;
using namespace mapreduce;
using namespace boost;

class TestWordFrequencyWriter: public CxxTest::TestSuite 
{
public:
    void testConvert(){
        WordFrequencyWriter writer;
        KeyValue kv(1);
        Buffer b;
        b.appendStr(string("lsajflksjdfklsjfljslkfjyuviousfiouwioen"));
        kv.setKey(b);

        b.clear();
        b.appendInt(235);
        kv.setValue(0, b);        
        
        Buffer b2 = writer.convert(kv);
        
        const char* p = b2.content();
        string s2("lsajflksjdfklsjfljslkfjyuviousfiouwioen:235");
        
        for (int i = 0; i < s2.size(); i++){    
            TS_ASSERT_EQUALS(p[i], s2[i]);
        }
        
    }

};


#endif /* _TESTWORDFREQWRITER_HPP */
