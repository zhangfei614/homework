#include<iostream>
#include<fstream>
#include "config.h"

using namespace std;

int main(){
	fstream fout("data.in",ios::out|ios::binary);
	
	for(unsigned int i=0;i<NUMBERS_COUNT;i++){
		fout<<i<<endl;
	}
	fout.close();
	return 0;	
}