/**
 * @file SetReducer.hpp
 * @description 
 *  it reduces a set of <key,value>, read from sorted key value file and output to user defined collector
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * @author Peng Bo
 * @date 2008-1-11
 *
 * */


#ifndef TPLATFORM_MAPREDUCE_SETREDUCER
#define TPLATFORM_MAPREDUCE_SETREDUCER

//#include "util/Logger.hpp"
#include <string>


namespace mapreduce{
    class DirectCollector;
    class HashableComparable;
    class RecordReader;
    class RecordWriter;
    class TaskConfigure;
    class FileStream;
    class Reducer;
    class ClassLoader;

    /**
     * class SetReducer supplies a function to reduce all the key value records in a file 
     * to output file 
     * */
    class SetReducer{
        public:
            /**
             * Constructor
             * */
            SetReducer(TaskConfigure& taskConfigure, const std::string& inputFile, const std::string& outputFile, 
                    bool doLocalWrite, bool doCombine, bool useLFS = true);
            

            ~SetReducer();

            /**
             * reduce
             * @return : count of key value generated
             *      -1 for failed
             * */
            int reduce();

        private:
            ClassLoader* m_loader;
            HashableComparable* m_comparator;
            DirectCollector* m_directCollector;
            RecordReader* m_reader;
            FileStream* m_readerStream;
            RecordWriter* m_writer;
            FileStream* m_writerStream;
            Reducer* m_reducer;

            //Logger m_logger;
    };
}

#endif


