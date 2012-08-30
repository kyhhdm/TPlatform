/**
 * @file   TaskMgr.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Tue Dec  4 21:50:24 2007
 * 
 * @brief  
 * 
 * 
 */


#ifndef TFS_TASK_MANAGER_HPP
#define TFS_TASK_MANAGER_HPP

#include "datatransfer/SocketMsg.hpp"
#include "Dealer.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include <ctime>
#include <map>
#include <vector>

namespace tfs
{

    enum TaskAction{ Idle_Task, Del_Chunk_Task, Transfer_Chunk_Task};
    enum DealerStatus{ Idle_Dealer,Read_Dealer, Write_Dealer, Append_Dealer, All_Dealer};
    
    class SysTask
    {
    public:
        TaskAction m_action;
        std::vector<int64_t> m_chunks;
        std::vector<ChunkServerAddr> m_chunkservers;
        //      std::vector<
    };
    
    class TaskMgr
    {
    public:
        static TaskMgr * getInstance();
        /** 
         * 添加一个系统维护任务,主要来自Master的命令
         * 
         * @param one_task 
         */
        void addSysTask(const SysTask & one_task);
        /** 
         * 得到一个任务
         * 
         * @param task 
         * 
         * @return 
         */
        bool getSysTask(SysTask & task);

        /** 
         * 添加一个正在运行的dealer,用于监控和系统管理
         * 
         * @param dealer_name
         */
        void addDealer(const std::string& dealer_name, const DealerStatus & status = Idle_Dealer);
        /** 
         * 删除的dealer
         * 
         * @param dealer_name
         * 
         * @return 
         */
        bool removeDealer(const std::string& dealer_name);

        /** 
         * 设置dealer的状态
         * 
         * @param dealer_name 
         * @param status 
         * 
         * @return 
         */
        bool setDealerStatus(const std::string& dealer_name,const DealerStatus & status);

        int getDealerNum(const DealerStatus & status = All_Dealer);

        /** 
         * 设置一个Chunk块的状态, 计数加1, 主要是Client使用
         * 
         * @param chunk_id 
         */
        void addBusyChunk(const int64_t& chunk_id);
        /** 
         * 判断一个chunk块是否有client引用
         * 
         * @param chunk_id 
         * 
         * @return 
         */
        bool isBusyChunk(const int64_t& chunk_id);

        /** 
         * 减少一个chunk的引用计数
         * 
         * @param chunk_id 
         * 
         * @return 
         */
        bool removeBusyChunk(const int64_t& chunk_id);
        
        
        ~TaskMgr();        
        
    private:
        static TaskMgr * m_pInstance;
        TaskMgr();


    private:
        std::queue<SysTask> m_task_queue;

        //        std::map<Dealer *,time_t> m_dealer_map;
        std::map<std::string,DealerStatus> m_dealer_map;

        std::map<int64_t,int> m_busy_chunk_map;
        
        boost::mutex m_task_mutex;
        boost::mutex m_dealer_mutex;
        boost::mutex m_busy_chunk_mutex;

        //        bool m_change_flag;
    };
}


#endif

