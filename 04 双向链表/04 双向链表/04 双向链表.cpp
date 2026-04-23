#include <iostream>

using namespace std;

struct Node {
	Node(int data = 0)
		: data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{ }
	int data_;
	Node* pre_;
	Node* next_;
};

//双向链表
class DoubleLink {
public:
	//构造函数
	DoubleLink(){
		//创建头节点
		head_ = new Node();
	}
	//析构函数
	~DoubleLink() {
		Node* p = head_;
		while (p != nullptr) {
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		//维护成员变量
		head_ = nullptr;
	}
public:
	//头插法
	void insertHead(int val) {
		Node* node = new Node(val);
		//空
		if (head_->next_ == nullptr) {
			node->pre_ = head_;
			head_->next_ = node;
		}
		else {
			//非空
			node->next_ = head_->next_;
			node->pre_ = head_;
			head_->next_->pre_ = node;
			head_->next_ = node;
		}
	}
	//尾插法
	void insertTail(int val) {
		
	}
private:
	//头节点
	Node* head_;
};

int main() {

}