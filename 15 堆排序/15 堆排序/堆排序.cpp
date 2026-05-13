#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

//堆下沉
void SiftDown(int arr[], int i, int n) {
	int val = arr[i];
	//n为末尾元素下标
	while (2 * i + 1 <= n) {
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
		SiftDown(arr, 0, i - 1);//i-1参与调整的元素下标
	}
}

int main() {
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	HeapSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}