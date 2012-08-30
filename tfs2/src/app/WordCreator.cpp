/**
 * @file	WordCreator.cpp
 *  Create data file for WordCount 	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	2008年03月26日 11时11分59秒 CST
 *
 */

#include <tfs/tfs.h>
#include <algorithm>
using namespace tfs::api;

int main() {
    FileSystem fs;
    if (fs.existFile("/wc.40M.18"))
        fs.removeFile("/wc.40M.18");
    fs.createFile("/wc.40M.18", 3, 0);
    AppendStream as("/wc.40M.18", 0);

    char cset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";

    char s[100];
    const int len = 18;

    s[len] = '\n';
    for (int i = 0; i < 40000000; ++i) {
        memcpy(s, cset + rand() % 57, 6);
        memcpy(s + 6, cset + rand() % 57, 6);
        memcpy(s + 12, cset + rand() % 57, 6);
        as.append(s, len + 1);
    }

    as.close();
    return 0;
}
