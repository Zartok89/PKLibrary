#include "QuickSort.h"

#include <memory>

int QuickSort::Partition(vector<int>& Vector, int FirstElement, int LastElement)
{
	int PivotValue = Vector[FirstElement];
	int Counter = 0;

	for (int i = FirstElement + 1; i <= LastElement; i++)
	{
		if (Vector[i] <= PivotValue)
		{
			Counter++;
		}
	}

	int PivotIndex = FirstElement + Counter;
	swap(Vector[PivotIndex], Vector[FirstElement]);

	int i = FirstElement;
	int j = LastElement;

	while (i < PivotIndex && j > PivotIndex)
	{
		while (Vector[i] <= PivotValue)
		{
			i++;
		}

		while (Vector[j] > PivotValue)
		{
			j--;
		}

		if (i < PivotIndex && j > PivotIndex)
		{
			swap(Vector[i++], Vector[j--]);
		}
	}

	return PivotIndex;
}

void QuickSort::QuickSortAlgorithm(vector<int>& Vector, int FirstElement, int LastElement)
{
	if (LastElement <= FirstElement) return;

	int PartitionIndex = Partition(Vector, FirstElement, LastElement);
	QuickSortAlgorithm(Vector, FirstElement, PartitionIndex - 1);
	QuickSortAlgorithm(Vector, PartitionIndex + 1, LastElement);
}