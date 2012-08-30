

#ifndef _CHUNKSERVER_HEADER_HPP
#define _CHUNKSERVER_HEADER_HPP

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loglevel.h>
#include "Transfer.h"

using namespace log4cplus;

namespace tfs
{
    typedef ::Ice::Long Long;
    typedef ::Ice::Int Int;
    typedef ::Ice::Byte Byte;
    typedef ::Ice::Short Short;
    typedef ::Ice::Float Float;
    typedef ::Ice::Double Double;


    using tfs::slice::Transfer;
    using tfs::slice::ErrorBase;
    using tfs::slice::DataError;
    using tfs::slice::ChunkError;
    using tfs::slice::ChunkNotExist;
    using tfs::slice::ByteSeq;


#define LOG_DEBUG(x)    LOG4CPLUS_DEBUG(Logger::getInstance("chunkserver"), x)
#define LOG_INFO(x)     LOG4CPLUS_INFO(Logger::getInstance("chunkserver"), x)
#define LOG_WARN(x)     LOG4CPLUS_WARN(Logger::getInstance("chunkserver"), x)
#define LOG_ERROR(x)    LOG4CPLUS_ERROR(Logger::getInstance("chunkserver"), x)
#define LOG_FATAL(x)    LOG4CPLUS_FATAL(Logger::getInstance("chunkserver"), x)
                      
}

#endif
