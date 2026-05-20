#include <iostream>
#include <vector>
#include <string>
#include "stringhash.h"

using namespace std;

//布隆过滤器
class BloomFilter {
public:
	BloomFilter(int bitSize = 1471) 
		: bitSize_(bitSize)
	{
		bitMap_.resize(bitSize_ / 32 + 1); //位图数组初始化为0
	}
public:
	//增加元素
	void setBit(const char* str) {
		// 计算k组哈希函数的值
	    // 经过哈希函数处理后不一定落在位图范围内，把大数映射到 位图数组内
		//外层函数已经拿到了指针，内层函数直接用这个指针传参即可，不需要再取地址。
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int idx = 0;
		int ofs = 0;

		idx = idx1 / 32;
		ofs = idx1 % 32;
		//bitMap_[idx] = bitMap_[idx] | (1 << ofs);
		bitMap_[idx] |= (1 << ofs);

		idx = idx2 / 32;
		ofs = idx2 % 32;
		bitMap_[idx] |= (1 << ofs);

		idx = idx3 / 32;
		ofs = idx3 % 32;
		bitMap_[idx] |= (1 << ofs);
	}
	//查找元素
	bool getBit(const char* str) {
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int idx = 0;
		int ofs = 0;

		idx = idx1 / 32;
		ofs = idx1 % 32;
		if ((bitMap_[idx] & (1 << ofs)) == 0) {
			return false;
		}

		idx = idx2 / 32;
		ofs = idx2 % 32;
		if ((bitMap_[idx] & (1 << ofs)) == 0) {
			return false;
		}

		idx = idx3 / 32;
		ofs = idx3 % 32;
		if ((bitMap_[idx] & (1 << ofs)) == 0) {
			return false;
		}
		//如果上面都为1，元素存在
		return true;
	}
private:
	int bitSize_;  //位图大小
	vector<int> bitMap_; //位图数组
};

//黑名单
class BlackList {
public:
	void add(string url) {
		bloomFilter_.setBit(url.c_str());
	}
	bool query(string url) {
		return bloomFilter_.getBit(url.c_str());
	}
private:
	BloomFilter bloomFilter_;
};

int main() {
	BlackList list;
	list.add("http://www.baidu.com");
	list.add("http://www.360buy.com");
	list.add("http://www.tmall.com");
	list.add("http://www.tencent.com");

	string url = "http://www.tmall.com";
	cout << list.query(url) << endl;
}