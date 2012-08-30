

#include "TransferImpl.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace tfs;


TransferImpl::TransferImpl(ChunkManager * p_mgr)
{
    assert(p_mgr != NULL);
    m_chunk_mgr = p_mgr;
}

TransferImpl::~TransferImpl()
{
}

ByteSeq TransferImpl::read(Long chunk_id,Int offset,Int len,const ::Ice::Current &)
{
    LOG_DEBUG("TransferImpl::read() prepare read chunk:(" << chunk_id << ","<< offset <<","<< len << ")");
    ifstream chunk_reader;
    int ret = m_chunk_mgr->getChunkInStream(chunk_reader,chunk_id);
    if (ret < 0){
        LOG_ERROR("TransferImpl::read() open chunk :" << chunk_id << "error");
        throw ChunkError("Open Chunk Error");
    }

    chunk_reader.seekg(offset);
    char * buf = new char[len];
    memset(buf,0,len);
    chunk_reader.read(buf,len);
    if (!chunk_reader){
        LOG_ERROR("TransferImpl::read() open chunk :" << chunk_id << "error");
        throw ChunkError("Read Chunk Data Error");        
    }
    // istream_iterator<unsigned char> input(chunk_reader);
    // istream_iterator<unsigned char> end_of_stream;
    //    copy(input,input + len,inserter(vdata,vdata.begin()));
    
    vector<unsigned char> vdata(len);
    vdata.assign(buf,buf + len);

    delete [] buf;
    return vdata;
}

int TransferImpl::write(Long chunk_id,const ByteSeq & seq,Int offset,Int len,const ::Ice::Current &)
{
	ofstream outfile;

	if(!m_chunk_mgr->addIOChunk(chunk_id)){
		LOG_ERROR("TransferImpl::write Error! Chunk is IO-ing!");
		throw ChunkError("Chunk is IO-ing!");
	}

	int ret = m_chunk_mgr->getChunkWriteStream(outfile,chunk_id);
	if (ret < 0)
	{
		m_chunk_mgr->delIOChunk(chunk_id);
		LOG_ERROR("TransferImpl::write Error! Get Chunk out stream Error!");
		throw ChunkError("Get Chunk out stream Error");
	}
	char * buf = new char[len];
	memset(buf,0,len);
	for (int i=0;i<seq.size();++i)
	{
		buf[i] = seq[i];
	}
	
	outfile.seekp(offset);
	outfile.write(buf,seq.size());		

	outfile.close();
	m_chunk_mgr->delIOChunk(chunk_id);
	m_chunk_mgr->updateChunk(chunk_id);

	LOG_INFO("TransferImpl::write() Write chunk:"<<chunk_id << " Complete!");
	delete [] buf;

	return len;
}

void TransferImpl::addChunk(Long chunk_id,const ::Ice::Current &)
{
	if (m_chunk_mgr->addNewChunk(chunk_id) < 0)
	{
		LOG_ERROR("TransferImpl::addChunk() Add Chunk Failed! ID:" << chunk_id);
		throw ChunkError("Add Chunk Failed! it's exsit!");
	}
	LOG_INFO("TransferImpl::addChunk() Add Chunk Complete! ID:" << chunk_id);
}
        
int TransferImpl::append(Long chunk_id,const ByteSeq & seq,Int len,const ::Ice::Current &)
{
	ofstream outfile;

	if(!m_chunk_mgr->addIOChunk(chunk_id)){
		throw ChunkError("Chunk is IO-ing!");
	}

	int ret = m_chunk_mgr->getChunkAppendStream(outfile,chunk_id);
	if (ret < 0)
	{
		m_chunk_mgr->delIOChunk(chunk_id);
		throw ChunkError("Get Chunk out stream Error");
	}
	char * buf = new char[len];
	memset(buf,0,len);
	for (int i=0;i<seq.size();++i)
	{
		buf[i] = seq[i];
	}

	size_t start = outfile.tellp();
	outfile.write(buf,seq.size());		

	outfile.close();
	m_chunk_mgr->delIOChunk(chunk_id);
	m_chunk_mgr->updateChunk(chunk_id);

	LOG_INFO("TransferImpl::append() append chunk:"<<chunk_id << " Complete!");
	delete [] buf;

	return start;

 //   ofstream outfile;

	//if(!m_chunk_mgr->addIOChunk(chunk_id)){
	//	throw ChunkError("Chunk is IO-ing!");
	//}

 //   //int ret = m_chunk_mgr

	//m_chunk_mgr->delIOChunk(chunk_id);
	//m_chunk_mgr->updateChunk(chunk_id);
    
}


void TransferImpl::rollback(Long op_id,const ::Ice::Current &)
{
}


string TransferImpl::getLocalPath(Long chunk_id,const ::Ice::Current& )
{
	string chunk_path;
	if (m_chunk_mgr->getChunkFilePath(chunk_path,chunk_id) < 0)
	{
		LOG_ERROR("TransferImpl::getLocalPath error, chunk id:" << chunk_id);
		throw ChunkError("No Such Chunk");
	}
	return chunk_path;
}
