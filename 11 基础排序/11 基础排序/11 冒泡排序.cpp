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

//插入排序 - 时间复杂度：最坏、平均：O(n^2) 最好：O(n) - 空间复杂度：O(1) - 稳定性：稳定
void InsertSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int tmp = arr[i + 1];
		int j = i; //待比较的前一个元素
		//一趟排序：第i趟排序比较i+1次
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
	BubbleSort(arr, COUNT);
	end = clock();
	cout << "BubbleSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ChoiceSort(brr, COUNT);
	end = clock();
	cout << "ChoiceSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	InsertSort(crr, COUNT);
	end = clock();
	cout << "InsertSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ShellSort(drr, COUNT);
	end = clock();
	cout << "ShellSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
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

	ShellSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}
#endif