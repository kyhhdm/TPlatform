/**
 * @file	MapTask.cpp
 *  Implementation of MapTask class.	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/08/2007 06:19:37 PM CST
 *
 */
#include "Worker.hpp"
#include "MapTask.hpp"
#include "mapred/SetMapper.hpp"
#include "mapred/Sorter.hpp"
#include "mapred/SetReducer.hpp"
#include <tfs/tfs.h>
#include <tianwang/Transfer.h>

#include <Ice/Ice.h>
#include <util/Config.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <signal.h>
#include <sys/wait.h>
#include <sstream>
#include <boost/scoped_array.hpp>
#include <stdio.h>
#include <errno.h>

using namespace mapreduce;
using namespace tfs::api;
using namespace std;

namespace fs = boost::filesystem;

#define LOG_MT_PREFIX "MapTask(" <<m_command.jobId <<"#" <<m_command.taskId <<"): "

MapTask::MapTask(const TaskConfigure &conf, 
        const MasterCommand &mc, const string &taskDir, Worker *worker) {
    m_command = mc;
    m_taskDir = taskDir;
    m_worker = worker;
    m_conf = conf;
}

bool MapTask::getFile(const MasterCommand &mc, string &path) {
    LOG_DEBUG(LOG_MT_PREFIX <<"Get map file, chunk id " <<mc.chunkID);
    //tfs::ChunkTransfer ct;
    /**
     * add by Chen Rishan
     * the module of datatransfer had been replaced of ice
     */
    try {
        Ice::CommunicatorPtr ic = Ice::initialize();
        Ice::ObjectPrx base = ic->stringToProxy("Transfer:tcp -h " 
                + mc.chunkLocation.name + " -p " 
                + boost::lexical_cast<string>(mc.chunkLocation.port) );
        tfs::slice::TransferPrx tp = tfs::slice::TransferPrx::checkedCast(base);

        if (mc.chunkLocation.name == m_worker->address().name) {
            path = tp->getLocalPath(mc.chunkID);
            LOG_INFO(LOG_MT_PREFIX <<"Map local file " + path);
        } else {
            LOG_INFO(LOG_MT_PREFIX <<"Get remote file from " <<mc.chunkLocation.name
                    <<":" <<mc.chunkLocation.port);
            path = m_taskDir + "_" + boost::lexical_cast<string>(mc.chunkID) + ".chk.tmp";
            LOG_INFO(LOG_MT_PREFIX <<"Map file " << path);

            // Get remote file
            ofstream fout(path.c_str(), ios::binary);

            int n = 500000;
            for (int i = 0; i < (mc.chunkSize-1) / n + 1; ++i) {
                int nleft = mc.chunkSize - n * i;
                vector<unsigned char> vc = tp->read(mc.chunkID, n * i, min(n, nleft));
                assert(vc.size() == min(n, nleft));
                fout.write((const char *)&vc[0], vc.size());
                if (!fout.good()) {
                    LOG_ERROR(LOG_MT_PREFIX <<"Transfer remote file error.");
                    return false;
                }
            }
            fout.close();
            LOG_DEBUG(LOG_MT_PREFIX <<"Get map file done.")
        }
    } catch (const Ice::Exception &ex) {
        LOG_ERROR(LOG_MT_PREFIX <<"Transfer remote file error.");
        return false;
    }
    return true;
}

void MapTask::map(const string &path, const string &m_taskDir) {
    try {
        Logger::getInstance("mapred_worker").removeAllAppenders();
        helpers::LogLog::getLogLog()->setInternalDebugging(false);
        SharedAppenderPtr append_1(
                new RollingFileAppender(m_taskDir + ".log", 4 * 1024 * 1024, 5));
        append_1->setName(m_taskDir);
        std::string pattern = "%D %p - %m\n";
        append_1->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
        Logger::getInstance("mapred_worker").addAppender(append_1);

        vector<string> vs;

        LOG_DEBUG(LOG_MT_PREFIX <<"Set mapper with reduceTaskNum = " 
                <<m_command.reduceTaskNum);
        for (int i = 0; i < m_command.reduceTaskNum; ++i) {
            string name = m_taskDir + "/" + boost::lexical_cast<string>(i);
            vs.push_back(name);
        }

        LOG_DEBUG(LOG_MT_PREFIX <<"Begin mapping.");
        SetMapper *sm = new SetMapper(m_conf, path, vs);
        int r = sm->map();
        //LOG_DEBUG(LOG_MT_PREFIX <<"End mapping.");

        if (r < 0) {
            LOG_ERROR(LOG_MT_PREFIX <<"Failed to map.");
            exit(1);
        } else {
            LOG_INFO(LOG_MT_PREFIX <<"Map " <<r <<" records.");
        } 
        delete sm;

        // Do local combine.
        if (m_command.doLocalCombine) {
            LOG_INFO(LOG_MT_PREFIX <<"Begin local combination.");
            vector<string> vf;
            for (int i = 0; i < vs.size(); ++i) {
                // Sort
                vf.clear();
                vf.push_back(vs[i]);
                string sfile = vs[i] + "_sorted";
                Sorter s(m_conf, sfile, vf);
                if (!s.sort()) {
                    LOG_ERROR(LOG_MT_PREFIX <<"Sort failed in local combination.");
                    exit(1);
                }

                // Reduce
                string outfile = vs[i] + "_combined";
                SetReducer sr(m_conf, sfile, outfile, true, true);
                if (sr.reduce() < 0) {
                    LOG_ERROR(LOG_MT_PREFIX <<"Reduce failed in local combination.");
                    exit(1);
                }

                // Delete original and intermediate file.
                fs::remove(sfile);
                //fs::remove(vs[i]);
            }
            // LOG_INFO(LOG_MT_PREFIX <<"End local combination.");
        }
        LOG_DEBUG(LOG_MT_PREFIX <<"Map completed.");
        exit(0); 
    } catch (exception &ex) {
        LOG_ERROR(LOG_MT_PREFIX <<"Catch " <<ex.what() <<endl)
            exit(-1);
    } catch (...) {
        LOG_ERROR(LOG_MT_PREFIX <<"Catch unknown exception")
            exit(-1);
    }
}

void MapTask::run() {
    string path;

    // Prepare source file.
    bool flag = getFile(m_command, path);
    if (!flag) {
        LOG_ERROR(LOG_MT_PREFIX <<"Can not get map file, abandon task.");
        if (m_worker != NULL)
            m_worker->abandonTask(m_command.jobId, m_command.taskId);
        return;
    }

    if (m_command.doLocalCombine) {
        LOG_DEBUG(LOG_MT_PREFIX <<"Will do local combination.");
    }

    int nretry = 0;
    int nsec;
    // Begin map.
    for (int round = 0; round < nretry + 1; ++round) {
        nsec = 0;
        if (fs::exists(m_taskDir)) {
            fs::remove_all(m_taskDir);
            LOG_DEBUG("Remove existed directory " <<m_taskDir);
        }

        fs::create_directory(fs::path(m_taskDir));

        if(!fs::is_directory(fs::path(m_taskDir))){
            LOG_ERROR(LOG_MT_PREFIX <<"create_directory " <<m_taskDir <<" error.");
            IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
            continue;
        }

        int pid = fork();
        int r, exitcode;
        if (pid == 0) {
            // child process

            string confString;
            m_conf.writeToString(confString);

            //char pathBuffer[512];
            //char* currentPath = getcwd(pathBuffer, 512);
            //string execFileName = string(currentPath)  + "/bin/mapred_mapper";
            
            string execFileName = m_worker->getHomeDir() + "/mapred_mapper";
            string logFileName = m_taskDir + "/../" + boost::lexical_cast<string>(m_command.jobId);

            LOG_INFO(LOG_MT_PREFIX <<"Exec maptask as :" << execFileName);
            LOG_INFO(LOG_MT_PREFIX <<"Exec maptask dataFile as :" << path);
            LOG_INFO(LOG_MT_PREFIX <<"Exec maptask taskDir as :" << m_taskDir);
            LOG_INFO(LOG_MT_PREFIX <<"Exec maptask confString as :" << confString);
            LOG_INFO(LOG_MT_PREFIX <<"Exec maptask reduceNum as :" << m_command.reduceTaskNum << " localCombine as" <<
                    m_command.doLocalCombine);
            
            //test fork-safety for PageLen test
            int ret = execl(execFileName.c_str(), execFileName.c_str(),
                path.c_str(),m_taskDir.c_str(),confString.c_str(),
                (boost::lexical_cast<string>(m_command.reduceTaskNum)).c_str(),
                (m_command.doLocalCombine?"1":"0"),
                logFileName.c_str(),
                NULL);

            if(ret == -1){
                perror("MapRed-MapTask");
            }
            return;
        }else if(pid < 0){
            LOG_ERROR(LOG_MT_PREFIX <<"Fork " <<m_command.taskId <<" error.");
            IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
            continue;
        } else {
            while (true) {
                // check process status
                if ((r = waitpid(pid, &exitcode, WNOHANG)) < 0) {
                    LOG_ERROR(LOG_MT_PREFIX <<"Wait " <<m_command.taskId <<" error.");
                    kill(pid, 9);
                    waitpid(pid, NULL, 0);
                    break;
                } else if (r > 0) {
                    //cerr <<WIFEXITED(exitcode) <<" " <<WEXITSTATUS(exitcode) <<endl;
                    if (WIFEXITED(exitcode) && (WEXITSTATUS(exitcode) == 0)) {
                        LOG_DEBUG(LOG_MT_PREFIX <<"Map return OK in approximate " <<nsec <<" seconds.");
                        // Remove chunk file
                        if (path.substr(path.length() - 3, 3) == "tmp") {
                            LOG_DEBUG(LOG_MT_PREFIX <<"Remove temparory chunk file " <<path);
                            fs::remove(path);
                        }
                        if (m_worker != NULL)
                            m_worker->completeTask(m_command.jobId, m_command.taskId);
                        return;
                    } else {
                        if (!WIFEXITED(exitcode)) {
                            LOG_ERROR(LOG_MT_PREFIX <<"Map process exited abnormally.")
                        } else {
                            LOG_ERROR(LOG_MT_PREFIX <<"Map return error code " 
                                    <<WEXITSTATUS(exitcode));
                        }
                    }
                    break;
                }

                // check whether this task is abandoned
                if (m_worker->killed(m_command.taskId)) {
                    LOG_INFO(LOG_MT_PREFIX <<"Job cancelled, abandon task.");
                    kill(pid, 9);
                    waitpid(pid, NULL, 0);
                    if (m_worker != NULL)
                        m_worker->abandonTask(m_command.jobId, m_command.taskId);
                    return;
                }
                //sleep(1);
                IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(1));
                ++ nsec;

                if (nsec % 60 == 0) {
                    LOG_DEBUG(LOG_MT_PREFIX <<"Map wait reach " <<nsec / 60 << " minutes for pid=" << pid << " taskDir=" << m_taskDir);
                }
                if (nsec > 20 * 60) {
                    LOG_WARN(LOG_MT_PREFIX <<"Map wait exceed 20 minutes, terminated.");
                    kill(pid, 9);
                    waitpid(pid, NULL, 0);
                    break;
                }
            }
        }
    }
    LOG_INFO(LOG_MT_PREFIX <<"Abandon task after " <<nretry <<" retries.");
    if (m_worker != NULL)
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
}
