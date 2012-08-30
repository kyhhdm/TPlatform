/**
 * @file TaskConfigure.hpp
 * @description:
 *  TaskConfigure is configuration class for task operation, especially it's initialization.
 *  
 *
 * @date 2008-04-02
 * */

#ifndef TPLATFORM_MAPREDUCE_TASKCONFIGURE
#define TPLATFORM_MAPREDUCE_TASKCONFIGURE

#include <mapred/Serializable.hpp>
#include <string>
#include <map>

namespace mapreduce{
    namespace api{
        class MapReduceJob;
    }
    
    /**
    * TaskConfigure contains user defined class names, 
    * In c++, it's awkfully to dynamically create objects by class name.
    *
    **/     
    class TaskConfigure: public Serializable{
        std::map<std::string,std::string> m_keyClassMap;
        void initialize();

        //core settings
        std::string m_soFile;
        std::string m_MapperClass;
        std::string m_ReducerClass;
        std::string m_MapperOutKeyClass;
        std::string m_MapperOutValueClass;
        //following group are optional
        std::string m_MapperInKeyClass;
        std::string m_MapperInValueClass;
        std::string m_MapperRecordReaderClass;
        std::string m_ReducerOutKeyClass;
        std::string m_ReducerOutValueClass;
        std::string m_ReducerRecordWriterClass;
        
    public:
        static const std::string DefaultReaderClass;
        static const std::string DefaultWriterClass;

        /**
         * Constructor
         *
         *
         **/     
        TaskConfigure();
        TaskConfigure(const std::string& configureFile);
        TaskConfigure(api::MapReduceJob& jobSpec);
        virtual ~TaskConfigure();

        /**
        * Serialization
        *
        **/            
        virtual bool writeToString(std::string& output) const;
        virtual bool readFromString(const std::string& input);

        /**
         * Accessor
         *
         **/                 
        std::string getDllName(){return m_soFile;}
        void setDllName(const std::string& soFile){m_soFile = soFile;}
        std::string getMapperClass(){return m_MapperClass;}
        void setMapperClass(const std::string& mapperClass){m_MapperClass = mapperClass;}
        std::string getReducerClass(){return m_ReducerClass;}
        void setReducerClass(const std::string& reducerClass){m_ReducerClass = reducerClass;}
        std::string getMapperOutKeyClass(){return m_MapperOutKeyClass;}
        void setMapperOutKeyClass(const std::string& mapperOutKeyClass){m_MapperOutKeyClass = mapperOutKeyClass;}
        std::string getMapperOutValueClass(){return m_MapperOutValueClass;}
        void setMapperOutValueClass(const std::string& mapperOutValueClass){m_MapperOutValueClass = mapperOutValueClass;}


        std::string getMapperInKeyClass(){return m_MapperInKeyClass;}
        void setMapperInKeyClass(const std::string& mapperInKeyClass){m_MapperInKeyClass = mapperInKeyClass;}
        std::string getMapperInValueClass(){return m_MapperInValueClass;}
        void setMapperInValueClass(const std::string& mapperInValueClass){m_MapperInValueClass = mapperInValueClass;}

        std::string getReducerOutKeyClass(){return m_ReducerOutKeyClass;}
        void setReducerOutKeyClass(const std::string& reducerOutKeyClass){m_ReducerOutKeyClass = reducerOutKeyClass;}
        std::string getReducerOutValueClass(){return m_ReducerOutValueClass;}
        void setReducerOutValueClass(const std::string& reducerOutValueClass){m_ReducerOutValueClass = reducerOutValueClass;}


        std::string getMapperRecordReaderClass();
        void setMapperRecordReaderClass(const std::string& readerClass){ m_MapperRecordReaderClass = readerClass;}
        std::string getReducerRecordWriterClass();
        void setReducerRecordWriterClass(const std::string& writerClass){ m_ReducerRecordWriterClass = writerClass;}

        std::string getIntermediateFileRecordReaderClass();
        std::string getIntermediateFileRecordWriterClass();

        std::string getHashableComparableClass();

    };
}

#endif
