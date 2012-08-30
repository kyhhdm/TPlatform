/**
 * @file	CommandMkdir.hpp
 * the making directory command	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMANDMKDIR_HPP
#define TERMINAL_COMMANDMKDIR_HPP 1

#include <string>
#include "Command.hpp"

namespace terminal{


class CommandMkdir : public Command
{
public:
    
    /**
     * make new directory
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);

};

}


#endif
