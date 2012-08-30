/**
 * @file	App.cpp
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	2008��03��26�� 11ʱ11��59�� CST
 *
 */

#include <tfs/tfs.h>
#include <iostream>
using namespace tfs::api;
using namespace std;

int main(int argc, char **argv) {
    FileSystem fs;
    cout <<argv[1] <<endl;
    fs.setReplication(argv[1], 2);
    return 0;
}
