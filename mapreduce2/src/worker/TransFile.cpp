/**
 * @file	TransFile.cpp
 * 	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/10/2007 02:00:22 PM CST
 *
 */

#include "Worker.hpp"
#include "TransFile.hpp"
#include <fstream>
#include <ctime>
using namespace std;

namespace mapreduce {

#define LOG_TF_PREFIX "TransFile(" <<m_socketfd <<"): "

TransFile::TransFile(const string file, int socketfd) {
    m_filename = file;
    m_socketfd = socketfd;
}

int TransFile::writen(int sockfd, char *p, int n) {
    int nleft = n, nwritten;
    while (nleft > 0) {
        if ((nwritten = write(sockfd, p, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR) {
                LOG_ERROR(LOG_TF_PREFIX <<"Write socket error, errno = EINTR, continue.");
                nwritten = 0;
            } else {
                LOG_ERROR(LOG_TF_PREFIX <<"Write socket error, errno = EINTR, continue.");
                return -1;
            }
        }
        nleft -= nwritten;
        p += nwritten;
    }
    return n;
}

void TransFile::run() {
    clock_t t = clock();
    int n = 0;
    char tmp[1024*1024];
    int size;
    ifstream fin(m_filename.c_str(), ios::binary);
    if (!fin.is_open()) {
        LOG_ERROR(LOG_TF_PREFIX <<"Can not open " << m_filename);
        size = -1;
        writen(m_socketfd, (char *)&size, sizeof(int));
        close(m_socketfd);
        return;
    }

    fin.seekg(0, ios::end);
    size = fin.tellg();
    //LOG_DEBUG(LOG_TF_PREFIX <<"Will transfer " <<size <<" bytes for " <<m_filename);
    if (writen(m_socketfd, (char *)&size, sizeof(int)) != sizeof(int)) {
        LOG_ERROR(LOG_TF_PREFIX <<"Write file size error.");
        close(m_socketfd);
        return;
    }
    fin.seekg(0, ios::beg);
    while(fin.read(tmp, 1024*1024), fin.gcount() > 0) {
        if (writen(m_socketfd, tmp, fin.gcount()) != fin.gcount() ) {
            LOG_ERROR(LOG_TF_PREFIX <<"Write file " <<m_filename <<" error.");
            close(m_socketfd);
            return;
        }
        n += fin.gcount();
    }
    close(m_socketfd);
    fin.close();
    LOG_INFO(LOG_TF_PREFIX <<"Transfer " <<n <<" bytes for " <<m_filename <<" in " 
            <<(clock() - t) / CLOCKS_PER_SEC <<" seconds.");
}

}   // namespace mapreduce
