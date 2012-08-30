/**
 * @file ClassLoader.hpp
 * @description:
 *  ClassLoader is a dynamically class loader for c++
 *  refer to : http://www.linuxjournal.com/article/3687
 *
 * @date 2008-04-02
 * */

#ifndef TPLATFORM_MAPREDUCE_CLASSLOADER
#define TPLATFORM_MAPREDUCE_CLASSLOADER

#include <string>
#include <map>


/**
* use Macro to define a maker function for dynamical library
*/
extern "C" {
#ifdef WIN32
    __declspec(dllexport) void* maker(const char* name);
#else
    void* maker(const char* name);
#endif
}

#define REGISTER_CLASS_BEGIN()          \
void* maker(const char* name){         

#define REGISTER_CLASS(ClassName)          \
    if( !strcmp(name,#ClassName) ){              \
        return (void*)(new ClassName());            \
    }

#define REGISTER_FEEDER_CLASS(KeyType, ValueType)          \
    if( !strcmp(name,"TKeyValueFeeder<"#KeyType","#ValueType">") ){              \
    return (void*)(new TKeyValueFeeder<KeyType,ValueType>());            \
    }

#define REGISTER_WRITER_CLASS(KeyType, ValueType)          \
    if( !strcmp(name,"TKeyValueWriter<"#KeyType","#ValueType">") ){              \
    return (void*)(new TKeyValueWriter<KeyType,ValueType>());            \
    }

#define REGISTER_TEXTFILEWRITER_CLASS(KeyType, ValueType)          \
    if( !strcmp(name,"TextFileWriter<"#KeyType","#ValueType">") ){              \
    return (void*)(new TextFileWriter<KeyType,ValueType>());            \
    }


#define REGISTER_CLASS_END()          \
    return NULL;                      \
}


/**
* compatible dynamical library functions encapslation
*/
#ifdef WIN32
#include <windows.h>
#define DLLHANDLE HINSTANCE
#define DllOpen LoadLibrary
#define DllGetAddress GetProcAddress
#define DllClose FreeLibrary
#define DllError string
#else
#include <dlfcn.h>
#define DLLHANDLE  void*
#define DllOpen(soFile) dlopen(soFile, RTLD_NOW)
#define DllGetAddress dlsym
#define DllClose dlclose
#define DllError dlerror
#endif

//typedef extern "C" void (*makerptr)(const char* name);
typedef void* (*makerptr)(const char* name);

namespace mapreduce{
    class ClassLoader{
        std::string m_soFile;
        DLLHANDLE m_handle;
        void* m_maker;
    public:
//        typedef extern "C" void (*makeptr)(const char* name);

        /**
         * Constructor
         *
         **/     
        ClassLoader(const char* soFile);
        ~ClassLoader();

        /**
         * CreateInstance by class name
         *
         * @param className
         * @param pObj [out] return object pointer
         *
         *
         **/                 
        bool createInstance(const char* className, void*& pObj);
    };

    class ClassLoaderProxy {
    public:
        ClassLoaderProxy(){;}
    };



}

#endif
