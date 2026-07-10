//#include <iostream>
//#include <list>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <queue>
//
//using namespace std;
//
////实现一个有向图的邻接表结构
//class Digraph
//{
//private:
//	//顶点
//	struct Vertic
//	{
//		Vertic(string data)
//			: data_(data)
//		{}
//		string data_;		//存储顶点信息
//		list<string> adjList_; //邻接链表结构
//	};
//	vector<Vertic> vertics_; //顶点集合
//public:
//	//从配置文件读取图的信息
//	void readFile(string filePath)
//	{
//		ifstream ifs;
//		ifs.open(filePath, ios::in);
//		if(!ifs.is_open())
//		{
//			cerr << "文件打开失败" << endl;
//			return;
//		}
//
//		//占用0号位置
//		vertics_.emplace_back("");
//
//		string buff;
//		while (getline(ifs, buff))
//		{
//			//跳过空行
//			if (buff.empty())
//			{
//				continue;
//			}
//
//			//查找' '，没找到说明后面没东西
//			int pos1 = buff.find(' ');
//			if (pos1 == string::npos)
//			{
//				vertics_.emplace_back(buff);
//				buff.erase(0, pos1);  //清空字符串，避免其对后面出边产生影响
//			}
//			else
//			{
//				vertics_.emplace_back(buff.substr(0, pos1));
//				buff = buff.substr(pos1 + 1);
//			}
//			
//			while (!buff.empty())
//			{
//				int pos = buff.find(',');
//
//				if(pos != string::npos)
//				{ 
//					vertics_.back().adjList_.emplace_back(buff.substr(0, pos));
//					buff = buff.substr(pos + 1);
//				}
//				else
//				{
//					// 没有逗号了，说明是最后一个元素
//					vertics_.back().adjList_.emplace_back(buff);
//					break;
//				}
//			}
//
//		}
//		ifs.close();
//	}
//	//输出邻接表信息
//	void show() const
//	{
//		for (int i = 1; i < vertics_.size(); i++)
//		{
//			cout << vertics_[i].data_ << " : ";
//			for (auto no : vertics_[i].adjList_)
//			{
//				cout << no << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	//深度优先遍历
//	void dfs()
//	{
//		vector<bool> visited(vertics_.size(), false);
//		cout << "深度优先遍历：";
//		dfs(1, visited);
//		cout << endl;
//	}
//	//广度优先遍历
//	void bfs()
//	{
//		vector<bool> visited(vertics_.size(), false);
//
//		queue<int> que;
//		que.push(1);
//		visited[1] = true;
//
//		cout << "广度优先遍历：";
//
//		while (!que.empty())
//		{
//			int front = que.front();
//			que.pop();
//
//			cout << vertics_[front].data_ << " ";
//
//			//当前顶点的出边顶点
//			for (auto it : vertics_[front].adjList_)
//			{
//				if (visited[stoi(it)] == false)
//				{
//					que.push(stoi(it));
//					visited[stoi(it)] = true;
//				}
//			}
//		}
//		cout << endl;
//	}
//	// 不带权值的最短路径问题
//	void shortPath(int begin, int end)
//	{
//		vector<bool> visited(vertics_.size(), false);
//
//		queue<int> que;
//		que.push(begin);
//		visited[begin] = true;
//
//		vector<int> path(vertics_.size(), 0);
//
//		while (!que.empty())
//		{
//			int front = que.front();
//			//到达路径末尾顶点
//			if (front == end)
//			{
//				break;
//			}
//
//			que.pop();
//
//			for (auto it : vertics_[front].adjList_)
//			{
//				if (visited[stoi(it)] == false)
//				{
//					que.push(stoi(it));
//					visited[stoi(it)] = true;
//					//记录 到 当前顶点 来的顶点
//					path[stoi(it)] = front;
//				}
//			}
//		}
//
//		if (!que.empty())
//		{
//			//存在最短路径
//			/*
//			while (end != 0)
//			{
//				cout << vertics_[end].data_ << " <= ";
//				end = path[end];
//			}
//			*/
//			showPath(end, path);
//		}
//		else
//		{
//			cout << "不存在最短路径！" << endl;
//		}
//		cout << endl;
//	}
//private:
//	//深度优先遍历递归实现
//	void dfs(int start, vector<bool>& visited)
//	{
//		if (visited[start] == true)
//		{
//			return;
//		}
//
//		//当前节点
//		cout << vertics_[start].data_ << " ";
//		visited[start] = true;
//
//		for (auto it : vertics_[start].adjList_)
//		{
//			//stoi把string转int
//			dfs(stoi(it), visited);
//		}
//	}
//	//打印不带权值最短路径
//	void showPath(int end, vector<int>& path)
//	{
//		//递归结束条件
//		if (end == 0)
//		{
//			return;
//		}
//		
//		showPath(path[end], path);
//		//回溯过程打印
//		cout << vertics_[end].data_ << " => ";
//	}
//};
//
//int main()
//{
//	Digraph graph;
//	graph.readFile("data.txt");
//	graph.show();
//	graph.dfs();
//	graph.bfs();
//	graph.shortPath(3, 4);
//}