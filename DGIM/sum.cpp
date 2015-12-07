#include"DGIM.h"
#include<fstream>


#define lgMAX 8
#define rMAX  50
#define WINDOW_LENGTH 100000
#define SLOT_LENGTH 1000
#define ESTIMATE_LENGTH 50000

#define BITV(x,i) ((x>>i)&1)

using namespace std;

int main(){
	ifstream fin("data.in",ios::in|ios::binary);
	
	//生成lgMAX个DGIM
	vector<DGIM> dgims;
	for(int i=0;i<lgMAX;i++){
		DGIM d(rMAX,WINDOW_LENGTH);
		dgims.push_back(d);
	}
	
	//读取随机数文件,先读入WINDOW_LENGTH个数，不估计
	unsigned int v;
	for(int i=0;i<WINDOW_LENGTH;i++){
		fin>>v;
		for(int j=0;j<lgMAX;j++){
			dgims[j].append(BITV(v,j));
		}
	}
	
	//每读入SLOT_LENGTH个数进行一次估计
	unsigned int count = 0;
	while(fin>>v){
		for(int i=0;i<lgMAX;i++){
			dgims[i].append(BITV(v,i));
		}
		count++;
		if(count == SLOT_LENGTH){
			unsigned int sum = 0;
			for(int i=0;i<lgMAX;i++){
				sum+= ((1<<i)*dgims[i].estimate(ESTIMATE_LENGTH));
			}
			cout<<sum<<endl;
			count = 0;
		}
	}
	
	fin.close();
	
	return 0;
}