/**
 * @file	tfsTerminal.cpp
 * the terminal of tfs file system, the tfs shell will be executed in this program;	
 * 
 * @author	Chen rishan, Peking University	
 * @date	08/03/2007 
 *
 */

#include "CommandManager.hpp"
#include "CommandExecuter.hpp"
#include "InputAccessor.hpp"
#include <iostream>
#include <cstdio>
#include <string>

using namespace tfs::api;
using namespace std;
using namespace terminal;

const size_t replication = 3;
const size_t chunkSize = 64 * 1024 * 1024;

void welcome()
{
    fprintf(stderr, "-----------------Welcome to tianwang filesystem-------------\n");
}

int main() {
  try{
    //welcome();
    string command;
    string parameter;
    bool result = false;
    int action = 0;
    CommandManager manager;
    CommandExecuter executer("/");
    InputAccessor input;
    char prompt[256];    

    while(1){
      sprintf(prompt, "tfs_shell:%s> ", executer.getCurrentDir().c_str() );
      command = input.getInput(prompt);
      action = manager.commandDepart(command, parameter);
      result = executer.execute(action,parameter);
      if(!result){
          fprintf(stderr, "Command '%s' failed\n", command.c_str());
      }
      if(executer.isQuit()){
          break;
      }
    }

  }catch(tfs::api::TFSException &ex){
    cerr << "tfs_shell terminated: ";
    cerr << ex.what() << endl;
  }
  return 0;
}
