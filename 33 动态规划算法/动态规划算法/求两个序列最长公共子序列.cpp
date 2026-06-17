#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/*
求两个序列最长公共子序列 

X: X[1], X[2], ... , X[n]
Y: Y[1], Y[2], ... , Y[m]


状态方程：从末尾往前划分子问题
X[n] == X[m]  LCS(X[n], Y[m]) = LCS(X[n-1], Y[m-1]) + 1;
X[n] != Y[m]  LCS(X[n], Y[m]) = max(LCS(X[n], Y[m-1]), LCS(x[n-1], Y[m]))


helloworld
hlweorod
*/

//分治算法
int cnt = 0;

int LCS(string X, int n, string Y, int m)
{
	if (n < 0 || m < 0)
	{
		return 0;
	}
	//记录递归次数
	cnt++;
	if (X[n] == Y[m])
	{
		return LCS(X, n - 1, Y, m - 1) + 1;
	}
	else
	{
		return max(LCS(X, n - 1, Y, m), LCS(X, n, Y, m-1));
	}
}

int main()
{
	string X = "helloworld";
	string Y = "hlweorod";
	int n = X.size() - 1;
	int m = Y.size() - 1;

	cout << "LCS lenght：" << LCS(X, n, Y, m) << endl;
	cout << "cnt = " << cnt << endl;

	return 0;
}