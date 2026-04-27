#include <iostream>

using namespace std;

class Queue {
	friend void expendTest();
public:
	Queue(int cap = 10) 
		: cap_(cap)
		, front_(0)
		, rear_(0)
		, size_(0)
	{
		pQue = new int[cap_];
	}
	~Queue(){
		delete[] pQue;
		pQue = nullptr;
	}
public:
	//入队
	void push(int val) {
		//队列满
		if ((rear_ + 1) % cap_ == front_) {
			expend(2 * cap_);
		}
		pQue[rear_] = val;
		//成环的关键
		rear_ = (rear_ + 1) % cap_;
		size_++;
	}
	//出队
	void pop() {
		//队列空
		if (front_ == rear_)
			throw "the Queue is empty!";// return;
		front_ = (front_ + 1) % cap_;
		size_--;
	}
	//获取队头
	int front() const {
		if (front_ == rear_)
			throw "the Queue is empty!";
		return pQue[front_];
	}
	//获取队尾
	int back() const {
		if (front_ == rear_)
			throw "the Queue is empty!";
		return pQue[(rear_ - 1 + cap_) % cap_];
	}
	//队列是否空
	bool empty() const {
		return front_ == rear_;
	}
	//队列大小
	int size() const {
		return size_;
	}
private:
	int* pQue;  //队列指针
	int cap_;   //容量
	int front_; //队头
	int rear_;  //队尾
	int size_;  //队列大小
private:
	void expend(int size) {
		int* p = new int[size];
		int index = front_;
		for (int i = 0; i < size_; i++) {
			p[i] = pQue[index];
			index = (index + 1) % cap_;
		}
		delete[] pQue;
		pQue = p;
		cap_ = size;

		cout << front_ << " " << rear_ <<endl;
		//front_ = 0; 
		//rear_ = size_;
	}
};

//扩容测试
void expendTest() {
	Queue q;

	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
	for (int i : arr) {
		q.push(i);
	}

	q.front(); q.pop();
	q.front(); q.pop();
	q.front(); q.pop();
	q.push(9);

	cout << "队列的大小为：" << q.size() << endl;
	cout << "队头：" << q.front_ << " 队尾：" << q.rear_ << endl;

	int arr[] = { 10 };
	for (int i : arr) {
		q.push(i);
	}

}

int main() {
	expendTest();

	//Queue q;

	//int arr[] = { 10, 23, 91, 2, 45, 13, 1, 2, 3, 4, 5, 11};
	//for (int i : arr) {
	//	q.push(i);
	//}

	//cout << "队列的大小为：" << q.size() << endl;
	//cout << "队尾：" << q.back() << endl;

	//while (!q.empty()) {
	//	cout << q.front() << " ";
	//	q.pop();
	//}
	//cout << endl;
	//cout << "队列的大小为：" << q.size() << endl;
}