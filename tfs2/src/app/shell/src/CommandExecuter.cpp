/**
 * @file	CommandExecuter.cpp
 * implementation of CommandExecuter.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/02/2007 
 *
 */

#include <string>
#include <iostream>
#include <cstdio>
#include "app/shell/include/CommandExecuter.hpp"

using namespace std;
using namespace terminal;

CommandExecuter::CommandExecuter()
{
    m_quit = false;
}

CommandExecuter::CommandExecuter(string current)
{
    m_currentDir = current;
    m_quit = false;
}

CommandExecuter::~CommandExecuter()
{
}

bool CommandExecuter::execute(int action, string parameter)
{
    bool result = false;
    switch(action){
    case 1:
    {//"ls":
        m_lister.setCurrent(m_currentDir);
        result = m_lister.exe(m_fs, parameter);
        break;
    }
    case 2:
    {//"mkdir":
        m_maker.setCurrent(m_currentDir);
        result = m_maker.exe(m_fs, parameter);
        break;
    }
    case 3:
    {//"rm"://TODO parameter -rf: remove all the dir
        m_remover.setCurrent(m_currentDir);
        result = m_remover.exe(m_fs, parameter);
        break;
    }
    case 4:
    {//"cd":
        m_changer.setCurrent(m_currentDir);
        if(m_changer.exe(m_fs, parameter) ){
            m_currentDir = m_changer.getCurrent();
            result = true;
        }    
        break;
    }
    /*
      case 5://"mv":
      //TODO the meaning of mv?
      break;
    */
    case 6:
    {//"pwd":
        fprintf(stderr, "%s\n", m_currentDir.c_str() );
        result = true;
        break;
    }
    case 7:
    {//"put":
        m_putter.setCurrent(m_currentDir);
        result = m_putter.exe(m_fs, parameter);
        break;
    }
    case 8:
    {//"get":
        m_geter.setCurrent(m_currentDir);
        result = m_geter.exe(m_fs, parameter);
        break;
    }
    case 9:
    {//"quit":
        result = true;
        m_quit = true;
        break;
    }
    case 12://"rename":
    {
        m_rename.setCurrent(m_currentDir);
        result = m_rename.exe(m_fs, parameter);
        break;
    }
    case 10:
    {//"help":
        cout << "\tls" << endl;
        cout << "\tpwd" << endl;
        cout << "\tcd <tfs_dir>" << endl;
        cout << "\tmkdir <tfs_dir>" << endl;
        cout << "\trm <tfs_file>" << endl;
        cout << "\trm -rf <tfs_dir>" << endl;
        cout << "\tput <local_file> [<tfs_file> [<blocksize>]]" << endl;
        cout << "\tget <tfs_file> [<local_file>]" << endl;
        cout << "\trename <src_file> <dest_file>" << endl;
        cout << "\tquit" << endl;
        cout << "\t!<system_command>" << endl;
        result = true;
        break;
    }
    case 11:
    {//"!systemcommand"
        //cout << "system shell command: " << parameter << endl;
        system(parameter.c_str());
        result = true;
        break;
    }
    default:
        cout << "ERROR: Unknown command" << endl;
    };
    return result;
}

string CommandExecuter::getCurrentDir()
{
    return m_currentDir;
}

bool CommandExecuter::isQuit()
{
    return m_quit;
}
