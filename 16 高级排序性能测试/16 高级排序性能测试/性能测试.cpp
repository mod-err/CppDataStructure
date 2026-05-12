#include <iostream>
#include "time.h"
#include <algorithm>

using namespace std;

//希尔排序 - 时间复杂度：平均：O(n^1.3) 最坏：O(n^2) 最好：O(n) - 空间复杂度：O(1) - 稳定性：不稳定
void ShellSort(int arr[], int size) {
	//分组数 gap = 5 2 1
	for (int gap = size / 2; gap > 0; gap = gap / 2) {
		// 内层循环：对每个分组做直接插入排序
		for (int i = gap; i < size; i++) {
			int tmp = arr[i];
			int j = i - gap; //待比较的前一个元素
			//一趟排序：从后往前比较
			for (; j >= 0; j = j - gap) {
				if (tmp < arr[j]) {
					arr[j + gap] = arr[j];
				}
				else {
					break;
				}
			}
			arr[j + gap] = tmp;
		}
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

//归并排序接口
void MergeSort(int arr[], int l, int r) {
	//递归结束条件
	if (l >= r) {
		return;
	}
	//递的过程
	int mid = (l + r) / 2;
	MergeSort(arr, l, mid);
	MergeSort(arr, mid + 1, r);
	//归并的过程
	int* p = new int[r - l + 1]; //堆开辟内存，存放排序结果
	int idx = 0; //内存索引
	int i = l;
	int j = mid + 1;
	while (i <= mid && j <= r) {
		//只有大于才移动
		if (arr[i] > arr[j]) {
			p[idx++] = arr[j++];
		}
		//小于等于不移动，稳定排序
		else {
			p[idx++] = arr[i++];
		}
	}
	//把左或右剩余数据放入内存
	while (i <= mid) {
		p[idx++] = arr[i++];
	}
	while (j <= r) {
		p[idx++] = arr[j++];
	}
	//将排序结果拷贝到arr中
	for (i = l, j = 0; i <= r; i++, j++) {
		arr[i] = p[j];
	}
	delete[]  p;
}

//归并排序
void MergeSort(int arr[], int size) {
	MergeSort(arr, 0, size - 1);
}

//堆下沉
void SiftDown(int arr[], int i, int n) {
	int val = arr[i];
	//n为末尾元素下标
	while (i <= (n - 1) / 2) {
		int child = 2 * i + 1;
		if (child + 1 <= n && arr[child + 1] > arr[child]) {
			child = child + 1;
		}
		if (arr[child] > val) {
			arr[i] = arr[child];
			i = child;
		}
		else {
			break;
		}
	}
	arr[i] = val;
}
//堆排序
void HeapSort(int arr[], int size) {
	//末尾元素下标
	int n = size - 1;
	//调整为大根堆
	for (int i = (n - 1) / 2; i >= 0; i--) {
		SiftDown(arr, i, n);
	}
	for (int i = n; i > 0; i--) {
		swap(arr[0], arr[i]);
		SiftDown(arr, 0, i - 1);//i-1参与调整的元素个数
	}
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
		brr[i] = val;
		crr[i] = val;
		drr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	QuickSort(arr, COUNT);
	end = clock();
	cout << "QuickSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	MergeSort(brr, COUNT);
	end = clock();
	cout << "MergeSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ShellSort(crr, COUNT);
	end = clock();
	cout << "ShellSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	HeapSort(drr, COUNT);
	end = clock();
	cout << "HeapSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	sort()
}
