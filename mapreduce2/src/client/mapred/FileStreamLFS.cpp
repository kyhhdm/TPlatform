/**
 * @file FileStreamLFS.cpp
 * the implementation of FileStreamLFS.hpp
 *
 * @author PengBo
 * @date 2008-05-21
 * */

#include "FileStreamLFS.hpp"
#include "MapReduceException.hpp"
#include <tianwang/LargeFile.h>
#include <util/Logger.hpp>

using namespace std;
using namespace mapreduce;

FileStreamLFS::FileStreamLFS(const std::string& filename, OpenMode mode, bool OpenOnDemand)
{
    m_fin = NULL;
    m_fout = NULL;
    m_openMode = mode;
    m_filename = filename;

    if (OpenOnDemand == false){
        open();
    }
}

FileStreamLFS::~FileStreamLFS()
{
    close();
}

void FileStreamLFS::open()
{
    if (m_openMode == FileStream::ReadOnly){
        if (m_fin != NULL) return;

        m_fin = new LargeFile;
        if(m_fin->open(m_filename.c_str(), O_RDONLY) <= 0){
            throw FSError(string("FileStreamLFS open file for read failed :") + m_filename);
        }
        //cout <<"FileStreamLFS opens " <<m_filename <<" for read " <<endl;
    }
    else if (m_openMode == FileStream::Append){
        //cout <<"FileStreamLFS opens " <<m_filename <<" for append " <<endl;
        if (m_fout != NULL) return;
        //has a append stream from end of file
        m_fout = new LargeFile;
        if(m_fout->open(m_filename.c_str(), O_WRONLY | O_APPEND | O_CREAT) <= 0){
            throw FSError(string("FileStreamLFS open file for append failed :") + m_filename);
        }
    }
}

void FileStreamLFS::close()
{
    //cout <<"FileStreamLFS with " <<m_filename <<" closed" <<endl;
    if(m_fin){
        delete m_fin;
        m_fin = NULL;
    }
    if(m_fout){
        delete m_fout;
        m_fout = NULL;
    }
}

int FileStreamLFS::read(char* buffer, int len)
{
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::ReadOnly){
        throw FSError("FileStreamLFS try to read append mode stream");
    }

    if(!m_fin){
        shouldClose = true;
        open();
    }

    ret = m_fin->read(buffer, len);
    
    if(shouldClose) close();
    return ret;
}

int FileStreamLFS::append(const char* buffer, int len)
{
    //cout <<"FileStreamLFS: append " <<len <<" bytes" <<endl;
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::Append){
        throw FSError("FileStreamLFS try to append readonly stream");
    }

    if(!m_fout){
        shouldClose = true;
        open();
    }

    ret = m_fout->write(buffer, len);

    if(shouldClose) close();
    return ret;    
}


//TODO
string FileStreamLFS::getMetaData(const std::string& propertyName)
{
    return string("not implemented yet");
}

bool FileStreamLFS::setMetaData(const std::string& propertyName, const std::string& data)
{
    return false;
}
