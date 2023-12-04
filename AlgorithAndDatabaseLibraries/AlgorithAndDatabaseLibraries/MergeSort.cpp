#include "MergeSort.h"

void MergeSort::MergingElements(vector<int>& Vector, int FirstElement, int MiddleElement, int LastElement)
{
	int LeftVectorSize = MiddleElement - FirstElement + 1;
	int RightVectorSize = LastElement - MiddleElement;

	vector<int> LeftVector(LeftVectorSize);
	vector<int> RightVector(RightVectorSize);

	for (int i = 0; i < LeftVectorSize; i++)
	{
		LeftVector[i] = Vector[FirstElement + i];
	}

	for (int i = 0; i < RightVectorSize; i++)
	{
		RightVector[i] = Vector[MiddleElement + 1 + i];
	}

	int i = 0;
	int j = 0;
	int k = FirstElement;

	while (i < LeftVectorSize && j < RightVectorSize)
	{
		if (LeftVector[i] <= RightVector[j])
		{
			Vector[k] = LeftVector[i];
			i++;
		}
		else
		{
			Vector[k] = RightVector[j];
			j++;
		}

		k++;
	}

	while (i < LeftVectorSize)
	{
		Vector[k] = LeftVector[i];
		i++;
		k++;
	}

	while (j < RightVectorSize)
	{
		Vector[k] = RightVector[j];
		j++;
		k++;
	}
}

void MergeSort::MergeSortAlgorithm(std::vector<int>& Vector, int FirstElement, int LastElement)
{
	if (LastElement <= FirstElement) return;

	int MiddleElement = (FirstElement + LastElement) / 2;

	MergeSortAlgorithm(Vector, FirstElement, MiddleElement);
	MergeSortAlgorithm(Vector, MiddleElement + 1, LastElement);
	MergingElements(Vector, FirstElement, MiddleElement, LastElement);
}