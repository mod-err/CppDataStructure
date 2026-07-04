#if 0

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
硬币选择问题：有1，3，5分面额的硬币，给定一个面值11，问组成给定面值所需要的最少的硬币数量是多少？
			 n为待求解的面值；
*/

bool compare(int v1, int v2)
{
	return v1 > v2;
}

int main()
{
	int arr[] = { 1, 3, 5 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int c = 11;

	//先由大到小排序: arr在这里隐式转化为指针,
	sort(arr, arr + length, compare);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	//负责索引选择的硬币
	int idx = 0;
	//记录选择硬币的个数
	int cnt = 0;

	while (c > 0)
	{
		if (c >= arr[idx])
		{
			c -= arr[idx];
			cnt++;
		}
		else
		{
			idx++;
		}
	}

	cout << "cnt = " << cnt << endl;
}

#endif
