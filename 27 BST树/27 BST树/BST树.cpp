#include <iostream>

using namespace std;

template<typename T, typename Comp = less<T>> 
class BSTree
{
public:
	BSTree(Comp comp = Comp()) 
		: root_(nullptr) 
		, comp_(comp)
	{}
	~BSTree() {}
public:
	//插入
	bool insert(T val) 
	{
		//没有根节点，先生成根节点
		if (root_ == nullptr) 
		{
			root_ = new Node(val);
			return true;
		}
		
		//当前节点的父节点
		Node* parent = nullptr;
		//从根节点往下找
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (val < cur->data_)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (val > cur->data_)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return false;
			}
		}

		//找到合适的位置插入
		if (val < parent->data_)
		{
			parent->left_ = new Node(val);
		}
		else if (val > parent->data_) 
		{
			parent->right_ = new Node(val);
		}
		return true;
	}
	//删除
	bool erase(T val) 
	{
		//没有根节点，直接返回
		if (root_ == nullptr)
		{
			return false;
		}
		//当前节点的父节点
		Node* parent = nullptr;
		//从根节点往下找
		Node* cur = root_;
		//寻找和val值相等的节点
		while (cur != nullptr)
		{
			if (val < cur->data_)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (val > cur->data_)
			{
				parent = cur;
				cur = cur->right_;
			}
			else 
			{
				//找到后跳出循环
				break;
			}
		}
		//没有找到待删除节点
		if (cur == nullptr)
		{
			return false;
		}

		//删除目标节点

		//情况3：左右孩子非空
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			//当前节点的左子树
			Node* max = cur->left_;
			while (max->right_ != nullptr)
			{
				parent = max;
				//找左子树的最大的
				max = max->right_;
			}
			cur->data_ = max->data_;
			//情况3转化为情况1/2
			cur = max;
		}

		//叶子节点包含在只有左或右孩子情况中
		if (cur->left_ == nullptr)  //只有右孩子
		{
			//删除的是根节点
			if (parent == nullptr)
			{
				root_ = cur->right_;
			}
			else if (parent->left_ == cur)
			{
				parent->left_ = cur->right_;
			}
			else
			{
				parent->right_ = cur->right_;
			}
		}
		else if (cur->right_ == nullptr) //只有左孩子
		{
			if (parent == nullptr)
			{
				root_ = cur->left_;
			}
			else if (parent->left_ == cur)
			{
				parent->left_ = cur->left_;
			}
			else
			{
				parent->right_ = cur->right_;
			}
		}

		delete cur;
		return true;
	}

private:
	struct Node
	{
		Node(T data = T()) //T()是匿名对象，调用默认构造
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}
		T data_;
		Node* left_;
		Node* right_;
	};

	Node* root_; // 根节点
	Comp comp_;  // 定义一个函数对象
};

int main() 
{
	BSTree<int> tree;

	int arr[] = { 58, 24, 67, 0 ,34, 62, 69, 5, 41, 64, 78 };

	for (int v : arr)
	{
		tree.insert(v);
	}
	tree.erase(58);

	return 0;
}

#if 0
//删除
bool erase(T val)
{
	//没有根节点，直接返回
	if (root_ == nullptr)
	{
		return false;
	}
	//当前节点的父节点
	Node* parent = nullptr;
	//从根节点往下找
	Node* cur = root_;
	//寻找和val值相等的节点
	while (cur != nullptr)
	{
		if (val < cur->data_)
		{
			parent = cur;
			cur = cur->left_;
		}
		else if (val > cur->data_)
		{
			parent = cur;
			cur = cur->right_;
		}
		else
		{
			//找到后跳出循环
			break;
		}
	}
	//没有找到待删除节点
	if (cur == nullptr)
	{
		return false;
	}

	//删除目标节点

	//情况3：左右孩子非空
	if (cur->left_ != nullptr && cur->right_ != nullptr)
	{
		parent = cur;
		//当前节点的左子树
		Node* max = cur->left_;
		while (max->right_ != nullptr)
		{
			parent = max;
			//找左子树的最大的
			max = max->right_;
		}
		cur->data_ = max->data_;
		//情况3转化为情况1/2
		cur = max;
	}

	/*
	先默认指向左节点：
		如果是叶子节点，指向右；
		如果只有左节点，指向左；
		如果只有右节点，指向右；
	*/
	Node* child = cur->left_;
	if (cur->left_ == nullptr)
	{
		child = cur->right_;
	}

	if (parent == nullptr)
	{
		root_ = child;
	}
	else if (parent->left_ == cur)
	{
		parent->left_ = child;
	}
	else
	{
		parent->right_ = child;
	}

	delete cur;
	return true;
}
#endif