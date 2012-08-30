/**
 * @file	CommandCd.hpp
 * the change directory command	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMANDCD_HPP
#define TERMINAL_COMMANDCD_HPP 1

#include <string>
#include "Command.hpp"

class tfs::api::FileSystem;

namespace terminal{


class CommandCd : public Command
{
public:
        
    /**
     * change the current working directory 
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);

};

}


#endif
