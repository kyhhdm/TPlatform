/**
 * @file	CommandGet.hpp
 * the command to get the tfsfile from the system
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/03/2007 
 *
 */

#ifndef TERMINAL_COMMANDGET_HPP
#define TERMINAL_COMMANDGET_HPP 1

#include <string>
#include "Command.hpp"

class tfs::api::FileSystem;

namespace terminal{

class CommandGet : public Command
{
public:
    
    
    /**
     * change the current working directory 
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);

    /**
     * Get a whole directory recursively
     */
   bool getDir(std::string tfsPath, std::string localPath); 

    /**
     * Get a whole directory recursively
     */
   bool getFile(std::string tfsPath, std::string localPath); 
};

}


#endif
