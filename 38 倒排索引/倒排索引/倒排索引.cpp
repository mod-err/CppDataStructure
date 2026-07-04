#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include <Windows.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//倒排项
struct InvertTerm
{
	InvertTerm(string docId, int freq, int location)
		:docId_(docId)
		,freq_(freq)
	{
		location_.push_back(location);
	}
	bool operator==(const InvertTerm& term) const
	{
		return this->docId_ == term.docId_;
	}
	bool operator<(const InvertTerm& term) const
	{
		return this->docId_ > term.docId_;
	}
	bool operator>(const InvertTerm& term) const
	{
		return this->freq_ > term.freq_;
	}
	string docId_; //文档的ID
	int freq_;     //单词在文档出现的频率
	list<int> location_; //单词在文档中出现的位置
};

//倒排列表
class InvertList
{
public:
	//添加倒排项
	void addTerm(string docId, int location)
	{
		for (auto& term : termList_)
		{
			//倒排项存在
			if (term.docId_ == docId)
			{
				term.freq_++;
				term.location_.push_back(location);
				return;
			}
		}
		//倒排项不存在
		InvertTerm term(docId, 1, location);
		termList_.push_back(term); //termList_存储的对象是InvertTerm，要先创建InvertTerm，再存放

		//termList_.emplace_back(docId, 1, location); //内部直接构造对象
	}
	//获取倒排列表的内容
	const list<InvertTerm>& getInvertList() const
	{
		return termList_;
	}
private:
	list<InvertTerm> termList_; //存储对应单词所有的倒排项
};

//倒排索引
class InvertIndex
{
public:
	// 设置文档搜索的根路径
	void setSeachPath(string path)
	{
		cout << "搜索文件...";
		getAllFile(path.c_str());
		cout << "完成！" << endl;

		cout << "开始创建倒排索引";
		createInvertIndex();
		cout << "完成！" << endl;
	}
	// 查询接口
	void query(string phrase)
	{
		//先进行分词操作
		vector<string> wordList;
		char* word = strtok(const_cast<char*>(phrase.c_str()), " ");
		while (word != nullptr)
		{
			word = trim(word);
			if (strlen(word) > 0)
			{
				wordList.push_back(word);
			}
			word = strtok(nullptr, " ");
		}

		//如果用户输入为空直接返回
		if (wordList.empty())
		{
			return;
		}

		//如果用户输入的分词后只有一个词
		if (wordList.size() == 1)
		{
			auto it = invertMap_.find(wordList[0]);
			if (it == invertMap_.end())
			{
				cout << "未搜索到任何匹配的内容!" << endl;
				return;
			}
			//先将分词中的倒排项放入vector中进行排序
			vector<InvertTerm> tmpTerm;
			for (auto& term : it->second.getInvertList())
			{
				tmpTerm.push_back(term);
			}
			sort(tmpTerm.begin(), tmpTerm.end(), greater<InvertTerm>());
			//按照单词出现频率输出
			for (auto& vterm : tmpTerm)
			{
				cout << vterm.docId_ << "\tfreqs:" << vterm.freq_ << endl;
			}
		}
		else
		{
			//多个单词的搜索结果进行合并处理
			vector<InvertList> invertList;
			for (int i = 0; i < wordList.size(); i++)
			{
				auto it = invertMap_.find(wordList[i]);
				if (it != invertMap_.end())
				{
					invertList.push_back(it->second);
				}
			}
			//开始遍历所有倒排列表
			vector<InvertTerm> termShared;
			/*
				所有的倒排列表取交集
				实现思路：
				"int" 倒排列表：P1, P2, P3, P4  存放在：v1容器
				"i=1" 倒排列表：P1, P3          存放在：v2容器
				"j=1" 倒排列表：P3, P4          存放在：v2容器
				第一轮循环：
				①先给"int"和"i"的倒排列表取交集，取完放置在 termShared 容器
				②交换 v1 和 termShared 容器，v1存放[P1,P3]
				第二轮循环：
				③再给 v1 和 v2 取交集，取完放置在 termSharem 容器
				最后结果：
				三者交集为P3
			*/
			vector<InvertTerm> v1(invertList[0].getInvertList().begin(), invertList[0].getInvertList().end());
			for (int i = 1; i < invertList.size(); i++)
			{
				vector<InvertTerm> v2(invertList[i].getInvertList().begin(), invertList[i].getInvertList().end());
				//set_intersection要求容器内元素有序
				sort(v1.begin(), v1.end());
				sort(v2.begin(), v2.end());
				//求相邻两个倒排列表的交集
				set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(termShared));
				v1.swap(termShared);
				termShared.clear();
			}

			//得分排名高的倒排项
			for (auto& term : v1)
			{
				cout << term.docId_ << "\tfreqs:" << term.freq_ << endl;
			}
		}
	}
	// 设置文档搜索的后缀名过滤
	void setSuffix(string suffix)
	{
		suffix_ = suffix;
	}
private:
	// 递归扫描路径下面所有的文件
	int getAllFile(const char* Path)
	{
		char szFind[MAX_PATH];
		WIN32_FIND_DATA FindFileData;
		strcpy(szFind, Path);
		strcat(szFind, "\\*.*");
		HANDLE hFind = FindFirstFile(szFind, &FindFileData);
		if (INVALID_HANDLE_VALUE == hFind)
			return -1;

		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					//发现子目录，递归之
					char szFile[MAX_PATH] = { 0 };
					strcpy(szFile, Path);
					strcat(szFile, "\\");
					strcat(szFile, FindFileData.cFileName);
					getAllFile(szFile);
				}
			}
			else
			{
				//找到文件，处理之
				//std::cout << Path << "\\" << FindFileData.cFileName << std::endl;

				string fileName(FindFileData.cFileName);
				int pos = fileName.find(suffix_);  // abcd.cpp   pos:4 +4 
				if (pos != string::npos && pos + suffix_.size() == fileName.size())
				{
					//std::cout << Path << "\\" << FindFileData.cFileName << std::endl;
					string filePath(Path);
					filePath.append("\\");
					filePath.append(fileName);
					fileList_.emplace_back(filePath);
				}
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);

		return 0;
	}
	// 创建倒排索引结构
	void createInvertIndex()
	{
		//逐文件进行构建倒排索引
		for (string& fileName : fileList_) //采用引用避免拷贝，减少开销
		{
			cout << "."; //一个"."代表一个文件
			ifstream ifs;
			ifs.open(fileName, ios::in);
			if (!ifs.is_open())
			{
				cerr << fileName << "文件打开失败！" << endl;
				continue; //跳过当前循环剩余内容，继续下次循环
			}
			
			//逐行读取文件的内容
			vector<string> wordList;
			int location = 0; //单词位置
			const int LINE_SIZE = 2048; //一行的大小
			char line[LINE_SIZE] = { 0 };
			//每读取一行是一次循环，知道读到文件末尾
			while (ifs.getline(line, LINE_SIZE))
			{
				//按照" "进行分词
				char* word = strtok(line, " ");
				while (word != nullptr)
				{
					//过滤一下word前后 多余空格 \t \n
					word = trim(word);
					if (strlen(word) > 0)
					{
						wordList.push_back(word);
					}
					word = strtok(nullptr, " ");
				}
			}

			//开始给wordList里面的单词创建或者修改倒排列表
			for (string& w : wordList)
			{
				location++;
				auto it = invertMap_.find(w); //map按照键值key查找，也就是string
				if (it == invertMap_.end())
				{
					//新建w单词的倒排列表
					InvertList list;
					list.addTerm(fileName, location);
					invertMap_.emplace(w, list);
				}
				else
				{
					it->second.addTerm(fileName, location);
				}
			}
			ifs.close();
		}
	}
	//去掉分词后，单词前后多余字符
	char* trim(char* word)
	{
		int i = 0;
		//逐个字符找不要的
		while (word[i] != '\0')
		{
			if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
			{
				i++;
			}
			else
			{
				break;
			}
		}
		//逐个保留需要的
		int j = i;
		while (word[j] != '\0')
		{
			if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n')
			{
				break;
			}
			j++;
		}
		word[j] = '\0'; //原字符串截断
		return word + i; //指针偏移到第一个有效字符
	}
private:
	string suffix_;  // 过滤文档后缀   .cpp .cc .cxx .c
	list<string> fileList_; //存储所有需要建立倒排的文件
	unordered_map<string, InvertList> invertMap_; //词典+倒排列表
};

int main()
{
	InvertIndex index;
	index.setSuffix(".cpp");
	index.setSeachPath("D:\\算法与数据结构\\CppDataStructure");

	while (1)
	{
		string buff;
		cout << "搜索内容：";
		cin >> buff;
		index.query(buff);
	}

	return 0;
}