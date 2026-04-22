#include <iostream>

using namespace std;

class CircleLink {
public:
	//构造函数
	CircleLink() {
		//指向头节点
		head_ = new Node();
		//指向尾节点
		tail_ = head_;
	}
	//析构函数
	~CircleLink() {

	}
private:
	//创建节点结构体：数据域+地址域
	struct Node {
		//结构体构造函数和类构造函数一样，唯一的区别：默认访问权限不同，结构体公有、类私有
		Node(int data = 0) : data_(data), next_(nullptr){ }
		int data_;
		Node* next_;
	};
	//头节点
	Node* head_;
	//尾节点
	Node* tail_;
};

int main() {

}
