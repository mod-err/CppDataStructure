#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//链式哈希表
class HashTable {
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		//如果用户指定桶大小
		if (size != primes_[0]) {
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
				if (size <= primes_[primeIdx_]) {
					break;
				}
			}
			//如果用户传入size过大，调整到最后一个素数
			if (primeIdx_ == PRIME_SIZE) {
				primeIdx_--;
			}
		}
		//用0初始化每个桶
		table_.resize(primes_[primeIdx_]);
	}
	~HashTable() {
		//没有创建在堆区的内存
	}
public:
	//插入
	void insert(int key) {
		//计算装载因子
		double factor = useBucketNum_ * 1.0 / table_.size();
		cout << "factor = " << factor << endl;
		if (factor > loadFactor_) {
			//哈希表开始扩容
			expand();
		}
		
		//除留余数法
		int idx = key % table_.size();
		//如果桶为空
		if (table_[idx].empty()) {
			useBucketNum_++;
		}
		table_[idx].push_back(key);
	}
	//删除
	void erase(int key) {
		int idx = key % table_.size();

		//auto = list<int>::iterator自动类型推导迭代器类型
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end()) {
			//删除该位置数据
			table_[idx].erase(it);
			if (table_[idx].empty()) {
				useBucketNum_--;
			}
		}
	}
	//查找
	int find(int key) {
		int idx = key % table_.size();

		//auto = list<int>::iterator自动类型推导迭代器类型
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end()) {
			return true;
		}
		return false;
	}
private:
	void expand() {
		primeIdx_++;
		if (primeIdx_ == PRIME_SIZE) {
			throw "hashtable can not expand anymore!";
		}
		//清空桶的使用记录
		useBucketNum_ = 0;

		vector<list<int>> oldTable;
		table_.swap(oldTable);
		table_.resize(primes_[primeIdx_]);

		for (auto list : oldTable) {
			for (auto key : list) {
				int idx = key % table_.size();
				if (table_[idx].empty()) {
					useBucketNum_++;
				}
				table_[idx].push_back(key);
			}
		}

	}
private:
	vector<list<int>> table_;  //哈希表的数据结构
	int useBucketNum_;  //记录已经使用的桶的个数
	double loadFactor_; //记录哈希表装载因子

	static const int PRIME_SIZE = 10; //素数表的大小
	static int primes_[PRIME_SIZE];    //素数表
	int primeIdx_;  //当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main() {
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	htable.insert(67);
	htable.insert(67);
	htable.insert(67);

	cout << htable.find(67) << endl;
	htable.erase(67);
	htable.erase(67);
	htable.erase(67);
	cout << htable.find(67) << endl;

	return 0;
}


