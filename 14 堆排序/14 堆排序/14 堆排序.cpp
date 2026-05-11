#include <iostream>
#include <functional>

using namespace std;

//优先级队列实现
class PriorityQueue {
public:
	//把「所有能比较两个 int、返回 bool」的东西，统一装成同一个类型
	using Comp = function<bool(int, int)>;  //便于更改比较规则
	//指定比较方法，无默认
	PriorityQueue(Comp comp)
		: size_(0)
		, cap_(20)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}
	//指定容量和比较方法，默认大根堆
	PriorityQueue(int cap = 20, Comp comp = greater<int>())
		: size_(0)
		, cap_(cap)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}
	~PriorityQueue() {
		delete[] que_;
		que_ = nullptr;
	}
public:
	// 入堆操作
	void push(int val) {
		//扩容
		if (size_ == cap_) {
		
		}
		//只有一个元素，直接入堆
		if (size_ == 0) {
			que_[size_] = val;
		}
		else {
			Siftup(size_, val);
		}
		size_++;
	}
	// 出堆操作
	void pop() {
		if (size == 0) {
			throw "PriorityQueue is empty!";
		}
		size_--;
		if (size_ > 0) {
			siftDown(0, size_);
		}
	}
	//
	//队列是否空
	bool empty() {
	
	}
	//大小
	int size() {
	
	}
private:
	void Siftup(int i, int val) {
		while (i > 0) {
			int father = (i - 1) / 2;
			if (comp_(val, que_[father])) {
				que_[i] = que_[father];
				i = father;
			}
			else {
				break;
			}
		}
		que_[i] = val;
	}
	void siftDown(int i, int val) {
		while (i < size_ / 2) {
			int child = 2 * i + 1; //i节点的左孩子
			if (comp_(que_[child + 1], que_[child])) {
				child = child + 1;
			}
			if (comp_(que_[child], val)) {
				que_[i] = que_[child];
				i = child;
			}
			else {
				break;
			}
		}
		que_[i] = val;
	}
private:
	int* que_; //指向动态扩容的数组
	int size_; //数组大小
	int cap_;  //数组容量
	Comp comp_;//比较器对象
};

int main() {

}