#if 0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const int SIZE = 100;
int parent[SIZE];

//边
struct Edge
{
	Edge(int begin, int end, int cost)
		: begin_(begin)
		, end_(end)
		, cost_(cost)
	{
	}
	bool operator<(const Edge& edge) const
	{
		return this->cost_ < edge.cost_;
	}
	int begin_; //起点
	int end_;   //终点
	int cost_;   //权值
};

//从配置文件读取图的信息
void readFile(string filepath, vector<Edge>& edges)
{
	ifstream ifs;

	ifs.open(filepath, ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	string line;
	//读取第一行：顶点个数
	getline(ifs, line);
	int n = stoi(line);

	//循环读取剩余的每一行
	while (getline(ifs, line))
	{
		if (line.empty())
		{
			continue; //跳过空行
		}
		stringstream ss(line);
		char begin;
		char end;
		int cost;
		//直接用>>提取，空格会自动跳过
		ss >> begin >> end >> cost; 
		//char是整型类型,传递给int参数时会进行隐式提升;'A'会变为65，'B'为66
		edges.emplace_back(begin, end, cost);
	}
	ifs.close();
}

int find(int x)
{
	if (x == parent[x])
	{
		return x;
	}
	return parent[x] = find(parent[x]);
}

void merge(vector<Edge>& edges, int idx)
{
	int x = find(edges[idx].begin_);
	int y = find(edges[idx].end_);
	if (x != y)
	{
		parent[x] = y;
		printf("%c -> %c cost:%d \n", edges[idx].begin_, edges[idx].end_, edges[idx].cost_);
	}
}


int main()
{
	//初始化parent[]数组
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	//存储边的数组
	vector<Edge> edges;

	readFile("graph.txt", edges);

	//所有的边按照权值大小进行排序
	sort(edges.begin(), edges.end(), less<Edge>());

	//测试输出
	for (const auto& e : edges) {
		cout << e.begin_ << " " << e.end_ << " " << e.cost_ << endl;
	}

	// 开始选边（按小到大进行选择）
	for (int i = 0; i < edges.size(); i++)
	{
		merge(edges, i);
	}

	return 0;
}
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const int SIZE = 100;
int parent[SIZE];

//边
struct Edge
{
	Edge(int begin, int end, int cost)
		: begin_(begin)
		, end_(end)
		, cost_(cost)
	{
	}
	bool operator<(const Edge& edge) const
	{
		return this->cost_ < edge.cost_;
	}
	char begin_; //起点
	char end_;   //终点
	int cost_;   //权值
};

//从配置文件读取图的信息
void readFile(string filepath, vector<Edge>& edges)
{
	ifstream ifs;

	ifs.open(filepath, ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	string line;
	//读取第一行：顶点个数
	getline(ifs, line);
	int n = stoi(line);

	//循环读取剩余的每一行
	while (getline(ifs, line))
	{
		if (line.empty())
		{
			continue; //跳过空行
		}
		stringstream ss(line);
		char begin;
		char end;
		int cost;
		ss >> begin >> end >> cost; // 直接用>>提取，空格会自动跳过
		edges.emplace_back(begin, end, cost);
	}
	ifs.close();
}

int find(int x)
{
	if (x == parent[x])
	{
		return x;
	}
	return parent[x] = find(parent[x]);
}

void merge(vector<Edge>& edges, int idx)
{
	int x = edges[idx].begin_;
	int y = edges[idx].end_;
	x = find(x);
	y = find(y);
	if (x != y)
	{
		parent[x] = y;
		cout << edges[idx].begin_ << " -> " << edges[idx].end_ << " cost:" << edges[idx].cost_ << endl;
		//printf("%c -> %c cost:%d \n", edges[idx].begin_, edges[idx].end_, edges[idx].cost_);
	}
}


int main()
{
	//初始化parent[]数组
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	//存储边的数组
	vector<Edge> edges;

	readFile("graph.txt", edges);

	//所有的边按照权值大小进行排序
	sort(edges.begin(), edges.end(), less<Edge>());

	//测试输出
	for (const auto& e : edges) {
		cout << e.begin_ << " " << e.end_ << " " << e.cost_ << endl;
	}

	// 开始选边（按小到大进行选择）
	for (int i = 0; i < edges.size(); i++)
	{
		merge(edges, i);
	}
	return 0;
}


