/**
 * @file Sorter.cpp
 * @description the implementation of Sorter.hpp
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */

#ifdef _GOGOGO_

#include "Sorter.hpp"
#include "TaskConfigure.hpp"
#include "ClassLoader.hpp"
#include "FileStreamLocal.hpp"
#include "HashableComparable.hpp"
#include "RecordWriter.hpp"
#include "RecordReader.hpp"
#include "RegionIterator.hpp"
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using namespace mapreduce;

Sorter::Sorter(TaskConfigure& taskConfigure, const std::string& outputFile, const vector<std::string>& inputFiles)
{
    m_loader = new ClassLoader(taskConfigure.getDllName().c_str()); 

    m_recordReaderClass = taskConfigure.getIntermediateFileRecordReaderClass();
    m_recordWriterClass = taskConfigure.getIntermediateFileRecordWriterClass();
    m_keyHashableComparableClass = taskConfigure.getHashableComparableClass();

    m_loader->createInstance(m_keyHashableComparableClass.c_str(), (void*&)m_comparor);

    //open stream with no OpenOnDemand flag
    m_writerStream = new FileStreamLocal(outputFile, FileStream::Append, false);
    //create RecordWriter instance
    m_loader->createInstance(m_recordWriterClass.c_str(), (void*&)m_writer);
    //initialize archive with default 8M buffer
    m_writer->initialize();
    m_writer->open(m_writerStream);

    //save inputFiles for delay instancing
    copy(inputFiles.begin(), inputFiles.end(), m_inputFiles.begin());
    

}

Sorter::~Sorter()
{
    delete m_writer;
    delete m_writerStream;
    delete m_comparor;
    delete m_loader;
}


void Sorter::chunkSort(std::vector<std::string>& chunkFiles)
{
    //  set chunk size = 256MB
    //  write each chunk to a tmp file.
    //vector<string> chunkFiles;
    int chunkKeyNumber = 10000;
    int curFileId = 0;
    int chunkId = 0;
    bool allFileDone = false;

    RecordReader* reader;
    RecordWriter* writer;
    HashableComparable* comp;
    int totalRecordNumber = 0;

    //create RecordReader instance
    m_loader->createInstance(m_recordReaderClass.c_str(), (void*&)reader);
    reader->initialize();
    //create RecordWriter instance
    m_loader->createInstance(m_recordWriterClass.c_str(), (void*&)writer);
    writer->initialize();
    //create a Comparable Predicate for sort()
    m_loader->createInstance(m_keyHashableComparableClass.c_str(), (void*&)comp);

    //create chunk file names

    //start sort chunk by chunk
    while(!allFileDone){
        KeyValueIndex* index = new KeyValueIndex[chunkKeyNumber];
        void* keys = reader->createKeys(chunkKeyNumber);
        int keySize = reader->getKeySize();
        bool chunkDone = false;
        bool readOk;
        int i = 0;

        while (!chunkDone) {
            bool readNextFile = false;
            FileStream* readStream = new FileStreamLocal(m_inputFiles[curFileId], FileStream::ReadOnly, false);
            //initialize archive with default 8M buffer
            reader->open(readStream);    

            while( i < chunkKeyNumber ){
                index[i].key =  (char*)keys + keySize;
                RegionIterator iter;
                readOk = reader->next(index[i].key, iter);
                if(readOk){
                    if(iter.size()>1){

                    } 
                    index[i].start
                        index[i].len;
                    i++; 
                }
                else{
                    //release this readStream
                    reader->close();
                    delete readStream;

                    curFileId++;
                    if(curFileId >= m_inputFiles.size()){
                        allFileDone = true;
                    }
                    else{
                        readNextFile = true;
                    }
                    break;
                }
            }

            if(readNextFile) continue;

            //deal with this chunk
            {
                //use quick sort in std sort 
                std::sort(index[0], index[i],*comp);

                //write this chunk
                FileStream* writerStream = new FileStreamLocal(chunkFiles[chunkId], FileStream::Append, false);
                //initialize archive with default 8M buffer
                writer->open(writerStream);    

                //loop write
                for(int j = 0; j < i ; j++){
                    writer->append( index[j].start, index[j].len);
                }

                //release 
                writer->close();
                delete writerStream;
                chunkDone = true;
                chunkId++;
            }
        }/* end while(!chunkDone) */

        //clean up chunk
        delete keys;
        delete index;
    }/* end while(!chunkDone) */

    //clean up
    delete reader;
    delete writer;
    delete comp;
}

void Sorter::merge(std::vector<std::string>& inputChunkFiles, std::string & outputChunkFile)
{
    vector<RecordReader*> readers;
    RecordWriter* writer;
    HashableComparable* comp;
	int chunkNumber = inputChunkFiles.size();

    //create RecordWriter instance
    m_loader->createInstance(m_recordWriterClass.c_str(), (void*&)writer);
    writer->initialize();
    //create a Comparable Predicate for sort()
    m_loader->createInstance(m_keyHashableComparableClass.c_str(), (void*&)comp);
    for (int i = 0 ;i < chunkNumber ; i++) {
        RecordReader *reader;
        //create RecordReader instance
        m_loader->createInstance(m_recordReaderClass.c_str(), (void*&)reader);
        reader->initialize();
        readers.push_back(reader);
    }

    multiset<KeyValueIndexEx, *comp> heap;

    //open files
	for (int i = 0 ;i < chunkNumber ; i++) {
        FileStream* readStream = new FileStreamLocal(inputChunkFiles[i], FileStream::ReadOnly, false);
        //initialize archive with default 8M buffer
        readers[i]->open(readStream);    
	}

    FileStream* writeStream = new FileStreamLocal(outputChunkFile, FileStream::Append, false);
    //initialize archive with default 8M buffer
    writer->open(writeStream);    

    //run merger loop
    KeyValueIndexEx* index = new KeyValueIndexEx[chunkNumber];
    void* keys = readers[0]->createKeys(chunkNumber);
    int keySize = readers[0]->getKeySize();
	bool readOk;
	bool endOfFile[] = new endOfFile[chunkNumber];

	for (int i = 0 ;i < chunkNumber ; i++) {
        index[i].key =  (char*)keys + i * keySize;
		index[i].streamId = i;
        readOk = readers[i]->next(index[i].key, index[i].start, index[i].len);
        if(readOk){
			heap.insert(index);
			endOfFile[i] = false;
        }
        else{
            //reach eof 
			endOfFile[i] = true;
		}
	}
  
	//merge by heap
	KeyValueIndexEx top;
	while(heap.size()){
		top = heap.pop();
		//write this one
		writer->append( top.start, top.len);
		//push up
		if(!endOfFile[top.streamId]){
			readOk = readers[top.streamId]->next(index[top.streamId].key, index[top.streamId].start, index[top.streamId].len);
			if(readOk){
				heap.insert(index[top.streamId]);
			}
			else{
				//reach eof 
				endOfFile[top.streamId] = true;
			}
		}
	}

    //clean up
    for (int i = 0 ;i < chunkNumber ; i++) {
        delete readers[i];
    }
    delete writer;
    delete comp;
	delete keys;
	delete index;
}

int Sorter::sort()
{
    vector<string> chunkFiles;
    int n, m;


    //step.1 load all inputFiles into memory and sort by chunk
    chunkSort(chunkFiles);

    //step.2 merge all chunk file and write result into target output file
    n = chunkFiles.size();
    m = 30;

    vector<string> inputChunkFiles;
    vector<string> outputChunkFiles;
    inputChunkFiles = chunkFiles;
    int iterationNumber = 0;

    while(1){
        int outputChunkNumber = (n%m) ? n/m + 1: n/m;

        //forat outputChunkFile names
        if(outputChunkNumber == 1){
            outputChunkFiles[0] = m_outputFile;
        }
        
        //merge m chunks
        for(int i = 0; i < outputChunkNumber; i++){
            int endPos = ((i+1) * m - 1) >= n ? n - 1 : (i+1) * m - 1;

            vector<string> inputChunks(inputChunkFiles[i * m],inputChunkFiles[endPos]);
            merge(inputChunks, outputChunkFiles[i]);
        }
        
        n = outputChunkNumber;
        if(n==1) break;
        inputChunkFiles = outputChunkFiles;
        outputChunkFiles.clear();
    }

    //clean temp directory
}

#endif