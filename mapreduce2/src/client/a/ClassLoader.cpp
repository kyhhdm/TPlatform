/**
 * @file ClassLoader.cpp
 * @description 
 *  a light weight class loader for mapreduce system
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */


#include "ClassLoader.hpp"
#include "MapReduceException.hpp"
#include <string>
#include <iostream>


using namespace std;
using namespace mapreduce;

ClassLoader::ClassLoader(const char* soFile)
{
    char* error;
    m_soFile = soFile;
    
    m_handle = DllOpen(soFile);
    if(m_handle == NULL){
        throw ClassLoaderError("dlopen(" + m_soFile +") failed: " + DllError());
    }
    m_maker = DllGetAddress(m_handle, "maker");  

    //if ((error = dlerror()) != NULL) {
    if(m_maker ==  NULL) {
        //throw ClassLoaderError("dlsym(maker) fail:" + error);
        throw ClassLoaderError(string("dlsym(maker) failed: ") + DllError());
    }
}

ClassLoader::~ClassLoader()
{
    if(m_handle) DllClose(m_handle);
}

bool ClassLoader::createInstance(const char* className, void*& pObj)
{
    //cout <<"Create instance of " <<className <<endl;
    if(m_handle == NULL || m_maker == NULL) return false;

    pObj = (*((makerptr)m_maker))(className);

    //use exception for error return, consistency.
    if(pObj == NULL){
        throw ClassLoaderError("createInstance(" + string(className) + ") failed.");
    }
    return (pObj!=NULL);
}


