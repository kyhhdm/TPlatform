// main.cpp
#include "app/fuse/include/TfsHello.hpp"
#include <client/tfs.h>
#include <iostream>
using namespace std;
using namespace tfs::api;


int main (int argc, char **argv) {
        FileSystem fs;
        if( !fs.existFile("/hello") ){
            try{
                fs.createFile("/hello", 1 , 3200000);
            }
            catch(TFSException& ex){
                cout << "Get exception: " << ex.what() << endl;
            }
        }
        TfsHello hello;
        // The first 3 parameters are identical to the fuse_main function.
        // The last parameter gives a pointer to a class instance, which is
        // required for static methods to access instance variables/ methods.
        return hello.main (argc, argv, NULL, &hello);
}

