#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int paration(vector<int>& vec, int l, int r)
{
	int val = vec[l];
	while (l < r)
	{
		while (l < r && vec[r] > val)
		{
			r--;
		}
		if (l < r)
		{
			vec[l] = vec[r];
			l++;
		}
		while (l < r && vec[l] < val)
		{
			l++;
		}
		if (l < r)
		{
			vec[r] = vec[l];
			r--;
		}
	}
	vec[l] = val;
	return l;
}

void quickSort(vector<int>& vec, int begin, int end)
{
	//begin == end时，区间只有1个元素，无需排序，直接返回
	if (begin >= end)
	{
		return;
	}

	int pos = paration(vec, begin, end);
	quickSort(vec, begin, pos - 1);
	quickSort(vec, pos + 1, end);
}

int main()
{
	vector<int> vec;
	for (int i = 0; i < 11; i++)
	{
		vec.push_back(rand() % 100); //0-99
	}

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	quickSort(vec, 0, vec.size() - 1);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
}