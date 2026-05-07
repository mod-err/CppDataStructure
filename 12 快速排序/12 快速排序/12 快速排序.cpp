#include <iostream>
#include <time.h>

using namespace std;

//分区函数：返回基准数下标
int Partition(int arr[], int l, int r) {

	int val = arr[l];

	while (l < r) {
		while (arr[r] >= val) {
			r--;
		}
		if (l < r) {
			arr[r] = val;
			l++;
		}
		while (arr[l] <= val) {
			l++;
		}
		if (l < r) {
			arr[l] = val;
			r--;
		}
	}
	if (l == r) {
		arr
	}
	return l;
}

//快排递归接口
void QuickSort(int arr[], int begin, int end) {
	//快排递归结束的条件
	if (begin >= end) {
		return;
	}
	//在[begin, end]区间进行分区处理
	int pos = Partition(arr, begin, end);
	//对左边和右边分别进行快排
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

//快速排序
void QuickSort(int arr[], int size) {
	return QuickSort(arr, 0, size - 1);
}

int main() {
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1; //0-100
		cout << arr[i] << " ";
	}
	cout << endl;

	QuickSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}