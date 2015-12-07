/*
 * test.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: zhangfei
 */
#define Nt 100000
#define kt  50000
#define m   1000

#include"DGIM.h"
#include<fstream>
using namespace std;

int main(){
	ifstream fin("test.in",ios::in|ios::binary);
	
	DGIM d(10,Nt);
	unsigned int v;
	for(int i=0;i<Nt;i++){
		fin>>v;
		d.append(v);
	}
	int count = 0;
	while(fin>>v){
		d.append(v);
		count++;
		if(count==m){
			cout<<d.estimate(kt)<<endl;
			// d.printBuckets();
			count = 0;
		}
	}
	fin.close();
	return 0;
}

