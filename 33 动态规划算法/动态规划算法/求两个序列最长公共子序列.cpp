//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <string>
//
//using namespace std;
//
///*
//求两个序列最长公共子序列 
//
//X: X[1], X[2], ... , X[n]
//Y: Y[1], Y[2], ... , Y[m]
//
//
//状态方程：从末尾往前划分子问题
//X[n] == X[m]  LCS(X[n], Y[m]) = LCS(X[n-1], Y[m-1]) + 1;
//X[n] != Y[m]  LCS(X[n], Y[m]) = max(LCS(X[n], Y[m-1]), LCS(x[n-1], Y[m]))
//
//eg:
//X: helloworld
//Y: hlweorod
//*/
//
//
//
//string X = "helloworld";
//string Y = "hlweord";
//int lenX = X.size(); //数组长度 = 数组下标 + 1;
//int lenY = Y.size();
//
////记录子问题的解
//vector<vector<int>> dp(lenX, vector<int>(lenY, -1)); //nxm初始化为-1
///*
//    作用：记录递归的路径
//    path[][] = 1; 走对角线
//    path[][] = 2; 走左下方
//    path[][] = 3; 走右上方
//*/
//vector<vector<int>> path(lenX, vector<int>(lenY, 0));
//
//
//int cnt = 0;
//
//int LCS(string X, int n, string Y, int m)
//{
//    if (n < 0 || m < 0)
//    {
//        return 0;
//    }
//    //记忆化：该子问题已经算过，直接返回缓存结果
//    if (dp[n][m] >= 0)
//    {
//        return dp[n][m];
//    }
//    //记录递归次数
//    cnt++;
//    //末尾项相同
//    if (X[n] == Y[m])
//    {
//        dp[n][m] = LCS(X, n - 1, Y, m - 1) + 1;
//        path[n][m] = 1; //由[n][m] -> [n-1][m-1]
//        return dp[n][m];
//    }
//    else
//    {
//        int len1 = LCS(X, n, Y, m - 1);
//        int len2 = LCS(X, n - 1, Y, m);
//        dp[n][m] = max(len1, len2);
//
//        if (len1 >= len2)
//        {
//            path[n][m] = 2; //由[n][m] -> [n][m-1]
//        }
//        else
//        {
//            path[n][m] = 3; //由[n][m] -> [n-1][m]
//        }
//
//        return dp[n][m];
//    }
//}
//
////[递归]打印重复字符
//void backStrace(string X, int n, string Y, int m)
//{
//    //递归结束条件：n、m大于等于0继续递归;
//    if (n < 0 || m < 0)
//    {
//        return;
//    }
//
//    //开始递归
//    if (path[n][m] == 1)
//    {
//        backStrace(X, n - 1, Y, m - 1);
//        //由于是从尾项开始比较，所以应该在递归回溯过程打印
//        cout << X[n] << " ";
//    }
//    else if (path[n][m] == 2)
//    {
//        backStrace(X, n, Y, m - 1); //向左递归
//    }
//    else if (path[n][m] == 3)
//    {
//        backStrace(X, n - 1, Y, m); //向右递归
//    }
//}
//
//int main()
//{
//	cout << "LCS lenght：" << LCS(X, lenX - 1, Y, lenY - 1) << endl; //传入的是下标
//	cout << "cnt = " << cnt << endl;
//
//    //打印重复字符
//    cout << "最长公共子序列：";
//    backStrace(X, lenX - 1, Y, lenY - 1);  cout << endl;
//
//    cout << "dp:" << endl;
//    for (int i = 0; i < lenX; i++)
//    {
//        for (int j = 0; j < lenY; j++)
//        {
//            if (dp[i][j] == -1)
//            {
//                cout << "* ";
//            }
//            else 
//            {
//                cout << dp[i][j] << " ";
//            }
//        }
//        cout << endl;
//    }
//
//    cout << "path:" << endl;
//    for (int i = 0; i < lenX; i++)
//    {
//        for (int j = 0; j < lenY; j++)
//        {
//            cout << path[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//	return 0;
//}