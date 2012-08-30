/**
 * @file	CommandLs.hpp
 * the list directory command	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMANDLS_HPP
#define TERMINAL_COMMANDLS_HPP 1

#include <string>
#include "app/shell/include/Command.hpp"

namespace terminal{


class CommandLs : public Command
{
public:
    
    
    /**
     * list the directory
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);

};

}

#endif
