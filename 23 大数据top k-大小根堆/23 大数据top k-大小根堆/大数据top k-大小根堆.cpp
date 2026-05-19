#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <time.h>

using namespace std;

//求最小的前k个数字：大根堆-从大到小
void topMin(int k, vector<int>& vec) {
	//优先级队列
	priority_queue<int> maxheap;
	//构建大根堆
	for (int i = 0; i < k; i++) {
		maxheap.push(vec[i]);
	}
	//寻找最小的k个元素
	for (int i = k; i < vec.size(); i++) {
		if (maxheap.top() > vec[i]) {
			//先出堆顶元素
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}
	//遍历输出
	while (!maxheap.empty()) {
		cout << maxheap.top() << " ";
		maxheap.pop();
	}
	cout << endl;
}

//求最大的前k个数字：小根堆-从小到大
void topMax(int k, vector<int>& vec) {
	priority_queue<int, vector<int>, greater<int>> minheap;
	for (int i = 0; i < k; i++) {
		minheap.push(vec[i]);
	}
	for (int i = k; i < vec.size(); i++) {
		if (minheap.top() < vec[i]) {
			minheap.pop();
			minheap.push(vec[i]);
		}
	}
	while (!minheap.empty()) {
		cout << minheap.top() << " ";
		minheap.pop();
	}
	cout << endl;
}

int main() {
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++){
		vec.push_back(rand() % 1000);
	}

	//求最小的前k个数字：大根堆-从大到小
	topMin(3, vec);
	//求最大的前k个数字：小根堆-从小到大
	topMax(3, vec);
}