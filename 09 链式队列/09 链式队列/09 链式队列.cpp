#include <iostream>

using namespace std;

class LinkQueue {
public:
	LinkQueue() : size_(0){
		//创建头结点
		head_ = new Node();

		head_->next_ = head_;
		head_->pre_ = head_;
	}
	~LinkQueue() {
		//边界情况：只有一个节点 or 空
		Node* p = head_->next_;
		//链表不为空
		while (p != head_) {
			head_->next_ = p->next_;
			p->next_->pre_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;  //维护成员变量
	}
public:
	//入队-尾插-O(1)-边界情况：空
	void push(int val) {
		Node* node = new Node(val);
		node->pre_ = head_->pre_;
		node->next_ = head_;
		head_->pre_->next_ = node;
		head_->pre_ = node;
		size_++;
	}
	//出队-头删-O(1)-边界情况：空
	void pop() {
		Node* p = head_->next_;  
		if (p == head_)
			throw "the Queue is empty!";
		head_->next_ = p->next_;
		p->next_->pre_ = head_;
		delete p; //删除第一个节点
		size_--;
	}
	//队头
	int front() const{
		if (head_->next_ == head_)
			throw "the Queue is empty!";
		return head_->next_->data_;
	}
	//队尾
	int back() const {
		if (head_->next_ == head_)
			throw "the Queue is empty!";
		return head_->pre_->data_;
	}
	//队空
	bool empty() const {
		return head_->next_ == head_;
	}
	//队大小
	int size() const {
		return size_;
	}
private:
	struct Node {
		Node(int data = 0)
			: data_(data)
			, pre_(nullptr)
			, next_(nullptr)
		{
		}
		int data_;
		Node* pre_;
		Node* next_;
	};
private:
	Node* head_; //指向头结点
	int size_; //队列大小
};

int main() {

	LinkQueue q;
	int arr[] = { 10, 23, 91, 2, 45, 13, 1, 2, 3, 4, 5, 11};
	for (int i : arr) {
		q.push(i);
	}

	cout << "队列的大小为：" << q.size() << endl;
	cout << "队尾：" << q.back() << endl;

	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	cout << "队列的大小为：" << q.size() << endl;
}