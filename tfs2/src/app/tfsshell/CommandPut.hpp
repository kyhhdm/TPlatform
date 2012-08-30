/**
 * @file	CommandPut.hpp
 * put local file to tfs system	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMANDPUT_HPP
#define TERMINAL_COMMANDPUT_HPP 1

#include <string>
#include "Command.hpp"

class tfs::api::FileSystem;

namespace terminal{


class CommandPut : public Command
{
public:
        
    /**
     * put the local file to tfs system 
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);

};

}


#endif
