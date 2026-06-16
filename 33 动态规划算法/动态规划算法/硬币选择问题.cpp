//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
///*
//硬币选择问题：有1，3，5分面额的硬币，给定一个面值11，问组成给定面值所需要的最少的硬币数量是多少？
//*/
//
///*
//	n为待求解的面值；
//	返回值为所需的最少硬币数量；
//*/
//const int n = 10;
//int dp[n+1] = { 0 };  //储面值 0 到面值 n 共 n+1 种情况的解
//int cnt = 0;
//
//int func(int n)
//{
//	//dp[n]这个子问题已经被求解过了，直接返回记录的值
//	if (dp[n] > 0)
//	{
//		cnt++;
//		return dp[n]; 
//	}
//
//	if (n == 1 || n == 3 || n == 5)
//	{
//		dp[n] = 1;
//		return 1;
//	}
//	else if (n == 2 || n == 4)
//	{
//		dp[n] = 2;
//		return 2;
//	}
//	else
//	{
//		int n1 = func(n - 1) + 1; //选择了1分硬币
//		int n2 = func(n - 3) + 1; //选择了3分硬币
//		int n3 = func(n - 5) + 1; //选择了5分硬币
//		dp[n] = min(min(n1, n2), n3);
//		return dp[n]; //选择最小的
//	}
//}
//
///*
//非递归求解
//状态转移方程：dp[i] = min{1 + dp[i - V[j]]}; i表示面值，V[j]表示第j个硬币的面额
//*/
//void func1(int n)
//{
//	//面额数组
//	int v[] = { 1, 3, 5 };
//	int len = sizeof(v) / sizeof(v[0]);
//	//存放重复子问题解的数组
//	int* dp = new int[n + 1];
//	//从 0 开始，逐个计算出 dp[0]、dp[1]、dp[2] ... dp[n]
//	for (int i = 0; i <= n; i++)
//	{
//		//初始化为最差情况：全部用1分硬币存储
//		dp[i] = i; 
//		//遍历所有可选的硬币面额（1 分、3 分、5 分）
//		for (int j = 0; j < len; j++)
//		{
//			//i >= v[j]：面值合法性判断; dp[i] > 1 + dp[i - v[j]]：最优性判断
//			if (i >= v[j] && dp[i] > 1 + dp[i - v[j]])
//			{
//				dp[i] = 1 + dp[i - v[j]];
//			}
//		}
//	}
//	cout << "num = " << dp[n] << endl;
//}
//
//int main()
//{
//	cout << "num = " << func(n) << endl;
//	cout << "cnt = " << cnt << endl;
//
//	func1(n);
//	return 0;
//}