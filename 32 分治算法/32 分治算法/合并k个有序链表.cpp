#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> vec1;
	for (int i = 0; i < 10; i++)
	{
		vec1.push_back(rand() % 100); //0-99
	}

	vector<int> vec2;
	for (int i = 0; i < 6; i++)
	{
		vec2.push_back(rand() % 100); //0-99
	}
}