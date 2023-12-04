// AlgorithmAndDatabaseLibraries.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "Graph.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;

void QuickSortPrint(shared_ptr<QuickSort> QuickSortLibrary, vector<int> VectorQuickSort)
{
	// ###Quick Sort###
	cout << "---QUICK SORT---" << endl;
	cout << "Unsorted array : ";
	for (int i : VectorQuickSort)
	{
		cout << i << " ";
	}
	cout << endl;

	QuickSortLibrary->QuickSortAlgorithm(VectorQuickSort, 0, VectorQuickSort.size() - 1);

	cout << "Sorted array : ";
	for (int i : VectorQuickSort)
	{
		cout << i << " ";
	}
}

void MergeSortPrint(shared_ptr<MergeSort> MergeSortLibrary, vector<int> VectorMergeSort)
{
	// ###Merge Sort###
	cout << endl;
	cout << endl;
	cout << "---MERGE SORT---" << endl;
	cout << "Unsorted array : ";
	for (int i : VectorMergeSort)
	{
		cout << i << " ";
	}

	MergeSortLibrary->MergeSortAlgorithm(VectorMergeSort, 0, VectorMergeSort.size() - 1);

	cout << endl;
	cout << "Sorted array : ";
	for (int i : VectorMergeSort)
	{
		cout << i << " ";
	}
	cout << endl;
}

void GraphPrint(const vector<int>& VertexPath) {
	for (int i = 0; i < VertexPath.size(); ++i) {
		cout << VertexPath[i];
		if (i < VertexPath.size() - 1) {
			cout << " -> ";
		}
	}
	cout << endl;

}

int main()
{
	shared_ptr<QuickSort> QuickSortLibrary = make_shared<QuickSort>();
	shared_ptr<MergeSort> MergeSortLibrary = make_shared<MergeSort>();
	unique_ptr<Graph> GraphLibrary = make_unique<Graph>();

	vector<int> VectorQuickSort = { 5, 12, 7, 1, 13, 2 ,23, 11, 18 };
	vector<int> VectorMergeSort = { 32, 5, 43, 1, 2, 9, 1, 18, 11 };
	int StartVertex = 0;
	int EndVertex = 6;

	QuickSortPrint(QuickSortLibrary, VectorQuickSort);

	MergeSortPrint(MergeSortLibrary, VectorMergeSort);

	cout << endl;
	cout << "Undirected Weighted Graph:" << endl;
	GraphLibrary->CreateGraph();
	GraphLibrary->PrintGraph();
	cout << endl;
	cout << "Shortest Path using Breadth First Search: ";
	GraphPrint(GraphLibrary->BreadthFirstSearch(StartVertex, EndVertex));
	cout << endl;
	cout << "Shortest Path using Dijsktra: ";
	GraphPrint(GraphLibrary->DijsktraPathfinding(StartVertex, EndVertex));
	cout << endl;
	int StartVertexAStar = 1;
	int EndVertexAStar = 6;
	GraphLibrary->CreateAStarGraph();
	cout << "Shortest Path using AStar: ";
	GraphPrint(GraphLibrary->AStarPathfindingTwo(StartVertexAStar, EndVertexAStar));
	return 0;
}