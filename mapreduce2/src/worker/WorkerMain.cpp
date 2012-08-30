/**
 * @file	WorkerMain.cpp
 * 	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	12/13/2007 11:09:32 AM CST
 *
 */

#include "Worker.hpp"
#include <iostream>
#include <libgen.h>

using namespace mapreduce;
using namespace std;

int main(int argc, char **argv) {
    char *prefix = "Worker Main: ";
    if (argc != 2) {
        cout <<"Usage: mapred_worker <config.ini>" <<endl;
        return 0;
    }
    
    try {
        char* homeDir = dirname( argv[0] );
        
        Worker worker(argv[1], homeDir);
        worker.run();
    } catch (Ice::Exception &ex) {
        LOG_FATAL(prefix <<ex);
    } catch (exception &ex){
        LOG_FATAL(prefix <<ex.what());
    }

    return 0;
}
