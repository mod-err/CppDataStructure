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
		Node(T data = T())
			:left_(nullptr)
			,right_(nullptr)
			,parent_(nullptr)
			,color_(BLACK) //默认颜色为黑色
		{}
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_; //父亲节点
		Color color_; 
	};
	Node* root_; //根节点
public:
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
	Node* left(Node* node)
	{
		return node->left_;
	}
	//返回节点的右孩子
	Node* right(Node* node)
	{
		return node->right_;
	}
	//返回父亲节点
	Node* parent(Node* node)
	{
		return node->parent_;
	}
public:
	//左旋转操作-非递归
	//在递归操作中只需要3行代码，旋转后的根节点与父亲节点的连接是在递归回溯时完成的，非递归操作需要加更多的代码
	void leftRotate(Node* node)
	{
		Node* child = node->right_;
		node->right_ = child->left_;

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
			if (node == node->parent_->left_)
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
	void leftRotate(Node* node)
	{

	}
};

int main() 
{

}