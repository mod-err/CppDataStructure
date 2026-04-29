#include <iostream>
#include <time.h>

using namespace std;

//冒泡排序
void BubbleSort(int arr[], int size) {
	//排序趟数
	for (int i = 0; i < size - 1; i++) {
		bool flag = false;
		//一趟排序次数
		for (int j = 0; j < size - 1 -i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
				flag = true;
			}
		}
		if (!flag) return;
	}
}

//选择排序 - 时间复杂度：O(n^2) - 空间复杂度：O(1) - 稳定性：不稳定
void ChoiceSort(int arr[], int size) {
	//排序趟数 - O(n)
	for (int i = 0; i < size - 1; i++) {
		//一趟排序 - O(n)
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[min] > arr[j])	min = j;
		}
		if (min != i) {
			int tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
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

	ChoiceSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}