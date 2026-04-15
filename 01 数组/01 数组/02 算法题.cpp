#include <iostream>

using namespace std;

//元素逆序
void Reverse(int arr[], int len) {
	int* p = arr;
	int* q = arr + len - 1;
	while (p < q) {
		char ch = *p;
		*p = *q;
		*q = ch;
		p++;
		q--;
	}
}

void test1() {
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}

	Reverse(arr, 10);
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
		//奇数
		if ((*p & 0x1) == 1) {
			
		}
		//偶数
		if ((*q & 0x1) == 0) {
			
		}
		int temp = *p;
		*p = *q;
		*q = temp;
		p++;
		q--;
	}
}

int main() {
	
}