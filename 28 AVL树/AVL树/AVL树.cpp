#include <iostream>
#include <cmath>

using namespace std;

//AVL树
template<typename T, typename Comp = less<T>>
class AVLTree
{
private:
    struct Node
    {
        Node(T data = T()) 
            : data_(data) , 
            : left_(nullptr), 
            : right_(nullptr)
        {
        }
        T data_;
        Node left_;
        Node right_;
        int height_; //当前节点的高度
    };
    //根节点
    Node* root_;
private:
    //计算高度函数
    int height(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        return node->height_;
        //等价于：当前节点为空返回高度0，不空返回当高度
        //return node == nullptr ? 0 : node->height_;
    }
    //右旋操作，以参数node为轴进行右旋操作，返回新的根节点
    Node* rightRotate(Node* node)
    {
        //孩子节点指向node节点的左孩子
        Node* child = node->left_;
        node->left = child->node;
        child->right_ = node;
        //高度更新 ： 左右子树高的那颗树的高度 + 1 (当前节点高度)
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height = max(height(child->left_), height(child->right_)) + 1;
        //返回旋转之后的根节点
        return child;
    }
    //左旋操作，以参数node为轴进行左旋操作，返回新的根节点
    Node* leftRotate(Node* node)
    {
        //孩子节点指向node节点的右孩子
        Node* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;
        //高度更新 ： 左右子树高的那颗树的高度 + 1 (当前节点高度)
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height = max(height(child->left_), height(child->right_)) + 1;
        //返回旋转之后的根节点
        return child;
    }
    //左平衡操作，先左旋后右旋，返回新的根节点
    Node* leftBalance(Node* node)
    {
        //旋转后的根节点连接到 传入节点的左子树
        node->left_ = leftRotate(node->left_);
        //返回旋转之后的根节点
        return rightRotate(node);
    }
    //右平衡操作，先右旋后左旋，返回新的根节点
    Node* rightBalance(Node* node)
    {
        //旋转后的根节点连接到 传入节点的右子树
        node->right_ = rightRotate(node->right_);
        //返回旋转之后的根节点
        return leftRotate(node);
    }
public:
    AVLTree() 
        : root_(nullptr)
    {}
    ~AVLTree()
    {

    }
public:
    //插入-递归-用户接口
    void insert(T val)
    {
        root_ = insert(root_, val);
    }    
    //删除-递归
    //查找-递归
private:
    //插入-递归
    Node* insert(Node* node, const T val)
    {
        //V-当前节点-插入操作
        if(node == nullptr)
        {
            return new Node(val);
        }
        //L
        if(val < node->data_)
        {
            node->left_ = insert(node->left_, val);
            /* ------此行之下是[递归回溯]过程执行------*/
            //与BST树比 添加1:node的左子树太高，导致node失衡
            //判断是 左孩子的左子树太高 还是 左孩子的右子树太高
            if(height(node->left_->left_) >= height(node->left_->right_))
            {
                //接收新的根节点
                node = rightRotate(node);
            }
            else
            {
                node = leftBalance(node);
            }
        }
        //R
        else if(val > node->data_)
        {
            node->right_ = insert(node->right_, val);
            /* ------此行之下是[递归回溯]过程执行------*/
            //添加2:node的右子树太高，导致node失衡
            //判断是 右孩子的右子树太高 还是 右孩子的左子树太高
            if(height(node->right_->right_) >= height(node->right_->left_))
            {
                //接收新的根节点
                node = leftRotate(node);
            }
            else
            {
                node = rightBalance(node);
            }
        }
        //相等
        else
        {
            return node;
        }
        //添加3：更新AVL树高度
        node->height_ = max(height(node->left, node->right)) + 1;
        //插入完成后，当前子树的根节点root_
        return node;
    }
};

int main()
{
    AVLTree<int> avl;
    for(int i = 1; i <= 10; i++)
    {
        avl.insert(i);
    }
    return 0;
}