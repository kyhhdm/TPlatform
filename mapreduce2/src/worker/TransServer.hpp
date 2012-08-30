/**
 * @file    TransServer.hpp
 *  Class TransServer. 
 * 
 * @author  Fan Kai(fk), Peking University
 * @date    12/08/2007 06:30:44 PM CST
 *
 */

#ifndef  TRANSSERVER_FILE_HEADER_INC
#define  TRANSSERVER_FILE_HEADER_INC

#include <IceUtil/Thread.h>

namespace mapreduce {

/// This class supply transfer service for intermediate files.
class TransServer: public IceUtil::Thread {
public:
    TransServer(short port, const std::string &dir) : m_port(port), m_storeDir(dir) {}

    void run();

private:
    short m_port;
    std::string m_storeDir;

};  // class TransServer

}   // namespace mapreduce

#endif   /* ----- #ifndef TRANSSERVER_FILE_HEADER_INC  ----- */

