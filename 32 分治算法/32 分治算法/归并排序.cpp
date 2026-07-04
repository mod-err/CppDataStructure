#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void mergeSort(vector<int>& vec, int l, int r)
{
	if (l >= r)
	{
		return;
	}

	//向下递的过程：划分子问题，降低问题规模
	int mid = (l + r) / 2;
	mergeSort(vec, l, mid);
	mergeSort(vec, mid + 1, r);

	//向上归并的过程
	int* p = new int[r - l + 1];
	int idx = 0;
	int i = l;
	int j = mid + 1;

	while (i <= mid && j <= r)
	{
		if (vec[i] > vec[j])
		{
			p[idx++] = vec[j++];
		}
		else
		{
			p[idx++] = vec[i++];
		}
	}
	while (i <= mid)
	{
		p[idx++] = vec[i++];
	}
	while (j <= r)
	{
		p[idx++] = vec[j++];
	}
	for (i = l, j = 0; i <= r; i++, j++)
	{
		vec[i] = p[j];
	}
	delete[] p;
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

	mergeSort(vec, 0, vec.size() - 1);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
}