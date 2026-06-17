//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
///*
//求非降子序列长度：可以不连续
//时间复杂度: O(n^2)
//
//eg: 5 3 4 1 8 7 9
//状态方程：
//dp[0] = 1;
//dp[i] = max{1, dp[j] + 1};  条件：arr[i] >= arr[j]
//*/
//int main()
//{
//	int arr[] = { 5, 3, 4, 1, 8, 7, 9 };
//	const int n = sizeof(arr) / sizeof(arr[0]);
//
//	int dp[n] = { 0 };
//
//	dp[0] = 1;
//	int maxLen = dp[0]; //记录最长非降子段
//
//	//i: 当前元素, j: i之前的元素
//	for (int i = 1; i < n; i++)
//	{
//		//默认不构成子段，从当前位置起始
//		dp[i] = 1;
//		for (int j = 0; j < i; j++)
//		{
//			if (arr[i] >= arr[j])
//			{
//				dp[i] = max(dp[i], dp[j] + 1);
//			}
//		}
//		if (dp[i] > maxLen)
//		{
//			maxLen = dp[i];
//		}
//	}
//	cout << maxLen << endl;
//
//	return 0;
//}