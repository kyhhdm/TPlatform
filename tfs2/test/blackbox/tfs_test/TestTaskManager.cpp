/**
 * @file TestTaskManager.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-09-21
 */

#include "TaskManager.hpp"
#include <iostream>
using namespace std;
using namespace tfs;

// define task function here
int testTask()
{   
    for (int i = 0; i < 5; i++){
        cout << i << endl;
        sleep (1);
    }
    return TRUE;
}
int testTask2()
{   
    for (int i = 0; i < 10; i++){
        cout << i << endl;
        sleep (1);
    }
    return TRUE;
}

int testTask3()
{
    return FALSE;
}

int main(int argc, char** argv)
{
    TaskManager tm;

//    tm.addTask(testTask2, 2, THREAD);
    tm.addTask(testTask3, 2, THREAD);
    tm.addTask(testTask3, 2, THREAD);

    for (int i = 0; i < 5; i++){
        tm.addTask(testTask, 1, THREAD);
        tm.addTask(testTask, 1, PROCESS);
    }
//     for (int i = 0; i < 10; i++){
//         tm.addTask(testTaskFail, 3, PROCESS);
//     }
    
    tm.start();
    
    return 0;
}

    
