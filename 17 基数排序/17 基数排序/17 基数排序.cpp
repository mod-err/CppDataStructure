#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

void RadixSort(int arr[], int size) {
	//找出最大值
	int max = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	//获取最大值的位数
	int len = to_string(max).size();

	vector<vector<int>> vecs;

	int mod = 10;
	int dev = 1;
	for (int i = 0; i < len; i++, mod*=10, dev*=10) {
		//提前初始化10个桶，不提前初始化vecs[0]、vecs[1] ... 全都不存在
		//vecs[]下标方位不会触发vector扩容，push_back()才会
		vecs.resize(10);

		for (int j = 0; j < size; j++) {
			//得到当前元素的第i位
			int idx = arr[j] % mod / dev;
			vecs[idx].push_back(arr[j]);
		}
		//依次遍历所有的桶，放入原数组中 
		int k = 0;
		for (auto vec : vecs) {
			for (int v : vec) {
				arr[k++] = v;
			}
		}
		vecs.clear();
	}
}

int main() {
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1; //0-100
		cout << arr[i] << " ";
	}
	cout << endl;

	RadixSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}

