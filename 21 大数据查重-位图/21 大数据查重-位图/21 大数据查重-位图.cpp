#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> vec = {12, 78, 90, 78, 123, 8, 9, 90};

	//查找最大值
	int max = vec[0];
	for (auto v : vec) {
		if (v > max) {
			max = v;
		}
	}
	//cout << max << endl;

	/*
	栈stack上数组大小必须是常量
	   int arr[100];
	堆heap才支持动态大小
	   int* arr = new int[max];
	*/
	int *bitmap = new int[max / 32 + 1](); //位图数组全部初始化为0
	for (auto v : vec) {
		int idx = v / 32;
		int ofs = v % 32;
		//左移运算符 << 的优先级 高于 按位或运算符 | &
		if (bitmap[idx] & 1 << ofs) {
			cout << v << " 重复出现过!" << endl;
			//return; //找第一次重复出现的 
		}
		else {
			bitmap[idx] = bitmap[idx] | 1 << ofs;
		}
	}
	delete[] bitmap;
}
