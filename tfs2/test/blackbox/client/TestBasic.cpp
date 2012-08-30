/**
 * @file    TestBasic.cpp
 *      This test transfer a direcotry and all sub files and sub dirs to tfs
 *      and then read them back, and check for correctness. Besides, this test
 *      is interruptable. When each chunk is transfered, it is recorded, and 
 *      when this test is started once again, it will begin from where it 
 *      was stopped.
 *
 *      Usage:
 *      1. Create tfs/build/test_basic/test, and move any files or direcotries 
 *          to this dir.
 *      2. Enter direcotry tfs/build/test_basic.
 *      3. Run init.sh, which init record file.
 *      4. Run blackbox/test_basic from tfs/build. When file is being transferred, the 
 *            transfered offset is shown dynamically
 *      5. you can kill the test or the tfs environment whenever you like, and
 *           recover later. The test will continue from where it stopped.
 *
 *      Meanning of the record file:
 *      1. files: this file record each dir and file that will be transferred.
 *      2. filenum: this file record five number which decide the state of 
 *          test. The meaning of the five numbers are : 
 *          a. number of total items to be transferred
 *          b. number of items that has already been transferred
 *          c. number of items that has been checked for correctness
 *          d. offset that has been transferred of the file that is begin 
 *              transferred
 *          e. number of errors that has been found
 *      3. You should run script init.sh before test. After test, the 
 *          record file will be automatically set, so next test can be started
 *          without running init.sh.
 *
 * 
 * @author  Fan Kai(FK), Peking University    
 * @date    07/21/2007 09:29:48 PM CST
 *
 */

#include <tfs/tfs.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

using namespace tfs::api;
using namespace std;

const int CHUNK_SIZE = 2*1024*1024;

vector<string> entries;
string local_dir = "test_basic";
string remote_dir = "/test_basic";
string files = local_dir + "/files";
string filenum = local_dir + "/filenum";
char tmp[CHUNK_SIZE], data[CHUNK_SIZE];
int nerrors, nfiles, fno, cno;
int64_t offset;
ofstream fout;

// Write record file.
void write_file() {
    fout.open(filenum.c_str());
    fout <<nfiles <<" " <<fno <<" " <<cno <<" " <<offset <<" " <<nerrors;
    fout.close();
}

void transfer_file(string local_file, string remote_file) {
    cout <<"\rTRANSFER FILE : " <<local_file <<" ... " <<endl;
    AppendStream as(remote_file, CHUNK_SIZE);
    ifstream fin(local_file.c_str(), ios::binary);
    int n;
    fin.seekg(offset);
    while ((fin.read(tmp, CHUNK_SIZE), n = fin.gcount() ) > 0) {
        as.append(tmp, n);
        as.flush();
        offset += n;
        write_file();
        cout <<"\r" <<offset <<flush;
    }
    as.close();
    offset = 0;
}

void check_file(const string local_file, const string remote_file) {
    cout <<"CHECK FILE:  " <<local_file <<" ... " <<endl;
    FileSystem fs;
    // Check file existance.
    if (!fs.existFile(remote_file)) {
        cout <<"Check file error : " + remote_file + " unexist" <<endl;
        nerrors ++;
        write_file();
        return;
    }
    ifstream fin(local_file.c_str(), ios::binary);
    fin.seekg(0, ios::end);
    InputStream is(remote_file, 0);
    // Check file length.
    if (is.seek(0, SEEK_END) != fin.tellg() ) {
        cout <<"File length of " <<local_file <<" disagrees width " <<remote_file
             <<is.seek(0, SEEK_END) <<" != " <<fin.tellg() <<endl;
        nerrors ++;
        write_file();
        return;
    }
    fin.seekg(0, ios::beg);
    is.seek(0, SEEK_SET);
    int n;
    // Check file content.
    while ((fin.read(data, CHUNK_SIZE), n = fin.gcount() ) > 0) {
        is.read(tmp, n);
        if (memcmp(data, tmp, n) != 0) {
            cout <<"File content of " <<local_file <<" disagrees width " <<remote_file <<endl;
            nerrors ++;
            write_file();
        }
        return;
    }
}

void check_dir(const string local_dir, const string remote_dir) {
    cout <<"CHECK DIR:   " <<local_dir <<" ... " <<endl;
    FileSystem fs;
    // Check dir existance.
    if (!fs.existDirectory(remote_dir)) {
        cout <<"Check dir error : " <<remote_dir <<" unexist" <<endl;
        nerrors ++;
        write_file();
        return;
    }
    DIR *dir = opendir(local_dir.c_str());
    if (dir == NULL) {
        cout <<"Open dir error : " << local_dir <<endl;
        nerrors ++;
        write_file();
        return;
    }
    struct dirent *entp;
    int n = 0;
    // Check dir content.
    while((entp = readdir(dir)) != NULL) {
        if (strcmp(".", entp->d_name) == 0) continue;
        if (strcmp("..", entp->d_name) == 0) continue;
        string name = local_dir + "/" + entp->d_name;
        ++n;
    }
    FilesInfo fi = fs.listDirectory(remote_dir);
    if (n != fi.size()) {
        cout <<"Number of subdirs and files of " << remote_dir <<
                " disagree with " <<local_dir <<endl;
        nerrors ++;
        write_file();
    }
}

void testBasic() {
    try {
        string name;
        ifstream fin;
        FileSystem tfs;

        if (opendir("test_basic") == NULL) {
            cout <<"Can not find directory: test_basic/" <<endl;
            return;
        }
        fin.open("test_basic/files");
        if (!fin.is_open()) {
            cout <<"Can not find test_basic/files" <<endl;
            return;
        }
        while (getline(fin, name))
            entries.push_back(name);
        fin.close();
        fstream filenum("test_basic/files", ios::in);
        fin.open("test_basic/filenum");
        if (!fin.is_open()) {
            cout <<"Can not find test_basic/filenum" <<endl;
            return;
        }
        fin >>nfiles >>fno >>cno >>offset >>nerrors;
        fin.close();

        if (entries.size() != nfiles || nfiles < fno) {
            cout <<"File numbers is in error." <<endl;
            return;
        }

        if (!tfs.existDirectory("/test_basic"))
            tfs.createDirectory("/test_basic");

        // Transfer files and dirs.
        while (fno < nfiles) {
            name = local_dir + "/" + entries[fno];
            if (opendir(name.c_str()) != NULL) {
                if (!tfs.existDirectory("/" + name))
                    tfs.createDirectory("/" + name);
            } else {
                if (!tfs.existFile("/" + name)) {
                    tfs.createFile("/" + name, 3, CHUNK_SIZE);
                    offset = 0;
                }
                transfer_file(name, "/" + name);
            }
            fno ++;
            write_file();
        }

        // Check files and dirs.
        while (cno < nfiles) {
            name = local_dir + "/" + entries[cno];
            if (opendir(name.c_str()) != NULL)
                check_dir(name, "/" + name);
            else 
                check_file(name, "/" + name);
            cno ++;
            write_file();
        }

        tfs.removeDirectory("/test_basic", true);
        fout.open("test_basic/filenum");
        fout <<nfiles <<" 0 0 0 0";
        fout.close();
        cout <<"Found errors : " <<nerrors <<endl;
    }
    catch (exception &ex) {
        cout <<ex.what() <<endl;
    }
}

int main() {
    testBasic();
    return 0;
}

