#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename T, typename Comp = less<T>> 
class BSTree
{
public:
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
	//非递归实现前序遍历-VLR
	void n_preOrder()
	{
		cout << "[非递]前序遍历：";
		//树为空
		if (root_ == nullptr)
		{
			return;
		}
		//树非空
		stack<Node*> s;
		s.push(root_);

		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->data_ << " ";  //V
			s.pop();

			if (top->right_ != nullptr)
			{
				s.push(top->right_);    //R
			}
			if (top->left_ != nullptr)
			{
				s.push(top->left_);     //L
			}
		}
		cout << endl;
	}
	//递归实现中序遍历-用户接口
	void inOrder()
	{
		cout << "[递归]中序遍历："; 
		inOrder(root_);
		cout << endl;
	}
	//非递归实现中序遍历-LVR
	void n_inOrder() 
	{
		cout << "[非递]中序遍历：";
		//树空
		if (root_ == nullptr)
		{
			return;
		}
		//树非空
		stack<Node*> s;
		Node* cur = root_;
		while (cur != nullptr)
		{
			s.push(cur);      
			cur = cur->left_;  //L
		}

		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->data_ << " ";  //V
			s.pop();

			cur = top->right_;   //R
			while (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_; 
			}
		}
		cout << endl;
	}
	//递归实现后序遍历-用户接口
	void postOrder()
	{
		cout << "[递归]后序遍历：";
		postOrder(root_);
		cout << endl;
	}
	//非递归实现后序遍历-LRV
	void n_postOrder()
	{
		cout << "[非递]后序遍历：";
		//树为空
		if (root_ == nullptr)
		{
			return;
		}
		//树非空
		stack<Node*> s;
		stack<int> n;
		s.push(root_);

		while (!s.empty())
		{
			Node* top = s.top();
			n.push(top->data_);   //V
			s.pop();

			if (top->left_ != nullptr)
			{
				s.push(top->left_);     //L
			}
			if (top->right_ != nullptr)
			{
				s.push(top->right_);    //R
			}
		}
		//打印
		while (!n.empty())
		{
			cout << n.top() << " ";
			n.pop();
		}
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
	//非递归实现层序遍历
	void n_levelOrder()
	{
		cout << "[非递]层序遍历：";
		if (root_ == nullptr)
		{
			return;
		}

		queue<Node*> q;
		q.push(root_);

		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->data_ << " ";
			q.pop();

			if (front->left_ != nullptr)
			{
				q.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				q.push(front->right_);
			}
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
	//递归实现区间搜索-用户接口
	void findValues(vector<T>& vec, T i, T j)
	{ 
		//递归要有节点做为输入参数，所以要重新封装函数
		cout << "[" << i << "," << j << "]" << "区间内元素为：";
		findValues(root_, vec, i, j);
	}
	//递归实现BST树判断-用户接口
	bool isBSTree()
	{
		Node* pre = nullptr;
		return isBSTree(root_, pre);
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
	//递归删除
	Node* erase(Node* node, const T val)
	{
		//递归结束条件：空节点，直接返回空
		if (node == nullptr)
		{
			return nullptr;
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
			//情况3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				Node* max = node->left_;
				while (max->right_ != nullptr)
				{
					max = max->right_;
				}
				node->data_ = max->data_;
				//前驱节点 = erase(当前节点左子树, val);
				node->left_ = erase(node->left_, max->data_); 
				return node;
			}
			//情况1/2
			if (node->left_ == nullptr)
			{
				Node* left = node->left_;
				delete node;
				return left;
			}
			else if (node->right_ == nullptr) 
			{
				Node* right = node->right_;
				delete node;
				return right;
			}
		}
		return node;
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
			inOrder(node->right_);     //R
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
	//递归实现区间搜索
	void findValues(Node* node, vector<T>& vec, T i, T j)
	{
		//中序遍历结果是有序的，所以借助其实现
		if (node != nullptr)
		{
			//利用BST L < V < R的特点减少递归次数
			
			//L-减少搜索次数，<=i 无需往右子树递归
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j);
			}
			//V
			if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);
			}
			//R-减少搜索次数，>=j 无需往右子树递归
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j);
			}
		}
	}
	//递归实现BST树判断
	bool isBSTree(Node* node, Node*& pre)
	{
		//判断BST树要借助中序遍历实现
		if (node != nullptr)
		{
			//L
			if (!isBSTree(node->left_, pre))
			{
				return false;
			}
			//V-当前节点的值 应该大于 前一节点的值
			if (pre != nullptr)
			{
				if (node->data_ <= pre->data_)
				{
					return false;
				}
			}
			//更新前驱节点
			pre = node;
			//R
			return isBSTree(node->right_, pre);
		}
		return true;

		//只进行了局部BST树判断，无法真正判断是不是BST树
		/*
		if (node == nullptr)
		{
			return true;
		}
		//V-判断当前节点
		if (node->left_ != nullptr && node->data_ <= node->left_->data_)
		{
			return false;
		}
		if (node->right_ != nullptr && node->data_ >= node->right_->data_)
		{
			return false;
		}
		//L-判断当前节点左子树
		if (!isBSTree(node->left_))
		{
			return false; //如果左子树返回假，无需进行下面的右子树判断，直接返回
		}
		//R-判断当前节点右子树
		return isBSTree(node->right_); 
		//代码冗余，判断右子树已经是在最后了，直接返回
		//if (!isBSTree(node->right_))
		//{
		//	return false;
		//}
		//else 
		//{
		//	return true; //前面的条件都未返回假，最后返回真
		//}
		*/
	}
};

int main() 
{
	BSTree<int> tree;

	int arr[] = { 58, 24, 67, 0 ,34, 62, 69, 5, 41, 64, 78 };

	for (int v : arr)
	{
		tree.n_insert(v);
		//tree.insert(v);
	}
	tree.preOrder();
	tree.n_preOrder();
	tree.inOrder();
	tree.n_inOrder();
	tree.postOrder();
	tree.n_postOrder();
	tree.levelOrder();
	tree.n_levelOrder();

	cout << "层数：" << tree.level() << endl;
	cout << "树节点总数：" << tree.number() << endl;

	//tree.n_erase(58);
	tree.erase(78);

	cout << "树节点总数：" << tree.number() << endl;

	//cout << tree.n_find(58) << endl;
	//cout << tree.n_find(0) << endl;
	cout << tree.find(78) << endl;
	cout << tree.find(0) << endl;

	//BST树区间搜索
	vector<int> vec;
	tree.findValues(vec, 10, 60);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	//判断是否是BST树
	
	//构建一颗不符合BST的树
	BSTree<int> bst;
	using Node = BSTree<int>::Node;

	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(60);
	Node* node3 = new Node(30);
	Node* node4 = new Node(80);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node2->left_ = node3;
	node2->right_  = node4;

	bst.inOrder();
	cout << bst.isBSTree();
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