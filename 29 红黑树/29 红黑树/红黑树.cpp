#include <iostream>

using namespace std;

template<typename T>
class RBTree
{
public:
	RBTree() : root_(nullptr) {}
	~RBTree() {}
private:
	enum Color 
	{
		BLACK,
		RED
	};
	struct Node
	{
		Node(T data = T(), Color c = BLACK)
			: data_(data)
			,left_(nullptr)
			,right_(nullptr)
			,parent_(nullptr)
			,color_(c) //默认颜色为黑色
		{}
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_; //父亲节点
		Color color_; 
	};
	Node* root_; //根节点
private:
	//获取节点的颜色
	Color getColor(Node* node)
	{
		return node == nullptr ? BLACK : node->color_;
	}
	//设置节点的颜色
	void setColor(Node* node, Color color)
	{
		node->color_ = color;
	}
	//返回节点的左孩子
	Node* Left(Node* node)
	{
		return node->left_;
	}
	//返回节点的右孩子
	Node* Right(Node* node)
	{
		return node->right_;
	}
	//返回父亲节点
	Node* Parent(Node* node)
	{
		return node->parent_;
	}
	//在递归操作中只需要3行代码，旋转后的根节点与父亲节点的连接是在递归回溯时完成的，非递归操作需要加更多代码
	//左旋转操作-非递归
	void leftRotate(Node* node)
	{
		Node* child = node->right_;
		node->right_ = child->left_;

		//修改左孩子的父节点指针指向
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}

		//旋转后的根节点与父节点连接
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			//判断node是在父节点的左或右子树
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}
		//修改child节点的父节点
		child->parent_ = node->parent_;

		child->left_ = node;
		//修改node节点的父节点
		node->parent_ = child;
	}
	//右旋转操作-非递归
	void rightRotate(Node* node)
	{
		Node* child = node->left_;
		node->left_ = child->right_;

		//child右孩子连接关系发生改变，修正其父节点指针
		if (child->right_ != nullptr)
		{
			child->right_->parent_ = node;
		}

		// 旋转后的根节点与父节点连接
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			//判断node是在父节点的左或右子树
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}

		//child节点连接关系发生改变，修正其父节点指针
		child->parent_ = node->parent_;

		child->right_ = node;
		//修改node节点的父节点
		node->parent_ = child;
	}
	//插入后进行调整
	void fixAfterInsert(Node* node)
	{
		//如果当前节点（红）父节点是红色，就一直调整
		while (getColor(Parent(node)) == RED)
		{
			if (Left(Parent(Parent(node))) == Parent(node))
			{
				//插入的节点在左子树中
				Node* uncle = Right(Parent(Parent(node)));
				//情况1：叔叔节点是红色
				if (getColor(uncle) == RED)
				{
					//父->黑
					setColor(Parent(node), BLACK);
					//叔->黑
					setColor(uncle, BLACK);
					//爷->红
					setColor(Parent(Parent(node)), RED);

					//指向爷爷节点，继续向上调整
					node = Parent(Parent(node));
				}
				else
				{
					//情况3：叔叔节点是黑色，插入节点和父节点不在一侧  ---->  转为情况2
					if (Right(Parent(node)) == node)
					{
						//传入Parent(node)保证旋转后node位置和情况2一致
						node = Parent(node);
						leftRotate(node);
					}
					//情况2：叔叔节点是黑色
					//父->黑
					setColor(Parent(node), BLACK);
					//爷->红
					setColor(Parent(Parent(node)), RED);
					//右旋爷爷，为了保证[黑路同]
					rightRotate(Parent(Parent(node)));
					break;
				}
			}
			else 
			{
				//插入的节点在右子树中
				Node* uncle = Left(Parent(Parent(node)));
				//情况1：叔叔节点是红色
				if (getColor(uncle) == RED)
				{
					//父->黑
					setColor(Parent(node), BLACK);
					//叔->黑
					setColor(uncle, BLACK);
					//爷->红
					setColor(Parent(Parent(node)), RED);

					//指向爷爷节点，继续向上调整
					node = Parent(Parent(node));
				}
				else
				{
					//情况3：叔叔节点是黑色，插入节点和父节点不在一侧  ---->  转为情况2
					if (Left(Parent(node)) == node)
					{
						//传入Parent(node)保证旋转后node位置和情况2一致
						node = Parent(node);
						rightRotate(node);
					}
					//情况2：叔叔节点是黑色
					//父->黑
					setColor(Parent(node), BLACK);
					//爷->红
					setColor(Parent(Parent(node)), RED);
					//左旋爷爷，为了保证[黑路同]
					leftRotate(Parent(Parent(node)));
					break;
				}
			}
		}
		
		//强制把根节点设置为黑色
		setColor(root_, BLACK);
	}
public:
	//插入操作-非递归
	void insert(const T val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val); //[根必黑]
			return;
		}

		Node* parent = nullptr;
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
				return;
			}
		}
		//parent指向待插入节点的父节点
		Node* node = new Node(val, RED);
		if (val < parent->data_)
		{
			parent->left_ = node;
		}
		else if (val > parent->data_)
		{
			parent->right_ = node;
		}
		node->parent_ = parent;

		//插入后，如果违反[不红红]，进行调整
		if (RED == getColor(parent))
		{
			fixAfterInsert(node);
		}
	}
};

int main() 
{
	RBTree<int> rb;
	for (int i = 1; i < 10; i++)
	{
		rb.insert(i);
	}
	return 0;
}