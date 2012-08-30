/**
 * @file	Mapper.cpp
 *      isolated process to provide fork-safety for MapTask execution
 *
 * @author	
 * @date	
 *
 */

#include "mapred/SetMapper.hpp"
#include "mapred/Sorter.hpp"
#include "mapred/SetReducer.hpp"
#include <tfs/tfs.h>

#include <util/Logger.hpp>
#include <util/Config.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <signal.h>
#include <sys/wait.h>
#include <sstream>
#include <libgen.h>

using namespace mapreduce;
using namespace std;

namespace fs = boost::filesystem;

//#define LOG_PREFIX "MapTask(" <<m_command.jobId <<"#" <<m_command.taskId <<"): "
#define LOG_PREFIX "ReduceTask(" <<m_taskDir <<"): "
// Define several macros for convience
#ifndef CXX_TEST
#define LOG_DEBUG(x)    {/*cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_DEBUG(Logger::getInstance("mapred_worker"), x) }
#define LOG_INFO(x)     {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_INFO(Logger::getInstance("mapred_worker"), x) }
#define LOG_WARN(x)     {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_WARN(Logger::getInstance("mapred_worker"), x) }
#define LOG_ERROR(x)    {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_ERROR(Logger::getInstance("mapred_worker"), x); Logger::getInstance("mapred_worker").setLogLevel(DEBUG_LOG_LEVEL); }
#define LOG_FATAL(x)    {/* cerr <<"[" <<Worker::name() <<"]" <<x <<endl;*/ LOG4CPLUS_FATAL(Logger::getInstance("mapred_worker"), x) }
#else
    #define LOG_DEBUG(x) 
    #define LOG_INFO(x) 
    #define LOG_WARN(x) 
    #define LOG_ERROR(x) 
    #define LOG_FATAL(x) 
#endif



void doReduce(const string &m_taskDir, const string &confString, 
           const string &sortedFile, const vector<string>& mappedFiles, bool doGroupBySort,
           const string &outputFileString, const string &partition, const string& logFileName) {
    //This is just for PageLen test
    TaskConfigure m_conf;

    try {
        Logger::getInstance("mapred_worker").removeAllAppenders();
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(
            new RollingFileAppender(logFileName + ".log", 4 * 1024 * 1024, 5));
        append_1->setName(logFileName);
        std::string pattern = "%D %p - %m\n";
        append_1->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
        Logger::getInstance("mapred_worker").addAppender(append_1);

        if(!m_conf.readFromString(confString)){
            //error configure 
            LOG_ERROR(LOG_PREFIX <<"Failed to get configure string from " << confString);
            exit(1);
        }
        
        //change homedir
        char dllName[512];
        m_conf.getDllName().copy(dllName, 512);
        char * homeDir = dirname(dllName); 
        if( chdir(homeDir) ){
            //error configure 
            LOG_ERROR(LOG_PREFIX <<"Failed to change to home as :" << homeDir);
            exit(2);
        }
 
        //if(groupMode == SEQUENCE){
        // Sort
        LOG_DEBUG(LOG_PREFIX <<"Begin sorting.");
        string tmpDirForSort = m_taskDir + "/_tmp_sort_";
        Sorter s(m_conf, sortedFile, mappedFiles, tmpDirForSort);
        if (!s.sort()) {
            LOG_ERROR(LOG_PREFIX <<"Sort Error.") 
                exit(1);
        }
        LOG_DEBUG(LOG_PREFIX <<"End Sorting.");

        // Reduce
        tfs::api::FileSystem tfs;
        LOG_DEBUG(LOG_PREFIX <<"Begin reducing.");
        //string outputFile = m_command.outputFile + "/" + boost::lexical_cast<string>(m_command.partition);
        string outputFile = outputFileString + "/" + partition;
        string tmpOutputFile = outputFile + ".tmp_" + boost::lexical_cast<string>(clock());
        SetReducer *sr = new SetReducer(m_conf, sortedFile, tmpOutputFile, false, false);
        int r = sr->reduce();
        delete sr;
        //fs::remove(sortedFile);
        if (tfs.existFile(outputFile)) {
            LOG_DEBUG(LOG_PREFIX <<"Remove existed tfs file " <<outputFile);
            tfs.removeFile(outputFile);
        }
        tfs.renameFile(tmpOutputFile, outputFile);
        LOG_DEBUG(LOG_PREFIX <<"Rename " <<tmpOutputFile <<" to " <<outputFile);
        //LOG_DEBUG(LOG_PREFIX <<"End reducing.");
        if (r < 0) {
            LOG_ERROR(LOG_PREFIX <<"Reduce partition " <<partition <<" Error.");
            exit(1);
        } else {
            LOG_INFO(LOG_PREFIX <<"Reduce partition " <<partition <<" Completed, " <<r <<" records in total.");
            exit(0);
        }
        //}//end of if
        /*
        if(groupMode == HASHTABLE){
        // Reduce
        tfs::api::FileSystem tfs;
        HasherReducer hr(lib.reducerLib(), lib.hasherLib(), lib.writerLib(), m_command.jobId, m_command.taskId);      
        LOG_DEBUG(LOG_PREFIX <<"Begin reducing.");
        string outputFile = m_command.outputFile + "/" + boost::lexical_cast<string>(m_command.partition);
        string tmpOutputFile = outputFile + ".tmp_" + boost::lexical_cast<string>(clock());
        int r = hr.reduce(tmpOutputFile, sortedFile, true);
        fs::remove(sortedFile);
        if (tfs.existFile(outputFile)) {
        LOG_DEBUG(LOG_PREFIX <<"Remove existed tfs file " <<outputFile);
        tfs.removeFile(outputFile);
        }
        tfs.renameFile(tmpOutputFile, outputFile);
        LOG_DEBUG(LOG_PREFIX <<"Rename " <<tmpOutputFile <<" to " <<outputFile);
        //LOG_DEBUG(LOG_PREFIX <<"End reducing.");
        if (r < 0) {
        LOG_ERROR(LOG_PREFIX <<"Reduce partition " <<m_command.partition <<" Error.");
        exit(1);
        } else {
        LOG_INFO(LOG_PREFIX <<"Reduce partition " <<m_command.partition <<" Completed.");
        exit(0);
        }
        }//end of if
        */
    } catch (exception &ex) {
        LOG_ERROR(LOG_PREFIX <<"reducer Catch " <<ex.what() <<endl)
            exit(1);
    } catch (...) {
        LOG_ERROR(LOG_PREFIX <<"Catch unknown exception")
            exit(1);
    }
}


int main(int argc, char* argv[])
{
    string taskDir, confString;
    string sortedFile, mappedFileString;
    string outputFileString, partition, logFileName;
    bool doGroupBySort;
    vector<string> mappedFiles;

    if(argc != 9 ) return -1;
    taskDir = argv[1];
    confString = argv[2];
    sortedFile = argv[3];
    mappedFileString = argv[4];
    doGroupBySort = argv[5][0]=='1'?true:false;
    outputFileString = argv[6];
    partition = argv[7];
    logFileName = argv[8];
    
    if(getenv("DEBUG_MAPREDUCE")){
        cout << "recude child start pid = " << getpid() << endl;
        sleep(60);
    }
    
    //get mappedFiles;
    string::size_type idx = 0, end;
    do{
        end = mappedFileString.find('\t', idx);
        if (end != string::npos){
            mappedFiles.push_back(mappedFileString.substr(idx, end - idx));
            idx = end + 1;
        }
    }while(end != string::npos);


    doReduce(taskDir, confString, sortedFile, mappedFiles, doGroupBySort, outputFileString, partition, logFileName);

    return 0;
}
