/** 
 * @file Statistics.hpp
 * This class records the system statistics when system running.
 * 
 * @author Zhifeng YANG
 * @date 2007-09-01
 */
#ifndef _STATISTICS_HPP
#define _STATISTICS_HPP 1
#include <ctime>
namespace tfs{
    enum ClientServiceOperation{
        OP_OPEN = 0,
        OP_CLOSE,
        OP_GET_CHUNKS_INFO,
        OP_ADD_CHUNK,
        OP_COMPLETE_WRITTEN_CHUNK,
        OP_ABANDON_ADD_CHUNK,
        OP_REPORT_BAD_CHUNKS,
        OP_SET_REPLICATION,
        OP_GET_FILE_INFO,
        OP_CREATE,
        OP_MKDIR,
        OP_RENAME,
        OP_RENAME_DIR,
        OP_REMOVE,
        OP_RMDIR,
        OP_LSDIR,
        OP_CONCAT,
        OP_UPDATE_CHUNK_INFO,
        OP_SIZE
    };
    
    class Statistics
    {
    public:
        Statistics();
        int m_operationsCount[OP_SIZE];
        time_t m_startTime;
    };

    inline Statistics::Statistics()
    {
        memset(m_operationsCount, 0, sizeof(int)*OP_SIZE);
    }
    
}


#endif /* _STATISTICS_HPP */
