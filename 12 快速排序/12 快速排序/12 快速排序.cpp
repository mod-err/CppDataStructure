#include <iostream>
#include <time.h>

using namespace std;

//插入排序
void InsertSort(int arr[], int begin, int end) {
	for (int i = 0; i < (end - begin); i++) {
		int tmp = arr[i + 1];
		int j = i;
		for (; j >= 0; j--) {
			if (tmp < arr[j]) {
				arr[j + 1] = arr[j];
			}
			else {
				break;
			}
		}
		arr[j + 1] = tmp;
	}
}

//分区函数：返回基准数下标
int Partition(int arr[], int l, int r) {

	//优化2：采用[三数取中法]选取基准数
	int mid = (l + r) / 2;
	if (arr[l] > arr[mid]) swap(arr[l], arr[mid]);
	if (arr[l] > arr[r]) swap(arr[l], arr[r]);
	if (arr[mid] > arr[r]) swap(arr[mid], arr[r]);

	//选取基准数
	int val = arr[l];

	while (l < r) {
		//只有[大于]基准数组才会被跳过，[小于/等于]会被移动
		while (l < r && arr[r] > val) {
			r--;
		}
		if (l < r) {
			arr[l] = arr[r];
			l++;
		}
		//只有[小于于]基准数组才会被跳过，[大于/等于]会被移动
		while (l < r && arr[l] < val) {
			l++;
		}
		if (l < r) {
			arr[r] = arr[l];
			r--;
		}
	}
	arr[l] = val;
	return l;
}

//快排递归接口
void QuickSort(int arr[], int begin, int end) {
	//快排递归结束的条件
	if (begin >= end) {
		return;
	}
	//优化1：当[begin, end]区间数据小到一定规模，采用插入排序
	if (end - begin <= 500) {
		InsertSort(arr, begin, end);
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
	int COUNT = 100000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	int* crr = new int[COUNT];
	int* drr = new int[COUNT];

	srand(time(NULL));

	for (int i = 0; i < COUNT; i++) {
		int val = rand() % COUNT;
		arr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	QuickSort(arr, COUNT);
	end = clock();
	cout << "BubbleSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
}


#if 0
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
#endif
