/**
 * @file	CommandExecuter.hpp
 * it charges for the executing of commands	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#ifndef TERMINAL_COMMANDEXECUTER_HPP
#define TERMINAL_COMMANDEXECUTER_HPP 1

#include <string>
#include "tfs/tfs.h"
#include "CommandLs.hpp"
#include "CommandMkdir.hpp"
#include "CommandCd.hpp"
#include "CommandGet.hpp"
#include "CommandPut.hpp"
#include "CommandRm.hpp"
#include "CommandRename.hpp"
class tfs::api::FileSystem;

namespace terminal{

class CommandExecuter
{
public:
    
    /**
     * default Constructor
     * @param
     * @throws
     */
    CommandExecuter();
    
    /**
     * Constructor
     * @param [in] current directory
     * @throws
     */
    CommandExecuter(std::string current);

    ~CommandExecuter();
    
    /**
     * execute the command in different actions
     * @param [in] action parameter
     * @throws
     * @return: the result of execution
     * 
     */
    bool execute(int action, std::string parameter);
    
    /**
     * get the current directory
     * @param [in] 
     * @throws
     * @return: current directory
     */
    std::string getCurrentDir();

    /**
     * to test whether quit
     * @param [in] 
     * @throws
     * @return:  
     */
    bool isQuit();

private:
    tfs::api::FileSystem m_fs;
    std::string m_currentDir;
    CommandLs m_lister;
    CommandMkdir m_maker;
    CommandCd m_changer;
    CommandGet m_geter;
    CommandPut m_putter;
    CommandRm m_remover;
    CommandRename m_rename;
    bool m_quit;
};

}

#endif
