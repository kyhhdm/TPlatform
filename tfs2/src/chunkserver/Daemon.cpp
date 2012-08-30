

#include "Daemon.hpp"
#include <unistd.h>
#include <cassert>
#include <string>
#include <vector>

using namespace std;
using namespace tfs;


//thread sleep, can be other implement
int Daemon::sleepCurThread(int second)
{
    sleep(second);
    return 1;
}

Daemon::~Daemon()
{
}
