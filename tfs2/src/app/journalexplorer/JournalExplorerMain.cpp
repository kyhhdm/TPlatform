/**
 * @file   JournalExplorerMain.cpp
 * @author Peng Bo
 * @date   2007 09 18
 * 
 * @brief  main function of the Journal data explorer
 * 
 * 
 */
#include "fsdirectory/FsJournalManager.hpp"
#include "util/Logger.hpp"
#include <ostream>

using namespace tfs;
using namespace std;

void help()
{       
    cout << "JournalExplorer version 0.1-patch 0" << endl;
    cout << "Usage:" << endl; 
    cout << "   tfs_journal <imageFilename> <logFileName> " << endl <<endl;
        
    cout << "   This program print contents in journal log file. " << endl 
             << "   It may be helpful for bug tracking, enjoy it!" << endl << endl;

    cout << "   TFS is Copyright (C) 2006-2007 Peking University Tianwang Group. " << endl;
    cout << "   and licensed under the GNU General Public License, version 2.   " << endl;
    cout << "   Bug reports, feedback, admiration, abuse, etc, to: tianwang.grids.cn/projects/tplatform." << endl;
    cout << endl;
}



int main(int argc, char* argv[])
{
    FsJournalManager journal("./");

    if(argc != 3) {
       return -1;
    }

    // setup logger
    helpers::LogLog::getLogLog()->setInternalDebugging(false);
    SharedAppenderPtr append_1(new RollingFileAppender("JournalExplorer.log", 5*1024, 5));
    append_1->setName("appender1");
    append_1->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
    Logger::getRoot().addAppender(append_1);

    // get logger
    Logger masterLogger = Logger::getInstance("journalexplorer");
    log4cplus::getNDC().push("JournalExplorer:run");

    //load image and log files
    FsDirectoryImpl* pDir = journal.getFsDirectoryDebugInstance(argv[1], argv[2]);

    //#BUGFIX, [#13] INode:findChunk segment fatal error
    //spring the trap here ->
    const Chunk* pChunk = pDir->findChunk(226257065020315009ll);
    if(pChunk) {
        cout << pChunk->size << pChunk->version << endl;
    }

    //
    log4cplus::getNDC().pop();
    return 0; 
}
