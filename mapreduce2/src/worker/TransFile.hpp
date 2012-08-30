/**
 * @file    TransFile.hpp
 *  Transfer a specified intermediate file.
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/10/2007 01:58:54 PM CST
 *
 */

#ifndef  TRANSFILE_FILE_HEADER_INC
#define  TRANSFILE_FILE_HEADER_INC

#include <IceUtil/Thread.h>
#include <string>

namespace mapreduce {

class TransFile: public IceUtil::Thread {
    public:
        TransFile(const std::string file, int socketfd);
        void run();
        int writen(int sockfd, char *p, int n);

    private:
        std::string m_filename;
        int m_socketfd;
};  // class TransFile

}   // namespace mapreduce

#endif   /* ----- #ifndef TRANSFILE_FILE_HEADER_INC  ----- */

