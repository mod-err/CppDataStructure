//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//int main()
//{
//	int arr[] = { -5, -10, 6, 3, -1 };
//	int n = sizeof(arr) / sizeof(arr[0]);
//
//	/*
//	n是变量，无法直接用于初始化数组;
//	除非写做const int n; 才可以 int arr[n];
//	这里初始化dp[n]数组, 不使用n+1; 因为传入的就是下标;
//	*/
//	int* dp = new int[n](); //()默认初始化为0; 
//
//	dp[0] = arr[0] < 0 ? 0 : arr[0]; //dp[0]就是和，如果arr[0]小于0，直接把和置为0
//	int max = dp[0]; //最大子段和
//	/*
//	状态方程：dp[i] = arr[i] + dp[i - 1];
//	*/
//	for (int i = 1; i < n; i++)
//	{
//		dp[i] = arr[i] + dp[i - 1];
//		//保证和小于0时，置为0；同时实现子段和
//		if (dp[i] < 0)
//		{
//			dp[i] = 0;
//		}
//		if (dp[i] > max)
//		{
//			max = dp[i];
//		}
//	}
//	cout << max << endl;
//
//	delete[] dp;
//	return 0;
//}