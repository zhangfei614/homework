#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include"config.h"
using namespace std;

int main(){
	
	ofstream fout("test.in",ios::out|ios::binary);
	
	srand(time(NULL));
	
	for(unsigned int i=0;i < RANDOM_NUMBERS; i++){
		fout<<(rand()% MAX_NUMBER)<<endl;
	}
	
	fout.close();
	
	return 0;
}