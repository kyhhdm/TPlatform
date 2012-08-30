/**
 * @file   Dealer.hpp
 * @author Tu Qichen <tqc@net.pku.edu.cn>
 * @date   Fri Dec  7 00:20:20 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef _TFS_DEALER_HPP
#define _TFS_DEALER_HPP

#include <string>
#include <ctime>

namespace tfs
{
    class Dealer
    {
    public:
        Dealer(){
            m_deal_flag = false;
        }
        virtual ~Dealer(){}

        void setAlive(){
            m_deal_flag = false;
        }
        void setDead(){
            m_deal_flag = true;
        }
        virtual bool isDead(){
            return m_deal_flag;
        }

        /** 
         * 设置线程名, not uniq
         * 
         * @param name 
         */
        void setName(const std::string & name)
        {
            m_name = name;
        }
        /** 
         * 得到线程名
         * 
         * 
         * @return 
         */
        std::string getName() const
        {
            return m_name;
        }
        /** 
         * 设置运行的开始时间
         * 
         */
        void setStartTime()
        {
            //            time_t now_time = time(NULL);
            m_start_time =  time(NULL);
        }

        /** 
         * 得到已经运行的时间
         * 
         * 
         * @return 
         */
        time_t getRunningTime()
        {
            time_t now_time = time(NULL);
            return now_time - m_start_time;
        }
        
    private:
        bool m_deal_flag;
        std::string m_name;
        time_t m_start_time;
    };
}

#endif

