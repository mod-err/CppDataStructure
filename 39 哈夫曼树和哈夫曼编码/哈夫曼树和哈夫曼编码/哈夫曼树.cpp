#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;

//哈夫曼树
class HuffmanTree
{
public:
	HuffmanTree()
		: root_(nullptr)
	{}
	~HuffmanTree()
	{
		if (root_ == nullptr)
		{
			return;
		}

		queue<Node*> q;
		q.push(root_);

		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();

			if (front->left_ != nullptr)
			{
				q.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				q.push(front->right_);
			}

			delete front;
		}
	}
	//创建哈夫曼树
	void create(string str)
	{
		//1.统计字符出现的概率
		map<char, int> dataMap;
		for (char ch : str)
		{
			dataMap[ch]++;
		}
		//2.放入优先级队列
		for (auto kv : dataMap)
		{
			minHeap_.push(new Node(kv.first, kv.second));
		}
        //3.构建树
		while (minHeap_.size() > 1)
		{
			//从小根堆中选择两个权值最小的
			Node* n1 = minHeap_.top();
			minHeap_.pop();

			Node* n2 = minHeap_.top();
			minHeap_.pop();

			//构建父节点
			Node* parent = new Node('\0', n1->weight_ + n2->weight_);
			parent->left_ = n1;
			parent->right_ = n2;

			//重新放入小根堆
			minHeap_.push(parent);
		}
		//根节点指向构建树的顶端
		root_ = minHeap_.top();
		minHeap_.pop();
	}
	//编码
	string encode(string str)
	{
		getHuffmanCode(root_, "");
		//存储编码的结果
		string encode_str;
		for (char ch : str)
		{
			//追加字符串
			encode_str.append(codeMap_[ch]);
		}
		return encode_str;
	}
	//解码
	string decode(string encode)
	{
		//存储解码的结果
		string decode_str;
		Node* cur = root_;
		for (char ch : encode)
		{
			if (ch == '0')
			{
				cur = cur->left_;
			}
			else if (ch == '1')
			{
				cur = cur->right_;
			}

			if (cur->left_ == nullptr && cur->right_ == nullptr)
			{
				//append是用来追加“字符串”的，而push_back是用来追加“单个字符”的。
				decode_str.push_back(cur->data_);
				cur = root_;
			}
		}
		return decode_str;
	}
private:
	struct Node
	{
		Node(char data, int weight)
			: data_(data)
			, weight_(weight)
			, left_(nullptr)
			, right_(nullptr)
		{}
		char data_;   //字符数据
		int weight_; //权值
		Node* left_;
		Node* right_;
	};
	Node* root_; //根节点
	map<char, string> codeMap_; //存放字符和编码
private:
	//自定义比较规则
	struct WeightGreat
	{
		bool operator()(const Node* n1, const Node* n2) const
		{
			return n1->weight_ > n2->weight_;
		}
	};
	//优先级队列 - 小根堆实现 - 自动排序：队头永远是最小的
	priority_queue<Node*, vector<Node*>, WeightGreat> minHeap_;
private:
	void getHuffmanCode(Node* node, string code)
	{
		if (node->left_ == nullptr && node->right_ == nullptr)
		{
			codeMap_.emplace(node->data_, code);
			return;
		}

		getHuffmanCode(node->left_, code + "0");
		getHuffmanCode(node->right_, code + "1");
	}
};

int main()
{
	string str = "ABACDAEFFSFSDFWAVFWSDFDFFHDEG";

	HuffmanTree hTree;
	hTree.create(str);

	string encode = hTree.encode(str);
	cout << "encode:" << encode << endl;

	cout << "decode:" << hTree.decode(encode) << endl;
	return 0;
}

/*
bool operator>(const Node& node) const
{
	return this->weight_ > node.weight_;
}
* 只有在比较Node对象时才会生效

priority_queue<Node*, vector<Node*>, greater<Node*>> minHeap_;
* 当指定 greater<Node*> 时，比较的是指针本身(即地址值)，而不是指针所指向的Node对象

*/