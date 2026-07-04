#if 0

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
0-1背包：
有一组物品，其重量为：w1, w2, ... , wn; 其价值为v1, v2, ... , vn; 
背包容量为capacity，如何把物品装入背包，能够使得背包价值最大化？

动态规划问题两个要素：
（1）最优子结构性质：最优解包含着其子问题的最优解
（2）重复子问题：子问题被重复计算

状态[描述子问题最优解的性质]：重量、价值、背包容量
  dp[i][j]:背包存放物品的价值  
  i:所选物品的范围i, ... , n
  j:背包的剩余容量

状态转移方程[由子问题的最优解如何合并出原问题的最优解]:
  i == n：只考虑wn物品; 
    wn > j：无法装入背包; dp[n][j] = 0;
    wn <= j: 可以装入背包; dp[n][j] = vn;
  i, i+1, i+2, ... , n是可选物品
    wi > j: 说明第i个物品无法装入背包; dp[i][j] = dp[i+1][j];
               dp[i+1][j]表示可选物品为i+1, i+2, ... , n的子问题     
    wi <= j: 说明第i个物品可以装入背包; dp[i][j] = max(dp[i+1][j], v1 + dp[i+1][j-wi])
               dp[i+1][j]表示未装入,
               v1 + dp[i+1][j-wi]表示装入背包,
               要选择二者的最大值;
               背包容量是稀缺资源，装入物品是有"机会成本"的: 放了第 i 个物品，就会占用wi的容量，这部分容量本来可以用来装其他更值钱的物品。


               容量
i     No       0 1 2 3 4 5 6  7  8  9  10 11 12   ⬆由下往上看, →由左往右看
  
0     1(8, 6)  0 0 8 8 8 8 15 15 15 15 15 21 21   no
1     2(6, 4)  0 0 8 8 8 8 15 15 15 15 15 21 21   no
2     3(4, 7)  0 0 8 8 8 8 15 15 15 15 15 21 21   yes  余5-4=1
3     4(2, 8)  0 0 8 8 8 8 8  14 14 14 14 14 14   yes  余7-2=5
4     5(5, 6)  0 0 0 0 0 6 6  6  6  6  6  6  6    yes  余12-5=7
*/

//物品重量
int w[] = { 8, 6, 4, 2, 5 };
//物品价值
int v[] = { 6, 4, 7, 8, 6 };
//背包容量
int capacity = 12;

const int N = sizeof(w) / sizeof(w[0]) - 1; //物品末尾下标4

//dp[5][13]: 5行, 13列; 行下标: 0-4行, 列下标: 0-12列;
vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

int Backpack(int n, int c)
{
    //背包没有物品, 先装下标为n物品: 末尾物品
    for (int j = 1; j <= c; j++) //1 - 12; 0不用考虑, 没容量, 任何物品都装不进去
    {
        if (w[n] > j)
        {
            dp[n][j] = 0; 
        }
        else if (w[n] <= j)
        {
            dp[n][j] = v[n];
        }
    }
    //背包已经有物品, 考虑下标范围为0 - 3的物品
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= c; j++)
        {
            if (w[i] > j)
            {
                dp[i][j] = dp[i + 1][j];
            }
            else if (w[i] <= j)
            {
                dp[i][j] = max(dp[i + 1][j], v[i] + dp[i + 1][j - w[i]]);
            }
        }
    }
    return dp[0][c];
}

//打印找到的最优物品
void backStrace(int n, int c)
{
    //处理下标0-3; 单独处理下标4, 其后面没有元素, 一起处理会越界
    for (int i = 0; i < n; i++)
    {
        if (dp[i][c] != dp[i + 1][c])
        {
            cout << w[i] << " ";
            c -= w[i];  //更新剩余容量
        }
    }
    //单独处理末尾物品
    if (c >= w[n])
    {
        cout << w[n] << endl;
    }
}

int main()
{
    cout << "max value: " << Backpack(N, capacity) << endl;
    backStrace(N, capacity);

    //打印dp数组: 0-4行, 0-12列
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
#endif


#if 0

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
状态转移方程[由子问题的最优解如何合并出原问题的最优解]:
1, ... , i, i+1, i+2, ... , n是可选物品
    wi > j: 说明第i个物品无法装入背包; dp[i][j] = dp[i-1][j];
               dp[i-1][j]表示可选物品为0,1, ... , i-1的子问题     
    wi <= j: 说明第i个物品可以装入背包; dp[i][j] = max(dp[i-1][j], v[i-1] + dp[i-1][j - w[i-1]]);
               dp[i-1][j]表示未装入,
               v[i-1] + dp[i-1][j - w[i-1]]表示装入背包,
               要选择二者的最大值;

i No      0 1 2 3 4 5 6  7  8  9  10 11 12   
0         0 0 0 0 0 0 0  0  0  0  0  0  0
1 1(8, 6) 0 0 0 0 0 0 0  0  6  6  6  6  6
2 2(6, 4) 0 0 0 0 0 0 4  4  6  6  6  6  6
3 3(4, 7) 0 0 0 0 7 7 7  7  7  7  11 11 13
4 4(2, 8) 0 0 8 8 8 8 15 15 15 15 15 15 19
5 5(5, 6) 0 0 8 8 8 8 15 15 15 15 15 21 21   

*/
               
//物品重量
int w[] = { 8, 6, 4, 2, 5 };
//物品价值
int v[] = { 6, 4, 7, 8, 6 };
//背包容量
int capacity = 12;

const int N = sizeof(w) / sizeof(w[0]); //物品个数5

//dp[66][13]: 6行, 13列; 行下标: 0-5行, 列下标: 0-12列;
vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

int Backpack(int n, int c)
{
    //考虑第1-5个物品
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (w[i-1] > j)
            {
                dp[i][j] = dp[i-1][j] ;
            }
            else if (w[i-1] <= j)
            {
                dp[i][j] = max(dp[i-1][j], v[i-1] + dp[i-1][j - w[i-1]]);
            }
        }
    }
    return dp[n][c];
}

//打印找到的最优物品
void backStrace(int n, int c)
{
    //处理第1-5个物品; 
    for (int i = n; i >= 1; i--)
    {
        if (dp[i][c] != dp[i-1][c])
        {
            cout << w[i-1] << " "; //倒序输出
            c -= w[i-1];
        }
    }
    cout << endl;
}

int main()
{
    cout << "max value: " << Backpack(N, capacity) << endl;
    backStrace(N, capacity);

    //打印dp数组: 0-4行, 0-12列
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

#endif