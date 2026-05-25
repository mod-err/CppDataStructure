#include <iostream>

using namespace std;

template<typename T, typename Comp = less<T>> 
class BSTree
{
private:
	struct Node
	{
		Node(T data = T()) //T()是匿名对象，调用默认构造
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{
		}
		T data_;
		Node* left_;
		Node* right_;
	};

	Node* root_; // 根节点
	Comp comp_;  // 定义一个函数对象
public:
	BSTree(Comp comp = Comp()) 
		: root_(nullptr) 
		, comp_(comp)
	{}
	~BSTree() 
	{
	
	}
public:
	//非递归插入
	bool n_insert(T val) 
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
	//递归插入-用户接口
	void insert(const T val)
	{
		root_ = insert(root_, val);
	}
	//非递归删除
	bool n_erase(T val) 
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
	//递归删除-用户接口
	void erase(const T val)
	{
		root_ = erase(root_, val);
	}
	//非递归查找
	bool n_find(T val)
	{
		//如果树为空直接返回假
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (val < cur->data_)
			{
				cur = cur->left_;
			}
			else if (val > cur->data_) 
			{
				cur = cur->right_;
			}
			else
			{
				//找到直接返回
				return true;
			}

		}
		return false;
	}
	//递归查找-用户接口
	bool find(const T val)
	{
		return find(root_, val);
	}
	//递归实现前序遍历-用户接口
	void preOrder()
	{
		cout << "[递归]前序遍历：";
		preOrder(root_); //root_是私有成员，所以要重载一个用户接口
		cout << endl;
	}
	//递归实现中序遍历-用户接口
	void inOrder()
	{
		cout << "[递归]前序遍历："; 
		inOrder(root_);
		cout << endl;
	}
	//递归实现后序遍历-用户接口
	void postOrder()
	{
		cout << "[递归]前序遍历：";
		postOrder(root_);
		cout << endl;
	}
	//递归实现层序遍历-用户接口
	void levelOrder()
	{
		cout << "[递归]层序遍历：";
		int h = level(); //树的层数
		for (int i = 0; i < h; i++)
		{
			levelOrder(root_, i); //递归调用树的层数次
		}
		cout << endl;
	}
	//递归计算层数-用户接口
	int level()
	{
		return level(root_);
	}
	//递归计算节点个数-用户接口
	int number()
	{
		return number(root_);
	}

private:
	//递归插入
	Node* insert(Node* node, const T val)
	{
		if (node == nullptr)
		{
			//找到待插入的位置，递归结束，生成新节点并返回其节点地址
			return new Node(val);
		}
		if (val < node->data_)
		{
			node->left_ = insert(node->left_, val);
		}
		else if (val > node->data_)
		{
			node->right_ = insert(node->right_, val);
		}
		else 
		{
			return node;
		}
		return node;
	}
	//递归查找
	bool find(Node* node, const T val)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (val < node->data_)
		{
			return find(node->left_, val);
		}
		else if(val > node->data_)
		{
			return find(node->right_, val);
		}
		else 
		{
			return true;
		}
	}
	//递归删除-用户接口
	Node* erase(Node* node, const T val)
	{
		if (node == nullptr)
		{
			return node;
		}

		if (val < node->data_)
		{
			node->left_ = erase(node->left_, val);
		}
		else if (val > node->data_)
		{
			node->right_ = erase(node->right_, val);
		}
		else
		{
			return node;
		}

	}
	//递归实现前序遍历-VLR
	void preOrder(Node* node) 
	{
		if (node != nullptr)
		{
			cout << node->data_ << " "; //V
			preOrder(node->left_);      //L
			preOrder(node->right_);     //R
		}
	}
	//递归实现中序遍历-LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);       //L
			cout << node->data_ << " "; //V
			preOrder(node->right_);     //R
		}
	}
	//递归实现后序遍历-LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);     //L
			postOrder(node->right_);    //R
			cout << node->data_ << " "; //V
		}
	}
	//递归实现层序遍历
	void levelOrder(Node* node, int i)
	{
		//树空：不遍历
		if (node == nullptr)
		{
			return;
		}
		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}
	//递归计算层数
	int level(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = level(node->left_);
		int right = level(node->right_);
		return max(left, right) + 1;  //left > right ? left + 1 : right + 1;
	}
	//递归计算节点个数
	int number(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = number(node->left_);   //L
		int right = number(node->right_); //R
		return left + right + 1; //V  +1是根节点，相当于后续遍历
	}
};

int main() 
{
	BSTree<int> tree;

	int arr[] = { 58, 24, 67, 0 ,34, 62, 69, 5, 41, 64, 78 };

	for (int v : arr)
	{
		//tree.n_insert(v);
		tree.insert(v);
	}
	tree.preOrder();
	tree.inOrder();
	tree.postOrder();
	tree.levelOrder();

	cout << "层数：" << tree.level() << endl;
	cout << "树节点总数：" << tree.number() << endl;

	tree.n_erase(58);

	//cout << tree.n_find(58) << endl;
	//cout << tree.n_find(0) << endl;
	cout << tree.find(58) << endl;
	cout << tree.find(0) << endl;

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