#include <iostream>
#include <string>
using namespace std;

class MyArry {
public:
	MyArry() {
		mSize = 0;
		mCapacity = 10; //默认开辟10个空间
		pAddress = new int[mCapacity];
	}
	MyArry(int Capacity) {
		mCapacity = Capacity;
		mSize = 0;
		pAddress = new int[mCapacity];
	}
	~MyArry() {
		if (pAddress != NULL) {
			delete[] pAddress;
			pAddress = NULL;
		}
	}
public:
	//尾插法插入数据
	void push_back(int value) {
		//动态扩容
		if (mCapacity == mSize) {
			expend(2 * mCapacity);
		}
		pAddress[mSize] = value;//等价于*(pAddress + mSize) = value;
		mSize++;
	}
	//尾删法删除数据
	void pop_back() {
		if (mSize == 0) {
			return;
		}
		mSize--;
	}
	//插入数据
	void insert(int pos, int value) {
		if (pos < 0 || pos > mSize) {
			return;
		}
		if (mCapacity == mSize) {
			expend(2 * mCapacity);
		}
		for (int i = mSize - 1; i >= pos; i--) {
			pAddress[i + 1] = pAddress[i];
		}
		pAddress[pos] = value;
		mSize++;
	}
	//删除指定位置数据
	void erase(int pos) {
		if (mSize == 0) {
			return;
		}
		if (pos < 0 || pos >= mSize) {
			return;
		}
		for (int i = pos; i < mSize; i++) {
			pAddress[i] = pAddress[i + 1];
		}
		mSize--;
	}
	//查找数据
	int find(int value) {
		for (int i = 0; i < mSize; i++) {
			if (pAddress[i] == value) {
				return i;
			}
		}
		return -1; //未找到返回-1
	}
	//打印数组
	void show() const {
		for (int i = 0; i < mSize; i++) {
			cout << pAddress[i] << " ";
		}
		cout << endl;
	}
	//获取数组的大小
	int size() {
		return mSize;
	}
	//获取数组的容量
	int capacity() {
		return mCapacity;
	}
private:
	//数组扩容
	void expend(int newCapacity) {
		int* p = new int[newCapacity]; // p 是局部变量！生命周期只在 expend 函数里,函数执行结束，p 这个变量会被系统自动销毁、彻底消失！
		for (int i = 0; i < mSize; i++) {
			p[i] = pAddress[i];
		}
		delete[]pAddress; //释放原来在堆区开辟的空间
		pAddress = p; //让 pAddress 指向新开辟的空间
		mCapacity = newCapacity;
	}
private:
	int* pAddress;//指针指向堆区开辟的真实数组
	int mCapacity;//数组容量，指向数组末尾的下一个位置
	int mSize;//数组大小
};

int main() {
	MyArry arr;

	for (int i = 0; i < 10; i++) {
		arr.push_back(i);
	}
	arr.show();
	cout << "数组容量：" << arr.capacity() << endl;
	cout << "数组大小：" << arr.size() << endl;

	arr.insert(3, 100);
	arr.show();
	cout << "数组容量：" << arr.capacity() << endl;
	cout << "数组大小：" << arr.size() << endl;


	int pos = arr.find(100);
	if (pos != -1)
	{
		arr.erase(pos);
		arr.show();
		cout << "数组容量：" << arr.capacity() << endl;
		cout << "数组大小：" << arr.size() << endl;
	}
}