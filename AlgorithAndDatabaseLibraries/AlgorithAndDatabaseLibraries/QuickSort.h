/*
 * Source:
 * https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 * https://www.programiz.com/dsa/quick-sort
 * https://favtutor.com/blogs/quick-sort-cpp
 */

#pragma once
#include <vector>

using namespace std;

class QuickSort
{
public:

	QuickSort() = default;

	int Partition(vector<int>& Vector, int FirstValue, int LastValue);

	void QuickSortAlgorithm(vector<int>& Vector, int FirstElement, int LastElement);

};
