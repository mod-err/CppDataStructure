/*
部分背包问题：有n个物体，第i个物体的重量为wi，价值为vi。在总重量不超过c的情况下让总价更高。
每一个物体都可以只取走一部分，价值和重量按比例计算。求最大总价值。
*/

#if 0

#include <iostream>
#include <algorithm>

using namespace std;

//物品重量
int w[] = { 8, 6, 4, 2, 5 };
//物品价值
int v[] = { 6, 4, 7, 8, 6 };
//物品个数
const int num = sizeof(w) / sizeof(w[0]);
//背包容量
int capacity = 12;

//定义物品类, 用于比较性价比
struct Product
{
	//计算物品价值
	double getPrice() const
	{
		return value * 1.0 / weight;
	}
	//重载 > 运算符
	bool operator > (const Product& p) const
	{
		return this->getPrice() > p.getPrice();
	}
	int id; //物品的id
	int weight; //物品的重量
	int value;  //物品的价值
};

bool compare(const Product& v1, const Product& v2)
{
	return v1 > v2;  //v1 > v2 等价于v1.operator>(v2); 这里调用重载的 operator>
}

int main()
{
	Product p[num];
	for (int i = 0; i < num; i++)
	{
		p[i].id = i;
		p[i].weight = w[i];
		p[i].value = v[i];
	}

	//先按照性价比进行排序
	sort(p, p + num, compare);

	//按照性价比高低顺序往背包中放(只考虑局部最优解)
	int idx = 0;
	double best_value = 0.0; //最优价值
	int r[num] = { 0 }; //记录可以被放入的物品

	while (capacity > 0)
	{
		if (p[idx].weight <= capacity)
		{
			best_value += p[idx].value; //计算价值
			r[p[idx].id] = p[idx].weight; //在物品原的id位置写入物品重量
			capacity -= p[idx].weight;  //更新背包容量
		}
		else
		{
			best_value += p[idx].getPrice() * capacity; //计算可以存放部分物品的价值
			r[p[idx].id] = p[idx].weight;
			break; //走到存放部分物品说明背包容量不足，直接跳出循环
		}
		idx++;
	}
	
	cout << best_value << endl;

	//记录可以被放入的物品
	for (int x : r)
	{
		cout << x << " ";
	}
	cout << endl;
	
	return 0;
}

#endif