#if 0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 10005;
int parent[SIZE];

struct Road
{
	Road(int u, int v, int w)
		: u_(u)
		, v_(v)
		, w_(w)
	{}
	bool operator < (const Road& road) const 
	{
		return this->w_ < road.w_;
	}
	int u_; //路连接u区
	int v_; //路连接v区
	int w_; //路径拥挤度
};

int find(int x)
{
	if (parent[x] == x)
	{
		return x;
	}
	return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y)
	{
		parent[x] = y;
	}
}

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	vector<Road> roads;

	int n, m, s, t;  //n个区，m条路，从s到t区拥挤度最大值最小
	cin >> n >> m >> s >> t;

	int u, v, w; //u区，v区，拥挤度w
	for (int j = 0; j < m; j++)
	{
		cin >> u >> v >> w; 
		roads.emplace_back(u, v, w);
	}

	sort(roads.begin(), roads.end(), less<Road>());

	//测试排序输出
	cout << "---------------------" << endl;
	for (const auto& e : roads) {
		cout << e.u_ << " " << e.v_ << " " << e.w_ << endl;
	}


	for (int i = 0; i < roads.size(); i++)
	{
		merge(roads[i].u_, roads[i].v_);
		if (find(s) == find(t))
		{
			cout << roads[i].w_ << endl;
			break;
		}
		// cout << roads[i].u_ << " -> " << roads[i].v_ << " cost:" << roads[i].w_ << endl;
	}
}

#endif