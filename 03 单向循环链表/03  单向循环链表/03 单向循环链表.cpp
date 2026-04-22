#include <iostream>

using namespace std;

struct Node {
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

void Joseph(Node* head, int k, int m) {
	Node* p = head;
	Node* q = head;
	//q指向p前一个节点
	while (q->next_ != head) {
		q = q->next_;
	}
	//从第k个人开始数
	for (int i = 1; i < k; i++) {
		q = p; //p紧跟在q后面
		p = p->next_;
	}
	//直到全部删除结束
	while (true) {
		for (int i = 1; i < m; i++) {
			q = p;
			p = p->next_;
		}
		//输出数据
		cout << p->data_ << " ";
		//结束条件
		if (p == q) {
			break;
		}
		//删除节点
		q->next_ = p->next_;
		delete p;
		p = q->next_;
	}
	cout << endl;
}

int main() {
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);
	Node* n9 = new Node(9);
	Node* n10 = new Node(10);

	n1->next_ = n2;
	n2->next_ = n3;
	n3->next_ = n4;
	n4->next_ = n5;
	n5->next_ = n6;
	n6->next_ = n7;
	n7->next_ = n8;
	n8->next_ = n9;
	n9->next_ = n10;
	n10->next_ = n1;

	Joseph(n1, 1, 1);
}

#if 0
class CircleLink {
public:
	//构造函数
	CircleLink() {
		//指向头节点
		head_ = new Node();
		//指向尾节点
		tail_ = head_;
		//形成环
		head_->next_ = head_;
	}
	//析构函数
	~CircleLink() {
		Node* p = head_->next_;
		while (p != head_) {
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}
public:
	//尾插法-O(1)
	void insertTail(int val) {
		Node* node = new Node(val);
		tail_->next_ = node;
		node->next_ = head_;
		tail_ = node;
	}
	//头插法-O(1)
	void inserthead(int val) {
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		//要考虑空链表的特殊情况
		if (head_ == tail_) {
			tail_ = node;
		}
	}
	//删除节点-O(n)
	bool remove(int val) {
		Node* p = head_->next_;
		Node* q = head_;
		while (p != head_) {
			if (p->data_ == val) {
				q->next_ = p->next_;
				delete p;
				if (q->next_ == head_) {
					tail_ = q;
				}
				return true;
			}
			else {
				p = p->next_;
				q = q->next_;
			}
		}
		return false;
	}
	//查找节点-O(n)-const表示函数不修改任何成员变量
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
	//打印节点
	void show() const {
		Node* p = head_->next_;
		while (p != head_) {
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
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
	CircleLink clink;
	for (int i = 0; i < 10; i++) {
		cout << i << " ";
		clink.inserthead(i);
	}
	cout << endl;

	cout << "头插法：" << endl;
	clink.show();//链表中存放顺序与插入顺序相反

	cout << "尾插法：" << endl;
	clink.insertTail(100);
	clink.insertTail(200);
	clink.show();

	cout << "删除：" << endl;
	clink.remove(100);
	clink.show();

	cout << "查找：" << (clink.find(200) ? "找到" : "未找到") << endl;
}
#endif
