/**
 * @file FileStreamLocal.cpp
 * the implementation of FileStreamLocal.hpp
 *
 * @author PengBo
 * @date 2008-01-07
 * */

#include "FileStreamLocal.hpp"
#include "MapReduceException.hpp"
#include <fstream>
#include <util/Logger.hpp>

using namespace std;
using namespace mapreduce;

FileStreamLocal::FileStreamLocal(const std::string& filename, OpenMode mode, bool OpenOnDemand)
{
    m_fin = NULL;
    m_fout = NULL;
    m_openMode = mode;
    m_filename = filename;

    if (OpenOnDemand == false){
        open();
    }
}

FileStreamLocal::~FileStreamLocal()
{
    close();
}

void FileStreamLocal::open()
{
    if (m_openMode == FileStream::ReadOnly){
        if (m_fin != NULL) return;

        m_fin = new ifstream;
        m_fin->open(m_filename.c_str(), ios::binary);
        if(!m_fin->is_open()){
            throw FSError(string("FileStreamLocal open file for read failed :") + m_filename);
        }
        //cout <<"FileStreamLocal opens " <<m_filename <<" for read " <<endl;
    }
    else if (m_openMode == FileStream::Append){
        //cout <<"FileStreamLocal opens " <<m_filename <<" for append " <<endl;
        if (m_fout != NULL) return;
        //has a append stream from end of file
        m_fout = new ofstream;
        m_fout->open(m_filename.c_str(), ios::binary|ios::app);
        if(!m_fout->is_open()){
            throw FSError(string("FileStreamLocal open file for append failed :") + m_filename);
        }
    }
}

void FileStreamLocal::close()
{
    //cout <<"FileStreamLocal with " <<m_filename <<" closed" <<endl;
    if(m_fin){
        delete m_fin;
        m_fin = NULL;
    }
    if(m_fout){
        delete m_fout;
        m_fout = NULL;
    }
}

int FileStreamLocal::read(char* buffer, int len)
{
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::ReadOnly){
        throw FSError("FileStreamLocal try to read append mode stream");
    }

    if(!m_fin){
        shouldClose = true;
        open();
    }

    m_fin->read(buffer, len);
    ret = m_fin->gcount();
    
    if(shouldClose) close();
    return ret;
}

int FileStreamLocal::append(const char* buffer, int len)
{
    //cout <<"FileStreamLocal: append " <<len <<" bytes" <<endl;
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::Append){
        throw FSError("FileStreamLocal try to append readonly stream");
    }

    if(!m_fout){
        shouldClose = true;
        open();
    }

    m_fout->write(buffer, len);
    if(m_fout->good()) ret = len;
    else ret = 0;

    if(shouldClose) close();
    return ret;    
}


//TODO
string FileStreamLocal::getMetaData(const std::string& propertyName)
{
    return string("not implemented yet");
}

bool FileStreamLocal::setMetaData(const std::string& propertyName, const std::string& data)
{
    return false;
}
