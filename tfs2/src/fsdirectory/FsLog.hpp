/** @file FsLog.hpp
 * FsLog is journal log file class.
 * Journal log file records all metadata mutation operations on FsDirectory interface,
 * it provides serialization of basic data types occurs in the parameters.
 *
 * Design Notes: <br>
 *      1.> #DEPRECATED# 
 *          use low level file i/o calls instead of any stream file i/o
 *          for performance and full controlbility.
 *          #DEPRECATED# it's difficult for buffer management
 *      2.> Now use iostream instead
 *      3.> This is a intruding serialization method, all object's data member must be accessable.
 *          Simple but not a very good OO design, especially needs more maintenances when object changes.
 */
#ifndef _TFSMASTER_FSLOG_HPP
#define _TFSMASTER_FSLOG_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include "fsdirectory/MasterConfig.hpp"
#include <fstream>
#include <assert.h>

namespace tfs {

    class FsLog {

    public:
        static const int MaxLogStringSize;
        static const char* LogFileNamePrefix;

        enum OpenFsLogType{
            CreateNewMode,
            AppendMode
        };

        /** Default constructor.
         */    
        FsLog();

        /** Construct from log file.
         * @param [in] logFileNames : 
         */    
        FsLog(const std::string& logFileName, OpenFsLogType openType = AppendMode);
            
        ~FsLog();

        /** accessors 
         */
        std::ofstream& getOutputStream();
        std::ifstream& getInputStream();

        /** Check if there are more log records unread.
         * 
         */    
        bool hasMore();

        /** Flush and fsync log data into I/O device for permanent storage.
         * 
         */    
        void flush();

        /** Serialization interface
         * 
         */
        FsLog& operator << (int value);
        FsLog& operator << (Short value);
        FsLog& operator << (Long value);
        FsLog& operator << (const std::string& strValue);
        FsLog& operator << (const Chunk& chunk);
        FsLog& operator << (const FileInfo& info);

        FsLog& operator >> (int& value);
        FsLog& operator >> (Short& value);
        FsLog& operator >> (Long& value);
        FsLog& operator >> (std::string& strValue);
        FsLog& operator >> (Chunk& chunk);
        FsLog& operator >> (FileInfo& info);

    private:
        /** File handles of backdoor files
         */    
        std::ofstream*     m_pLogOutput;
        std::ifstream*     m_pLogInput;
        
        char*   m_buffer;
    };

    //============inline implementations========================================
    inline std::ofstream& FsLog::getOutputStream() { return *m_pLogOutput; }
    inline std::ifstream& FsLog::getInputStream() { return *m_pLogInput; }
    inline bool FsLog::hasMore() { return !(m_pLogInput->eof() || m_pLogInput->fail());}

    inline void FsLog::flush() { m_pLogOutput->flush();}

    inline FsLog& FsLog::operator << (int value)
    {
        m_pLogOutput->write((const char*)&value , sizeof(int));
        return *this;
    }
    inline FsLog& FsLog::operator >> (int& value)
    {
        m_pLogInput->read((char*)&value , sizeof(int));
        return *this;
    }

    inline FsLog& FsLog::operator << (Short value)
    {
        m_pLogOutput->write((const char*)&value , sizeof(Short));
        return *this;
    }
    inline FsLog& FsLog::operator >> (Short& value)
    {
        m_pLogInput->read((char*)&value , sizeof(Short));
        return *this;
    }

    inline FsLog& FsLog::operator << (Long value)
    {
        m_pLogOutput->write((const char*)&value , sizeof(Long));
        return *this;
    }
    inline FsLog& FsLog::operator >> (Long& value)
    {
        m_pLogInput->read((char*)&value , sizeof(Long));
        return *this;
    }

    inline FsLog& FsLog::operator << (const std::string& strValue)
    {
        int len = strValue.length();
        m_pLogOutput->write((const char*)&len , sizeof(int));
        m_pLogOutput->write((const char*)strValue.c_str() , len);
        return *this;
    }
    inline FsLog& FsLog::operator >> (std::string& strValue)
    {
        int len;
        m_pLogInput->read((char*)&len , sizeof(int));
        
        assert(len < MaxLogStringSize);

        m_pLogInput->read((char*)m_buffer , len);
        m_buffer[len] = 0;
        strValue = std::string(m_buffer);

        return *this;
    }


    inline FsLog& FsLog::operator << (const Chunk& chunk)
    {
        m_pLogOutput->write((const char*)&chunk, sizeof(Chunk));
        return *this;
    }
    inline FsLog& FsLog::operator >> (Chunk& chunk)
    {
        m_pLogInput->read((char*)&chunk , sizeof(Chunk));
        return *this;
    }

    inline FsLog& FsLog::operator << (const FileInfo& info)
    {
        int len = info.name.length();
        m_pLogOutput->write((const char*)&len , sizeof(int));
        m_pLogOutput->write((const char*)info.name.c_str() , len);
        m_pLogOutput->write((const char*)&info.chunkSize, sizeof(info.chunkSize));
        m_pLogOutput->write((const char*)&info.createTime, sizeof(info.createTime));
        m_pLogOutput->write((const char*)&info.replication, sizeof(info.replication));
        m_pLogOutput->write((const char*)&info.size, sizeof(info.size));
        return *this;
    }
    inline FsLog& FsLog::operator >> (FileInfo& info)
    {
        int len;
        m_pLogInput->read((char*)&len , sizeof(int));

        assert(len < MaxLogStringSize);

        m_pLogInput->read((char*)m_buffer , len);
        m_buffer[len] = 0;
        info.name = std::string(m_buffer);

        m_pLogInput->read((char*)&info.chunkSize, sizeof(info.chunkSize));
        m_pLogInput->read((char*)&info.createTime, sizeof(info.createTime));
        m_pLogInput->read((char*)&info.replication, sizeof(info.replication));
        m_pLogInput->read((char*)&info.size, sizeof(info.size));

        return *this;

    }

}

#endif /* _TFSMASTER_FSLOG_HPP */
