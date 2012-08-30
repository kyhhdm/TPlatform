/**
 * @file	CommandRm.hpp
 * the remove directory command	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/05/2007 
 *
 */

#ifndef TERMINAL_COMMANDRM_HPP
#define TERMINAL_COMMANDRM_HPP 1

#include <string>
#include "app/shell/include/Command.hpp"

class tfs::api::FileSystem;

namespace terminal{


class CommandRm : public Command
{
public:
        
    /**
     * remove the current working directory 
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);
    
    /**
     * remove the file
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    bool removeFile(tfs::api::FileSystem& fs, std::string filePath);
    
    /**
     * remove the whole directory, include the subdirectories
     * @param [in] filepath
     * @throws
     * @return: the result of the command execution
     */
    bool removeDirectory(tfs::api::FileSystem& fs, std::string directoryPath);

};

}


#endif
