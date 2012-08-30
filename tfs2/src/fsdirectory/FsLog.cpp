/** @file FsLog.cpp
 *
 * @author PengBo
 * @date 18 7 2007
 *
 */

#include "fsdirectory/FsLog.hpp"

using namespace std;
using namespace tfs;

const int FsLog::MaxLogStringSize = 8*1024;
const char* FsLog::LogFileNamePrefix = "log";

FsLog::FsLog()
{
    m_buffer = new char[MaxLogStringSize];
    m_pLogOutput = new ofstream(LogFileNamePrefix);
    m_pLogInput = new ifstream(LogFileNamePrefix);

}

FsLog::FsLog(const std::string& logFileName, OpenFsLogType openType)
{
    m_buffer = new char[MaxLogStringSize];
    std::ios_base::openmode mode = std::ios_base::app;

    if (openType == FsLog::CreateNewMode ) {
        mode = std::ios_base::trunc;
    }

    m_pLogOutput = new ofstream(logFileName.c_str(), mode);
    m_pLogInput = new ifstream(logFileName.c_str());
}

FsLog::~FsLog()
{
    delete[] m_buffer;
    delete m_pLogOutput;
    delete m_pLogInput;
}


