#include <iostream>

using namespace std;

class LinkStack {
public:
	LinkStack() {
		head_ = new Node();
		mSize = 0;
	}
	~LinkStack() {
		Node* p = head_;
		while (p != nullptr) {
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
public:
	//入栈-O(1)-头插法：输出顺序和插入顺序相反，先进后出
	void push(int val) {
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		mSize++;
	}
	//出栈
	void pop() {
		if (head_->next_ == nullptr)
			throw "stack is empty!"; //抛出异常也是程序返回的一种方式，类似return
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		mSize--;
	}
	//返回栈顶元素-const表示不改变任何成员变量
	int top() const {
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		return head_->next_->data_;
	}
	//栈空
	bool empty() const {
		return head_->next_ == nullptr;
	}
	//返回栈大小
	int size() const {
		return mSize;
	}
private:
	struct Node {
		Node(int data = 0) 
			: data_(data)
			, next_(nullptr)
		{ }
		int data_;
		Node* next_;
	};
	Node* head_;
	int mSize; //栈大小
};

int main() {
	LinkStack s;

	int arr[] = { 90, 28, 12, 0, 8, 46, 39 };
	for (int v : arr) {
		s.push(v);
	}
	cout << "栈的大小为：" << s.size() << endl;

	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << "栈的大小为：" << s.size() << endl;
}