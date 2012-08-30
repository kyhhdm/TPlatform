/**
 * @file ArchiveBuffer.cpp
 * the implementation of ArchiveBuffer
 *
 * @author PengBo
 * @date 2008-01-07
 * */

#include "ArchiveBuffer.hpp"
#include "FileStream.hpp"
#include "ByteCodec.hpp"
#include "MapReduceException.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace mapreduce;


int ArchiveBuffer::defaultSize = 8*1024*1024;
int ArchiveBuffer::defaultRecordSizeThreshold = 1024;

ArchiveBuffer::Buffer::Buffer(int bufferSize)
{
    m_recordEndPos = m_curPos = m_endPos = 0;
    m_buffer = new char[bufferSize];
    m_bufferSize = bufferSize;
}

ArchiveBuffer::Buffer::~Buffer()
{
    delete[] m_buffer;
}

ArchiveBuffer::ArchiveBuffer(int bufferSize , bool autoClearBuffer)
{
    m_stream = NULL;
    m_mode = FileStream::Unkown;

    if(bufferSize <= 0 || bufferSize > 64*1024*1024l) bufferSize = defaultSize;
    m_bufferSize = bufferSize;
	m_autoClearBuffer = autoClearBuffer;
    m_endBufferId = 0;
    m_recordSizeThreshold = defaultRecordSizeThreshold;

    Buffer *buffer = new Buffer(m_bufferSize);
    m_buffers.push_back(buffer);

    m_bufferOffset = 0ll;
}

ArchiveBuffer::~ArchiveBuffer()
{
    closeStream();

    for(unsigned int i = 0; i < m_buffers.size(); i++){
        delete m_buffers[i];
    }
}


void ArchiveBuffer::openStream(FileStream* stream)
{
	if(m_stream) closeStream();

    m_stream = stream;
    if (m_mode == FileStream::Unkown){
        m_mode = stream->getOpenMode();
    }
    else{
        if(m_mode != stream->getOpenMode()){
            throw FSError("ArchiveBuffer reopen stream OpenMode mismatch error!");
        }
    }

    if(m_mode == FileStream::Append){
        //setup an empty buffer
        m_buffers[m_buffers.size()-1]->setTail(m_bufferSize);
    }

    //reset stream buffer offset
    m_bufferOffset = 0ll;
}


void ArchiveBuffer::closeStream()
{
	if(m_stream){
        //
        //save unsaved data, this can't guarantee record atomicity. be CAREFUL
        //do nothing for ReadOnly stream
        //
        if(m_mode == FileStream::Append){
            Buffer *curBuffer = m_buffers[0];
            m_stream->append(curBuffer->begin(), curBuffer->cur()-curBuffer->begin());
            delete curBuffer;
            Buffer *buffer = new Buffer(m_bufferSize);
            m_buffers[0] = buffer;
        }

        //close stream
		m_stream->close();
		m_stream = NULL;
	}
}


int ArchiveBuffer::commitReadRecord()
{
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    curBuffer->setRecordEnd(); 
    m_endBufferId = m_buffers.size()-1;

    //cout << "commitReadRecord: endBufferId = " << m_endBufferId << endl;

    return curBuffer->cur()-curBuffer->begin() + m_bufferSize * (m_buffers.size()-1);
}

void ArchiveBuffer::commitAppendRecord()
{
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    curBuffer->setRecordEnd(); 
}

int ArchiveBuffer::getCurPos()
{
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    return curBuffer->cur()-curBuffer->begin() + m_bufferSize * (m_buffers.size()-1);
}

unsigned long long ArchiveBuffer::getByteOffset()
{
    return getCurPos() + m_bufferOffset;
}

RegionIterator ArchiveBuffer::getRecord(int startPos, int endPos)
{
    Region region;
    int startBufferId, endBufferId;

    startBufferId = startPos / m_bufferSize;
    endBufferId = endPos / m_bufferSize;

    int start , end;

    m_regions.clear();

    for(int i = startBufferId; i <= endBufferId; i++){
        if(i > startBufferId) start = 0;
        else start = startPos - startBufferId * m_bufferSize;
        if(i < endBufferId) end = m_buffers[i]->end() - m_buffers[i]->begin();
        else end = endPos - endBufferId * m_bufferSize;

        region.pStart = m_buffers[i]->begin() + (start % m_bufferSize);
        region.len = end - start;
        
        if(region.len > 0){
            m_regions.push_back(region);
        }
    }

    return RegionIterator(m_regions.begin(), (int)m_regions.size());

}


//
// Read
//
char* ArchiveBuffer::readZString(char endChar)
{
    char *p, *pRet;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    pRet = NULL;

    //#TODO, need faster search algorithm 
    for(p = curBuffer->cur(); p< curBuffer->end(); ++p){
        if (*p == endChar) {

            //modify source data!!!
            *p = '\0'; //return ZString always

            pRet = curBuffer->cur();
            //if(p+1 <= curBuffer->end()){
                curBuffer->setCur(p + 1 - curBuffer->begin());
                return pRet;
            //}
        }
    }

    //record break, let's add new buffer
	if(0 == readInNewBuffer()){
		//reach eof
		return NULL;
	}

    curBuffer = m_buffers[m_buffers.size()-1];
    for(p = curBuffer->cur(); p< curBuffer->end(); ++p){
        if (*p == endChar) {

            //modify source data!!!
            *p = '\0'; //return ZString always

            pRet = curBuffer->cur();
            curBuffer->setCur(p + 1 - curBuffer->begin());
            return pRet;
        }
    }

    //not found in new buffer
    throw BufferError("ArchiveBuffer::readZString fail for record too large");
}

char* ArchiveBuffer::readPString(int &stringLen)
{
    char *p;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    bool newBufferReaded = false;
    
    p = curBuffer->cur(); 
    stringLen = 0;

    //first get len byte of PString
    if(p + 4 <= curBuffer->end()){
        stringLen = CByteCode::decode(p);
    }
    else{
        //assume the PString is at least 4 bytes,
        //otherwise move it to new buffer.
        if(0 == readInNewBuffer()){
			return NULL;
		}
        newBufferReaded = true;
        curBuffer = m_buffers[m_buffers.size()-1];
        p = curBuffer->cur(); 
        stringLen = CByteCode::decode(p);
    }
   
    //now, p pointer to string content
    if(p + stringLen <= curBuffer->end()){
        curBuffer->setCur(p + stringLen - curBuffer->begin());
        return p;
    }

    if(!newBufferReaded){
        //record break, let's add new buffer
        if(0 == readInNewBuffer()){
			return NULL;
		}
        curBuffer = m_buffers[m_buffers.size()-1];
        p = curBuffer->cur(); 
        stringLen = CByteCode::decode(p);

        if(p + stringLen <= curBuffer->end()){
            curBuffer->setCur(p + stringLen - curBuffer->begin());
            return p;
        }
    }

    //not found in new buffer
    throw BufferError("readPString fail for record too large");
}

char* ArchiveBuffer::readData(int dataSize)
{
    char *p;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    
    p = curBuffer->cur(); 
    if(p + dataSize <= curBuffer->end()){
        curBuffer->setCur(p + dataSize - curBuffer->begin());
        return p;
    }

    //record break, let's add new buffer
	if(0 == readInNewBuffer()){
		return NULL;
	}

    curBuffer = m_buffers[m_buffers.size()-1];
    p = curBuffer->cur(); 
    if(p + dataSize <= curBuffer->end()){
        curBuffer->setCur(p + dataSize - curBuffer->begin());
        return p;
    }

    //not found in new buffer
    throw BufferError("ArchiveBuffer::readData fail for record too large");
}


//
// Append
//
char* ArchiveBuffer::appendZString(const char* data, char endChar)
{
    char *p;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    int stringLen = strlen(data);

    p = curBuffer->cur(); 
    
    //clear buffer if it's nearly full
    if(!(p + stringLen + 1<= curBuffer->end())){
        clearBuffer();
        p = curBuffer->cur(); 
    }

    if(p + stringLen + 1<= curBuffer->end()){
        memcpy(p, data, stringLen);
        p[stringLen] = endChar;
        curBuffer->setCur(p + stringLen + 1 - curBuffer->begin());
        return p;
    }

    throw BufferError("ArchiveBuffer::appendZString fail for record too large");
}

char* ArchiveBuffer::appendPString(const char* data, int len)
{
    char *p, *pStart;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];

    pStart = p = curBuffer->cur(); 

    if(!(p + 4 + len <= curBuffer->end())){
        clearBuffer();
        pStart = p = curBuffer->cur(); 
    }
    
    if(p + 4 + len <= curBuffer->end()){
        CByteCode::code(len, p);
        
        memcpy(p, data, len);
        curBuffer->setCur(p + len - curBuffer->begin());
        return pStart;
    }

    throw BufferError("ArchiveBuffer::appendPString fail for record too large");

}

char* ArchiveBuffer::appendData(const void* data, int dataSize)
{
    char *p;
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];

    p = curBuffer->cur(); 
    
    if(!(p + dataSize <= curBuffer->end())){
        clearBuffer();
        p = curBuffer->cur(); 
    }

    if(p + dataSize <= curBuffer->end()){
        memcpy(p, data, dataSize);
        curBuffer->setCur(p + dataSize - curBuffer->begin());
        return p;
    }

    throw BufferError("ArchiveBuffer::appendPString fail for record too large");

}

void ArchiveBuffer::clearBuffer()
{
    //
    //#!!!, all position returned by getCurPos will invalidate after this call
    //

    if(m_mode == FileStream::ReadOnly){
        //realse all buffers before the last record
        //for(int i = 0; i < m_endBufferId ; i++){
        //    delete m_buffers[i];
        //}
        vector<Buffer*>::iterator pos = m_buffers.begin();
        for(int i = 0; i < m_endBufferId ; i++){

            //update stream buffer offset
            m_bufferOffset += (*pos)->end() - (*pos)->begin();

            //for debug purpose
            (*pos)->clear();

            delete *pos;
            pos = m_buffers.erase(pos);
        }
        //m_buffers.erase(0,m_endBufferId);
        
        /*if(m_endBufferId > 0){
            cout << "clearBuffer : endBufferId = " << m_endBufferId << endl;
        }*/

        m_endBufferId = 0;
    }
    else if (m_mode == FileStream::Append){
        //write data and clear buffer
        Buffer *curBuffer = m_buffers[m_buffers.size()-1];
        int dataSize;

        dataSize = curBuffer->recordEnd()-curBuffer->begin();
        if(dataSize > 0){
            m_stream->append(curBuffer->begin(), dataSize);

            //update stream buffer offset
            m_bufferOffset += dataSize;

            if((dataSize = curBuffer->cur() - curBuffer->recordEnd())>0){
                //move data from <recordEnd,cur> to 0
                if(curBuffer->recordEnd() - curBuffer->begin() < dataSize){
                    char *tmp = new char[dataSize];
                    memcpy(tmp, curBuffer->recordEnd(), dataSize);
                    memcpy(curBuffer->begin(), tmp, dataSize);
                    delete[] tmp;
                }
                else{
                    memcpy(curBuffer->begin(), curBuffer->recordEnd(), dataSize);
                }
            }

            curBuffer->setCur(0);
            curBuffer->setRecordEnd();
            curBuffer->setCur(dataSize);
        }
    }

}

int ArchiveBuffer::readInNewBuffer()
{
    Buffer *curBuffer = m_buffers[m_buffers.size()-1];
    int readLen;

    int curDataLen = curBuffer->end() - curBuffer->begin();
    bool emptyBuffer = (curBuffer->end() == curBuffer->begin());
    bool fullBuffer = (curDataLen == m_bufferSize);
    
    if(!fullBuffer){
        if(emptyBuffer || (m_bufferSize - curDataLen) > m_recordSizeThreshold){
            //it an empty buffer, just read in data
            readLen = m_stream->read(curBuffer->cur(), m_bufferSize - curDataLen);
            curBuffer->setTail(curDataLen + readLen);
            if(m_autoClearBuffer) clearBuffer();
            return readLen;
        }
        else{
            //the left space is too small, so skip them
        }
    }

    Buffer *buffer = new Buffer(m_bufferSize);
    m_buffers.push_back(buffer);

    int copyDataLen = curBuffer->end() - curBuffer->cur();
    int fillDataLen = m_bufferSize - copyDataLen;


    if(copyDataLen > 0) memcpy(buffer->begin(),curBuffer->cur(),copyDataLen);
    curBuffer->cutTail();
    
    readLen = m_stream->read(buffer->cur() + copyDataLen, fillDataLen);
    buffer->setTail(copyDataLen + readLen);

	//at last , free buffer if autoClearBuffer
	if(m_autoClearBuffer) clearBuffer();
    return readLen;
}
