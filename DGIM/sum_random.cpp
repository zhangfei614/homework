#include"DGIM.h"
#include<ctime>
#include<cstdlib>
#include<chrono>

#define lgMAX 8
#define rMAX  2
#define WINDOW_LENGTH 100000000
#define SLOT_LENGTH 1000000
#define ESTIMATE_LENGTH 50000000

#define BITV(x,i) ((x>>i)&1)

using namespace std;

int main(){
	
	//生成lgMAX个DGIM
	vector<DGIM> dgims;
	for(int i=0;i<lgMAX;i++){
		DGIM d(rMAX,WINDOW_LENGTH);
		dgims.push_back(d);
	}
	
	//产生随机数，前WINDOW_LENGTH个数不估计
	srand(time(NULL));
	unsigned int v;
	for(int i=0;i<WINDOW_LENGTH;i++){
		v = (rand()%(1<<lgMAX));
		for(int i=0;i<lgMAX;i++){
			dgims[i].append(BITV(v,i));
		}
	}
	
	//测试时间
	auto start = chrono::system_clock::now();
	unsigned long aSum = 0;
	int times = 10;
	//每读入SLOT_LENGTH个数进行一次估计
	unsigned int count = 0;
	while(times > 0){
		v = (rand()%(1<<lgMAX));
		for(int i=0;i<lgMAX;i++){
			dgims[i].append(BITV(v,i));
		}
		count++;
		if(count == SLOT_LENGTH){
			
			unsigned int sum = 0;
			for(int i=0;i<lgMAX;i++){
				sum+= ((1<<i)*dgims[i].estimate(ESTIMATE_LENGTH));
			}
			// cout<<sum<<endl ;
			count = 0;
			
			times--;
			auto end = chrono::system_clock::now();
			unsigned long dur= chrono::duration_cast<chrono::milliseconds>(end - start).count();
			// cout<<dur<<endl;
			aSum+=dur;
			start = chrono::system_clock::now();
		}
	}
	
	cout<<aSum/(float)10<<endl;
	return 0;
}