#include <iostream>

using namespace std;

class SeqStack {
public:
	SeqStack(int size = 10) 
		: mcap(size)
		, mtop(0)
	{
		mpStack = new int[mcap]; //创建栈
	}
	~SeqStack() {
		delete[] mpStack;
		mpStack = nullptr;
	}
public:
	//入栈
	void push(int val) {
		if (mtop == mcap)
			expend(2 * mcap);
		mpStack[mtop++] = val; //先赋值再自增
	}
	//出栈
	void pop() {
		if (mtop == 0)
			throw "stack is empty!"; //报错并返回return
		mtop--;
	}
	//返回栈顶元素-const表示不改变任何成员变量
	int top() const {
		if (mtop == 0)
			throw "stack is empty!";
		return mpStack[mtop - 1]; //不能写做--mtop; 这样会改动指针
	}
	//栈空
	bool empty() const {
		return mtop == 0; //mtop == 0是布尔表达式，相等返回true，不相等返回false
	}
	//返回栈大小
	int size() const{
		return mtop;
	}
private:
	int* mpStack; //栈指针
	int mtop; //栈顶位置 == 栈大小
	int mcap; //栈容量
private:
	//扩容
	void expend(int size) {
		int* p = new int[size];
		memcpy(mpStack, p, mtop * sizeof(int));
		delete[] mpStack;   //释放原内存
		mpStack = p; 		//指向新内存
		mcap = size;
	}
};

int main() {
	SeqStack s;

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