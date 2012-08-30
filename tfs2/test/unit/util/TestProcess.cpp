/**
 * @file TestProcess.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-25
 */

#include "util/Process.hpp"
#include "util/Runnable.hpp"

#include <iostream>
using namespace std;

int func()
{
    while(true){
        cout << "haha" << endl;
        sleep (2);
    }
    return 0;
}

int main()
{
    tfs::Runnable *thread = new tfs::Process();

    if (!thread->run(func)){
        cout << "Error: thread run" << endl;
    }
    sleep(10);
    
    if (!thread->kill()){
        cout << "Error: thread wait" << endl;
    }
    delete thread;
    
    return 0;
}


