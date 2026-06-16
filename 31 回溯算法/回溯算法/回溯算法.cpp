#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//子集树
/*
	arr[]：待操作数据
	i：数据起始下标
	len：数据长度
	x[len]：子集树辅助数组，记录节点走向左孩子还是有孩子，左子孩子标为1，右子孩子标为0
*/
#if 0
void func(int arr[], int i, int len, int x[])
{
	if (i == len)
	{
		for (int j = 0; j < len; j++)
		{
			if (x[j] == 1)
			{
				cout << arr[j] << " ";
			}
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;
		func(arr, i + 1, len, x);

		x[i] = 0;
		func(arr, i + 1, len, x);
	}
}

int main()
{
	int arr[] = { 1, 2, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	int x[3] = { 0 };
	func(arr, 0, len, x);
}
#endif

#if 0
/*
整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差值最小
*/

int arr[] = {12, 6, 7, 11, 16, 3, 9};
const int len = sizeof(arr) / sizeof(arr[0]);
int x[len] = { 0 };
unsigned int minOut = 0xFFFFFFFF; //记录最小的差值
int sum1 = 0;  //记录选中数组和
int sum2 = 0;  //记录未选择数组和
int xMin[len] = {0}; //记录最小子集

//代码2：构建子集树-时间复杂度O(2^n)，2^n个子集；在递归过程中，计算和，而不是走到叶子节点再计算
void func(int arr[], int i, int len, int x[])
{
	if (i == len)
	{
		int result = abs(sum1 - sum2);
		if (result < minOut)
		{
			minOut = result;
			for (int j = 0; j < len; j++)
			{
				xMin[j] = x[j];
			}
		}
	}
	else
	{
		//深度优先搜一条路 → 走到头 → 退回来还原现场 → 再搜另一条路
		sum2 -= arr[i];
		sum1 += arr[i];
		x[i] = 1;
		func(arr, i + 1, len, x);
		sum1 -= arr[i];
		sum2 += arr[i];

		x[i] = 0;
		func(arr, i + 1, len, x);
	}
}

int main()
{
	//算出未选择数字和
	for (int v : arr)
	{
		sum2 += v;
	}

	func(arr, 0, len, x);

	for (int i = 0; i < len; i++)
	{
		if (xMin[i] == 1)
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
	cout << "min" << minOut << endl;
}


//代码1：构建子集树-时间复杂度O(n * 2^n)，2^n个子集
void func(int arr[], int i, int len, int x[])
{
	if (i == len)
	{
		for (int j = 0; j < len; j++) //O(n)
		{
			if (x[j] == 1)
			{
				sum1 += arr[j];
			}
			else
			{
				sum2 += arr[j];
			}
		}
		vec.push_back(abs(sum1 - sum2));
		cout << sum1 << "+" << sum2 << "=" << sum1 + sum2 << " "
			 << sum1 << "-" << sum2 << "=" << abs(sum1 - sum2) << endl;
	}
	else   
	{
		x[i] = 1;
		func(arr, i + 1, len, x);
		x[i] = 0;
		func(arr, i + 1, len, x);
	}
}

int main() 
{
	func(arr, 0, len, x);

	int min = vec[0];
	for (int v : vec)
	{
		if (v < min)
		{
			min = v;
		}
	}
	cout << "最小差值为：" << min << endl;
}
#endif

#if 0
/*
整数选择问题：给定2n整数，从里面挑选出n个整数，让选择的整数的和，和剩下的整数的和的差值最小
*/

int arr[] = { 12, 6, 7, 11, 16, 3, 9, 4 };
const int len = sizeof(arr) / sizeof(arr[0]);
unsigned int minOut = 0xFFFFFFFF; //记录最小差值
vector<int> vec;     //记录子集中选择的数字
vector<int> bestvec; //记录最优子集
int sum1 = 0; //选择的数字和
int sum2 = 0; //未选择的数字和
int cnt = 0;  //记录递归到达叶子节点次数
int leftcnt = len; //记录未处理的数字的个数

//构建子集树
void func(int arr[], int i, int len)
{
	if (i == len)
	{
		cnt++; //到达叶子节点

		if (vec.size() != len / 2)
		{
			return;
		}

		int result = abs(sum1 - sum2);
		if (result < minOut)
		{
			minOut = result;
			bestvec = vec;
		}
	}
	else
	{
		leftcnt--;  //表示剩余的未处理的元素的个数
		//进行左子树剪枝：如果还未选择够n个整数，继续选择
		if (vec.size() < len / 2)
		{
			sum2 -= arr[i];
			sum1 += arr[i];
			vec.push_back(arr[i]);
			func(arr, i + 1, len);
			vec.pop_back();
			sum1 -= arr[i];
			sum2 += arr[i];
		}

		//进行右子树剪枝：已选择的数字的个数 + 未来能选择的所有数字个数 >= n
		if (vec.size() + leftcnt >= len / 2)
		{
			func(arr, i + 1, len);
		}
		leftcnt++; //当前i节点已处理完成，回溯到其父节点了
	}
}

int main()
{
	for (int v : arr)
	{
		sum2 += v;
	}

	func(arr, 0, len);

	for (int v : bestvec)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min = " << minOut << endl;
	cout << "cnt = " << cnt << endl;
}
#endif

#if 0
/*
挑选数组：有一组整数，挑选出一组数字，让其和等于指定的值，存在解打印，不存在不打印
*/
int arr[] = { 4, 8, 12, 16, 7, 9, 3 };
const int len = sizeof(arr) / sizeof(arr[0]);
int number = 18;

vector<int> vec; //记录所选数字
int sum = 0;  //记录所选数字和
int cnt = 0;  //记录递归到达叶子节点次数
int remainSum = 0;  //记录未处理的数字的和

//构建子集树
void func(int arr[], int i, int len)
{
	if (i == len)
	{
		cnt++;
		// 判断不满足，提前return
		if (sum != number)
		{
			return;
		}

		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
		cout << "sum = " << sum << endl;
	}
	else
	{
		//处理当前节点，不能放在if内，if是判断选择不选择，处理是不管选择还是不选择都算处理
		remainSum -= arr[i];
		//左子树剪枝：已经计算的和+当前要选的数字 <= 要求的和 才有继续遍历的必要
		if (sum + arr[i] <= number)
		{
			sum += arr[i];
			vec.push_back(arr[i]);
			func(arr, i + 1, len);
			vec.pop_back();
			sum -= arr[i];
		}

		//右子树剪枝：当前和 + 余下的数字和 >= 要求的和; 才有继续遍历的必要
		if (sum + remainSum >= number)
		{
			func(arr, i + 1, len);
		}
		//回溯到父节点，更新变量状态为未处理
		remainSum += arr[i];
	}
}

int main()
{
	for (int v : arr)
	{
		remainSum += v;
	}

	func(arr, 0, len);

	cout << "cnt = " << cnt << endl;
}
#endif

#if 0
/*
挑选数组：有一组整数，挑选出一组数字，让其和等于指定的值，存在解打印，不存在不打印
*/
int arr[] = { 4, 8, 12, 16, 7, 9, 3 }; 
const int len = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> vec; //记录所选数字

void func(int i, int sum)
{
	//达到目标和，提前返回
	if (sum == number)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
		cout << "sum = " << sum << endl;
	}
	else
	{
		for (int k = i; k < len; k++)
		{
			//进行剪枝操作：已经计算的和 + 当前要选择的数字 <= 最终要求和，才继续！
			//注意：必须是<=，如果只写 < 会过滤掉正确结果
			if (sum + arr[k] <= number)
			{
				vec.push_back(arr[k]);
				//不允许选择的数字有重复
				func(k + 1, sum + arr[k]);
				//允许选择的数字有重复
				//func(k, sum + arr[k]);
				vec.pop_back();
			}
		}
	}
}

int main()
{
	func(0, 0);
}
#endif

#if 0
/*
0-1背包问题：
    有一组物品，其重量分别是：w1, w2,...wn; 其价值分别是v1, v2,...vn;
    现在有一个背包，其容量是C，如何把物品装入背包，能够使得背包价值最大化？
*/

int w[] = { 12, 5, 8, 9, 6 }; //物品的重量
int v[] = { 9, 11, 4, 7,8 };  //物品的价值
int c = 20; //背包容量

const int len = sizeof(w) / sizeof(w[0]); 

int totalWeight = 0; //总重量
int totalValue = 0;  //总价值
int maxValue = 0;    //最大价值
vector<int> goods;   //选择的物品
vector<int> bestgoods; //选择最优的物品
int remainValue;     //剩余物品的价值
int cnt = 0;

//构建子集树
void func(int i)
{
	if (i == len)
	{
		cnt++;
		if (totalValue > maxValue)
		{
			maxValue = totalValue;
			bestgoods = goods; //拷贝最优解时选择的物品
		}
		
	}
	else
	{
		//处理当前节点，减去当前节点价值
		remainValue -= v[i];
		//左子树剪枝：已经计算的总重量 + 当前物品重量 < 限制重量; 才有必要继续遍历
		if (totalWeight + w[i] < c)
		{
			totalWeight += w[i];
			totalValue += v[i];
			goods.push_back(w[i]);
			func(i + 1);
			goods.pop_back();
			totalValue -= v[i];
			totalWeight -= w[i];
		}
		//右子树剪枝：已经计算的总价值 + 剩余还未计算的价值 > 已经计算的最大价值; 才有必要继续遍历
		if (totalValue + remainValue > maxValue)
		{
			func(i + 1);
		}
		//回溯到父节点，还原当前节点价值
		remainValue += v[i];
	}
}

int main()
{
	//所有物品价值和
	for (int y : v)
	{
		remainValue += y;
	}

	func(0);

	for (int x : bestgoods)
	{
		cout << x << " ";
	}
	cout << endl;

	cout << "maxValue = " << maxValue << endl;
	cout << cnt << endl;
	return 0;
}
#endif

/*
解空间-排列树：求解原始数据的排列树
*/

#if 0
void swap(int arr[], int i, int k)
{
	int temp = arr[i];
	arr[i] = arr[k];
	arr[k] = temp;
}

void func(int arr[], int i, int len)
{
	if (i == len)
	{
		for (int j = 0; j < len; j++)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < len; k++)
		{
			swap(arr, i, k);  //交换i指向的元素和k指向的元素
			func(arr, i + 1, len);
			swap(arr, i, k);  //回溯过程中还原状态
		}
	}
}


int main() 
{
	int arr[] = { 1, 2, 3, 4 };
	int len = sizeof(arr) / sizeof(arr[0]);

	func(arr, 0, len);
}
#endif

/*
八皇后问题：8x8的棋盘，8个皇后摆放的位置不在同一行、同一列、同一斜线
*/

#if 0
int cnt = 0;

//棋子摆放的位置是否符合要求
bool isPlaceOK(int arr[], int i)
{
	for (int j = 0; j < i; j++)
	{
		//不在同行、同列、同斜线(通过行列差值是否相同判断)
		if (i == j || arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]))
		{
			return false;
		}
	}
	return true;
}

void swap(int arr[], int i, int k)
{
	int temp = arr[i];
	arr[i] = arr[k];
	arr[k] = temp;
}

void func(int arr[], int i, int len)
{
	if (i == len)
	{
		cnt++;
		for (int j = 0; j < len; j++)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else 
	{
		for (int k = i; k < len; k++)
		{
			swap(arr, i, k);
			if (isPlaceOK(arr, i))
			{
				func(arr, i + 1, len);
			}
			swap(arr, i, k); //回溯过程中还原现场
		}
	}
}

int main()
{
	//下标代表行，对应元素代表列
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int len = sizeof(arr) / sizeof(arr[0]);

	func(arr, 0, len);
	cout << cnt << endl;
}
#endif

/*
穷举法求排列树
*/

vector<int> vec;
bool state[3];

void func(int arr[], int i, int len)
{
	if (i == len)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = 0; k < len; k++)
		{
			if (state[k] == false)
			{
				state[k] = true;
				vec.push_back(arr[k]);
				func(arr, i + 1, len); //k表示可选择的元素的起始下标，i表示层数
				vec.pop_back();
				state[k] = false;
			}
		}
	}
}


int main()
{
	int arr[] = { 1, 2, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);

	func(arr, 0, len);
}

