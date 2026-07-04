#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class TrieTree
{
public:
	TrieTree()
	{
		root_ = new TrieNode('\0', 0);
	}
	~TrieTree()
	{
		//相当于层序遍历释放所有节点，利用队列实现
		queue<TrieNode*> q;
		q.push(root_);
		while (!q.empty())
		{
			//指针指向队头
			TrieNode* front = q.front();
			//出队头
			q.pop();
			//把当前层的下一层的节点全部入队
			for (auto kv : front->nodeMap_)
			{
				q.push(kv.second);
			}
			delete front;
		}
	}
private:
	//节点类型定义
	struct TrieNode
	{
		TrieNode(char ch, int freqs)
			: ch_(ch)
			, freqs_(freqs)
		{
		}
		//节点字符数据存储
		char ch_;
		//单词的末尾字符存储的单词的数量（频率）
		int freqs_;
		//存储孩子节点字符数据和节点指针的对应关系
		map<char, TrieNode*> nodeMap_;
	};
	//指向树的根节点
	TrieNode* root_;
public:
	//添加单词
	void add(const string& word)
	{
		TrieNode* cur = root_;

		for (int i = 0; i < word.size(); i++)
		{
			auto it = cur->nodeMap_.find(word[i]); //auto == map<char, TireNode*>::iterator
			if (it == cur->nodeMap_.end())
			{
				//没有找到相应字符，创建它
				TrieNode* child = new TrieNode(word[i], 0);
				cur->nodeMap_.emplace(word[i], child);
				cur = child;
			}
			else
			{
				//相应字符已经存在，移动cur指向对应的字符节点
				cur = it->second;
			}
		}
		// cur指向了word单词的最后一个节点
		cur->freqs_++;
	}
	//查找单词
	int query(const string& word)
	{
		TrieNode* cur = root_;

		for (int i = 0; i < word.size(); i++)
		{
			//迭代器指向当前节点的下一个节点
			auto it = cur->nodeMap_.find(word[i]);
			if (it == cur->nodeMap_.end())
			{
				//首个字母都没有找到
				return 0;
			}
			else
			{
				//相应字符已经存在，移动cur指向对应的字符节点
				cur = it->second;
			}
		}
		return cur->freqs_;
	}
	//前序遍历
	void preOrder()
	{
		//用于存储单词
		vector<string> wordList;
		string word;
		preOrder(root_, word, wordList);
		for (auto s : wordList)
		{
			cout << s << endl;
		}
	}
	//串的前缀索引
	void queryPrefix(const string& prefix)
	{
		/*
		这一段就是查找的代码，目的是找到要前缀搜索的串的入口
		例如：此时要前缀搜索"ch"开头的单词，执行完这段代码后，cur指向'h'所在的节点 
		*/
		TrieNode* cur = root_;
		for (int i = 0; i < prefix.size(); i++)
		{
			auto it = cur->nodeMap_.find(prefix[i]);
			if(it == cur->nodeMap_.end())
			{ 
				cout << "No words with prefix \"" << prefix << "\"" << endl;
				return; //第一个字符没为找到返回空
			}
			else
			{
				//相应字符已经存在，移动cur指向当前节点孩子节点
				cur = it->second;
			}
		}
		/*--------------------------------------*/
		/*
		经过前面的查找操作后，已经拿到了前缀查找的分支，接下来就是把其前序遍历全部取出以前缀开头的单词
		*/
		vector<string> wordList;
		//因为前序遍历的第一步操作就是把字符存入，所以为了避免重复存入，这里的word应该传入0, prefix.size() - 1
		preOrder(cur, prefix.substr(0, prefix.size() - 1), wordList);
		for (auto s : wordList)
		{
			cout << s << endl;
		}
	}
	//删除
	void remove(const string& word)
	{
		TrieNode* cur = root_;
		//del代表从哪个节点开始删除
		TrieNode* del = root_;

		char delch = word[0];

		for (int i = 0; i < word.size(); i++)
		{
			auto it = cur->nodeMap_.find(word[i]);
			if (it == cur->nodeMap_.end())
			{
				return;
			}
			else
			{
				//情况2：待删除单词和其他单词有公共前缀或包含某一单词
				if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1)
				{
					//指向公共前缀的末尾
					del = cur;
					//记录公共前缀末尾的单词
					delch = word[i];
				}
				//相应字符已经存在，移动cur指向对应的字符节点
				cur = it->second;
			}
		}
		//word单词是存在的
		if (cur->nodeMap_.empty())
		{
			//要删除的单词末尾节点后面没有节点

			/*
				处理情况1 和 情况2
				情况1：del = root_; delch = word[0]; 直接从根节点的孩子节点开始删除
			    情况2：公共前缀的末尾 的孩子节点开始删除
			*/

			//指向 公共前缀的末尾 的 孩子节点
			TrieNode* delChild = del->nodeMap_[delch];

			del->nodeMap_.erase(delch);

			//从孩子节点开始删除
			queue<TrieNode*> q;
			q.push(delChild);

			while (!q.empty())
			{
				TrieNode* front = q.front();
				q.pop();
				for (auto kv : front->nodeMap_)
				{
					q.push(kv.second);
				}
				delete front;
			}
		}
		else
		{
			//情况3：要删除的单词末尾节点后还有节点
			cur->freqs_ = 0; //不做删除操作，只是将频率置0
		}
	}
private:
	void preOrder(TrieNode* cur, string word, vector<string>& wordList)
	{
		//前序遍历 VLR
		if (cur != root_)
		{
			word.push_back(cur->ch_);
			if (cur->freqs_ > 0)
			{
				//已经遍历到一个有效单词
				wordList.push_back(word);
			}
		}

		//首次进入处理根节点 和 递归处理孩子节点
		for (auto kv : cur->nodeMap_)
		{
			preOrder(kv.second, word, wordList);
		}
	}
};

int main()
{
	TrieTree trie;
	trie.add("hello");
	trie.add("hello");
	trie.add("helloo");
	trie.add("hel");
	trie.add("hel");
	trie.add("hel");
	trie.add("china");
	trie.add("ch");
	trie.add("ch");
	trie.add("heword");
	trie.add("hellw");

	cout << trie.query("hel") << endl;

	cout << "--------------------------" << endl;
	trie.preOrder();

	cout << "--------------------------" << endl;
	trie.queryPrefix("he");

	trie.remove("hel");
	cout << trie.query("hel") << endl;
}