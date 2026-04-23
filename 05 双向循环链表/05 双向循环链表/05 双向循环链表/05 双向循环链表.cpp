#include <iostream>

using namespace std;

class DoubleCircleLink {
public:
	DoubleCircleLink() {
		//创建头结点
		head_ = new Node();
		//创建环
		head_->next_ = head_;
		head_->pre_ = head_;

	}
	//析构函数-考虑边界：链表空 or 非空
	~DoubleCircleLink() {
		Node* p = head_->next_;
		while (p != head_) {
			head_->next_ = p->next_;
			p->next_->pre_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}
public:
	//头插法-O(1)
	void insertHead(int val) {
		Node* node = new Node(val);
		node->next_ = head_->next_;
		node->pre_ = head_;
		head_->next_->pre_ = node;
		head_->next_ = node;
	}
	//尾插法-O(1)-考虑边界：空 or 非空
	void insertTail(int val) {
		Node* node = new Node(val);
		//尾结点
		Node* tail = head_->pre_;

		node->pre_ = tail;
		tail->next_ = node;
		node->next_ = head_;
		head_->pre_ = node;
	}
	//删除-O(n)-考虑边界情况：删除尾结点
	void remove(int val) {
		Node* p = head_->next_;
		while (p != head_) {
			if (p->data_ == val) {
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				delete p;
				return;
			}
			else {
				p = p->next_;
			}
		}
	}
	//查找
	bool find(int val) const{
		Node* p = head_->next_;
		while (p != head_) {
			if (p->data_ == val) {
				return true;
			}
			else {
				p = p->next_;
			}
		}
		return false;
	}
	//打印
	void show() const{
		Node* p = head_->next_;
		while (p != head_) {
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
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
	Node* head_;
};
int main() {
	DoubleCircleLink DClink;

	for (int i = 0; i < 10; i++) {
		cout << i << " ";
		DClink.insertHead(i);
	}
	cout << endl;

	cout << "头插结果：" << endl;
	DClink.show();

	cout << "尾插结果：" << endl;
	DClink.insertTail(100);
	DClink.insertTail(200);
	DClink.insertTail(300);
	DClink.show();

	cout << "删除：" << endl;
	DClink.remove(300);
	DClink.remove(100);
	DClink.remove(9);
	DClink.show();

	cout << "查找100：" << (DClink.find(100) ? "找到" : "未找到") << endl;
	cout << "查找0：" << (DClink.find(0) ? "找到" : "未找到") << endl;
}