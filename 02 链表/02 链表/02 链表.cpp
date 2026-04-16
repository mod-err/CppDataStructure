#include <iostream>

using namespace std;

//节点类型
struct Node {
	//有参构造初始化
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_; //数据域
	Node* next_;//地址域
};

//链表类
class Clink {
public:
	Clink() {
		//给head_初始化指向头节点
		head_ = new Node();
	}
	~Clink() {
		Node* p = head_;
		while (p != nullptr) { //当前节点不为空
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		head_ = nullptr;
		
	}
public:
	//链表尾插法 O(n)
	void insertTail(int val) {
		//找到尾节点
		Node* p = head_; //指向头节点
		while (p->next_ != nullptr) {  //找到为空的节点就停下
			p = p->next_;
		}
		//生成新节点
		Node* node = new Node(val);
		//把节点挂在尾节点
		p->next_ = node;
	}
	//链表头插法 O(1)
	void insertHead(int val) {
		//生成新节点
		Node* node = new Node(val);
		//头节点指向的节点挂在新节点
		node->next_ = head_->next_;
		//新节点挂在头节点
		head_->next_ = node;
	}
	//链表节点删除--单个节点
	void remove(int val) {
		Node* q = head_; //指向p的前一个节点
		Node* p = head_->next_;
		while (p != nullptr) {
			if (p->data_ == val) {
				q->next_ = p->next_;
				delete p;
				return; //删除后返回；p在栈区，超出生命周期 被释放；不会成为野指针
			}
			else {
				p = p->next_;
				q = q->next_;
			}
		}
	}
	//链表节点删除--多个节点
	void removeAll(int val) {
		Node* q = head_; //指向p的前一个节点
		Node* p = head_->next_;
		while (p != nullptr) {
			if (p->data_ == val) {
				q->next_ = p->next_;
				delete p;
				p = q->next_;
			}
			else {
				p = p->next_;
				q = q->next_;
			}
		}
	}
	//查找节点 O(n)
	bool find(int val) {
		Node* p = head_->next_;
		while (p != nullptr) {
			if (p->data_ == val) {
				return true;
			}
			else {
				p = p->next_;
			}
		}
		return false;
	}
	//打印链表
	void show() {
		Node* p = head_->next_;
		while (p != nullptr) {
			cout << p->data_ << " ";
			p = p->next_; //指向下一个节点
		}
		cout << endl;
	}
private:
	Node* head_; //指向链表头节点
};

int main() {
	Clink link;
	for (int i = 0; i < 10; i++) {
		link.insertHead(i);
		cout << i << " ";
	}
	cout << endl;

	cout << "头插法：" << endl;
	link.show();

	cout << "删除节点：" << endl;
	link.remove(5);
	link.show();

	cout << "删除所有符合条件的节点：" << endl;
	link.insertTail(3);
	link.insertHead(3);
	link.show();
	link.removeAll(3);
	link.show();

	cout << "查找'6'" << endl;
	cout << link.find(6) << endl;;
}