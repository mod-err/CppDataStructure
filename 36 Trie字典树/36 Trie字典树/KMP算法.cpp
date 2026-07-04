#if 0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 计算一个子串的next[]数组, 返回数组
vector<int> getNext(const string& s2)
{
	if (s2.empty())
	{
		return {};
	}

	vector<int> next(s2.size()); //创建s2.size()个元素, 默认值为0

	int j = 0;  //j用来遍历字串
	int k = -1; //k表示公共前后缀长度

	next[j] = k; //情况1: j=0

	while (j < s2.size() - 1)   //时间复杂度O(m)
	{
		if (k == -1 || s2[j] == s2[k])
		{
			/*
			情况2：j = 1;
			j = 1; k = 0; next[j] = k;

			情况3：s2[j] == s2[k];
			*/
			j++; 
			k++; 

			//KMP算法的优化
			if (s2[k] == s2[j])
			{
				next[j] = next[k]; //继续回退直到不相等
			}
			else 
			{
				next[j] = k;
			}
		}
		else 
		{
			//情况3：s2[j] != s2[k];
			k = next[k];
		}
	}
	return next;
}

//KMP搜索 - 时间复杂度O(m) + O(n) = O(m+n)
int KMP(const string& s1, const string& s2)
{
	int i = 0;
	int j = 0;

	//获取一个子串的next[]数组, 拿到数组的指针
	vector<int> next = getNext(s2);

	int size1 = s1.size();
	int size2 = s2.size();
	while (i < size1 && j < size2)  //时间复杂度：O(n)
	{
		//next[0] = -1; 首字母匹配失败, i++; j++;
		if (j == -1 || s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			//回退j
			j = next[j];
		}
	}
	//字串走到了末尾: 找到匹配字串
	if (j == s2.length())
	{
		return i - j;
	}
	//主串走到了末尾: 没找到匹配字串
	if (i == s1.length())
	{
		return -1;
	}
}

int main()
{
	string s = "ABCDCABDEFG";
	string t = "XXX";

	int k = KMP(s, t);
	int l = k + t.size();

	if (k == -1)
	{
		cout << "not found!" << endl;
	}
	else
	{
		for (; k < l; k++)
		{
			cout << s[k] << " ";
		}
		cout << endl;
	}

	return 0;
}

#endif 