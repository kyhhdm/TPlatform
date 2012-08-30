/**
 * @file	TransTask.cpp
 * 	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/08/2007 06:17:08 PM CST
 *
 */

#include "TransTask.hpp"
#include "Worker.hpp"
#include <boost/lexical_cast.hpp>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/filesystem.hpp>
#include <ctime>

using namespace mapreduce;
using namespace std;
namespace fs = boost::filesystem;

#define LOG_TT_PREFIX "TransTask(" <<m_command.jobId <<"#" <<m_command.taskId <<"): "

TransTask::TransTask(const MasterCommand &mc, const std::string &jobDir, 
                     Worker *worker) {
    m_command = mc;
    m_jobDir = jobDir;
    m_worker = worker;
}

int TransTask::readn(int sockfd, char *p, int n) {
    int nleft = n;
    int nread;
    while (nleft > 0) {
        if ((nread = read(sockfd, p, nleft)) < 0) {
            if (errno == EINTR) {
                LOG_ERROR(LOG_TT_PREFIX <<"Read socket error, errno = EINTR, continue.");
                nread = 0;
            } else {
                LOG_ERROR(LOG_TT_PREFIX <<"Read socket error, errno = " <<errno);
                return -1;
            }
        } else if (nread == 0) {
            //LOG_ERROR(LOG_TT_PREFIX <<"Read socket error, EOF reached.");
            break;
        }
        nleft -= nread;
        p += nread;
    }
    return n - nleft;
}

void TransTask::run() {
    if (m_worker == NULL) return;
    clock_t t = clock();

    // Local file
    if (m_command.transMapWorker == m_worker->address()) {
        string file = m_jobDir + "/" 
                + boost::lexical_cast<string>(m_command.transMapTaskId)
                + "/" + boost::lexical_cast<string>(m_command.partition);
        if (fs::exists(file + "_combined"))
            file += "_combined";
        LOG_INFO(LOG_TT_PREFIX <<"Add local file " + file);
        m_worker->addMappedFile(m_command.jobId, m_command.partition, file);
        m_worker->completeTask(m_command.jobId, m_command.taskId);
        return;
    }

    // Remote file.
    string taskDir = m_jobDir + "/" + boost::lexical_cast<string>(m_command.partition);
    if (!fs::exists(taskDir)) {
        fs::create_directory(taskDir);
        if(!fs::is_directory(taskDir)){
            LOG_ERROR(LOG_TT_PREFIX <<"create_directory " << taskDir <<" error.");
            //IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));
            m_worker->abandonTask(m_command.jobId, m_command.taskId);
            return;
        }

        LOG_DEBUG(LOG_TT_PREFIX <<taskDir <<" created.");
    }
    string outfile = taskDir + "/" 
        + boost::lexical_cast<string>(m_command.transMapTaskId) + "_"
        + m_command.transMapWorker.name + ":"
        + boost::lexical_cast<string>(m_command.transMapWorker.port);
    LOG_DEBUG(LOG_TT_PREFIX <<"Try to get " <<outfile <<" from " 
              <<m_command.transMapWorker.name 
              <<":" <<m_command.transMapWorker.port);


    // Connect transfer server.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        LOG_ERROR(LOG_TT_PREFIX <<"Get socket error, errno = " <<errno);
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        return;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(short(m_command.transMapWorker.port));
    inet_pton(AF_INET, m_command.transMapWorker.name.c_str(), &addr.sin_addr);

    //LOG_DEBUG(LOG_TT_PREFIX <<"Connecting ..."); 
    if (connect(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        LOG_ERROR(LOG_TT_PREFIX <<"Connect transfer server error, errno = " <<errno);
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        close(sockfd);
        return;
    }
    //LOG_DEBUG(LOG_TT_PREFIX <<"Connect over."); 

    // Specify the file to be transferred.
    if (write(sockfd, &m_command.jobId, sizeof(int)) < sizeof(int) 
           || write(sockfd, &m_command.transMapTaskId, sizeof(int)) < sizeof(int)
           || write(sockfd, &m_command.partition, sizeof(int)) < sizeof(int)) {
        LOG_ERROR(LOG_TT_PREFIX <<"Write file info error, errno = " <<errno);
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        close(sockfd);
        return;
    }
    //LOG_DEBUG(LOG_TT_PREFIX <<"Write file info over");

    char tmp[1024*1024];
    ofstream fout(outfile.c_str(), ios::binary);
    if (!fout.is_open()) {
        LOG_ERROR(LOG_TT_PREFIX <<"Can not open " + outfile + " for write.");
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        close(sockfd);
        return;
    }

    // Get file.
    int size = -1, n = 0, m;
    //LOG_DEBUG(LOG_TT_PREFIX <<"Try to get file size.");
    if (readn(sockfd, (char *)&size, sizeof(int)) < sizeof(int)) {
        LOG_ERROR(LOG_TT_PREFIX <<"Can not read file size.");
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        close(sockfd);
        return;
    }
    //LOG_DEBUG(LOG_TT_PREFIX <<"Get file size " <<size);

    if (size == -1) {
        LOG_ERROR(LOG_TT_PREFIX <<"Destination file is not available.");
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
        close(sockfd);
        return;
    }

    while ((m = readn(sockfd, tmp, 1024*1024)) > 0) {
        n += m;
        fout.write(tmp, m);
    } 
    //LOG_DEBUG(LOG_TT_PREFIX <<"Transfer over.");

    if (n == size) {
        LOG_INFO(LOG_TT_PREFIX <<"Get " <<n <<" bytes for " <<outfile <<" in " 
                <<(clock() - t) / CLOCKS_PER_SEC <<" seconds.");
        m_worker->addMappedFile(m_command.jobId, m_command.partition, outfile);
        m_worker->completeTask(m_command.jobId, m_command.taskId);
    } else {
        LOG_ERROR(LOG_TT_PREFIX <<"Get " <<n <<" bytes for " <<outfile 
                  <<" and expect " <<size <<" bytes"); 
        m_worker->abandonTask(m_command.jobId, m_command.taskId);
    }
    close(sockfd);
}
