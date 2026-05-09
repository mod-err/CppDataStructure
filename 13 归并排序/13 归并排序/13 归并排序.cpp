#include <iostream>
#include <time.h>

using namespace std;

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
	MergeSort(arr, 0 ,size - 1);
}

int main() {
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1; //0-100
		cout << arr[i] << " ";
	}
	cout << endl;

	MergeSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}

