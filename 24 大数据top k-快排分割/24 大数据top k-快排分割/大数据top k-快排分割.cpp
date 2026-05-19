#include <iostream>

using namespace std;

//快排分割函数
int Paration(int arr[], int l, int r)
{
	int val = arr[l];

	while (l < r)
	{
		while (l < r && arr[r] > val)
			r--;
		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}
		while (l < r && arr[l] < val)
			l++;
		if (l < r) 
		{
			arr[r] = arr[l];
			r--;
		}
	}
	arr[l] = val;
	return l;
}

//求top k函数
void SelectTopK(int arr[], int begin, int end, int k)
{
	int pos = Paration(arr, begin, end);
	if (pos == k - 1)
	{
		return;
	}
	else if (pos > k - 1)
	{
		return SelectTopK(arr, begin, pos - 1, k);
	}	
	else if (pos < k - 1)
	{
		return SelectTopK(arr, pos + 1, end, k);
	}
}

int main() 
{
	int arr[10] = { 64, 45, 52, 80, 66, 68, 0, 2, 18, 75 };
	int size = sizeof(arr) / sizeof(arr[0]);

	int k = 3;
	SelectTopK(arr, 0, size - 1, k);

	for (int i = 0; i < k; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}