//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//int paration(vector<int>& vec, int l, int r)
//{
//	int val = vec[l];
//	while (l < r)
//	{
//		while (l < r && vec[r] > val)
//		{
//			r--;
//		}
//		if (l < r)
//		{
//			vec[l] = vec[r];
//			l++;
//		}
//		while (l < r && vec[l] < val)
//		{
//			l++;
//		}
//		if (l < r)
//		{
//			vec[r] = vec[l];
//			r--;
//		}
//	}
//	vec[l] = val;
//	return l;
//}
//
//int min_select_topK(vector<int>& vec, int begin, int end, int k)
//{
//	int pos = paration(vec, begin, end);
//
//	if (pos == k - 1)
//	{
//		return pos;
//	}
//	else if (pos > k - 1)
//	{
//		return min_select_topK(vec, begin, pos - 1, k);
//	}
//	else if (pos < k - 1)
//	{
//		return min_select_topK(vec, pos + 1, end, k);
//	}
//}
//
//int max_select_topK(vector<int>& vec, int begin, int end, int k)
//{
//	int pos = paration(vec, begin, end);
//
//	if (pos == vec.size() - k)
//	{
//		return pos;
//	}
//	else if (pos > vec.size() - k)
//	{
//		return max_select_topK(vec, begin, pos - 1, k);
//	}
//	else if (pos < vec.size() - k)
//	{
//		return max_select_topK(vec, pos + 1, end, k);
//	}
//}
//
//int main()
//{
//	vector<int> vec;
//	for (int i = 0; i < 20; i++)
//	{
//		vec.push_back(rand() % 100); //0-99
//	}
//	for (int v : vec)
//	{
//		cout << v << " ";
//	}
//	cout << endl;
//
//	int k = min_select_topK(vec, 0, vec.size() - 1, 5);
//	cout << "第5小的元素：" << vec[k] << endl;
//	cout << "前5小的元素：";
//	for (int i = 0; i <= k; i++)
//	{
//		cout << vec[i] << " ";
//	}
//	cout << endl;
//
//	k = max_select_topK(vec, 0, vec.size() - 1, 5);
//	cout << "第5大的元素：" << vec[k] << endl;
//	cout << "前5大的元素：";
//	for (int i = k; i <= vec.size() - 1; i++)
//	{
//		cout << vec[i] << " ";
//	}
//	cout << endl;
//
//	for (int v : vec)
//	{
//		cout << v << " ";
//	}
//	cout << endl;
//}