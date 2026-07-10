#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

//给unsigned int起别名为uint
using uint = unsigned int;
//定义无穷大
const uint INF = INT_MAX;

#if 0
//迪杰斯特拉算法
int Dijkstra(vector<vector<uint>>& graph, int start, int end)
{
	const int N = graph.size();
	//存储各个顶点的最短路径
	vector<uint> dis(N, 0);
	//S集合和U集合
	vector<bool> use(N, false);

	//把start放入S集合
	use[start] = true;

	//初始化start到其他U集合顶点权值
	for (int i = 0; i < N; i++)
	{
		dis[i] = graph[start][i];
	}
	//把U集合中顶点处理完
	for (int i = 1; i < N; i++)
	{
		//找到U集合中最小权值
		int k = -1;
		int min = INF;
		for (int j = 0; j < N; j++)
		{
			if (use[j] == false && min > dis[j])
			{
				min = dis[j];
				k = j;
			}
		}
		//k仍然等于-1说明U集合中没有元素了
		if (k == -1)
		{
			break;
		}
		//把选中的顶点加入到S集合中
		use[k] = true;
		//把U集合中剩余顶点权值信息更新
		for (int j = 0; j < N; j++)
		{
			if (use[j] == false && dis[j] > min + graph[k][j])
			{
				dis[j] = min + graph[k][j];
			}
		}
	}
	//测试打印
	for (int d : dis)
	{
		cout << d << " ";
	}
	return dis[end];
}
#endif

//迪杰斯特拉算法-优化
int Dijkstra(vector<vector<uint>>& graph, int start, int end)
{
	const int N = graph.size();
	//存储各个顶点的最短路径
	vector<uint> dis(N, 0);
	//S集合和U集合
	vector<bool> use(N, false);

	//把start放入S集合
	use[start] = true;

	//初始化start到其他U集合顶点权值 
	/*
		原时间复杂度 O(n) * O(2n) = O(n ^ 2)
		修改后：
		采用小根堆，priority_queue<pair<权值，顶点>>，避免每次遍历查找最小值
		时间复杂度： O(n) * O(logn) = O(nlogn)
	*/

	//给长类型起别名
	using node = pair<uint, int>;
	using container = vector<node>;
	using compare = greater<pair<uint, int>>;
	//小根堆，插入时间复杂度O(logn)
	priority_queue<node, container, compare> que;

	for (int i = 0; i < N; i++)
	{
		dis[i] = graph[start][i];
		que.emplace(dis[i], i);
	}

	//把U集合中顶点处理完
	for (int i = 1; i < N; i++)
	{
		//找到U集合中最小权值
		int k = -1;
		int min = INF;

		min = que.top().first;
		k = que.top().second;

		//k仍然等于-1说明U集合中没有元素了
		if (k == -1)
		{
			break;
		}
		//把选中的顶点加入到S集合中
		use[k] = true;
		//把U集合中剩余顶点权值信息更新
		for (int j = 0; j < N; j++)
		{
			if (use[j] == false && dis[j] > min + graph[k][j])
			{
				dis[j] = min + graph[k][j];
			}
		}
	}
	//测试打印
	for (int d : dis)
	{
		cout << d << " ";
	}
	return dis[end];
}

int main()
{
	//初始化邻接矩阵
	vector<vector<uint>> graph = 
	{
		{0, 6, 3, INF, INF, INF},
		{6, 0, 2, 5, INF, INF},
		{3, 2, 0, 3, 4, INF},
		{INF, 5, 3, 0, 2, 3},
		{INF, INF, 4, 2, 0, 5},
		{INF, INF, INF, 3, 5, 0}
	};

	int distance = Dijkstra(graph, 3, 5);
}