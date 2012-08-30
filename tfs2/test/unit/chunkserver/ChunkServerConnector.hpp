

#ifndef _CHUNK_SERVER_CONNERTOR_HPP
#define _CHUNK_SERVER_CONNERTOR_HPP

#include <string>
#include <vector>

class ChunkServerConnector
{
public:
    ChunkServerConnector(const std::string & str_ip,int port);
    ~ChunkServerConnector();
    
};

#endif
