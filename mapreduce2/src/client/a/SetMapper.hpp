/**
 * @file SetMapper.hpp
 * @description
 *   it maps a set of <key,value>, and handles the input and output of intermediate keyvalue files
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * @author Peng Bo
 * @date 2008-1-11
 *
 * */
#ifndef TPLATFORM_MAPREDUCE_SETMAPPER
#define TPLATFORM_MAPREDUCE_SETMAPPER

//#include "util/Logger.hpp"
#include "TaskConfigure.hpp"
#include <string>
#include <vector>

namespace mapreduce{
    class Partitioner;
    class RecordReader;
    class TaskConfigure;
    class FileStream;
    class Mapper;
    class ClassLoader;
 
    /**
     * class SetMapper supplies a function to map all keyvalue records in a file to 
     * other keyvalue records in another file
     *
     * */
    class SetMapper{
        public:
            /**
             * Constructor
             * it get the dynamic library and use it the map the set of <Key, Value>
             */
            SetMapper(TaskConfigure& taskConfigure, const std::string& inputFile, const std::vector<std::string>& outputFiles,
                    bool useLFS = true);

            ~SetMapper();

            /**
             *  Map
             *
             *  @return: count of keyvalue generated / -1 for failed
             * */
            int map();

        private:
			ClassLoader* m_loader;
			Partitioner* m_partitioner;
			RecordReader* m_reader;
            FileStream* m_readerStream;
            Mapper* m_mapper;
            
            //Logger m_logger;
    };
}

#endif
