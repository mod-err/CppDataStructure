//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
///*
//	n代表第几项
//	返回值为第几项的结果
//*/
//const int N = 10;
//int dp[N + 1] = { 0 };
//int cnt = 0;
//
////int fibonacci(int n)
////{
////	if (dp[n] > 0)
////	{
////		cnt++;
////		return dp[n];
////	}
////	if (n == 0)
////	{
////		dp[n] = 0;
////		return 0;
////	}
////	else if (n == 1 || n == 2)
////	{
////		dp[n] = 1;
////		return 1;
////	}
////	else 
////	{
////		dp[n] = fibonacci(n - 1) + fibonacci(n - 2);
////		return dp[n];
////	}
////}
//
//int fibonacci(int n) 
//{
//	dp[0] = 0;
//	dp[1] = dp[2] = 1;
//	for (int i = 3; i <= n; i++)
//	{
//		dp[i] = dp[i - 1] + dp[i - 2];
//	}
//	return dp[n];
//}
//
//int main()
//{
//	cout << fibonacci(N) << endl;
//	cout << "cnt = " << cnt << endl;
//	return 0;
//}