#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>

#define RANDOM_NUMBERS 1000000
#define MAX_NUMBER 256

using namespace std;

int main(){
	
	ofstream fout("data.in",ios::out|ios::binary);
	
	srand(time(NULL));
	
	for(unsigned int i=0;i < RANDOM_NUMBERS; i++){
		fout<<(rand()% MAX_NUMBER)<<endl;
	}
	
	fout.close();
	
	return 0;
}