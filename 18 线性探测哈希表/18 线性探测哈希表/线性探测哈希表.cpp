#include <iostream>
#include <ctime>

using namespace std;

//桶的状态
enum State {
	STATE_UNUSE, //从来未使用的桶
	STATE_USING, //正在使用的桶
	STATE_DEL,   //元素被删除的桶
};

//桶类型
struct Bucket {
	Bucket(int key = 0, State state = STATE_UNUSE)
		:key_(key)
		,state_(state)
	{}
	int key_;     //桶内存储的数据
	State state_; //当前桶的状态
};

//线性探测哈希表
class HashTable {
public:
	//构造函数
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primesIdx_(0)
	{
		//如果用户传入了size
		if (size != primes_[0]) {
			//把用户输入的size调整到距离素数表最近的元素上
			for (; primesIdx_ < PRIME_SIZE; primesIdx_++) {
				if (primes_[primesIdx_] >= size) {
					break;
				}
			}
			if (primesIdx_ == PRIME_SIZE) {
				primesIdx_--;
			}
		}
		//素数表读取当前长度
		tableSize_ = primes_[primesIdx_];
		//初始化哈希表
		table_ = new Bucket[tableSize_];
	}
	~HashTable() {
		delete[] table_;
		table_ = nullptr;
	}
public:
	//插入
	bool insert(int key) {
		double factor = useBucketNum_ * 1.0 / tableSize_;
		cout << "factor = " << factor << endl;
		if (factor > loadFactor_) {
			expand();
		}

		int idx = key % tableSize_; 

		int i = idx;
		do {
			if (table_[i].state_ != STATE_USING) {
				table_[i].key_ = key;
				table_[i].state_ = STATE_USING;
				useBucketNum_++;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);
	}
	//删除
	bool erase(int key) {
		int idx = key % tableSize_;

		int i = idx;
		do {
			//找到目标直接返回
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
				table_[i].state_ = STATE_DEL;
				useBucketNum_--;
				return true;
			}
			//遇到空桶，终止查找
			if (table_[i].state_ == STATE_UNUSE) {
				break;
			}
			i = (i + 1) % tableSize_;
			//STATE_DEL继续向后查找
		} while (i != idx);

		return false;
	}
	//查找
	bool find(int key) {
		int idx = key % tableSize_;

		int i = idx;
		do {
			//找到目标直接返回
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
				return true;
			}
			//遇到空桶，终止查找
			if (table_[i].state_ == STATE_UNUSE) {
				break;
			}
			i = (i + 1) % tableSize_;
			//STATE_DEL继续向后查找
		} while (i != idx);

		return false;
	}
private:
	//扩容
	void expand() {
		primesIdx_++;
		if (primesIdx_ == PRIME_SIZE) {
			throw "HashTable is too large, can not expand anymore!";
		}
		Bucket* newTable_ = new Bucket[primes_[primesIdx_]];
		//扩容后重新哈希
		for (int i = 0; i < tableSize_; i++) {
			if (table_[i].state_ == STATE_USING) {

				int idx = table_[i].key_ % primes_[primesIdx_];

				int k = idx;
				do {
					if (newTable_[k].state_ != STATE_USING) {
						newTable_[k].key_ = table_[i].key_;
						newTable_[k].state_ = STATE_USING;
						break;
					}
					k = (k + 1) % primes_[primesIdx_];
				} while (k != idx);
			}
		}

		delete[] table_;
		table_ = newTable_;
		tableSize_ = primes_[primesIdx_];
	}
private:
	Bucket* table_;     //指向动态开辟的哈希表
	int tableSize_;     //哈希表长度
	int useBucketNum_;  //已经使用的桶的个数
	double loadFactor_; //哈希表的装载因子

	static const int PRIME_SIZE = 10; //素数表大小
	static int primes_[PRIME_SIZE];   //素数表
	int primesIdx_;                   //当前使用的素数下标
};

//static静态成员变量：类内声明，类外初始化
//const static类型可以直接在类内初始化
int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main() {
	HashTable htable;
	htable.insert(12);
	htable.insert(18);
	htable.insert(21);
	htable.insert(24);
	htable.insert(33);
	htable.insert(45);
	htable.insert(67);

	cout << "查找12: " << (htable.find(12) ? "找到" : "未找到") << endl;
	htable.erase(12);
	cout << "删除12后查找: " << (htable.find(12) ? "找到" : "未找到") << endl;

	cout << "查找67: " << (htable.find(67) ? "找到" : "未找到") << endl;
	return 0;
}