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

#include <util/Logger.hpp>
#include <util/Config.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <signal.h>
#include <sys/wait.h>
#include <sstream>
#include <boost/scoped_array.hpp>
#include <libgen.h>

using namespace mapreduce;
using namespace std;

namespace fs = boost::filesystem;

//#define LOG_PREFIX "MapTask(" <<m_command.jobId <<"#" <<m_command.taskId <<"): "
#define LOG_PREFIX "MapTask(" <<m_taskDir <<"): "
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



void doMap(const string &path, const string &m_taskDir, const string &confString, 
        int reduceTaskNum, bool doLocalCombine, const string& logFileName) {
    //This is just for PageLen test
    TaskConfigure m_conf;

    //code from MapTask.cpp::map()    
    try {
        Logger::getInstance("mapred_worker").removeAllAppenders();
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(
                new RollingFileAppender(logFileName + ".log", 4 * 1024 * 1024, 5));
        append_1->setName(logFileName);
        std::string pattern = "%D %p - %m\n";
        append_1->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
        Logger::getInstance("mapred_worker").addAppender(append_1);

        vector<string> vs;

        if(!m_conf.readFromString(confString)){
            //error configure 
            LOG_ERROR(LOG_PREFIX <<"Failed to get configure string from " << confString);
            exit(1);
        }
        
        LOG_DEBUG(LOG_PREFIX <<"dll name  as :" << m_conf.getDllName());

        //change homedir
        char dllName[512];
        m_conf.getDllName().copy(dllName, 512);
        char * homeDir = dirname(dllName); 
        if( chdir(homeDir) ){
            //error configure 
            LOG_ERROR(LOG_PREFIX <<"Failed to change to home as :" << homeDir);
            exit(2);
        }
        
        LOG_DEBUG(LOG_PREFIX <<"Start MapTask as :" << "path=" << path << "\n\ttaskDir=" << m_taskDir << "\n\tconfString=" <<
                confString);
        LOG_DEBUG(LOG_PREFIX <<"Set mapper with reduceTaskNum = " 
                  <<reduceTaskNum);
        for (int i = 0; i < reduceTaskNum; ++i) {
            string name = m_taskDir + "/" + boost::lexical_cast<string>(i);
            vs.push_back(name);
        }
        
        LOG_DEBUG(LOG_PREFIX <<"dll name  as :" << m_conf.getDllName());
        LOG_DEBUG(LOG_PREFIX <<"Begin mapping.");
        SetMapper *sm = new SetMapper(m_conf, path, vs);
        int r = sm->map();
        //LOG_DEBUG(LOG_PREFIX <<"End mapping.");

        if (r < 0) {
            LOG_ERROR(LOG_PREFIX <<"Failed to map.");
            exit(2);
        } else {
            LOG_INFO(LOG_PREFIX <<"Map " <<r <<" records.");
        } 
        delete sm;

        // Do local combine.
        if (doLocalCombine) {
            LOG_INFO(LOG_PREFIX <<"Begin local combination.");
            vector<string> vf;
            for (int i = 0; i < vs.size(); ++i) {
                // Sort
                vf.clear();
                vf.push_back(vs[i]);
                string sfile = vs[i] + "_sorted";
                Sorter s(m_conf, sfile, vf);
                if (!s.sort()) {
                    LOG_ERROR(LOG_PREFIX <<"Sort failed in local combination.");
                    exit(3);
                }

                // Reduce
                string outfile = vs[i] + "_combined";
                SetReducer sr(m_conf, sfile, outfile, true, true);
                if (sr.reduce() < 0) {
                    LOG_ERROR(LOG_PREFIX <<"Reduce failed in local combination.");
                    exit(4);
                }

                // Delete original and intermediate file.
                fs::remove(sfile);
                //fs::remove(vs[i]);
            }
            // LOG_INFO(LOG_PREFIX <<"End local combination.");
        }
        LOG_DEBUG(LOG_PREFIX <<"Map completed.");
        exit(0); 
    } catch (exception &ex) {
        LOG_ERROR(LOG_PREFIX <<"Catch " <<ex.what() <<endl)
        exit(-1);
    } catch (...) {
        LOG_ERROR(LOG_PREFIX <<"Catch unknown exception")
        exit(-1);
    }
}


int main(int argc, char* argv[])
{
    string path, taskDir, confString, logFileName;
    int reduceNumber;
    bool doLocalCombine;


    if(argc != 7 ) return -1;
    path = argv[1];
    taskDir = argv[2];
    confString = argv[3];
    reduceNumber = boost::lexical_cast<int>(argv[4]); 
    doLocalCombine = argv[5][0]=='1'?true:false;
    logFileName = argv[6];

    if(getenv("DEBUG_MAPREDUCE")){
        cout << "recude child start pid = " << getpid() << endl;
        sleep(60);
    }
    
    doMap(path, taskDir, confString, reduceNumber, doLocalCombine, logFileName);

    return 0;
}
