#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<algorithm>
#include "config.h"

using namespace std;

int main(){
	fstream fout("data.in",ios::out|ios::binary);
	
	vector<int> v;
	for(unsigned int i=0;i<NUMBERS_COUNT;i++){
		v.push_back(i);
	}
	
	srand(time(NULL));
	random_shuffle(v.begin(),v.end());
	for(unsigned int i=0;i<NUMBERS_COUNT;i++){
		fout<<v[i]<<endl;
	}
	
	fout.close();
	return 0;	
}