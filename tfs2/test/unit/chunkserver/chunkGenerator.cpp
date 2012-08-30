/*
 * @FILE:  chunkGenerator.cpp 
 * AUTHOR: Chen Rishan
 * CREATED DATE: 23 7月 2007
 * DESCRIPTION: it generates the chunks
 */

#include<iostream> 
#include<fstream>
using namespace std;

char file[6][2]={"0","1","2","3","4","5"};

int 
main(void)
{

	long i = 0;
	ofstream fout("chunk_6",ios::out);

	for(long i = 0;i < 64000000;i ++){
		fout << "a"; 
	}
	long i = 0;
	ofstream fout[6];
	for(int j = 0;j < 6;j ++){
		fout[j].open(file[j],ios::out);
		for(int k = 0;k < 64000;k ++){
			fout[j] << char(i%10);
			i ++;  
		}	
		fout[j].close();
	}
	return 0;
}










