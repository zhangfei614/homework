/*
 * DGIM.h
 *
 *  Created on: Dec 6, 2015
 *      Author: zhangfei
 */

#ifndef DGIM_H_
#define DGIM_H_

#include<iostream>
#include<vector>

typedef struct Bucket{
	unsigned int ts;	//该桶时间戳
	unsigned char j;	//该桶中的有2^j个1
} Bucket;

class DGIM {
private:
	std::vector<Bucket> buckets;	//所有的桶
	unsigned int ts;		//当前时间戳
	unsigned char r;			//每个桶最多有r个
	unsigned int N;				//时间窗口长度
public:
	DGIM(unsigned char r, unsigned int N) {
		this->r = r;
		this->N = N;
		ts = 0;
	}

	//向该流中追加一个0或1
	void append(unsigned char v);		

	//估计最近k个值中1的个数
	unsigned int estimate(unsigned int k);		

	//打印当前桶的状况
	void printBuckets();
};

#endif /* DGIM_H_ */
