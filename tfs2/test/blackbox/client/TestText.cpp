/**
 * @file	TestText.cpp
 * 	
 * 
 * @author	Fan Kai(fk), Peking University	
 * @date	2008��05��20�� 21ʱ08��27�� CST
 *
 */

#include <tfs/TextReader.hpp>
#include <tfs/TextWriter.hpp>
#include <iostream>
using namespace std;
using namespace tfs::api;


int main() {
    /*
    TextWriter tw("/Makefile");
    tw <<"fuck the world ";
    tw <<5;
    tw <<" joke\n";
    tw.close();
    */

    TextReader tr("/testtext");
    char c;
    while(tr >>c) {
        cout <<tr.eof() <<" " <<bool(tr) <<endl;
       cout <<c; 
    }

    cout <<"end" <<endl;
    string s;
    int i;
    cout <<"fail: "<<tr.getline() <<endl;
    cout <<"fail: "<<tr.bad() <<endl;
    cout <<"fail: " <<tr.fail() <<endl;

    tr >>s;
    cout <<s;
    tr >>s;
    cout <<s;
    tr >>s;
    cout <<s;
    tr >>i;
    cout <<i <<endl;
    cout <<tr.bad() <<endl;
    cout <<tr.fail() <<endl;
    double d;
   // tr >>d;
    cout <<d<<endl;
    cout <<tr.bad() <<endl;
    cout <<tr.fail() <<endl;

   // tr.exceptions(failbit|badbit|eofbit);
    tr.clear();
    tr >> s;
    cout <<s <<endl;



    cout <<endl;
}

