#if 0

#include <iostream>
#include <string>

using namespace std;

//暴力搜索
int BF(string& s1, string& s2)
{
	int i = 0;
	int j = 0;

	while (i < s1.length() && j < s2.length())
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
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
	string t = "ABD";

	int k = BF(s, t);
	int l = k + t.size();

	for (; k < l; k++)
	{
		cout << s[k] << " ";
	}
	cout << endl;

	return 0;
}

#endif