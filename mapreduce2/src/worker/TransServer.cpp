/**
 * @file	TransServer.cpp
 *  Implementation of TransServer class.
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/08/2007 06:30:49 PM CST
 *
 */

#include "TransServer.hpp"
#include "TransFile.hpp"
#include "Worker.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <errno.h>

namespace mapreduce {

using namespace std;
namespace fs = boost::filesystem;

void TransServer::run() {
	struct sockaddr_in conn_addr, serv_addr;
    char addr_str[100];
    string jobstr, name;
    int jobId, port, listenfd, partition, taskId;
    socklen_t len;

    // Apply and listen to a special port
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        LOG_ERROR("TransServer: Get tcp port failed, errno = " <<errno);
        exit(1);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(m_port);

    if (bind(listenfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        LOG_ERROR("TransServer: Bind tcp port failed, errno = " <<errno);
        exit(1);
    }

    if (listen(listenfd, m_port)) {
        LOG_ERROR("TransServer: Listen tcp port failed, errno = " <<errno);
        exit(1);
    } else {
        LOG_INFO("TransServer: Listen to port " + boost::lexical_cast<string>(m_port));
    }

    for (;;) {
        len = sizeof(conn_addr);
        // Accept connection.
		int connfd = accept(listenfd, (sockaddr*)&conn_addr, &len);
        if (connfd < 0) {
            LOG_ERROR("TransServer: Accept connection error, errno = " <<errno);
            continue;
        }
        inet_ntop(AF_INET, &conn_addr.sin_addr, addr_str, sizeof(addr_str));
        port = (int)ntohs(conn_addr.sin_port);
        LOG_INFO("TransServer: Accept connection from " <<addr_str <<":" <<port);

        // Get file name and transfer file.
        read(connfd, &jobId, sizeof(jobId));
        read(connfd, &taskId, sizeof(taskId));
        read(connfd, &partition, sizeof(partition));
        name = m_storeDir + boost::lexical_cast<string>(jobId) + "/" 
            + boost::lexical_cast<string>(taskId) + "/" 
            + boost::lexical_cast<string>(partition);
        if (fs::exists(name + "_combined"))
            name += "_combined";
        LOG_INFO("TransServer: Transfer " <<name <<" to " <<addr_str 
                <<":" <<port <<" sockfd = " <<connfd);
        IceUtil::ThreadPtr tf = new TransFile(name, connfd);
        tf->start().detach();
    }
}

}   // namespace mapreduce
