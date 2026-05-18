#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "time.h"

using namespace std;

//哈希表查找首个重复元素
void findRepeat(vector<int>& vec) {
	unordered_set<int> s;
	for (auto key : vec) {  //O(n)
		//unordered_set<int>::iterator it = s1.find(key);
		//哈希表查找O(1)
		auto it = s.find(key);
		//如果在哈希表中未找到，插入哈希表
		if (it == s.end()) {
			s.insert(key);
		}
		else {
			//输出重复的元素
			cout << "key：" << key << endl;
			return; //去掉return即查找所有
		}
	}
}

//哈希表查找重复元素及其重复次数
void findRepeatCnt(vector<int>& vec) {
	unordered_map<int, int> m;
	for (auto key : vec) {
		//auto it = m.find(key);
		//if (it == m.end()) {
		//	m.insert(make_pair(key, 1));
		//}
		//else {
		//	it->second++;
		//}
		m[key]++;  //m[key] == it->second;
		/*
		map[key]，它会自动帮你做两件事：
			如果 key 不存在 → 自动创建这个 key，并把对应的值默认初始化为 0
			如果 key 已存在 → 直接拿到这个 key 对应的 value
		*/

	}
	//输出重复元素及其次数
	for (auto pair : m) {
		if (pair.second > 1) {
			cout << "key：" << pair.first << " cnt：" << pair.second << endl;
		}
	}
}

//哈希表找出来第一个没有重复出现过的字符
void findString(string& str) {
	unordered_map<char, int> m;
	for (auto ch : str) {
		//auto it = m.find(ch);
		//if (it == m.end()) {
		//	m.insert(make_pair(ch, 1));
		//}
		//else {
		//	it->second++;
		//}
		m[ch]++;
	}
	//输出
	for (auto ch : str) {
		if (m[ch] == 1) {
			cout << "第一个没用重复的元素是：" << ch << endl;
			return;
		}
	}
}

int main() {
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++) {
		vec.push_back(rand() % 10000);
	}

	//哈希表-过滤重复数字
	unordered_set<int> s;
	for (auto key : s) {
		s.insert(key); //set不允许容器中有重复的元素
	}

	//哈希表-查找首个重复元素
	//findRepeat(vec);

	//哈希表-查找重复元素及其重复次数
	//findRepeatCnt(vec);

	string src = "jjhffgiyuhrtytrs";
	findString(src);
}