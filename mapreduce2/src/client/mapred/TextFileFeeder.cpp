/**
* @file TextFileFeeder.cpp
* @description 
*  RecordReader for Text File
*  <int,char*> is the key value type, while use void*
*  it turns to <int*, char**>, be careful
*  
**/

#include "TextFileFeeder.hpp"
#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include "FileStream.hpp"
#include "MapReduceException.hpp"
#include <iostream>

using namespace std;
using namespace mapreduce;

TextFileFeeder::TextFileFeeder()
{
    m_archive = NULL;
}

TextFileFeeder::~TextFileFeeder()
{        
    if(m_archive){
        close();
        delete m_archive;
        m_archive = NULL;
    }            
}

void TextFileFeeder::initialize(int bufferSize, bool autoClearBuffer)
{
    m_archive = new Archive(bufferSize, autoClearBuffer);
}

void TextFileFeeder::open(FileStream* stream)
{
    if(m_archive){
        m_archive->open(stream);
    }
}

void TextFileFeeder::flush()
{
    m_archive->getBuffer()->commitReadRecord();
}

void TextFileFeeder::close()
{
    if(m_archive) m_archive->close();
}

bool TextFileFeeder::next(void*& key, void*& value)
{
    char* line;

    line = m_archive->getBuffer()->readZString('\n');

    if(line == NULL) return false;
    else{
        int byteOffset;
        //in fact , it should be unsigned long long 
        byteOffset = (int)m_archive->getBuffer()->getByteOffset();
        *(int*)key = byteOffset;
        *(char**)value = line;
        return true;
    }
}

bool TextFileFeeder::releaseKeys(void*& keys)
{
    if(keys != NULL){
        int* pkeys = (int*)keys;
        delete[] pkeys;
    }
    return true;
}

bool TextFileFeeder::releaseValues(void*& values)
{
    if(values != NULL){
        char** pvalues = (char**)values;
        delete[] pvalues;
    }
    return true;
}
