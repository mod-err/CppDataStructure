#include <iostream>

using namespace std;

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
	//头插法-O(1)-考虑边界情况：链表空
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
	//尾插法-O(n)
	void insertTail(int val) {
		Node* p = head_;
		//指向尾结点；尾插法不能写做p != nullptr，这样写p会指向空节点，导致尾差失败
		while (p->next_ != nullptr) {
			p = p->next_;
		}

		Node* node = new Node(val);
		node->pre_ = p;
		p->next_ = node;
	}
	//删除-O(n)-考虑边界情况：删除尾结点
	void remove(int val) {
		Node* p = head_->next_;
		while (p != nullptr) {
			if (p->data_ == val) {
				//p指向待删除节点
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr) {
					//考虑删除的是末尾节点情况，避免p->next_为空p->next_->pre_访问空指针崩溃
					p->next_->pre_ = p->pre_;
				}
				//删除所有符合条件的数据
				//Node* next = p->next_;
				delete p;
				//p = next;
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
	//打印
	void show() const{
		Node* p = head_->next_;
		while (p != nullptr) {
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
		{
		}
		int data_;
		Node* pre_;
		Node* next_;
	};
	//头节点
	Node* head_;
};

int main() {
	DoubleLink Dlink;

	for (int i = 0; i < 10; i++) {
		cout << i << " ";
		Dlink.insertHead(i);
	}
	cout << endl;

	cout << "头插结果：" << endl;
	Dlink.show();

	cout << "尾插结果：" << endl;
	Dlink.insertTail(100);
	Dlink.insertTail(200);
	Dlink.insertTail(300);
	Dlink.show();

	cout << "删除：" << endl;
	Dlink.remove(300);
	Dlink.remove(100);
	Dlink.remove(9);
	Dlink.show();

	cout << "查找100：" << (Dlink.find(100) ? "找到" : "未找到") << endl;
	cout << "查找0：" << (Dlink.find(0) ? "找到" : "未找到") << endl;
}