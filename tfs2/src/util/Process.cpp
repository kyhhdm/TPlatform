/**
 * @file Process.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-25
 */

#include "util/Process.hpp"
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
using namespace tfs;

Process::~Process()
{
    if (m_pid != 0){
        ::kill(m_pid, SIGKILL);
    }
}

bool Process::run(RunnableFunc func){
    m_pid = fork();
    if (m_pid == 0){
        // child
        exit(func());
    }
    else if (m_pid == -1){
        // error
        cerr << "Error: Process::run() create proccess" << endl;
        return false;
    }
    else{
        // parent
        return true;
    }
}

bool Process::wait(int &status){
    if (m_pid != 0){
        waitpid(m_pid, &status, 0);
        if (WIFEXITED(status)){
            status = WEXITSTATUS(status);
        }
        else{
            cerr << "Error: Process::wait() child process terminated innormally" << endl;
            return false;
        }
        
    }
    m_pid = 0;
    return true;
}

bool Process::kill(){
    if (m_pid != 0){
        ::kill(m_pid, SIGKILL);
    }
    cout << "killed a process" << endl;
    return true;
}
