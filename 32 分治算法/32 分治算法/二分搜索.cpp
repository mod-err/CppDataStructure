#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool binarySearch(vector<int>& vec, int r, int l, int val)
{
	if (r > l)
	{
		return false;
	}

	int mid = (r + l) / 2;
	if (vec[mid] == val)
	{
		return true;
	}
	else if (vec[mid] > val)
	{
		return binarySearch(vec, r, mid - 1, val);
	}
	else
	{
		return binarySearch(vec, mid + 1, l, val);
	}
}

int main()
{
	vector<int> vec;
	for (int i = 0; i < 11; i++)
	{
		vec.push_back(rand() % 100); //0-99
	}
	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	
	cout << "result = " << binarySearch(vec, 0, 11, 0) << endl;
}