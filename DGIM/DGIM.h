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
	unsigned int ts;
	unsigned char j;
} Bucket, *BucketPtr;

class DGIM {
private:
	std::vector<Bucket> buckets;
	unsigned int ts;		//时间戳
	unsigned char r;			//每个桶最多有r个
	unsigned int N;				//时间窗口长度
public:
	DGIM(unsigned char r, unsigned int N) {
		this->r = r;
		this->N = N;
		ts = 0;
	}

	void append(unsigned char v);		//向该流中追加一个值

	unsigned int estimate(unsigned int k);		//估计最近k个值中一个的个数

	void printBuckets();
};

#endif /* DGIM_H_ */
