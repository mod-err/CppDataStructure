#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string X = "helloworld";
string Y = "hlweord";
int lenX = X.size(); //数组长度 = 数组下标 + 1;
int lenY = Y.size();

//记录子问题的解
vector<vector<int>> dp(lenX, vector<int>(lenY, -1)); //nxm初始化为-1
//记录查找路径
vector<vector<int>> path(lenX, vector<int>(lenY, 0));

//[非递归]查找
int LCS(string X, int n, string Y, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (X[i-1] == Y[j-1])
            {
                // 末尾字符相同，继承左上角的结果+1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                // 末尾不同，取“删X末尾”和“删Y末尾”的最大值
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

//[非递归]打印重复字符
void backStrace(string X, int n, string Y, int m)
{

}

int main()
{
    cout << "LCS lenght：" << LCS(X, lenX - 1, Y, lenY - 1) << endl; //传入的是下标

    //打印重复字符
    cout << "最长公共子序列：";
    //backStrace(X, lenX - 1, Y, lenY - 1);  cout << endl;

    return 0;
}