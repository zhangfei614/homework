#ifndef DGIM_H
#define DGIM_H

#include<iostream>
#include<vector>

typedef struct {
	unsigned int timestamp;
	unsigned char j;
}Bucket,*BucketPtr;

class DGIM{
	private:
		std::vector<Bucket> buckets;
		unsigned int timestamp;		//时间戳
		unsigned char r;			//每个桶最多有r个
		unsigned int N;				//时间窗口长度
		unsigned char lgN;			//j的最大值为lgN
	public:
		DGIM(unsigned char r,unsigned int N,unsigned char lgN){
			this->r = r;
			this->N = N;
			this->lgN = lgN;
			timestamp = 0;
		}
		
		void append(unsigned char v);		//向该流中追加一个值
		
		unsigned int estimate(unsigned int k);		//估计最近k个值中一个的个数
};


#endif