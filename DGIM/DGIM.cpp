/*
 * DGIM.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: zhangfei
 */

#include"DGIM.h"

using namespace std;

void DGIM::append(unsigned char v) {
	ts += 1;
	if (!buckets.empty()) {
		//判断最后一个的桶是否过期
		if ((ts - buckets[0].ts) >= N) {
			for (int i = 1; i < buckets.size(); i++) {
				buckets[i - 1] = buckets[i];
			}
			buckets.pop_back();
		}
	}
	if (v == 1) {		//如果新加入元素为1，则对桶进行调整
		Bucket b = { ts, 1 };
		buckets.push_back(b);
		vector<int> indexs;
		int count = 1;
		for (int i = buckets.size() - 2; i >= 0; i--) {
			if (buckets[i].j == buckets[i + 1].j) {
				count++;
				if (count > r) {
					buckets[i].ts = buckets[i + 1].ts;
					buckets[i].j++;
					indexs.push_back(i + 1);
					count = 1;
				}
			}else{
				count=1;
			}

		}
		for (int i = 0; i < indexs.size(); i++) {
			buckets.erase(buckets.begin() + indexs[i]);
		}
	}
}

unsigned int DGIM::estimate(unsigned int k) {
	unsigned int sum = 0;
	for(int i=buckets.size()-1;i >= 0;i--){
		if((ts - buckets[i].ts) <= k){
			sum += (1<<(buckets[i].j-1));
		}else{
			break;
		}
	}
	return sum;
}

void DGIM::printBuckets() {
	for (int i = 0; i < buckets.size(); i++) {
		cout << "(" << buckets[i].ts << "," << (int) buckets[i].j << ")";
	}
	cout << endl;
}

