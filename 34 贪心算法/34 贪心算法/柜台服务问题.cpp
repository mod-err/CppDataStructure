/*
柜台服务问题：
n个柜台提供服务，每个柜台给一个用户提供服务的时间是t(用数组表示每一个柜台提供服务的时长)。
问怎么排列，使得柜台给所有用户提供服务的时间最少。
*/

#include <iostream>
#include <algorithm>

using namespace std;

//定义排序规则的仿函数
bool compare(int v1, int v2)
{
	return v1 > v2;
}

//每个柜台提供服务的时间
int arr[] = { 2, 3, 4 };
const int len = sizeof(arr) / sizeof(arr[0]);

//办理业务的人数
int n = 15;

//记录每个柜台服务的人数
int s[len] = { 0 }; 

//记录所有人办理完所耗费的时间
int min_time = 0;

//记录最小的边际成本
int min_cost = 0;

int main()
{
	sort(arr, arr + len, compare);

	for (int i = 0; i < 15; i++)
	{
		//记录最小的边际成本
		min_cost = arr[0] * (s[0] + 1);
		//记录最小边际成本柜台编号
		int idx = 0;
		//每增加一个人，每个柜台的边际成本
		for (int j = 1; j < len; j++)
		{
			if (min_cost > arr[j] * (s[j] + 1))
			{
				min_cost = arr[j] * (s[j] + 1);
				idx = j;
			}
		}
		s[idx]++;
	}

	//得出最后一个顾客服务完成耗时
	for (int k = 0; k < len; k++)
	{
		min_time = max(min_time, arr[k] * s[k]);
		cout << arr[k] << ": " << s[k] << endl;
	}

	cout << min_time << endl;

	return 0;
}
