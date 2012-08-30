/**
 * @file	CommandManager.cpp
 * it manages the commands input to the terminal	
 * 
 * @author	Chen rishan, Peking University	
 * @date	09/29/2007 
 *
 */

#include <string>
#include <sstream>
#include <iostream>
#include "CommandManager.hpp"

using namespace std;
using namespace terminal;

CommandManager::CommandManager()
{
    m_iter = m_table.begin();
}

CommandManager::~CommandManager()
{
}

void CommandManager::insert(std::string command)
{
    m_table.push_back(command);
    for(std::vector<std::string>::iterator iter = m_table.begin(); iter != m_table.end(); iter ++){
        if(iter + 1 == m_table.end() )
            m_iter = iter;
    }
}

std::string CommandManager::back()
{
    string result;
    if(m_iter == m_table.end() ){
        return result;
    }
    if(m_iter == m_table.begin() )
        return *m_iter;
    result = *m_iter;
    m_iter --;
    return result;
}

std::string CommandManager::forward()
{
    string empty;
    if(m_iter == m_table.end() ){
        return empty;
    }
    m_iter ++;
    if(m_iter != m_table.end() ){
        return *m_iter;
    }
    return empty;
}

int CommandManager::commandDepart(std::string command, string& parameter)
{
    int action = 0;    
    istringstream input(command);
    string actionString;
    input >> actionString;
    int command_len = command.length();
    int action_begin;
    if(actionString != ""){
        action_begin = command.find(actionString);
    }
    else{
        action_begin = command_len - 1;
    }
    int action_len = actionString.length();
    int action_end = action_begin + action_len;
    int parameter_len = command_len - action_end;
    //**BUGFIX**
    //think about the situation that:
    //command is "  mkdir test"
    //so the actionString is "mkdir"
    //and the parameter should be " test"
    
    //to depart the command: depart into action and its parameter
    if(action_len != 0){
        parameter = command.substr(action_end, parameter_len);
    }
    else{
        action = 0;
        return action;
    }
    if(actionString == "ls")
        action = 1;
    else if(actionString == "cd")
        action = 4;
    else if(actionString == "mkdir")
        action = 2;
    else if(actionString == "rm")
        action = 3;
    else if(actionString == "mv")
        action = 5;
    else if(actionString == "pwd")
        action = 6;
    else if(actionString == "put")
        action = 7;
    else if(actionString == "get")
        action = 8;
    else if(actionString == "rename")
        action = 12;
    else if(actionString == "quit"|| actionString == "q" || actionString == "exit" || actionString == "bye")
        action = 9;
    else if(actionString == "help")
        action = 10;
    else if(actionString.size()>0 && actionString[0] == '!'){    
        action = 11;
        parameter = command.substr(1);
    }
    else{                       // else show help
        cout << "tfs_shell: " << actionString << " :not found" << endl;
        action = 10;
    }
    
    return action;
}

