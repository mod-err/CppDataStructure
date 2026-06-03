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
	void leftRotate(Node* node)
	{

	}
	//右旋转操作-非递归
	void leftRotate(Node* node)
	{

	}
};

int main() 
{

}