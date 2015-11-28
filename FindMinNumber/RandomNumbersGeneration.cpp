#include<iostream>
#include<fstream>
#include<random>
#include<ctime>

#include "config.h"

using namespace std;

int main(){
	
	//open the file
	ofstream fout("data.in",ios::out|ios::binary);	
	
	//generate the engine by time
	default_random_engine dre(time(NULL));	
	
	uniform_int_distribution<unsigned int> uid(0,MAX_NUMBER);	
	
	for(int i=0;i<NUMBERS_COUNT;i++){
		fout<<uid(dre)<<endl;
	}
	
	fout.close();
	
	return 0;
}