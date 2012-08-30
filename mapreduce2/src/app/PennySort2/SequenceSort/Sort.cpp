// Using merge sort to sort the pennysort records
// author: yzf
// 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

const int RUN_MAX_RECORD = 1024*1024*5; // 500MB

struct record
{ 
    char    sortkey[10];
    char    recnum[10];
    char    txtfld[80];
};

struct indexed_record
{
    record r;
    int run;
};

ostream& operator<< (ostream& os, const record& r){
    os.write((char*)&r, sizeof(record));
    return os;
}

istream& operator>> (istream& is, const record& r){
    is.read((char*)&r, sizeof(record));
    return is;
}
struct record_less_than: public binary_function<record, record, bool>
{
    bool operator() (const record& r1, const record& r2)
        {
            return memcmp(&r1, &r2, 10) < 0;
        }
};
struct irecord_greater_than: public binary_function<indexed_record, indexed_record, bool>
{
    bool operator() (const indexed_record& r1, const indexed_record& r2)
        {
            return memcmp(&r1.r, &r2.r, 10) > 0;
        }
};

int main(int argc, char** argv){
    if (argc != 3){
        cerr << "Usage: pennysort <infile> <outfile>" << endl;
        return 1;
    }
    ifstream ifs(argv[1]);
    if (!ifs){
        cerr << "Cannot open input file " << argv[1] << endl;
        return 2;
    }
    ofstream ofs(argv[2]);
    if (!ofs){
        cerr << "Cannot open output file " << argv[2] << endl;
        return 2;
    }
    time_t start = time(NULL);
    record *records = new record[RUN_MAX_RECORD];
    cout << "memory size: " << RUN_MAX_RECORD * sizeof(record) / (1024*1024) << "MB" << endl;
    record_less_than rlt;

    int run_num = 0;
    int i;
    time_t prevtime = start, currtime;
    double elipsed;

    for(i = 0; (ifs >> records[i]); i++){
        if (i == RUN_MAX_RECORD - 1){
            cout << "generating run " << run_num << endl;
            // do in-memory sort
            sort(records, records+RUN_MAX_RECORD, rlt);
            currtime = time(NULL);
            elipsed = difftime(currtime, prevtime);
            cout << elipsed << " seconds in-memory sort" << endl;
            prevtime = currtime;
            // generate run file
            stringstream ss;
            ss << argv[2] << run_num++;
            ofstream ofstmp(ss.str().c_str());
            if (!ofstmp){
                cerr << "Cannot open tmp file " << ss.str() << endl;
                return 3;
            }
            for (int j = 0; j < RUN_MAX_RECORD; j++){
                ofstmp << records[j];
            }
            ofstmp.close();
            currtime = time(NULL);
            elipsed = difftime(currtime, prevtime);
            cout << elipsed << " seconds writting run file" << endl;
            prevtime = currtime;
            i = -1;
        }
    }
    if (i > 0){
        cout << "generating run " << run_num << endl;
        // do in-memory sort
        sort(records, records+i, rlt);
        currtime = time(NULL);
        elipsed = difftime(currtime, prevtime);
        cout << elipsed << " seconds in-memory sort" << endl;
        prevtime = currtime;
        
        // generate run file
        stringstream ss;
        ss << argv[2] << run_num++;
        ofstream ofstmp(ss.str().c_str());
        if (!ofstmp){
            cerr << "Cannot open tmp file " << ss.str() << endl;
            return 3;
        }
        for (int j = 0; j < i; j++){
            ofstmp << records[j];
        }
        ofstmp.close();
        currtime = time(NULL);
        elipsed = difftime(currtime, prevtime);
        cout << elipsed << " seconds writting run file" << endl;
        prevtime = currtime;
    }
    delete [] records;
    time_t end = time(NULL);
    elipsed = difftime(end, start);
    cout << elipsed << " seconds generated all runs!" << endl;
    // merge
    cout << "merging " << run_num << " runs..." << endl;

    irecord_greater_than irlt;  // for min heap
    indexed_record* irecords = new indexed_record[run_num];
    ifstream* ifss = new ifstream[run_num];
    // open all tmp files
    for (i = 0; i < run_num; i++){
        stringstream ss;
        ss << argv[2] << i;
        ifss[i].open(ss.str().c_str());
        if (!ifss[i]){
            cerr << "Cannot open tmp file " << ss.str() << endl;
            break;
        }
        irecords[i].run = i;
        ifss[i] >> irecords[i].r;
    }
    make_heap(irecords, irecords + run_num, irlt);
    while(true){
        pop_heap(irecords, irecords + run_num, irlt);
        ofs << irecords[run_num-1].r;
        ifss[irecords[run_num-1].run] >> irecords[run_num-1].r;
        if (!ifss[irecords[run_num-1].run]){
            // this run has no more records
            run_num--;
            if (run_num == 0){
                break;
            }
        } else{
            push_heap(irecords, irecords + run_num, irlt);
        }
        
    }    

    delete [] ifss;
    currtime = time(NULL);
    elipsed = difftime(currtime, prevtime);
    cout  << elipsed  << " seconds merge all runs " << endl;

    end = time(NULL);
    elipsed = difftime(end, start);
    cout << "total time: "<< elipsed << " seconds" << endl;
    return 0;
}
