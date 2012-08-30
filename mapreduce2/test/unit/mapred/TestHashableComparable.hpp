/** 
 * @file TestHashableComparable.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-21
 */
#ifndef _TEST_MAPREDUCE_HASHABLECOMPARABLE_HPP
#define _TEST_MAPREDUCE_HASHABLECOMPARABLE_HPP


#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "HashableComparable.hpp"
#include "THashableComparable.hpp"
#include "TStringHashableComparable.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>



using namespace std;
using namespace mapreduce;

class HashableComparableFixture : public CxxTest::GlobalFixture{
public:    
    bool setUpWorld() { 

        return true; 
    }

    bool tearDownWorld() { 
        return true; 
    }

    bool setUp() { 
        return true; 
    }    
    bool tearDown() { 
        return true; 
    }
};


static HashableComparableFixture HashableComparableFixture;



class TestHashableComparable: public CxxTest::TestSuite
{
    void doTestIntHash()
    {
        THashableComparable<int> hasher;

        unsigned int hashValue;
        int key = 1024;
        int key2 = key;

        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        TS_ASSERT( hashValue == hasher.hash(&key2));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = 0;
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = 1024*1024;
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

    }

    void doTestIntCompare()
    {
        THashableComparable<int> comparator;

        int i;
        int data[]={1,2,3,4,6,5,8,7,9,10};
        int dataSize = sizeof(data)/sizeof(int);
        vector<int*> index;

        cout << "before sorting...:" ;
        for ( i = 0; i < dataSize ; i ++){
            index.push_back(&data[i]);
            cout << *index[i] << ",";
        }
        cout << endl;

        //use quick sort in std sort 
        TS_ASSERT_THROWS_NOTHING(std::sort(index.begin(), index.end(),comparator));

        cout << "after sorting...:" ;
        for ( i = 0; i < dataSize ; i ++){
            cout << *index[i] << ",";
        }
        cout << endl;

    }

    void doTestStringHash()
    {
        THashableComparable<std::string> hasher;

        unsigned int hashValue;
        std::string key = "hello";
        std::string key2 = "hello";

        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        TS_ASSERT( hashValue == hasher.hash(&key2));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = "";
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = "hello world!";
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

    }

    void doTestStringCompare()
    {
        THashableComparable<std::string> comparator;

        int i;
        char* data[]={
            "a good boy",
            "a bad boy",
            "computer",
            "art",
            "school",
            "bible",
            "life",
            "spirit"};
        int dataSize = sizeof(data)/sizeof(char*);
        string* _data = new string[dataSize];
        vector<std::string*> index;

        cout << "before sorting...:" ;
        for ( i = 0; i < dataSize ; i ++){
            _data[i].assign(data[i]);
            index.push_back(&_data[i]);
            cout << *index[i] << endl;  
        }
        cout << endl;

        //use quick sort in std sort 
        TS_ASSERT_THROWS_NOTHING(std::sort(index.begin(), index.end(),comparator));

        cout << "after sorting...:" ;
        for ( i = 0; i < dataSize; i ++){
            cout << *index[i] << endl;
        }
        cout << endl;

    }


    void doTestCStringHash()
    {
        TStringHashableComparable<char*> hasher;

        unsigned int hashValue;
        char* key = "hello";

        //#!!!
        //if char key2[10], hash(&key2) will fail
        //
        char _key[10];
        char* key2 = _key;
        strcpy(key2,"hello");
        

        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        TS_ASSERT( hashValue == hasher.hash(&key2));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = "";
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

        key = "hello world!";
        TS_ASSERT_THROWS_NOTHING(hashValue = hasher.hash(&key));
        cout << "hash(" << key << ") = " << hashValue << endl;

    }

    void doTestCStringCompare()
    {
        TStringHashableComparable<char*> comparator;

        int i;
        char* data[]={
            "a good boy",
            "a bad boy",
            "computer",
            "art",
            "school",
            "bible",
            "life",
            "spirit"};
        int dataSize = sizeof(data)/sizeof(char*);
        vector<char**> index;

        cout << "before sorting...:" ;
        for ( i = 0; i < dataSize ; i ++){
            index.push_back(&data[i]);
            cout << *index[i] << endl;  
        }
        cout << endl;

        //use quick sort in std sort 
        TS_ASSERT_THROWS_NOTHING(std::sort(index.begin(), index.end(),comparator));

        cout << "after sorting...:" ;
        for ( i = 0; i < dataSize; i ++){
            cout << *index[i] << endl;
        }
        cout << endl;

    }



public:

    //==============test goes here =====================

    void testLocal1(void){
        doTestIntHash();
    }

    void testLocal2(void){
        doTestIntCompare();
    }

    void testLocal3(void){
        doTestStringHash();
    }

    void testLocal4(void){
        doTestStringCompare();
    }

    void testLocal5(void){
        doTestCStringHash();
    }

    void testLocal6(void){
        doTestCStringCompare();
    }


};


#endif /* _TEST_TFSMASTER_HashableComparable_HPP */

