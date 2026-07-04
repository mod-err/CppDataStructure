#include <iostream>

using namespace std;

//跳跃表SkipList
class SkipList
{
public:
	SkipList()
	{
		//初始化最高层头节点
		head_ = new HeadNode(1);
	}
	~SkipList()
	{
		//获取层数
		int level = head_->level_;
		//head_->level_指向最高层头节点
		for (int i = 0; i < head_->level_; i++)
		{
			Node* cur = head_->next_;
			while (cur != nullptr)
			{
				Node* tmp = cur->next_;
				delete cur;
				cur = tmp;
			}
			cur = head_;
			//down_是在父类中的所以类型是Node，而head_是HeadNode类型，必须强转一下
			head_ = static_cast<HeadNode*>(head_->down_);
			delete cur;
		}

	}
private:
	//普通节点
	struct Node
	{
		Node(int data = 0) 
			:data_(data)
			,next_(nullptr)
			,down_(nullptr)
		{}
		int data_; //节点存放的数据
		Node* next_; //当前节点的下一个节点
		Node* down_; //当前节点对应的下一层节点
	};
	//头节点-共有继承：struct默认权限都是public，所以这里共有继承可以全部访问父类
	struct HeadNode : public Node
	{
		HeadNode(int level)
			:level_(level)
		{}
		int level_;
	};
private:
	HeadNode* head_;
public:
	//查找
	bool find(int val)
	{
		Node* pre = head_;
		Node* cur = head_->next_;
		
		while(1)
		{
			//如果当前层cur指向的节点不为空
			if (cur != nullptr)
			{
				if (cur->data_ < val)
				{
					pre = cur;
					cur = cur->next_;
				}
				else if (cur->data_ == val)
				{
					return true;
				}
			}
			
			//cur == nullptr已经走到当前层末尾了
			if (pre->down_ == nullptr)
			{
				break;
			}

			//若当前节点值 大于 目标值，或 cur 走到当前层末尾（空指针）：下降
			pre = pre->down_;
			cur = pre->next_;
		}
		return false;
	}
	//添加
	void add(int val)
	{
		//不重复插入数据
		if (find(val))
		{
			return;
		}

		//抛硬币，data数据添加几层
		int level = getLevel();
		/*
		只有在插入数据要添加的层数大于最高层数时，才加盖新层
		例如：
			目前最高3层，插入数据val抛硬币要加盖10层；
			那超过4层的层数都是只有一个val节点，没有任何意义；
			①val要加level = 2层（小于等于最高层），直接添加
			②val要加level = 5层（level > 目前最高层），才创建一层，最高层变成4层，也就是val每层都有
		*/
		if (level > head_->level_)
		{
			//每次只添加一层
			level = head_->level_ + 1;
			//创建新层
			HeadNode* hnode = new HeadNode(level); 
			//头节点head_指向最高层头节点
			hnode->down_ = head_;  
			head_ = hnode;
		}

		/*
		* 把要添加的节点先垂直连接，在左右连接
		* 创建指针数组，存储创建的节点指针，通过[i]可以访问创建的新指针

		在创建节点时，从最低层开始创建
			i = level-1是最低层的节点，
			i = 0是最高层，
			连接时候是高层指向底层，所以有i->i+1；
		如果从高层往底层创建，那没有办法完成高层指针指向底层，因为低层指针还没创建
		例如：level = 3;
		0 ⚪  最晚被创建
		1 ⚪
		2 ⚪  最先被创建
		*/
		Node** nodeList = new Node * [level];
		for (int i = level - 1; i >= 0; i--)
		{
			nodeList[i] = new Node(val);
			if (i < level - 1)
			{
				nodeList[i]->down_ = nodeList[i + 1];
			}
		}
		//从最低层进行左右连接
		/*
		假设当前跳跃表最高层是10层，而要插入的节点只有3层：下坠到第 3 层，只在1-3层插入
		即使是只插入一层，那也是插在第一层
		*/
		Node* head = head_;
		for (int i = head_->level_; i > level; i--)
		{
			head = head->down_;
		}

		//head指向要插入节点的链表
		Node* pre = head;
		Node* cur = pre->next_;

		for (int i = 0; i < level; i++)
		{
			//寻找插入区间，pre区间左端点，cur区间右端点
			while (cur != nullptr && cur->data_ < val)
			{
				pre = cur;
				cur = cur->next_;
			}
			//新节点插入到pre和cur之间
			nodeList[i]->next_ = cur;
			pre->next_ = nodeList[i];

			//准备插入下一层
			pre = pre->down_; //pre下到下一层
			//插入最后一层完成后，pre指向了最后一层的下一层即空，不加判断cur直接访问空指针报错了
			if (pre != nullptr)
			{
				cur = pre->next_;
			}
		}

		delete[] nodeList;
		nodeList = nullptr;
	}
	//删除
	void remove(int val)
	{
		Node* pre = head_;
		Node* cur = head_->next_;
		while (1)
		{
			if (cur->data_ < val)
			{
				pre = cur;
				cur = cur->next_;
			}
			else if(cur->data_ == val)
			{
				pre->next_ = cur->next_;
				delete cur;
			}
			//cur == nullptr 或 cur->data > val
			if (pre->down_ == nullptr)
			{
				break;
			}

			pre = pre->down_;
			//如果删除后最高层只剩下一个头节点，那要降层
			if (head_->next_ == nullptr)
			{
				delete head_;
				head_ = static_cast<HeadNode*>(pre);
			}
			cur = pre->next_;
		}
	}
	//打印
	void show() const
	{
		Node* head = head_;
		while (head != nullptr)
		{
			Node* cur = head->next_;
			while (cur != nullptr)
			{
				cout << cur->data_ << " ";
				cur = cur->next_;
			}
			cout << endl;
			head = head->down_;
		}
	}
private:
	//跳跃表是一种概率平衡的数据结构，它的层数不是固定的，而是通过随机过程决定
	int getLevel() const
	{
		int level = 1;
		while (rand() % 2 == 1) //rand() % 2 生成0或1
		{
			level++;
		}
		return level;
	}
};

int main()
{
	SkipList list;
	srand(time(nullptr));

	for (int i = 0; i < 20; i++)
	{
		list.add(rand() % 100);
	}

	list.show();

	cout << "---------------" << endl;
	list.remove(1);
	list.show();

	cout << list.find(1) << endl;

	return 0;
}