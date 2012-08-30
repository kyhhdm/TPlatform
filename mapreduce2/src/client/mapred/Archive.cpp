/**
 * @file Archive.cpp
 * the implementation of Archive.hpp
 *
 * @author PengBo
 * @date 2008-01-07
 * */

#include "Archive.hpp"
#include "ArchiveBuffer.hpp"
#include "FileStream.hpp"
#include "MapReduceException.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace mapreduce;

Archive::Archive(int bufferSize, bool autoClearBuffer)
{
    m_buffer = new ArchiveBuffer(bufferSize, autoClearBuffer);
    m_initFlag = false;
}

Archive::~Archive()
{
    if(m_buffer) delete m_buffer;
}

void Archive::open(FileStream* stream)
{
    if(!stream) throw FSError("Archive::open null stream failed!");

    if(m_buffer->getFileStream()){
        m_buffer->closeStream();
    }

    //cout <<"Archive: open stream " <<endl;
	m_buffer->openStream(stream);

    if(stream->getOpenMode() == FileStream::ReadOnly){
        //read in KeyValue typename
        m_keyTypeName = stream->getMetaData("KeyTypeName");
        m_valueTypeName = stream->getMetaData("ValueTypeName");
        m_initFlag = true;
    }
    else{
        m_keyTypeName = stream->getMetaData("KeyTypeName");
        m_valueTypeName = stream->getMetaData("ValueTypeName");
        if(m_keyTypeName.length() != 0 || m_valueTypeName.length() != 0 ){
            m_initFlag = true;
        }
    }
}


void Archive::close()
{
	m_buffer->closeStream();
	
	m_initFlag = false;
}

void Archive::initialize(const std::string& keyTypeName, const std::string& valueTypeName)
{
    if(m_initFlag) return ;

    m_keyTypeName = keyTypeName;
    m_valueTypeName = valueTypeName;
    m_initFlag = true;

    //set metadata
    m_buffer->getFileStream()->setMetaData("KeyTypeName", keyTypeName);
    m_buffer->getFileStream()->setMetaData("valueTypeName", valueTypeName);

}

namespace mapreduce{

//implementation of global functions
Archive& operator<<(Archive& ar, char* data){
    ar.getBuffer()->appendZString(data);
    return ar;
}

Archive& operator<<(Archive& ar, char data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, short data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, int data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, long data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, long long& data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, unsigned char data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, unsigned short data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, unsigned int data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, unsigned long data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, unsigned long long& data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, float data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, double& data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

Archive& operator<<(Archive& ar, long double& data){
    ar.getBuffer()->appendData(&data, sizeof(data));
    return ar;
}

//read in
Archive& operator>>(Archive& ar, char*& data){
    data = (char*)(ar.getBuffer()->readData(sizeof(char)));
    return ar;
}

Archive& operator>>(Archive& ar, short*& data){
    data = (short*)(ar.getBuffer()->readData(sizeof(short)));
    return ar;
}

Archive& operator>>(Archive& ar, int*& data){
    data = (int*)(ar.getBuffer()->readData(sizeof(int)));
    return ar;
}

Archive& operator>>(Archive& ar, long*& data){
    data = (long*)(ar.getBuffer()->readData(sizeof(long)));
    return ar;
}

Archive& operator>>(Archive& ar, long long*& data){
    data = (long long*)(ar.getBuffer()->readData(sizeof(long long)));
    return ar;
}

Archive& operator>>(Archive& ar, unsigned char*& data){
    data = (unsigned char*)(ar.getBuffer()->readData(sizeof(unsigned char)));
    return ar;
}

Archive& operator>>(Archive& ar, unsigned short*& data){
    data = (unsigned short*)(ar.getBuffer()->readData(sizeof(unsigned short)));
    return ar;
}

Archive& operator>>(Archive& ar, unsigned int*& data){
    data = (unsigned int*)(ar.getBuffer()->readData(sizeof(unsigned int)));
    return ar;
}

Archive& operator>>(Archive& ar, unsigned long*& data){
    data = (unsigned long*)(ar.getBuffer()->readData(sizeof(unsigned long)));
    return ar;
}

Archive& operator>>(Archive& ar, unsigned long long*& data){
    data = (unsigned long long*)(ar.getBuffer()->readData(sizeof(unsigned long long)));
    return ar;
}

Archive& operator>>(Archive& ar, float*& data){
    data = (float*)(ar.getBuffer()->readData(sizeof(float)));
    return ar;
}

Archive& operator>>(Archive& ar, double*& data){
    data = (double*)(ar.getBuffer()->readData(sizeof(double)));
    return ar;
}

Archive& operator>>(Archive& ar, long double*& data){
    data = (long double*)(ar.getBuffer()->readData(sizeof(long double)));
    return ar;
}

//char* 
Archive& operator>>(Archive& ar, char**& data){
    char* tmp = (char*)(ar.getBuffer()->readZString());
    if (tmp == NULL) data = NULL;
    else *data = tmp;
    return ar;
}

//class objects 
Archive& operator<<(Archive& ar, std::string& data){
    ar.getBuffer()->appendZString(data.c_str());
    return ar;
}

Archive& operator>>(Archive& ar, std::string*& data){
    char *tmp = ar.getBuffer()->readZString();
    if(tmp == NULL) data = NULL;
    else data->assign(tmp);
    return ar;
}

}
