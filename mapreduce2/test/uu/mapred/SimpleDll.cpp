/**
 * @file SimpleDll.cpp
 * @description 
 *  test dynamic library construction
 *
 * @author Peng Bo
 * @date 2008-4-18
 * */


#include "ClassLoader.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

//=================SimpleDll.hpp==============
class TestInterface{
public:
    virtual void hello()=0;
};

class TestReader : public TestInterface{
public:
    void hello(){cout << "TestReader ~" << endl;}
};

class TestWriter : public TestInterface{
public:
    void hello(){cout << "TestWriter ~" << endl;}
};

template<typename KeyType> 
class TestTemplate : public TestInterface{
public:
    void hello(){
        KeyType var;
        const type_info* info = &typeid(var);
        cout << "TestTemplate<" << info->name() << "> ~" << endl;
    }
};

//======================================


REGISTER_CLASS_BEGIN();
REGISTER_CLASS(TestReader);
REGISTER_CLASS(TestWriter);
REGISTER_CLASS(TestTemplate<int>);
REGISTER_CLASS(TestTemplate<float>);
REGISTER_CLASS_END(); 

