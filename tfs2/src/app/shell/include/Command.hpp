/**
 * @file	Command.hpp
 * the base command
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMAND_HPP
#define TERMINAL_COMMAND_HPP 1

#include<string>

class tfs::api::FileSystem;

namespace terminal{


class Command
{
public:
    
    /**
     * Constructor
     * @param
     * @throws
     */
    Command(){};

    Command(std::string currentDir){m_currentDir = currentDir;}
    
    virtual ~Command(){};
    
    /**
     * the execution 
     * @param [in] filepath
     * @param [in] filesystem
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter) = 0;

    /**
     * get the current directory
     * @param [in] 
     * @throws
     * @return: current directory
     */
    std::string getCurrent(){return m_currentDir;}
    
    /**
     * set the current directory
     * @param [in] filepath
     * @throws
     * @return: 
     */
    void setCurrent(std::string currentDir){m_currentDir = currentDir;}

protected:
    std::string m_currentDir;
};

}


#endif
