#include <iostream>

using namespace std;

const int SIZE = 9;
int parent[SIZE];

//并查集-查询方法-递归实现
int rfind(int x)
{
	if (parent[x] == x)
	{
		return x;
	}
	return rfind(parent[x]);
}

//并查集-查询方法-非递归实现
int find(int x)
{
	while (x != parent[x])
	{
		x = parent[x];
	}
	return x;
}

//并查集-union合并方法
void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	//x和y原来不在一个集合中，才需要合并
	if (x != y)
	{
		//合并两个集合
		parent[y] = x;
	}
}

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	int x, y;
	for (int j = 0; j < 6; j++)
	{
		cin >> x >> y;
		merge(x, y);
	}

	//cout << (find(2) == find(4)) << endl;

	for (auto v : parent)
	{
		cout << v << " ";
	}
	cout << endl;
}