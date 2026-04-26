#include <iostream>
#include <stack>

using namespace std;

bool priority(char c1, char c2) {
	//c1优先级高或等于返回true
	if (c1 == '*' || c1 == '/') {
		return true;
	}
	if (c1 == '+' || c1 == '-') {
		if (c2 == '+' || c2 == '-') {
			return true;
		}
	}
	//c1优先级小返回false
	return false;
}

//中缀转后缀
string middleToEndExpr(string expr) {
	//存放结果数组
	string result;
	//运算符栈
	stack<char> opStack;
	for (char ch : expr) {
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')') {
			//数字
			result.push_back(ch);
		}
		else {
			//运算符
			
			//栈空直接入栈
			if (opStack.empty()) {
				opStack.push(ch);
			}
			//左括号直接入栈
			else if (ch == '(') {
				opStack.push(ch);
			}
			//右括号
			else if (ch == ')') {
				while (opStack.top() != '(') {
					result.push_back(opStack.top());
					opStack.pop();
				}
				//把 '(' 出栈
				opStack.pop();
			}
			else {
				//不为空 且 栈顶优先级高或等
				while (!opStack.empty() && priority(opStack.top(), ch)) {
					//栈顶优先级高或等
					result.push_back(opStack.top());
					opStack.pop();
				}
				//高或者等先入栈 or 优先级低
				opStack.push(ch);
			}
		}
	}
	while (!opStack.empty()) {
		result.push_back(opStack.top());
		opStack.pop();
	}
	return result;
}

int main() {
	cout << middleToEndExpr("2+(4+6)/2+6/3") << endl;
	cout << middleToEndExpr("3+4*2/(1-5)") << endl; 

}

#if 0
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
#endif