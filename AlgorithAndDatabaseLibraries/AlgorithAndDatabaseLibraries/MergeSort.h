/*
 * Source:
 * https://www.geeksforgeeks.org/merge-sort/
 * https://www.programiz.com/dsa/merge-sort
 * https://favtutor.com/blogs/merge-sort-cpp
 */
#pragma once
#include <vector>

using namespace std;

class MergeSort
{
public:
	MergeSort() = default;

	void MergingElements(vector<int>& Vector, int FirstElement, int MiddleElement, int LastElement);
	void MergeSortAlgorithm(vector<int>& Vector, int FirstElement, int LastElement);
};

