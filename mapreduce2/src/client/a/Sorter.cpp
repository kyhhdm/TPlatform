/**
 * @file Sorter.cpp
 * @description the implementation of Sorter.hpp
 *
 * @author Peng Bo
 * @date 2008-4-1
 * */

#include "Sorter.hpp"
#include "TaskConfigure.hpp"
#include "ClassLoader.hpp"
#include "FileStreamLocal.hpp"
#include "HashableComparable.hpp"
#include "RecordWriter.hpp"
#include "RecordReader.hpp"
//#include "Region.hpp"
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;
using boost::lexical_cast;

Sorter::Sorter(TaskConfigure& taskConfigure, const std::string& outputFile, const vector<std::string>& inputFiles, const string& tmpDir):
    m_inputFiles(inputFiles.begin(), inputFiles.end())
{
    m_loader = new ClassLoader(taskConfigure.getDllName().c_str()); 

    m_recordReaderClass = taskConfigure.getIntermediateFileRecordReaderClass();
    m_recordWriterClass = taskConfigure.getIntermediateFileRecordWriterClass();
    m_keyHashableComparableClass = taskConfigure.getHashableComparableClass();

    m_loader->createInstance(m_keyHashableComparableClass.c_str(), (void*&)m_comparator);

    //save inputFiles for delay instancing
    //copy(inputFiles.begin(), inputFiles.end(), m_inputFiles.begin());
    m_outputFile = outputFile;
    
    m_tmpDirectory = tmpDir;

}

Sorter::~Sorter()
{
    delete m_comparator;
    delete m_loader;
}


void Sorter::chunkSort(std::vector<std::string>& chunkFiles)
{
    //  set chunk size = 256MB
    //  write each chunk to a tmp file.
    //vector<string> chunkFiles;
    //int chunkKeyNumber = 1000000;
    int chunkKeyNumber = 5000000; // 500MB memory
    int curFileId = 0;
    int chunkId = 0;
    bool allFileDone = false;

    RecordReader* reader;
    RecordWriter* writer;
    int totalRecordNumber = 0;

    //create RecordReader instance
    m_loader->createInstance(m_recordReaderClass.c_str(), (void*&)reader);
    reader->initialize(8*1024*1024, true);
    //create RecordWriter instance
    m_loader->createInstance(m_recordWriterClass.c_str(), (void*&)writer);
    writer->initialize(8*1024*1024, true);

    //create chunk file names
    //m_tmpDirectory/chunk_xx
    chunkFiles.clear();

    bool readNextFile = true;
    FileStream* readStream;
    
    //calc chunkKeyNumber by memory limit settings
    //memory include archive buffer and keys, values data
    //
    int keySize = reader->getKeySize();
    int valueSize = reader->getValueSize();
    chunkKeyNumber = 512*1024*1024l / ((keySize + valueSize)*2);

    //start sort chunk by chunk
    while(!allFileDone){

        void* keys = reader->createKeys(chunkKeyNumber);
        void* values = reader->createValues(chunkKeyNumber);
        int valueSize = reader->getValueSize();

        KeyValueIndex *index = new KeyValueIndex[chunkKeyNumber];

        bool chunkDone = false;
        bool readOk;
        int i = 0;
        

        while (!chunkDone) {
            if (readNextFile) {
                 readStream = new FileStreamLocal(m_inputFiles[curFileId], FileStream::ReadOnly, false);
                //initialize archive with default 8M buffer
                reader->open(readStream);  
                readNextFile = false;
            }

            while( i < chunkKeyNumber ){
                void* pKey = (char*)keys + keySize * i ;
                void* pValue = (char*)values + valueSize * i;
                readOk = reader->next(pKey, pValue);
                index[i].key =  pKey;
                index[i].value = pValue;

                if(readOk){
                    i++; 
                }
                else{
                    //release this readStream
                    
                    reader->close();
                    delete readStream;

                    curFileId++;
                    if((unsigned int)curFileId >= m_inputFiles.size()){
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
            
            //create this output file, even if it's null
            //if( i > 0 ){            
            {
                //use quick sort in std sort 
                KeyValueIndexCmp keyValueIndexCmp(m_comparator);
                std::sort(index, index + i,keyValueIndexCmp);

                //write this chunk
                chunkFiles.push_back(m_tmpDirectory + "chunk_" + lexical_cast<std::string>(chunkId));
                FileStream* writerStream = new FileStreamLocal(chunkFiles[chunkId], FileStream::Append, false);
                //initialize archive with default 8M buffer
                writer->open(writerStream);    

                //loop write
                for(int j = 0; j < i ; j++){
                    writer->append( index[j].key, index[j].value);
                }

                //release 
                writer->close();
                delete writerStream;
            }
            chunkDone = true;
            //release read buffer after chunkDone
            reader->flush();

            chunkId++;
            
        }/* end while(!chunkDone) */
        
        //clean up chunk
        //release created object can't not call destructor by delete here.->memory leak maybe
        //or caused the glibc throws exception
        //by add releaseKeys() etc.
        //BUG FIXED: new/delete and new[]/delete dismatch, be careful about type, the user-defined type must be used obviously
        reader->releaseKeys(keys);
        reader->releaseValues(values);
        delete[] index;

    }/* end while(!allFileDone) */
    
    //clean up
    delete reader;
    delete writer;
}

void Sorter::merge(std::vector<std::string>& inputChunkFiles, std::string & outputChunkFile)
{
    vector<RecordReader*> readers;
    RecordWriter* writer;
	int chunkNumber = inputChunkFiles.size();

    //check chunkNumber, >2 at least
    if(chunkNumber <= 0 ) return;
    else if(chunkNumber == 1) {
        //move inputFile into outputFile directly
        path src( inputChunkFiles[0]);
        path dst( outputChunkFile);
        //cout << "#TODO, move inputFile into outputFile directly" << endl;
        
        //::remove(outputChunkFile.c_str());
        //::rename(inputChunkFiles[0].c_str(), outputChunkFile.c_str());

        if(exists(dst)) remove(dst);
        rename(src, dst);
        return;
    }

    //create RecordWriter instance
    m_loader->createInstance(m_recordWriterClass.c_str(), (void*&)writer);
    writer->initialize();
    for (int i = 0 ;i < chunkNumber ; i++) {
        RecordReader *reader;
        //create RecordReader instance
        m_loader->createInstance(m_recordReaderClass.c_str(), (void*&)reader);
        reader->initialize(64*1024, true);
        readers.push_back(reader);
    }

    KeyValueIndexCmp keyValueIndexCmp(m_comparator);
    multiset<KeyValueIndexEx, KeyValueIndexCmp> heap(keyValueIndexCmp);

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
    void* values = readers[0]->createValues(chunkNumber);
    int valueSize = readers[0]->getValueSize();

	bool readOk;
	bool *endOfFile = new bool[chunkNumber];

	for (int i = 0 ;i < chunkNumber ; i++) {
        void* pKey = (char*)keys + keySize * i ;
        void* pValue = (char*)values + valueSize * i;
        readOk = readers[i]->next(pKey, pValue);
        index[i].key =  pKey;
        index[i].value = pValue;
        index[i].streamId = i;

        if(readOk){
			heap.insert(index[i]);
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

		top = *heap.begin();
        heap.erase(heap.begin());

		//write this one
		writer->append(top.key, top.value);
		//push up
		if(!endOfFile[top.streamId]){
            //release read buffer first
            readers[top.streamId]->flush();

            //#TODO, reuse key value object, maybe memory leak here for object not released
            void* pKey = (char*)keys + keySize * top.streamId ;
            void* pValue = (char*)values + valueSize * top.streamId;
			readOk = readers[top.streamId]->next(pKey, pValue);
			if(readOk){
                index[top.streamId].key = pKey;
                index[top.streamId].value = pValue;
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
	delete[] keys;
    delete[] values;
	delete[] index;
}

bool Sorter::sort()
{
    vector<string> chunkFiles;
    int n, m;

    remove_all(m_tmpDirectory);
    create_directory( m_tmpDirectory );

    //step.1 load all inputFiles into memory and sort by chunk
    chunkSort(chunkFiles);
    
    //step.2 merge all chunk file and write result into target output file
    n = chunkFiles.size();
    m = 30;

    vector<string> inputChunkFiles;
    vector<string> outputChunkFiles;
    inputChunkFiles = chunkFiles;

    while(1){

        int outputChunkNumber = (n%m) ? n/m + 1: n/m;

        //cout <<"merge " <<n <<" files to " <<outputChunkNumber <<endl;
        
        //merge m chunks
        for(int i = 0; i < outputChunkNumber; i++){
            int endPos = ((i+1) * m ) >= n  ? n  : (i+1) * m ;

            //format outputChunkFile names
            if(outputChunkNumber == 1){
                outputChunkFiles.push_back(m_outputFile);
            }
            else{
                //m_tmpDirectory/merger_xx
                outputChunkFiles.push_back(m_tmpDirectory + "merge_" + lexical_cast<std::string>(i));
            }

            vector<string> inputChunks(inputChunkFiles.begin() + i * m,inputChunkFiles.begin() + endPos);
            //copy(inputChunkFiles.begin() + i * m,inputChunkFiles.begin() + endPos, inputChunks.begin());
            merge(inputChunks, outputChunkFiles[i]);
        }
        
        n = outputChunkNumber;
        if(n==1) break;
        inputChunkFiles = outputChunkFiles;
        outputChunkFiles.clear();
    }

    //clean temp directory
    //remove_all(m_tmpDirectory);

    return true;
}

