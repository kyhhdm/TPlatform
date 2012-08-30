/**
 * @file FileStreamTfs.cpp
 * the implementation of FileStreamTfs.hpp
 *
 * @author PengBo
 * @date 2008-01-07
 * */

#include "FileStreamTfs.hpp"
#include "MapReduceException.hpp"
#include <tfs/tfs.h>
#include <iostream>

using namespace std;
using namespace tfs::api;
using namespace mapreduce;

FileStreamTfs::FileStreamTfs(const std::string& filename, OpenMode mode, bool OpenOnDemand)
{
    m_fin = NULL;
    m_fout = NULL;
    m_openMode = mode;
    m_filename = filename;

    if (OpenOnDemand == false){
        open();
    }
}

FileStreamTfs::~FileStreamTfs()
{
    close();
}

void FileStreamTfs::open()
{
    try{
        if (m_openMode == FileStream::ReadOnly){
            if (m_fin != NULL) return;
            m_fin = new InputStream;
            m_fin->open(m_filename.c_str(), 0);
            //cout <<"FileStreamTfs opens " <<m_filename <<" for read " <<endl;
        }
        else if (m_openMode == FileStream::Append){
            //cout <<"FileStreamTfs opens " <<m_filename <<" for append " <<endl;
            if (m_fout != NULL) return;

            FileSystem fs;
            if (!fs.existFile(m_filename)){
                fs.createFile(m_filename, 1, 0);
            }

            m_fout = new AppendStream;
            m_fout->open(m_filename.c_str(), 0);
        }
    }
    catch (tfs::api::TFSException& e){
        throw FSError(string("FileStreamTfs open file failed :") + m_filename + " error=>" + e.what());
    }
}

void FileStreamTfs::close()
{
    //cout <<"FileStreamTfs with " <<m_filename <<" closed" <<endl;
    if(m_fin){
        delete m_fin;
        m_fin = NULL;
    }
    if(m_fout){
        delete m_fout;
        m_fout = NULL;
    }
}


int FileStreamTfs::read(char* buffer, int len)
{
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::ReadOnly){
        throw FSError("FileStreamTfs try to read append mode stream");
    }

    if(!m_fin){
        shouldClose = true;
        open();
    }

    try{
        ret = m_fin->read(buffer, len);
    }
    catch (tfs::api::TFSException& e){
        if(shouldClose) close();
        throw FSError(string("FileStreamTfs read file failed :") + e.what());
    }

    if(shouldClose) close();
    return ret;
}

int FileStreamTfs::append(const char* buffer, int len)
{
    //cout <<"FileStreamTfs append " <<len <<" bytes" <<endl;
    bool shouldClose = false;
    int ret;

    if(m_openMode != FileStream::Append){
        throw FSError("FileStreamTfs try to append readonly stream");
    }

    if(!m_fout){
        shouldClose = true;
        open();
    }

   try{
        m_fout->append(buffer, len);
    }
    catch (tfs::api::TFSException& e){
        if(shouldClose) close();
        throw FSError(string("FileStreamTfs append file failed :") + e.what());
    }

    if(shouldClose) close();
    return len;  
}


//TODO
string FileStreamTfs::getMetaData(const std::string& propertyName)
{
    return string("not implemented yet");
}

bool FileStreamTfs::setMetaData(const std::string& propertyName, const std::string& data)
{
    return false;
}
