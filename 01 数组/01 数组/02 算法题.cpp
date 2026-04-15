#include <iostream>

using namespace std;

//元素逆序
void Reverse(int arr[], int len) {
	int* p = arr;
	int* q = arr + len - 1;
	while (p < q) {
		int temp = *p;
		*p = *q;
		*q = temp;
		p++;
		q--;
	}
}
void Reverse1(int arr[], int len) {
	int p = 0;
	int q = len - 1;
	while (p < q) {
		int temp = arr[p];
		arr[p] = arr[q];
		arr[q] = temp;
		p++;
		q--;
	}
}

void test1() {
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}

	Reverse1(arr, 10);
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

//偶左奇右
void AdjustArr(int arr[], int len) {
	int* p = arr;
	int* q = arr + len - 1;
	while (p < q) {
		//如果是奇数跳过if
		if ((*p & 0x1) == 0) {
			p++;
			continue;
		}
		//如果是偶数跳过if
		if ((*q & 0x1) == 1) {
			q--;
			continue;
		}
		int temp = *p;
		*p = *q;
		*q = temp;
		p++;
		q--;
	}
}

int main() {
	test1();

	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}

	AdjustArr(arr, 10);
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}