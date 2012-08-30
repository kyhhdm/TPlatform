/**
 * @file	CommandManager.hpp
 * it manages the commands input to the terminal	
 * 
 * @author	Chen rishan, Peking University	
 * @date	09/29/2007 
 *
 */

#ifndef TERMINAL_COMMANDMANAGER_HPP
#define TERMINAL_COMMANDMANAGER_HPP 1

#include<string>
#include<vector>

namespace terminal{

class CommandManager
{
public:
    /**
     * Constructor
     * @param
     * @throws
     */
    CommandManager();

    ~CommandManager();
    
    /**
     * Add new command
     * @param [in] command
     * @throws
     * @return:
     */
    void insert(std::string command);
    
    /**
     * get command that input before current command in screen
     * @param [in]
     * @throws
     * @return:
     */
    std::string back();
    
    /**
     * get command that input after current command
     * @param [in]
     * @throws
     * @return:
     */
    std::string forward();
    
    /**
     * depart command into actions
     * @param [in] filename, command
     * @throws
     * @return:the encoding of actions , and absolutely path of file
     */
    int commandDepart(std::string command, std::string& parameter);

private:
    std::vector<std::string> m_table;
    std::vector<std::string>::iterator m_iter;
};

}

#endif
