#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
给定一个三角形，找出自顶向下的最小路径和，每一步只能移动到下一行中相邻的节点上
例如：给定三角形
{
0   	[2]
1      [3,4]
2     [6,5,7]
3    [4,1,8,3]
}
自顶向下最小路径和为11 (即:2+3+5+1=11)
*/

vector<int> v1 = { 2 };
vector<int> v2 = { 3, 4 };
vector<int> v3 = { 6, 5, 7};
vector<int> v4 = { 4, 1, 8, 3 };
vector<vector<int>> v = { v1, v2, v3, v4 };

int m = 3; //最后一行下标
int n = v4.size() - 1; //最长数组下标n=3

//4行4列
vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

/*
动态规划算法：
	dp[i][j]: i行, j列, dp[i][j]和值

状态转移方程:
	第m行末尾行没有子问题: 
		d[m][j] = v[m][j];
	第i, i+1, ... , m行
		dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + v[i][j];
*/
int func()
{
	for (int j = 0; j < v4.size(); j++)
	{
		dp[n][j] = v[n][j];
	}

	for (int i = m - 1; i >= 0; i--)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + v[i][j];
		}
	}
	return dp[0][0];
}


int main()
{
	func();

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int func(int i, int j)
{
	//递归结束条件：超出最后一行直接返回0
	if (i > m)
	{
		return 0;
	}
	else
	{
		//左边路径的和
		int left = func(i + 1, j);
		//右边路径的和
		int right = func(i + 1, j + 1);

		return v[i][j] + min(left, right); //返回当前选择的值 + 左右路径和的最小值
	}
}