#include <iostream>

using namespace std;

int BinarySearch(int arr[], int size, int val) {
	int first = 0;
	int last = size - 1;

	while (first <= last) {
		int mid = (first + last) / 2;

		if (arr[mid] > val) {
			last = mid - 1;
		}
		else if(arr[mid] < val) {
			first = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

int main() {
	int arr[] = { 12, 23, 34, 45, 50 ,56, 67, 78, 89, 99};
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << BinarySearch(arr, size, 56) << endl;
	cout << BinarySearch(arr, size, 12) << endl;
	cout << BinarySearch(arr, size, 99) << endl;
	cout << BinarySearch(arr, size, 45) << endl;
}