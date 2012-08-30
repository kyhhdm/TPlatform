/**
 * @file Sorter.hpp
 * @description
 *  it sorts the set of <key,value>, which are inputs for for Reduce task
 *
 * @author Peng Bo
 * @date 2008-1-11
 * */

#ifndef TPLATFORM_MAPREDUCE_SORTER
#define TPLATFORM_MAPREDUCE_SORTER

#include "TaskConfigure.hpp"
#include "HashableComparable.hpp"
#include <string>
#include <vector>

namespace mapreduce{
    class HashableComparable;
    class RecordWriter;
    class RecordReader;
    class TaskConfigure;
    class FileStream;
    class ClassLoader;

    /**
     * class Sorter supplies a function to sort all keyvalue records in multiple files 
     * and output the result to a single file
     * */
    class Sorter {
    public:
        /**
        * Constructor
        * 
        */
        Sorter(TaskConfigure& taskConfigure, const std::string& outputFile, const std::vector<std::string>& inputFiles, const std::string &tmpDir = "_tmp_sort/");

        ~Sorter();

        /**
        * sort all <Key, Value> pairs in the input files, and output to outputFile
        * 
        * @return : success/error code
        * @throws 
        *
        */
        bool sort();

    private:

        ClassLoader* m_loader;
        HashableComparable* m_comparator;
        
        std::vector<std::string> m_inputFiles;
        std::string m_outputFile;
        std::string m_recordReaderClass;
        std::string m_recordWriterClass;
        std::string m_keyHashableComparableClass;

        std::string m_tmpDirectory;

        //Logger m_logger;

        /**
        * sort all input files and create output sorted chunks files
        */ 
        void chunkSort(std::vector<std::string>& chunkFiles);

        /**
        * merge sorted chunk files
        */ 
        void merge(std::vector<std::string>& inputChunkFiles, std::string & outputChunkFile);


    };

    class KeyValueIndex{
    public:
        void* key;
        void* value;
    };

    class KeyValueIndexEx{
    public:
        void* key;
        void* value;
        int streamId;
    };

    class KeyValueIndexCmp{
        HashableComparable* m_comparator;
    public:
        KeyValueIndexCmp(HashableComparable* comparator):m_comparator(comparator){;}
        bool operator()(const KeyValueIndex& t1, const KeyValueIndex& t2) const{
            //return m_comparator->operator()(t1.key, t2.key);
            return (*m_comparator)(t1.key, t2.key);
        }
        bool operator()(const KeyValueIndexEx& t1, const KeyValueIndexEx& t2) const{
            return (*m_comparator)(t1.key, t2.key);
        }
    };

    //class KeyValueIndex{
    //public:
    //    void* key;
    //    char* start;
    //    int len;
    //public:
    //};

  //  class KeyValueIndexEx{
  //  public:
  //      void* key;
  //      char* start;
  //      int len;
		//int streamId;
  //  public:
  //  };


}

#endif


